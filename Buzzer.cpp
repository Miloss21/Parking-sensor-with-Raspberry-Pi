#include "Buzzer.h"
#include <wiringPi.h>

Buzzer::Buzzer(int pin) : pin(pin) {}

Buzzer::~Buzzer() {
    off();
}

bool Buzzer::init() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    return true;
}

void Buzzer::on() {
    digitalWrite(pin, HIGH);
}

void Buzzer::off() {
    digitalWrite(pin, LOW);
}

void Buzzer::beep(int duration_ms) {
    on();
    delay(duration_ms);
    off();
}

void Buzzer::beepByDistance(float distance) {
    
    if (distance > 100 || distance < 0) {
        off();
        return;
    }

    
    if (distance > 60) {
        beep(100);
        delay(600);
        return;
    }

    
    if (distance > 30) {
        beep(100);
        delay(300);
        return;
    }

    
    if (distance > 10) {
        beep(100);
        delay(100);
        return;
    }

    
    on();
}