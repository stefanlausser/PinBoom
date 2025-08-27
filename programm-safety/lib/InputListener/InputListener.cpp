#include "InputListener.h"
#include <Arduino.h>

InputListener::InputListener(int pin, uint8_t mode) {
    _pin = pin;
    pinMode(_pin, mode);
}

bool InputListener::readInput() {
    bool reading = digitalRead(_pin);

    if (reading != _lastState) {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if (reading != _stableState) {
            _stableState = reading;
        }
    }

    _lastState = reading;
    return _stableState;
}

bool InputListener::isPressedEdge() {
    bool current = readInput();
    static bool previous = HIGH;

    bool edge = (previous == HIGH && current == LOW);
    previous = current;
    return edge;
}
