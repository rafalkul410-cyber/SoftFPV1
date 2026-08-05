#include "lora.h"

/**
  * @brief Odczyt jednego rejestru po SPI
  */
uint8_t LoRa_ReadReg(uint8_t addr) {
    uint8_t tx_buf[2] = { addr & 0x7F, 0x00 }; // Bit 7 = 0 dla odczytu
    uint8_t rx_buf[2] = { 0 };

    LORA_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi1, tx_buf, rx_buf, 2, HAL_MAX_DELAY);
    LORA_CS_HIGH();

    return rx_buf[1];
}

/**
  * @brief Zapis jednego rejestru po SPI
  */
void LoRa_WriteReg(uint8_t addr, uint8_t value) {
    uint8_t tx_buf[2] = { addr | 0x80, value }; // Bit 7 = 1 dla zapisu

    LORA_CS_LOW();
    HAL_SPI_Transmit(&hspi1, tx_buf, 2, HAL_MAX_DELAY);
    LORA_CS_HIGH();
}

/**
  * @brief Odczyt serii bajtów (Burst Read) z rejestru FIFO
  */
void LoRa_ReadBurst(uint8_t addr, uint8_t *buffer, uint8_t len) {
    uint8_t reg = addr & 0x7F;

    LORA_CS_LOW();
    HAL_SPI_Transmit(&hspi1, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi1, buffer, len, HAL_MAX_DELAY);
    LORA_CS_HIGH();
}

/**
  * @brief Odczyt odebranego pakietu z bufora FIFO modułu LoRa
  */
uint8_t LoRa_ReadPacket(uint8_t *buffer, uint8_t max_len) {
    // 1. Odczytaj flagi przerwań
    uint8_t irq_flags = LoRa_ReadReg(REG_IRQ_FLAGS);

    // 2. Wyczyść flagi w module (zapis 0xFF czyszcząco)
    LoRa_WriteReg(REG_IRQ_FLAGS, 0xFF);

    // 3. Sprawdź, czy wystąpił błąd CRC (Bit 5 w REG_IRQ_FLAGS)
    if (irq_flags & (1 << 5)) {
        return 0; // Błąd CRC - odrzucamy ramkę
    }

    // 4. Pobierz liczbę odebranych bajtów
    uint8_t bytes_received = LoRa_ReadReg(REG_RX_NB_BYTES);

    // 5. Pobierz adres w pamięci FIFO, gdzie zaczyna się odebrana ramka
    uint8_t current_rx_addr = LoRa_ReadReg(REG_FIFO_RX_CURRENT_ADDR);

    // 6. Przestaw wskaźnik FIFO na początek tej ramki
    LoRa_WriteReg(REG_FIFO_ADDR_PTR, current_rx_addr);

    // 7. Odczytaj dane z FIFO
    if (bytes_received > max_len) {
        bytes_received = max_len;
    }
    LoRa_ReadBurst(REG_FIFO, buffer, bytes_received);

    return bytes_received;
}
