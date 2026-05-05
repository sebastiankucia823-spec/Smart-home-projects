# 🚪 Smart Home Actuators

Sterownik elementów wykonawczych inteligentnego domu: serwomechanizmu oraz silnika DC.

## 📝 Opis projektu
Projekt pozwala na manualne sterowanie mechanizmami domowymi za pomocą przycisków analogowych. Serwo może służyć jako napęd rolet lub drzwi (z ograniczeniem kąta obrotu), a silnik DC jako wentylator z dwustopniową regulacją prędkości.

## ⚙️ Funkcjonalności
* **Precyzyjne sterowanie serwem:** Inkrementacja i dekrementacja kąta za pomocą przycisków.
* **Wielostopniowy wentylator:** Obsługa dwóch biegów (PWM) oraz funkcji wyłączenia silnika.
* **Monitoring:** Bieżąca pozycja serwa oraz stan silnika wysyłane na port szeregowy.

## 🔌 Wykorzystane piny
| Komponent | Pin | Funkcja |
| :--- | :--- | :--- |
| **Serwo** | PC11 | Sterowanie sygnałem PWM |
| **Silnik DC (INA)** | PD1 | Prędkość obrotowa (PWM) |
| **Silnik DC (INB)** | PB1 | Kierunek obrotów |
| **Przyciski** | PA4 | Odczyt analogowy poziomów napięć |

## 🛠 Wymagane biblioteki
* `Servo.h` (standardowa biblioteka Arduino)

## 🚀 Jak uruchomić?
1. Podłącz serwo i silnik (pamiętaj o zewnętrznym zasilaniu dla silnika, jeśli pobiera dużo prądu!).
2. Wgraj kod na płytkę.
3. Użyj przycisków, aby regulować wysokość rolety lub prędkość wentylatora.