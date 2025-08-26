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

  if(serialService.receiveData() != SYSTEM_STARTED) {
    serialService.sendData(CONFIRMATION);
  }
  if(serialService.receiveData() == NOTAUS_TRIGGERED) {
    notausState = true;
  }
  if(serialService.receiveData() == NOTAUS_OK) {
    notausState = false;
  }

  digitalWrite(LED_BUILTIN, notausState ? HIGH : LOW);
}

