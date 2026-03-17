#include "Sensor.h"
#include <wiringPi.h>

#define MAX_DISTANCE 400

Sensor::Sensor(int trigPin, int echoPin) : trigPin(trigPin), echoPin(echoPin) {}

Sensor::~Sensor() {}

bool Sensor::init() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(trigPin, LOW);
    delay(100);
    return true;
}

float Sensor::measureDistance() {
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    
    long timeout = micros() + 30000;
    while (digitalRead(echoPin) == LOW) {
        if (micros() > timeout) return -1;
    }
    long start_time = micros();

    
    timeout = micros() + 30000;
    while (digitalRead(echoPin) == HIGH) {
        if (micros() > timeout) return -1;
    }
    long end_time = micros();

    
    float elapsed = end_time - start_time;
    float distance = (elapsed * 0.0343) / 2.0;

    if (distance > MAX_DISTANCE) return -1;

    return distance;
}