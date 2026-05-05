/*
 * Smart_Lamp_VU_Meter.ino
 * 
 * Funkcja: Automatyczne sterowanie diodą RGB w zależności od natężenia światła
 * oraz wyświetlanie poziomu jasności na linijce LED (Bar Graph).
 * Dodatkowo obsługa przycisków analogowych z logowaniem na Serial Port.
 */

// --- Konfiguracja Pinów (Mapowanie dla STM32/Arduino) ---
#define LIGHT_SENSOR PB11
#define KEYS_INPUT    PA4

// RGB LED
#define RGB_RED      PC10
#define RGB_GREEN    PD0
#define RGB_BLUE     PC12

// Linijka LED (10 diod)
const uint8_t LED_LINE[] = {PB13, PB15, PB6, PC0, PC1, PA9, PA12, PD6, PD9, PC6};

// Wyświetlacz 7-segmentowy (zdefiniowany, ale nieużyty w logice loop)
#define LED_8A PC3
#define LED_8B PB12
#define LED_8C PA0
#define LED_8D PA15
#define LED_8E PD3
#define LED_8F PA11
#define LED_8G PD4
#define DIG_L  PC8
#define DIG_R  PC9

void setup() {
  Serial.begin(9600);
  
  // Konfiguracja wejść
  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(KEYS_INPUT, INPUT);
  
  // Konfiguracja wyjść RGB
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);
  
  // Konfiguracja linijki LED w pętli (czystszy kod)
  for (int i = 0; i < 10; i++) {
    pinMode(LED_LINE[i], OUTPUT);
  }

  // Stan początkowy
  digitalWrite(RGB_GREEN, HIGH);
  digitalWrite(RGB_RED, HIGH);
}

void loop() {
  // 1. Odczyt czujnika światła
  int lightLevel = analogRead(LIGHT_SENSOR);
  int pwmValue = lightLevel / 4; // Skalowanie do 0-255 dla analogWrite

  // Sterowanie kolorem niebieskim przez PWM
  analogWrite(RGB_BLUE, pwmValue);

  // 2. Automatyczny włącznik (Progi jasności)
  if (pwmValue > 100) {
    digitalWrite(RGB_RED, LOW);
    digitalWrite(RGB_GREEN, LOW);
    digitalWrite(RGB_BLUE, LOW);
  } else {
    digitalWrite(RGB_RED, HIGH);
    digitalWrite(RGB_GREEN, HIGH);
    digitalWrite(RGB_BLUE, HIGH);
  }

  // 3. Obsługa przycisków analogowych
  int keyVal = analogRead(KEYS_INPUT);
  char direction = ' ';

  if (keyVal > 1010 && keyVal < 1020)      direction = 'n';
  else if (keyVal > 510 && keyVal < 520)  direction = 'p';
  else if (keyVal > 680 && keyVal < 690)  direction = 'l';
  else if (keyVal > 410 && keyVal < 420)  direction = 'o';

  if (direction != ' ') {
    Serial.print("Kierunek: ");
    Serial.println(direction);
  }

  // 4. Skalowanie poziomu dla linijki LED (0-10)
  int barLevel = lightLevel / 100; 
  Serial.print("Poziom jasności (0-10): ");
  Serial.println(barLevel);

  // Aktualizacja linijki LED
  updateBarGraph(barLevel);

  delay(100); // Zmniejszyłem delay dla lepszej responsywności
}

// Funkcja pomocnicza do obsługi linijki LED
void updateBarGraph(int level) {
  for (int i = 0; i < 10; i++) {
    if (i < level) {
      digitalWrite(LED_LINE[i], HIGH);
    } else {
      digitalWrite(LED_LINE[i], LOW);
    }
  }
}