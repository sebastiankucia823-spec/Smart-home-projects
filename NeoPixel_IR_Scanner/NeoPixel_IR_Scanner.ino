/*
 * NeoPixel_IR_Scanner.ino
 * 
 * Funkcja: Animacja "wędrującego punktu" na pierścieniu/pasku NeoPixel.
 * Odczyt wartości z czujnika IR (podczerwieni) i wyświetlanie danych
 * w czasie rzeczywistym na wyświetlaczu LCD 16x2.
 */

#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

// --- Konfiguracja Pinów ---
#define LIGHT_SENSOR PB11
#define KEYS_INPUT    PA4
#define IR_SENSOR     PC2
#define PIXEL_PIN     PB7
#define NUMPIXELS     16

// Inicjalizacja obiektów
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_NeoPixel pasek(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int pixelPos = 0; // Pozycja świecącej diody

void setup() {
  Serial.begin(9600);
  
  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(KEYS_INPUT, INPUT);
  pinMode(IR_SENSOR, INPUT);

  // Inicjalizacja LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(1000);
  lcd.clear();

  // Inicjalizacja NeoPixel
  pasek.begin();
  pasek.clear();
  pasek.show();
}

void loop() {
  // 1. Obsługa paska NeoPixel (Animacja krążącego punktu)
  pasek.clear(); 
  // Ustawiamy kolor (R, G, B) - tutaj niebieski
  pasek.setPixelColor(pixelPos, pasek.Color(0, 0, 255));
  pasek.show();

  // Inkrementacja pozycji diody
  pixelPos++;
  if (pixelPos >= NUMPIXELS) {
    pixelPos = 0;
  }

  // 2. Odczyt czujnika IR i diagnostyka
  int irValue = analogRead(IR_SENSOR);
  int lightValue = analogRead(LIGHT_SENSOR);
  
  Serial.print("IR: ");
  Serial.println(irValue);

  // 3. Wyświetlanie danych na LCD
  // Używamy printf-style lub czyszczenia fragmentu, by uniknąć migotania całego ekranu
  lcd.setCursor(0, 0);
  lcd.print("IR Val: ");
  lcd.print(irValue);
  lcd.print("    "); // Nadpisywanie starych cyfr spacjami

  lcd.setCursor(0, 1);
  lcd.print("Light: ");
  lcd.print(lightValue);
  lcd.print("    ");

  delay(150); // Prędkość animacji
}