#pragma once

class Sensor {
public:
    Sensor(int trigPin, int echoPin);
    ~Sensor();

    bool init();
    float measureDistance();

private:
    int trigPin;
    int echoPin;
};