#include "MotorControlService.h"
#include <Arduino.h>

MotorControlService::MotorControlService(int avrPin, int dirPin, int breakPin, int hallUPin, int hallVPin, int hallWPin) 
    : AVR_Pin(avrPin), DIR_Pin(dirPin), BREAK_Pin(breakPin), HALLU_Pin(hallUPin), HALLV_Pin(hallVPin), HALLW_Pin(hallWPin),
     currentDirection(FORWARD), targetSpeed(0), targetDirection(FORWARD) {
    pinMode(AVR_Pin, OUTPUT);
    pinMode(DIR_Pin, OUTPUT);
    pinMode(BREAK_Pin, OUTPUT);
    pinMode(HALLU_Pin, INPUT);
    pinMode(HALLV_Pin, INPUT);
    pinMode(HALLW_Pin, INPUT);
}

void MotorControlService::update() {
    if(enableAutobreak && targetSpeed == 0) {
        breakState = engaged;
    }
    if (breakState == engaged && targetSpeed > 0) {
        breakState = released;
    }
    if (breakState == engaged) {
        digitalWrite(BREAK_Pin, HIGH);
    } else {
        digitalWrite(BREAK_Pin, LOW);
    }

}

void MotorControlService::drive(int speed, MotorDirection direction) {
    targetSpeed = speed;
    targetDirection = direction;
}

void MotorControlService::stop() {
    targetSpeed = 0;
    targetDirection = FORWARD;
}
void MotorControlService::emergencyStop() {
    targetSpeed = 0;
    breakState = engaged;
}

int MotorControlService::getCurrentSpeed() {
    
}