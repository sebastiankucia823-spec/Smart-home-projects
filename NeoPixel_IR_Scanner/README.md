# 🌈 NeoPixel IR Scanner

Interaktywny system oświetlenia oparty na diodach adresowalnych WS2812B (NeoPixel) oraz czujniku podczerwieni (IR).

## 📝 Opis projektu
Projekt realizuje funkcję wizualnego "skanera". Pojedynczy punkt świetlny porusza się w pętli po pasku LED, a jego prędkość i status systemu są monitorowane na bieżąco. Dane z czujników są wyświetlane na ekranie LCD, co pozwala na podgląd wartości analogowych w czasie rzeczywistym.

## ⚙️ Funkcjonalności
* **Animacja NeoPixel:** Płynne przemieszczanie się punktu (kolor niebieski) po 16 diodach.
* **Monitorowanie IR:** Odczyt wartości z czujnika podczerwieni (PC2).
* **Interfejs LCD:** Wyświetlanie wartości z sensora podczerwieni oraz fotorezystora na ekranie 16x2 przez magistralę I2C.
* **Diagnostyka Serial:** Wysyłanie pomiarów na port szeregowy (9600 bps).

## 🔌 Wykorzystane piny (STM32/Arduino)
| Komponent | Pin |
| :--- | :--- |
| **NeoPixel (DIN)** | PB7 |
| **LCD (SDA/SCL)** | I2C (0x27) |
| **Czujnik IR** | PC2 |
| **Czujnik Światła** | PB11 |
| **Przyciski** | PA4 |

## 🛠 Wymagane biblioteki
Do poprawnej kompilacji projektu wymagane są:
1. `Adafruit_NeoPixel`
2. `LiquidCrystal_I2C`

## 🚀 Jak użyć?
1. Podłącz komponenty zgodnie z tabelą pinów.
2. Zainstaluj wymagane biblioteki w Arduino IDE.
3. Wgraj plik `.ino` na swoją płytkę.
4. Otwórz Monitor Szeregowy, aby zobaczyć szczegółowe dane.

---
*Projekt wykonany w ramach nauki programowania systemów wbudowanych.*