#include <Arduino.h>
#include <SerialCommunicationService.h>
#include <CommunicationKeys.h>
#include <Variablen.h>
#include <Automatic.h>

SerialCommunicationService serialService;

void setup() {
  serialService.begin(9600);
}

void loop() {
 //======= Eingänge lesen =======
  bool Button = digitalRead(I2);
  bool ENDSTOP_1 = digitalRead(I3);
  bool ENDSTOP_2 = digitalRead(I4);
  bool ENDSTOP_3 = digitalRead(I5);
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

  //======= Not-Aus Logik =======
  if(NOTAUS) emergencystate = true;
  if(emergencystate && !NOTAUS && Button) emergencystate = false;

  if(emergencystate){
    motor.emergencyStop();
  }else{
    motor.update();
    automatic_run(Button, ENDSTOP_1, ENDSTOP_2, ENDSTOP_3);
  }
}

