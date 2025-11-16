#include <Arduino.h>
#include <SerialCommunicationService.h>
#include <CommunicationKeys.h>
#include <Variablen.h>
#include <MotorControlService.h>

SerialCommunicationService serialService;
MotorControlService motorService(O7, O8, O9, A0, A1, A2);
void handleSerialCommands();

void setup() {
  serialService.begin(9600);
}

void loop() {
 //======= Eingänge lesen =======
  bool Button = digitalRead(I2);
  bool ENDSTOP_1 = digitalRead(I3);
  bool ENDSTOP_2 = digitalRead(I4);
  bool ENDSTOP_3 = digitalRead(I5);

  motorService.update();

  noInterrupts();
  handleSerialCommands();
  if(NOTAUS){
    emergencystate = true;
    while (true)
    {
      handleSerialCommands();
      if(Button){
        NOTAUS = false;
        emergencystate = false;
        break;
      }
    }   
  }
}

void handleSerialCommands() {
  //======== Serielle Kommunikation =======
  byte received = serialService.receiveData();
  switch (received)
    {
    case SYSTEM_STARTED:
      serialService.sendData(CONFIRMATION);
      break;
    case NOTAUS_TRIGGERED:
      NOTAUS = true;
      serialService.sendData(CONFIRMATION);
      break;
    case NOTAUS_OK:
      NOTAUS = false;
      serialService.sendData(CONFIRMATION);
      break;
    default:
      break;
    }
}

