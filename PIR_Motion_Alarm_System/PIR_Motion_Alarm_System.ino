/*
 * PIR_Motion_Alarm_System.ino
 * 
 * Funkcja: Wykrywanie ruchu za pomocą czujnika PIR. 
 * System sygnalizuje stan za pomocą diody RGB (Zielony - OK, Czerwony - Ruch),
 * wyświetla znaki na wyświetlaczu 7-segmentowym oraz animuje pasek LED.
 */

// --- Konfiguracja Pinów ---
#define PIR_PIN    PB2

// RGB LED
#define RGB_RED    PC10
#define RGB_GREEN  PD0
#define RGB_BLUE   PC12

// Linijka LED
const uint8_t LED_BAR[] = {PB13, PB15, PB6, PC0, PC1, PA9, PA12, PD6, PD9, PC6};

// Wyświetlacz 7-segmentowy
const uint8_t SEGMENTS[] = {PC3, PB12, PA0, PA15, PD3, PA11, PD4}; // a, b, c, d, e, f, g
#define DIG_L PC8
#define DIG_R PC9

void setup() {
  Serial.begin(9600);

  pinMode(PIR_PIN, INPUT);
  
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);

  for (int i = 0; i < 10; i++) pinMode(LED_BAR[i], OUTPUT);
  for (int i = 0; i < 7; i++)  pinMode(SEGMENTS[i], OUTPUT);
  
  pinMode(DIG_L, OUTPUT);
  pinMode(DIG_R, OUTPUT);
}

void loop() {
  // 1. Płynne przejście koloru zielonego (Fade)
  for (int i = 0; i < 256; i++) {
    analogWrite(RGB_GREEN, i);
    delay(5); // Szybszy efekt dla płynności
  }

  // 2. Odczyt czujnika ruchu PIR
  bool motionDetected = digitalRead(PIR_PIN);
  Serial.print("Status PIR: ");
  Serial.println(motionDetected);

  if (motionDetected) {
    handleAlarm();
  } else {
    standbyMode();
  }
}

// Funkcja wywoływana po wykryciu ruchu
void handleAlarm() {
  digitalWrite(RGB_RED, HIGH);  // Alarm na czerwono
  digitalWrite(RGB_GREEN, LOW);
  digitalWrite(RGB_BLUE, LOW);

  showChar('A'); // Wyświetl "A" jak Alarm
  runLedAnimation();
}

// Funkcja trybu czuwania
void standbyMode() {
  digitalWrite(RGB_RED, LOW);
  digitalWrite(RGB_GREEN, HIGH); // Zielony - bezpiecznie
  digitalWrite(RGB_BLUE, LOW);
  
  clearLedBar();
}

// --- Funkcje Pomocnicze ---

void runLedAnimation() {
  // Efekt "rozchodzenia się" od środka do brzegów
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BAR[4 - i], HIGH);
    digitalWrite(LED_BAR[5 + i], HIGH);
    delay(100);
  }
}

void clearLedBar() {
  for (int i = 0; i < 10; i++) digitalWrite(LED_BAR[i], LOW);
}

void showChar(char c) {
  digitalWrite(DIG_L, HIGH); // Aktywuj cyfrę
  digitalWrite(DIG_R, LOW);

  // Przykładowe mapowanie dla A i E
  if (c == 'A') {
    // Segmenty: a,b,c,e,f,g (bez d)
    byte pins[] = {0,0,0,1,0,0,0}; 
    for(int i=0; i<7; i++) digitalWrite(SEGMENTS[i], pins[i]);
  } else if (c == 'E') {
    // Segmenty: a,d,e,f,g (bez b,c)
    byte pins[] = {0,1,1,0,0,0,0};
    for(int i=0; i<7; i++) digitalWrite(SEGMENTS[i], pins[i]);
  }
}