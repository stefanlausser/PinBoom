#ifndef AUTOMATIC_H
#define AUTOMATIC_H

#include <Arduino.h>

void automatic_init();

void automatic_run(bool Button, bool End_1,bool End_2, bool End_3);

void handleEmergency();

#endif