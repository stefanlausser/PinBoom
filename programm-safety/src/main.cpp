#include <Arduino.h>
#include <SerialCommunicationService.h>
#include <CommunicationKeys.h>
#include <Variablen.h>
#include <InputListener.h>

SerialCommunicationService serialService;
InputListener notausListener(NOTAUS, INPUT_PULLUP);
InputListener tasterListener(TASTER, INPUT_PULLUP);
InputListener motorschutzListener(MOTORSCHUTZ, INPUT_PULLUP);

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
  motorschutzState = motorschutzListener.readInput();
  if(tasterListener.isPressedEdge() && !notausState){
    Systemstarted = !Systemstarted;
  }

  if(serialService.receiveData() == CONFIRMATION) {
    receivedCommunicationTime = millis();
    latency = receivedCommunicationTime-sentCommunicationTime;
    
  }

  if(!notausState && !motorschutzState && latency <= MAX_LATENCY && (millis() - receivedCommunicationTime) <= MAX_UPDATE_INTERVAL && Systemstarted) {
    digitalWrite(Q1, HIGH);
    digitalWrite(Q2, HIGH);
    if(millis() - sentCommunicationTime >= UPDATE_INTERVAL) {
      serialService.sendData(GO);
      sentCommunicationTime = millis();
    }

  }else {
    digitalWrite(Q1, LOW);
    digitalWrite(Q2, LOW);
    Systemstarted = false;
    if(millis() - sentCommunicationTime > UPDATE_INTERVAL) {
      serialService.sendData(STOP);
      sentCommunicationTime = millis();
    }
  }

}