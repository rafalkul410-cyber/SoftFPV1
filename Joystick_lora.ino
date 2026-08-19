#include <SPI.h>
#include <LoRa.h>

typedef struct __attribute__((packed)) {
    int16_t  throttle;   // Gaz: 0 - 500 (zawis) - 1000
    int16_t  pitch;      // Pochylenie (-500 do 500)
    int16_t  roll;       // Przechylenie (-500 do 500)
    int16_t  yaw;        // Odchylenie (-500 do 500)
    int8_t   kill;       // 0 = OFF, 1 = AKTYWNY
    uint8_t  checksum;   // Suma kontrolna XOR
} LoRa_ControlPacket_t;

// --- PINY JOYSTICKÓW I PRZEŁĄCZNIKÓW ---
const int PIN_VRX_1 = 32; // Throttle (ADC1)
const int PIN_VRY_1 = 33; // Yaw (ADC1)
const int PIN_SW_1  = 25; // Przycisk Joy 1

const int PIN_VRX_2 = 34; // Pitch (ADC1)
const int PIN_VRY_2 = 35; // Roll (ADC1)
const int PIN_SW_2  = 26; // Przycisk Joy 2

const int PIN_KS    = 27; // Kill Switch

// --- KALIBRACJA PUNKTÓW ŚRODKOWYCH ---
const int MID_THR   = 1894;
const int MID_YAW   = 1844;
const int MID_PITCH = 1876;
const int MID_ROLL  = 1844;

// --- PINY LORA (VSPI) ---
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_CS    5
#define LORA_RST   4
#define LORA_DIO0  2

#define BAND       433E6

// Obliczanie sumy kontrolnej XOR (z 9 pierwszych bajtów)
uint8_t calculateChecksum(const LoRa_ControlPacket_t* packet) {
    uint8_t crc = 0;
    const uint8_t* bytePtr = (const uint8_t*)packet;
    for (size_t i = 0; i < sizeof(LoRa_ControlPacket_t) - 1; i++) {
        crc ^= bytePtr[i];
    }
    return crc;
}

int skalujOs(int raw, int raw_min, int raw_srodek, int raw_max, int deadband = 40) {
    raw = constrain(raw, raw_min, raw_max);
    if (abs(raw - raw_srodek) <= deadband) return 0;

    if (raw < raw_srodek) {
        return map(raw, raw_min, raw_srodek - deadband, -500, 0);
    } else {
        return map(raw, raw_srodek + deadband, raw_max, 0, 500);
    }
}

int skalujThrottle(int raw, int raw_min, int raw_srodek, int raw_max, int deadband = 40) {
    raw = constrain(raw, raw_min, raw_max);
    if (abs(raw - raw_srodek) <= deadband) return 500;

    if (raw < raw_srodek) {
        return map(raw, raw_min, raw_srodek - deadband, 0, 500);
    } else {
        return map(raw, raw_srodek + deadband, raw_max, 500, 1000);
    }
}

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("\n--- Start Nadajnika LoRa ESP32 ---");

    pinMode(PIN_SW_1, INPUT_PULLUP);
    pinMode(PIN_SW_2, INPUT_PULLUP);
    pinMode(PIN_KS, INPUT_PULLUP);

    // 1. Najpierw konfiguracja magistrali SPI i pinów LoRa
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
    LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);

    // 2. Start modułu LoRa
    if (!LoRa.begin(BAND)) {
        Serial.println("Blad: Nie odnaleziono modulu LoRa! Sprawdz polaczenia.");
        while (1) {
            delay(500);
            Serial.print(".");
        }
    }

    // 3. Konfiguracja parametrów (po udanym begin)
    LoRa.setTxPower(2);
    LoRa.enableCrc();
    LoRa.setSyncWord(0x12);

    Serial.println("LoRa gotowa. Rozpoczynam nadawanie...");
}

void loop() {
    int vrx_1 = analogRead(PIN_VRX_1); // Throttle
    int vry_1 = analogRead(PIN_VRY_1); // Yaw
    int vrx_2 = analogRead(PIN_VRX_2); // Pitch
    int vry_2 = analogRead(PIN_VRY_2); // Roll

    int ks = (digitalRead(PIN_KS) == LOW) ? 1 : 0;

    LoRa_ControlPacket_t packet;

    packet.throttle = constrain(skalujThrottle(vrx_1, 0, MID_THR, 4095, 40), 0, 1000);
    packet.pitch    = constrain(skalujOs(vrx_2, 0, MID_PITCH, 4095, 40), -500, 500);
    packet.roll     = constrain(skalujOs(vry_2, 0, MID_ROLL,  4095, 40), -500, 500);
    packet.yaw      = constrain(skalujOs(vry_1, 0, MID_YAW,   4095, 40), -500, 500);
    packet.kill     = ks;
    packet.checksum = calculateChecksum(&packet);

    // Wysyłanie binarne
    LoRa.beginPacket();
    LoRa.write((uint8_t*)&packet, sizeof(LoRa_ControlPacket_t));
    LoRa.endPacket();

    Serial.printf("Wyslano -> Thr: %4d | Yaw: %4d | Pitch: %4d | Roll: %4d | Kill: %d | CRC: 0x%02X\n",
                  packet.throttle, packet.yaw, packet.pitch, packet.roll, packet.kill, packet.checksum);

    delay(50); // 20 Hz
}