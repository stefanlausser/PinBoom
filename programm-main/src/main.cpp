#include <Arduino.h>
#include <SerialCommunicationService.h>
#include <CommunicationKeys.h>
#include <Variablen.h>

SerialCommunicationService serialService;

void setup() {
  serialService.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  byte received = serialService.receiveData();
    switch (received)
    {
    case SYSTEM_STARTED:
      serialService.sendData(CONFIRMATION);
      break;
    case NOTAUS_TRIGGERED:
      notausState = true;
      serialService.sendData(CONFIRMATION);
      break;
    case NOTAUS_OK:
      notausState = false;
      serialService.sendData(CONFIRMATION);
      break;
    default:
      break;
    }

  digitalWrite(LED_BUILTIN, notausState ? HIGH : LOW);
}

