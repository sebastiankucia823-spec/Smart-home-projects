# 🔢 Keypad Light Multiplexer

Zaawansowany system monitorowania światła z dynamicznym wyświetlaczem 7-segmentowym.

## 📝 Opis projektu
System domyślnie monitoruje natężenie światła i wyświetla wynik w skali 0-99 na dwucyfrowym wyświetlaczu 7-segmentowym. Użytkownik może w dowolnym momencie wpisać dwucyfrową liczbę z klawiatury, aby "nadpisać" wyświetlaną wartość. Projekt wykorzystuje **multipleksowanie programowe**, co pozwala na sterowanie dwiema cyframi przy użyciu jednego zestawu pinów segmentowych.

## ⚙️ Funkcjonalności
* **Dual Mode:** Automatyczny odczyt z fotorezystora lub tryb ręczny z klawiatury.
* **Multipleksowanie:** Odświeżanie wyświetlacza co 3ms dla płynnego obrazu bez migotania.
* **Interfejs LCD:** Intuicyjne menu wprowadzania danych.
* **Smart Mapping:** Skalowanie surowego odczytu analogowego (0-1023) na czytelną skalę (0-99).

## 🔌 Kluczowe połączenia
* **Klawiatura 4x4:** Piny PC7, PA8, PB14, PB4 (wiersze) oraz PB5, PB3, PC4, PC5 (kolumny).
* **Wyświetlacz 7-seg:** Wspólne segmenty na portach PC i PA, sterowanie cyframi na PC8/PC9.
* **Sensor:** PB11 (wejście analogowe).

## 🛠 Wymagane biblioteki
* `Keypad`
* `LiquidCrystal_I2C`

---
*Kolejny krok w nauce systemów wbudowanych - obsługa przerwań czasowych i optymalizacja wyjść.*