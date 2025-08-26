#ifndef SERIALCOMMUNICATIONSERVICE_H
#define SERIALCOMMUNICATIONSERVICE_H

#include <Arduino.h> // Needed for String type
#include <SoftwareSerial.h>

class SerialCommunicationService {
public:
    SerialCommunicationService();
    void begin(long baudRate);
    void sendData(byte* data, size_t length);
    byte* receiveData();

private:
    long _baudRate;
    SoftwareSerial Communication{10, 11}; // RX, TX

};

#endif // SERIALCOMMUNICATIONSERVICE_H
