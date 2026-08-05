#ifndef INC_LORA_H_
#define INC_LORA_H_

#include "main.h"
#include "spi.h"

// --- DEFINICJE REJESTRÓW SX1276 / RFM95 ---
#define REG_FIFO                    0x00
#define REG_OP_MODE                 0x01
#define REG_FIFO_ADDR_PTR           0x0D
#define REG_FIFO_RX_CURRENT_ADDR    0x10
#define REG_IRQ_FLAGS               0x12
#define REG_RX_NB_BYTES             0x13

// --- STEROWANIE PINEM CS (PA4 / A4 na Nucleo) ---
#define LORA_CS_LOW()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define LORA_CS_HIGH()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

// --- STRUKTURA PAKIETU DANYCH ---
typedef struct __attribute__((packed)) {
    int16_t  throttle;   // Sygnał ciągu (0 - 1000)
    int16_t  pitch;      // Zadane pochylenie
    int16_t  roll;       // Zadane przechylenie
    int16_t  yaw;        // Zadane odchylenie
    uint8_t  checksum;   // Suma kontrolna
} LoRa_ControlPacket_t;

// --- PROTOTYPY FUNKCJI ---
uint8_t LoRa_ReadReg(uint8_t addr);
void    LoRa_WriteReg(uint8_t addr, uint8_t value);
void    LoRa_ReadBurst(uint8_t addr, uint8_t *buffer, uint8_t len);
uint8_t LoRa_ReadPacket(uint8_t *buffer, uint8_t max_len);

#endif /* INC_LORA_H_ */
