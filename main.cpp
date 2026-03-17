#include <iostream>
#include <string>
#include <wiringPi.h>
#include "LCD.h"
#include "Sensor.h"
#include "Buzzer.h"

// WiringPi pin brojevi
#define TRIG_PIN  0   // GPIO 17
#define ECHO_PIN  2   // GPIO 27
#define BUZZER_PIN 3  // GPIO 22

std::string getStatus(float distance) {
    if (distance < 0)        return "  VAN DOMETA    ";
    if (distance <= 10)      return "   OPASNOST!    ";
    if (distance <= 30)      return "    BLIZU!      ";
    if (distance <= 60)      return "   OPREZNO!     ";
    if (distance <= 100)     return "     PAZI!      ";
    return "      OK        ";
}

int main() {
    
    if (wiringPiSetup() == -1) {
        std::cerr << "WiringPi setup failed!" << std::endl;
        return 1;
    }

    
    LCD lcd(0x27);
    Sensor sensor(TRIG_PIN, ECHO_PIN);
    Buzzer buzzer(BUZZER_PIN);

    if (!lcd.init()) {
        std::cerr << "LCD init failed!" << std::endl;
        return 1;
    }

    if (!sensor.init()) {
        std::cerr << "Sensor init failed!" << std::endl;
        return 1;
    }

    if (!buzzer.init()) {
        std::cerr << "Buzzer init failed!" << std::endl;
        return 1;
    }

    
    lcd.printLine(0, " Parking senzor ");
    lcd.printLine(1, "  Pokretanje... ");
    delay(2000);
    lcd.clear();

    std::cout << "Parking senzor pokrenut!" << std::endl;

    while (true) {
        float distance = sensor.measureDistance();

        
        if (distance < 0) {
            lcd.printLine(0, " Van dometa     ");
            lcd.printLine(1, "                ");
        } else {
            
            std::string distStr = "Dist: " + std::to_string((int)distance) + " cm";
            lcd.printLine(0, distStr);

            
            lcd.printLine(1, getStatus(distance));
        }

        
        if (distance < 0) {
            std::cout << "Van dometa" << std::endl;
        } else {
            std::cout << "Distanca: " << distance << " cm" << std::endl;
        }

        
        buzzer.beepByDistance(distance);
    }

    return 0;
}