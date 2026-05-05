/*
 * Keypad_Light_Multiplexer.ino
 * 
 * Funkcja: Inteligentny monitor natężenia światła z możliwością ręcznego 
 * nadpisania wartości przez klawiaturę 4x4. Wykorzystuje technikę 
 * multipleksowania dla dwucyfrowego wyświetlacza 7-segmentowego.
 */

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// --- Mapowanie Pinów ---
#define LIGHT_SENSOR PB11
#define LINE5        PA9
#define DIG_L        PC9
#define DIG_R        PC8

const uint8_t SEGMENTS[] = {PC3, PB12, PA0, PA15, PD3, PA11, PD4}; // a, b, c, d, e, f, g

// --- Klawiatura ---
const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'}, {'4','5','6','B'},
  {'7','8','9','C'}, {'*','0','#','D'}
};
byte rowPins[ROWS] = {PC7, PA8, PB14, PB4};
byte colPins[COLS] = {PB5, PB3, PC4, PC5};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Zmienne globalne ---
String enteredCode = "";
int numTens = 0;
int numOnes = 0;
unsigned long lastUpdate = 0;
const int refreshTime = 3; 
bool showLeft = true;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(DIG_L, OUTPUT);
  pinMode(DIG_R, OUTPUT);
  pinMode(LINE5, OUTPUT);

  for (int i = 0; i < 7; i++) pinMode(SEGMENTS[i], OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Wprowadz liczbe:");
}

void loop() {
  handleKeypad();
  updateLogic();
  multiplexDisplay();
}

// --- Logika obsługi klawiatury ---
void handleKeypad() {
  char k = keypad.getKey();
  if (k >= '0' && k <= '9' && enteredCode.length() < 2) {
    enteredCode += k;
    refreshLCD();
  } else if (k == '*') {
    enteredCode = "";
    refreshLCD();
  }
}

void refreshLCD() {
  lcd.setCursor(0, 1);
  if (enteredCode.length() > 0) {
    lcd.print("-> ");
    lcd.print(enteredCode);
    lcd.print("   "); 
  } else {
    lcd.print("                ");
  }
}

// --- Logika obliczeń ---
void updateLogic() {
  int displayValue;
  
  if (enteredCode.length() == 2) {
    displayValue = enteredCode.toInt();
  } else {
    int raw = analogRead(LIGHT_SENSOR);
    displayValue = map(raw, 0, 1023, 99, 0); 
  }

  numTens = displayValue / 10;
  numOnes = displayValue % 10;
}

// --- Obsługa wyświetlacza (Multipleksowanie) ---
void multiplexDisplay() {
  if (millis() - lastUpdate >= refreshTime) {
    lastUpdate = millis();

    // Wygaszenie obu cyfr przed zmianą (zapobiega "duchom")
    digitalWrite(DIG_L, LOW);
    digitalWrite(DIG_R, LOW);

    if (showLeft) {
      drawDigit(numTens);
      digitalWrite(DIG_L, HIGH); // Wspólna katoda/anoda - zależnie od modelu
    } else {
      drawDigit(numOnes);
      digitalWrite(DIG_R, HIGH);
    }
    showLeft = !showLeft;
  }
}

void drawDigit(int d) {
  // Mapowanie segmentów (0-9)
  const byte digits[10][7] = {
    {0,0,0,0,0,0,1}, {1,0,0,1,1,1,1}, {0,0,1,0,0,1,0}, {0,0,0,0,1,1,0},
    {1,0,0,1,1,0,0}, {0,1,0,0,1,0,0}, {0,1,0,0,0,0,0}, {0,0,0,1,1,1,1},
    {0,0,0,0,0,0,0}, {0,0,0,0,1,0,0}
  };

  for (int i = 0; i < 7; i++) {
    digitalWrite(SEGMENTS[i], digits[d][i]);
  }
  // Obsługa dodatkowej linii/kropki jeśli potrzebna
  digitalWrite(LINE5, (d == 1 || d == 4 || d == 7) ? 1 : 0);
}