#include "SerialCommunicationService.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

SerialCommunicationService::SerialCommunicationService(){
}

void SerialCommunicationService::begin(long baudRate) {
    _baudRate = baudRate;
    Communication.begin(_baudRate);
}

void SerialCommunicationService::sendData(byte* data, size_t length) {
    Serial.write(data, length);
}

byte* SerialCommunicationService::receiveData() {
    static byte buffer[256]; // Adjust size as needed
    size_t index = 0;

    while (Serial.available() > 0 && index < sizeof(buffer)) {
        buffer[index++] = Serial.read();
    }

    if (index == 0) {
        return nullptr; // No data received
    }

    // Null-terminate the buffer to make it a valid string if needed
    if (index < sizeof(buffer)) {
        buffer[index] = '\0';
    } else {
        buffer[sizeof(buffer) - 1] = '\0'; // Ensure null-termination
    }

    return buffer;
}