/*
 * Keypad_7Seg_Controller.ino
 * 
 * Funkcja: Obsługa klawiatury matrycowej 4x4 oraz wyświetlacza 
 * 7-segmentowego. Po naciśnięciu klawisza, odpowiednia cyfra 
 * pojawia się na Serial Monitorze i (opcjonalnie) na wyświetlaczu.
 */

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// --- Konfiguracja Wyświetlacza 7-segmentowego ---
const uint8_t SEGMENTS[] = {PC3, PB12, PA0, PA15, PD3, PA11, PD4}; // a, b, c, d, e, f, g
#define DIG_L PC9
#define DIG_R PC8
#define LINE5 PA9 // Dodatkowa dioda/linia z Twojego kodu

// --- Konfiguracja Klawiatury (Keypad) ---
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {PC7, PA8, PB14, PB4}; 
byte colPins[COLS] = {PB5, PB3, PC4, PC5}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  
  // Inicjalizacja segmentów
  for(int i = 0; i < 7; i++) {
    pinMode(SEGMENTS[i], OUTPUT);
  }
  pinMode(DIG_L, OUTPUT);
  pinMode(DIG_R, OUTPUT);
  pinMode(LINE5, OUTPUT);

  // Inicjalizacja LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Klawiatura OK!");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Nacisnieto: ");
    Serial.println(key);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Klawisz: ");
    lcd.print(key);

    // Wyświetlanie na 7-seg (przykład dla cyfr)
    if (key >= '0' && key <= '9') {
      displayDigit(key - '0'); 
    }
  }
}

// Funkcja sterująca segmentami (0-9)
void displayDigit(int num) {
  // Mapowanie segmentów dla cyfr 0-9 (0 = zapalona, 1 = zgaszona - typowa wspólna anoda)
  // Jeśli masz wspólną katodę, odwróć 0 i 1
  const byte digits[10][7] = {
    {0,0,0,0,0,0,1}, // 0
    {1,0,0,1,1,1,1}, // 1
    {0,0,1,0,0,1,0}, // 2
    {0,0,0,0,1,1,0}, // 3
    {1,0,0,1,1,0,0}, // 4
    {0,1,0,0,1,0,0}, // 5
    {0,1,0,0,0,0,0}, // 6
    {0,0,0,1,1,1,1}, // 7
    {0,0,0,0,0,0,0}, // 8
    {0,0,0,0,1,0,0}  // 9
  };

  digitalWrite(DIG_L, LOW);  // Wybór cyfry lewej
  digitalWrite(DIG_R, HIGH); // Wybór cyfry prawej

  for (int i = 0; i < 7; i++) {
    digitalWrite(SEGMENTS[i], digits[num][i]);
  }
}