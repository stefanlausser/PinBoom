#include <Arduino.h>
#include "SerialCommunicationService.h"
#include "Variablen.h"

SerialCommunicationService serialService;

void setup() {
    pinMode(NOTAUS, INPUT_PULLUP);
    pinMode(Q1, OUTPUT);
    digitalWrite(Q1, LOW); // Q1 initial ausschalten
    pinMode(Q2, OUTPUT);
    digitalWrite(Q2, LOW); // Q2 initial ausschalten

    serialService.begin(9600);

    byte dataStart[2] = {0x01, 0x00}; // NOT AUS System gestartet

    do {
        serialService.sendData(dataStart, 2);

        unsigned long startTime = millis();

        while (serialService.receiveData() == nullptr) {
            if (millis() - startTime > MAX_LATENCY) {
                break; // Timeout -> nochmal senden
            }
            delay(100);
        }

        latency = millis() - startTime;
    } while (latency > MAX_LATENCY);
}

void loop() {
    bool temp = digitalRead(NOTAUS);
    
    if(temp != lastNotausStatus) {
        lastDebounceTime = millis();
    } 
    
    if((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        if(temp != notausStatus) {
            notausStatus = temp;
        }
        lastNotausStatus = notausStatus;
    }

    if (notausStatus == LOW) {
      digitalWrite(Q1, LOW); // Q1 Ausschalten
      digitalWrite(Q2, LOW); // Q2 Ausschalten
        byte dataPress[2] = {0x01, 0x01}; // NOT AUS gedrückt
        serialService.sendData(dataPress, 2);

        while (digitalRead(NOTAUS) == LOW) {
            delay(100); // Warten, bis losgelassen
        }
      digitalWrite(Q1, HIGH); // Q1 Einschalten
      digitalWrite(Q2, HIGH); // Q2 Einschalten

        byte dataRelease[2] = {0x01, 0x02}; // NOT AUS losgelassen
        serialService.sendData(dataRelease, 2);
    }
}
