#pragma once

class Buzzer {
public:
    Buzzer(int pin);
    ~Buzzer();

    bool init();
    void on();
    void off();
    void beep(int duration_ms);
    void beepByDistance(float distance);

private:
    int pin;
};