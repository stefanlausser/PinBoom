#ifndef INPUT_LISTENER_H
#define INPUT_LISTENER_H

#include <Arduino.h>

class InputListener {
  public:
    InputListener(int pin, uint8_t mode);
    bool readInput();         // Gibt den stabilen Zustand zurück
    bool isPressedEdge();     // Gibt true zurück, wenn Taste gerade gedrückt wurde (Flanke)

  private:
    int _pin;
    bool _lastState = HIGH; // Falls Pullup verwendet
    bool _stableState = HIGH;
    unsigned long _lastDebounceTime = 0;
    const unsigned long _debounceDelay = 50; // ms
};

#endif
