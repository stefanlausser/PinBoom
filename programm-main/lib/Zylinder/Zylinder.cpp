#include "Zylinder.h"
#include <Arduino.h>

Zylinder::Zylinder(int pin) {
    controlPin = pin;
    pinMode(controlPin, OUTPUT);
}
void Zylinder::ausfahren() {
    
    if(millis() - timer >= 1) {
        timer = millis();
        digitalWrite(controlPin, HIGH);
    }else{
        digitalWrite(controlPin, LOW);
    }
}
void Zylinder::einfahren() {
    if(millis() - timer >= 2) {
        timer = millis();
        digitalWrite(controlPin, HIGH);
    }else{
        digitalWrite(controlPin, LOW);
    }
}