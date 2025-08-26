#include "SerialCommunicationService.h"
#include <Arduino.h>

SerialCommunicationService::SerialCommunicationService() {

}

void SerialCommunicationService::begin(long baudRate) {
    _baudRate = baudRate;
    Serial.begin(_baudRate);
}

void SerialCommunicationService::sendData(const byte data) {
    Serial.write(data);
}

byte SerialCommunicationService::receiveData() {
    if(Serial.available() == 0) {
        return NULL; // No data available
    }
    return Serial.read();
}