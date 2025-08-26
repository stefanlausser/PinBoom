#include <Arduino.h>
#include <SerialCommunicationService.h>
#include <CommunicationKeys.h>
#include <Variablen.h>

SerialCommunicationService serialService;


void setup() {
serialService.begin(9600);
pinMode(NOTAUS, INPUT_PULLUP);
pinMode(Q1, OUTPUT);
pinMode(Q2, OUTPUT);

digitalWrite(Q1, LOW);
digitalWrite(Q2, LOW);

do
{
  serialService.sendData(SYSTEM_STARTED);
  lastCommunicationTime = millis();
  while (serialService.receiveData() != CONFIRMATION)
  {
    if (millis()-lastCommunicationTime>MAX_UPDATE_INTERVAL)
    {
      break;
    }
  }
  
  latency = millis() - lastCommunicationTime;

} while (latency > MAX_LATENCY);
}




void loop() {
  bool read = digitalRead(NOTAUS);
  if (read != notausState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (read != notausState) {
      notausState = read;
    }  
  }

  if(notausState == true) {
    digitalWrite(Q1, HIGH);
    digitalWrite(Q2, HIGH);
    serialService.sendData(NOTAUS_OK);
  } else {
    digitalWrite(Q1, LOW);
    digitalWrite(Q2, LOW);
    serialService.sendData(NOTAUS_TRIGGERED);
  }


}
