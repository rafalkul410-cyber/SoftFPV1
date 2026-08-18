
#ifndef LORA_H_
#define LORA_H_

#include "main.h"

#include <stdint.h>
#include <string.h>

// Dokładny odpowiednik struktury z ESP32 (9 bajtów)
#pragma pack(push, 1)
typedef struct {
    int16_t  throttle;   // 2 bajty
    int16_t  pitch;      // 2 bajty
    int16_t  roll;       // 2 bajty
    int16_t  yaw;        // 2 bajty
    int8_t   killswitch; // 1 bajt
    uint8_t  checksum;   // 1 bajt
} LoRa_ControlPacket_t;  // Łącznie: dokładnie 10 bajtów
#pragma pack(pop)

uint8_t Verify_LoRa_Checksum(const LoRa_ControlPacket_t* pkt);

// --- KONFIGURACJA PINÓW Z TWOJEGO SCHEMATU ---
// CS  -> PA4 (A3)
// RST -> PC15 (D8)
#define LORA_CS_PORT    GPIOA
#define LORA_CS_PIN     GPIO_PIN_4

#define LORA_RST_PORT   GPIOB
#define LORA_RST_PIN    GPIO_PIN_5

// Sterowanie pinem CS
#define LORA_CS_LOW()   HAL_GPIO_WritePin(LORA_CS_PORT, LORA_CS_PIN, GPIO_PIN_RESET)
#define LORA_CS_HIGH()  HAL_GPIO_WritePin(LORA_CS_PORT, LORA_CS_PIN, GPIO_PIN_SET)


extern volatile uint32_t packet_count;
extern volatile uint32_t valid_packet_count;
extern volatile uint32_t crc_error_count;
extern volatile uint8_t raw_data[64];
extern volatile uint8_t raw_len;

// Funkcje
void LoRa_Reset(void);
uint8_t LoRa_ReadReg(uint8_t addr);
void LoRa_WriteReg(uint8_t addr, uint8_t value);
uint8_t LoRa_Init(void);
uint8_t LoRa_Process(LoRa_ControlPacket_t *current_state);
#endif /* LORA_H_ */

