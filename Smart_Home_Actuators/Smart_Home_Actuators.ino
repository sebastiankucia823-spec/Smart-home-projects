/*
 * Smart_Home_Actuators.ino
 * 
 * Funkcja: Sterowanie serwomechanizmem (roleta/drzwi) oraz silnikiem DC 
 * (wentylator) za pomocą przycisków analogowych.
 * Obsługuje różne prędkości obrotowe silnika (biegi).
 */

#include <Servo.h>

// --- Konfiguracja Pinów ---
#define KEYS_INPUT     PA4
#define SERVO_PIN      PC11
#define DC_MOTOR_INA   PD1
#define DC_MOTOR_INB   PB1

Servo mainServo;
int servoPos = 90; // Pozycja startowa serwa

void setup() {
  Serial.begin(9600);
  
  pinMode(KEYS_INPUT, INPUT);
  
  // Konfiguracja serwa
  mainServo.attach(SERVO_PIN);
  mainServo.write(servoPos);
  
  // Konfiguracja silnika DC
  pinMode(DC_MOTOR_INA, OUTPUT);
  pinMode(DC_MOTOR_INB, OUTPUT);
  
  digitalWrite(DC_MOTOR_INB, LOW); // Silnik kręci się w jedną stronę
}

void loop() {
  int keyVal = analogRead(KEYS_INPUT);

  // 1. Sterowanie Serwem (np. Roleta)
  // Przycisk "W górę / Prawo"
  if (keyVal > 500 && keyVal < 550) {
    servoPos++;
    if (servoPos > 117) servoPos = 117;
    mainServo.write(servoPos);
    Serial.print("Serwo: ");
    Serial.println(servoPos);
  } 
  // Przycisk "W dół / Lewo"
  else if (keyVal > 670 && keyVal < 700) {
    servoPos--;
    if (servoPos < 0) servoPos = 0;
    mainServo.write(servoPos);
    Serial.print("Serwo: ");
    Serial.println(servoPos);
  }

  // 2. Sterowanie Silnikiem DC (Biegi)
  // Przykładowa logika: dodatkowe zakresy napięć dla biegów
  if (keyVal > 1010 && keyVal < 1020) {
    setGear(2); // Drugi bieg (max)
  } else if (keyVal > 410 && keyVal < 420) {
    setGear(1); // Pierwszy bieg
  } else if (keyVal < 50) {
    setGear(0); // Wyłączony
  }

  delay(50); // Opóźnienie dla płynności ruchu
}

// Funkcja ustawiająca "bieg" silnika
void setGear(int gear) {
  switch(gear) {
    case 0:
      analogWrite(DC_MOTOR_INA, 0);
      Serial.println("Silnik: OFF");
      break;
    case 1:
      analogWrite(DC_MOTOR_INA, 100);
      Serial.println("Silnik: Bieg 1");
      break;
    case 2:
      analogWrite(DC_MOTOR_INA, 255);
      Serial.println("Silnik: Bieg 2");
      break;
  }
}