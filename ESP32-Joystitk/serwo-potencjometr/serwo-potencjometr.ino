#include <ESP32Servo.h>


const int pinPotencjometru = 34; 
const int pinSerwa = 18;         
const int dioda= 25;
Servo mojeSerwo;

void setup() {
 Serial.begin(9600);

mojeSerwo.attach(pinSerwa);
pinMode(dioda, OUTPUT);
}

void loop() 
{
  // 1. Odczyt wartości z potencjometru (zakres 0 - 4095 dla ESP32)
  int wartoscPotencjometru = analogRead(pinPotencjometru);
  
  // 2. Skalowanie wartości z zakresu ADC (0-4095) na zakres kąta serwa (0-180)
  int katSerwa = map(wartoscPotencjometru, 0, 4095, 0, 180);
  
  // 3. Ruch serwomechanizmu
  mojeSerwo.write(katSerwa);
  
  // Opcjonalnie: Wyświetlanie danych w Monitorze Szeregowym
  Serial.print("Potencjometr: ");
  Serial.print(wartoscPotencjometru);
  Serial.print(" -> Kat serwa: ");
  Serial.println(katSerwa);
  digitalWrite(dioda,1);

  // Krótki odczek dla stabilizacji pracy
  delay(15);
}
