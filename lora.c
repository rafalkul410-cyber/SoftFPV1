#include "lora.h"
#include <string.h>

extern SPI_HandleTypeDef hspi1;

// Liczniki diagnostyczne
volatile uint32_t packet_count = 0;
volatile uint32_t valid_packet_count = 0;
volatile uint32_t crc_error_count = 0;

// Zmienne diagnostyczne do Live Expressions
extern volatile uint8_t dbg_rx_frame[16];
extern volatile uint8_t dbg_raw_len;
extern volatile uint8_t dbg_pkt_crc;
extern volatile uint8_t dbg_calc_crc;

// Reset sprzętowy układu SX1278
void LoRa_Reset(void) {
    HAL_GPIO_WritePin(LORA_RST_PORT, LORA_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(LORA_RST_PORT, LORA_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(10);
}

// Odczyt pojedynczego rejestru po SPI
uint8_t LoRa_ReadReg(uint8_t addr) {
    uint8_t tx[2] = { (uint8_t)(addr & 0x7F), 0x00 };
    uint8_t rx[2] = { 0 };

    LORA_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, 100);
    LORA_CS_HIGH();

    return rx[1];
}

// Zapis pojedynczego rejestru po SPI
void LoRa_WriteReg(uint8_t addr, uint8_t value) {
    uint8_t tx[2] = { (uint8_t)(addr | 0x80), value };

    LORA_CS_LOW();
    HAL_SPI_Transmit(&hspi1, tx, 2, 100);
    LORA_CS_HIGH();
}

// Inicjalizacja modemu pod pasmo 433 MHz
uint8_t LoRa_Init(void) {
    LORA_CS_HIGH();

    // 1. Sprzętowy Reset
    LoRa_Reset();

    // 2. Test obecności krzemu SX1278 (rejestr 0x42 musi zwrócić 0x12)
    uint8_t ver = LoRa_ReadReg(0x42);
    if (ver != 0x12) {
        return 0; // Brak odpowiedzi z układu po SPI
    }

    // 3. Wejście w tryb LoRa + SLEEP
    LoRa_WriteReg(0x01, 0x00); // FSK SLEEP
    HAL_Delay(10);
    LoRa_WriteReg(0x01, 0x80); // LORA SLEEP (Bit 7 = 1)
    HAL_Delay(10);

    // 4. Przejście w tryb STANDBY przed konfiguracją RF
    LoRa_WriteReg(0x01, 0x81); // LORA STANDBY
    HAL_Delay(5);

    // 5. Ustawienie częstotliwości 433.000 MHz
    LoRa_WriteReg(0x06, 0x6C);
    LoRa_WriteReg(0x07, 0x40); //0x80
    LoRa_WriteReg(0x08, 0x00);

    // 6. Konfiguracja parametrów LoRa (zgodna z biblioteką ESP32)
    LoRa_WriteReg(0x1D, 0x72); // RegModemConfig1: BW 125 kHz, CR 4/5, Explicit Header
    LoRa_WriteReg(0x1E, 0x70); // RegModemConfig2: SF7
    LoRa_WriteReg(0x26, 0x04); // RegModemConfig3: AGC Auto On
    LoRa_WriteReg(0x39, 0x12); // RegSyncWord: domyślne 0x12

    // 7. Konfiguracja wskaźników bufora FIFO
    LoRa_WriteReg(0x0E, 0x00); // FifoTxBaseAddr
    LoRa_WriteReg(0x0F, 0x00); // FifoRxBaseAddr
    LoRa_WriteReg(0x0D, 0x00); // FifoAddrPtr

    // 8. Wyczyszczenie starych flag i start ciągłego nasłuchu
    LoRa_WriteReg(0x12, 0xFF);
    LoRa_WriteReg(0x01, 0x85); // LORA RX CONTINUOUS

    return 1;
}

// Funkcja walidująca i aktualizująca stan sterowania
static void Update_control(LoRa_ControlPacket_t* current_state, const LoRa_ControlPacket_t* new_pkt) {
    if (new_pkt->killswitch == 0 || new_pkt->killswitch == 1) {
        current_state->killswitch = new_pkt->killswitch;
    }

    // Wyzerowanie nastaw w przypadku zadziałania Kill Switcha
    if (current_state->killswitch == 1) {
        current_state->throttle = 0;
        current_state->pitch    = 0;
        current_state->roll     = 0;
        current_state->yaw      = 0;
        return;
    }

    if (new_pkt->throttle >= 0 && new_pkt->throttle <= 1000) {
        current_state->throttle = new_pkt->throttle;
    }
    if (new_pkt->pitch >= -500 && new_pkt->pitch <= 500) {
        current_state->pitch = new_pkt->pitch;
    }
    if (new_pkt->roll >= -500 && new_pkt->roll <= 500) {
        current_state->roll = new_pkt->roll;
    }
    if (new_pkt->yaw >= -500 && new_pkt->yaw <= 500) {
        current_state->yaw = new_pkt->yaw;
    }
}

// Weryfikacja sumy kontrolnej XOR (pierwsze 9 bajtów)
uint8_t Verify_LoRa_Checksum(const LoRa_ControlPacket_t* pkt) {
    uint8_t crc = 0;
    const uint8_t* bytePtr = (const uint8_t*)pkt;

    for (size_t i = 0; i < sizeof(LoRa_ControlPacket_t) - 1; i++) {
        crc ^= bytePtr[i];
    }
    return (crc == pkt->checksum);
}

// Odczyt surowego pakietu z FIFO
uint8_t LoRa_Receive_Raw(uint8_t *buf, uint8_t *len) {
    // Podtrzymanie trybu RX CONTINUOUS w razie zakłóceń na paśmie
    if ((LoRa_ReadReg(0x01) & 0x07) != 0x05) {
        LoRa_WriteReg(0x01, 0x85);
    }

    uint8_t irq = LoRa_ReadReg(0x12); // RegIrqFlags

    // Sprawdzenie flagi RxDone (bit 6)
    if (irq & 0x40) {
        // Odrzucenie ramek z błędem CRC w powietrzu (bit 5)
        if (irq & 0x20) {
            LoRa_WriteReg(0x12, 0xFF);
            return 0;
        }

        // Odczyt długości oraz adresu startowego w FIFO
        *len = LoRa_ReadReg(0x13);
        uint8_t current_addr = LoRa_ReadReg(0x10);

        // Ustawienie wskaźnika FIFO na początek pakietu
        LoRa_WriteReg(0x0D, current_addr);

        // Odczyt właściwych bajtów
        for (uint8_t i = 0; i < *len; i++) {
            buf[i] = LoRa_ReadReg(0x00);
        }

        // Skasowanie flag przerwań PO odczycie całego pakietu
        LoRa_WriteReg(0x12, 0xFF);
        return 1;
    }

    // Czyszczenie innych pojedynczych flag
    if (irq != 0) {
        LoRa_WriteReg(0x12, 0xFF);
    }

    return 0;
}

// Główna funkcja przetwarzania ramki
uint8_t LoRa_Process(LoRa_ControlPacket_t* current_state) {
    uint8_t raw_data[32] = {0};
    uint8_t len = 0;

    if (LoRa_Receive_Raw(raw_data, &len)) {
        packet_count++;
        dbg_raw_len = len;

        // Kopiowanie do tablicy podglądu Live Expressions
        for (uint8_t i = 0; i < len && i < 16; i++) {
            dbg_rx_frame[i] = raw_data[i];
        }

        if (len == sizeof(LoRa_ControlPacket_t)) {
            uint8_t calc = 0;
            for (uint8_t i = 0; i < sizeof(LoRa_ControlPacket_t) - 1; i++) {
                calc ^= dbg_rx_frame[i];
            }

            dbg_pkt_crc = dbg_rx_frame[9];
            dbg_calc_crc = calc;

            if (calc == dbg_rx_frame[9]) {
                Update_control(current_state, (LoRa_ControlPacket_t*)dbg_rx_frame);
                valid_packet_count++;
                return 1;
            } else {
                crc_error_count++;
            }
        } else {
            crc_error_count++;
        }
    }
    return 0;
}
