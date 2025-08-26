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

  if(received == SYSTEM_STARTED) {
    serialService.sendData(CONFIRMATION);
  }
  if(received == NOTAUS_TRIGGERED) {
    notausState = true;
  }
  if(received == NOTAUS_OK) {
    notausState = false;
  }

  digitalWrite(LED_BUILTIN, notausState ? HIGH : LOW);
}

