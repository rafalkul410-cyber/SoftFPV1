#include "lora.h"

extern SPI_HandleTypeDef hspi1;

//Definicja liczników
volatile unint32_t packet_count = 0;
volatile uint32_t valid_packet_count=0;
volatile uint32_t crc_erroe_count=0;

// Reset sprzętowy układu LoRa
void LoRa_Reset(void) {
    HAL_GPIO_WritePin(LORA_RST_PORT, LORA_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(LORA_RST_PORT, LORA_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(10);
}

// Odczyt rejestru po SPI
uint8_t LoRa_ReadReg(uint8_t addr) {
    uint8_t tx[2] = { addr & 0x7F, 0x00 };
    uint8_t rx[2] = { 0 };

    LORA_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, HAL_MAX_DELAY);
    LORA_CS_HIGH();

    return rx[1];
}

// Zapis rejestru po SPI
void LoRa_WriteReg(uint8_t addr, uint8_t value) {
    uint8_t tx[2] = { addr | 0x80, value };

    LORA_CS_LOW();
    HAL_SPI_Transmit(&hspi1, tx, 2, HAL_MAX_DELAY);
    LORA_CS_HIGH();
}

// Inicjalizacja pod 433 MHz
uint8_t LoRa_Init(void) {
    LORA_CS_HIGH();

    // 1. NAJPIERW Reset sprzętowy układu
    LoRa_Reset();

    // 2. Test komunikacji SPI (rejestr 0x42 musi zwrócić 0x12)
    uint8_t ver = LoRa_ReadReg(0x42);
    if (ver != 0x12) {
        return 0; // Brak odpowiedzi po SPI!
    }

    // 3. Przestawienie w tryb LoRa oraz SLEEP (wymagane do zmiany parametrów)
    LoRa_WriteReg(0x01, 0x00); // SLEEP
    HAL_Delay(5);
    LoRa_WriteReg(0x01, 0x80); // LORA MODE
    HAL_Delay(5);

    // 4. Ustawienie częstotliwości 433.000 MHz
    LoRa_WriteReg(0x06, 0x6C);
    LoRa_WriteReg(0x07, 0x80);
    LoRa_WriteReg(0x08, 0x00);

    // 5. DOPIERO TERAZ: Konfiguracja modemu i włączenie AGC
    LoRa_WriteReg(0x1D, 0x72); // RegModemConfig1: BW 125 kHz, CR 4/5
    LoRa_WriteReg(0x1E, 0x70); // RegModemConfig2: SF7
    LoRa_WriteReg(0x26, 0x04); // RegModemConfig3: AgcAutoOn = 1 (Włącza automatyczne wzmocnienie)

    // 6. Ustawienie bufora i przełączenie w ciągły odbiór (RX CONTINUOUS)
    LoRa_WriteReg(0x0F, 0x00); // Base RX Addr
    LoRa_WriteReg(0x01, 0x85); // RX CONTINUOUS

    return 1; // Układ skonfigurowany i nasłuchuje!
}
// funckja walidująca stan zminennch z LoRa
static void Update_control(LoRa_ControlPacket_t*current_state, const LoRa_ControlPacket_t*new_pkt){
	//Throttle akceptuj 0-1000
	if(new_pkt->throttle>=0 && new_pkt->throttle<=1000){
		current_state->throttle=new_pkt->throttle;
		}
	//pitch akceptuj -500 - 500
	if(new_pkt->pitch>=-500 && new_pkt->pitch<=500){
		current_state->pitch=new_pkt->pitch;
		}
	//roll akceptuj -500 - 500
	if(new_pkt->roll>=-500 && new_pkt->roll<=500){
		current_state->roll=new_pkt->roll;
		}
	//yaw akceptuj -500 - 500
	if(new_pkt->yaw>=-500 && new_pkt->yaw<=500){
			current_state->yaw=new_pkt->yaw;
		}
}
// Weryfikacja sumy kontrolnej XOR
uint8_t Verify_LoRa_Checksum(const LoRa_ControlPacket_t* pkt) {
    uint8_t crc = 0;
    const uint8_t* bytePtr = (const uint8_t*)pkt;

    for (size_t i = 0; i < sizeof(LoRa_ControlPacket_t) - 1; i++) {
        crc ^= bytePtr[i];
    }
    return (crc == pkt->checksum);
}

// Odczyt odebranych pakietów z FIFO
uint8_t LoRa_Receive_Raw(uint8_t *buf, uint8_t *len) {
    uint8_t irq = LoRa_ReadReg(0x12); // RegIrqFlags

    // Sprawdź flaga RxDone (bit 6)
    if (irq & 0x40) {

        // 1. Odrzuć pakiety uszkodzone radiowo (PayloadCrcError = bit 5)
        if (irq & 0x20) {
            LoRa_WriteReg(0x12, 0xFF); // Wyczyszczenie flag IRQ
            return 0; // Błąd CRC w powietrzu – ignorujemy pakiet
        }

        LoRa_WriteReg(0x12, 0xFF); // Wyczyszczenie flag IRQ

        *len = LoRa_ReadReg(0x13);                 // Długość odebranego pakietu
        uint8_t current_addr = LoRa_ReadReg(0x10); // Adres startowy pakietu w FIFO

        // 2. Zapisz adres wskaźnika FIFO TYLKO RAZ przed pętlą!
        LoRa_WriteReg(0x0D, current_addr);

        // 3. Odczytuj kolejne bajty (układ sam automatycznie zwiększa adres)
        for (uint8_t i = 0; i < *len; i++) {
            buf[i] = LoRa_ReadReg(0x00);
        }

        return 1; // Odebrano poprawną ramkę!
    }

    return 0;
}

uint8_t LoRa_Process(LoRa_ControlPacket_t*current_state){

}

