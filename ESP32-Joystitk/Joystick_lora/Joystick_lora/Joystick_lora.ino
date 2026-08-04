#include <SPI.h>
#include <LoRa.h>

// --- TWOJE PINY JOYSTICKA ---
const int PIN_VRX = 32; // Analogowy (ADC1)
const int PIN_VRY = 33; // Analogowy (ADC1)
const int PIN_SW  = 25; // Cyfrowy (Przycisk)

// --- KONFIGURACJA PINÓW LORA (VSPI) ---
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_CS    5
#define LORA_RST   4
#define LORA_DIO0  2

#define BAND       433E6 // 433 MHz (433000000 Hz)

void setup() {
  Serial.begin(115200);

  // Wewnętrzny rezystor podciągający dla przycisku SW (1 = puszczony, 0 = wciśnięty)
  pinMode(PIN_SW, INPUT_PULLUP);

  // Inicjalizacja SPI oraz modułu LoRa
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);

  Serial.println("Inicjalizacja nadajnika LoRa...");
  if (!LoRa.begin(BAND)) {
    Serial.println("Błąd: Nie odnaleziono modułu LoRa! Sprawdź połączenia.");
    while (1);
  }

  Serial.println("LoRa gotowa. Rozpoczynam nadawanie...");
}

void loop() {
  // 1. Odczyt danych z joysticka
  int vrx = analogRead(PIN_VRX); // Zakres 0 - 4095
  int vry = analogRead(PIN_VRY); // Zakres 0 - 4095
  int sw  = digitalRead(PIN_SW); // 0 = wciśnięty, 1 = puszczony

  // 2. Podgląd w Serial Monitorze
  Serial.printf("Wysyłanie -> X (D32): %4d | Y (D33): %4d | SW (D25): %d\n", vrx, vry, sw);

  // 3. Wysyłanie pakietu przez LoRa (format: "VRx,VRy,SW")
  LoRa.beginPacket();
  LoRa.print(vrx);
  LoRa.print(",");
  LoRa.print(vry);
  LoRa.print(",");
  LoRa.print(sw);
  LoRa.endPacket();

  delay(50); // Częstotliwość nadawania OK. 20 Hz
}