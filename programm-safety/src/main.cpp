#include <Arduino.h>
#include <SerialCommunicationService.h>
#include <CommunicationKeys.h>
#include <Variablen.h>
#include <InputListener.h>

SerialCommunicationService serialService;
InputListener notausListener(NOTAUS, INPUT_PULLUP);
InputListener tasterListener(TASTER, INPUT_PULLUP);

void setup() {

serialService.begin(9600);

pinMode(Q1, OUTPUT);
pinMode(Q2, OUTPUT);
digitalWrite(Q1, LOW);
digitalWrite(Q2, LOW);


do
{
  serialService.sendData(SYSTEM_STARTED);
  sentCommunicationTime = millis();
  while (serialService.receiveData() != CONFIRMATION)
  {
    if (millis()-sentCommunicationTime>MAX_UPDATE_INTERVAL)
    {
      break;
    }
  }
  
  latency = millis() - sentCommunicationTime;

} while (latency > MAX_LATENCY);
}




void loop() {
  notausState = notausListener.readInput();
  if(tasterListener.isPressedEdge()){
    Systemstarted = !Systemstarted;
  }

  if(serialService.receiveData() == CONFIRMATION) {
    receivedCommunicationTime = millis();
    latency = receivedCommunicationTime-sentCommunicationTime;
    
  }

  if(!notausState && latency <= MAX_LATENCY && (millis() - receivedCommunicationTime) <= MAX_UPDATE_INTERVAL && Systemstarted) {
    digitalWrite(Q1, HIGH);
    digitalWrite(Q2, HIGH);
    if(millis() - sentCommunicationTime >= UPDATE_INTERVAL) {
      serialService.sendData(NOTAUS_OK);
      sentCommunicationTime = millis();
    }

  }else {
    digitalWrite(Q1, LOW);
    digitalWrite(Q2, LOW);
    if(millis() - sentCommunicationTime > UPDATE_INTERVAL) {
      serialService.sendData(NOTAUS_TRIGGERED);
      sentCommunicationTime = millis();
    }
  }

}