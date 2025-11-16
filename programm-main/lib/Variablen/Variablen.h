#ifndef VARIABLEN_H
#define VARIABLEN_H

#include <Arduino.h>

// ===== Pinbelegung =====
#define I2 2   // Button
#define I3 3   // Endstop 1
#define I4 4   // Endstop 2
#define I5 5   // Endstop 3
#define I6 6   // Motor-Speed
#define O7 7  // Motor-PWM
#define O8 8  // Motor-Richtung
#define O9 9  // Motor-Break

// ===== Konstanten =====
const short SerialReadIntervall = 50; // ms

// ===== Externe Variablen =====
extern bool NOTAUS;
extern bool emergencystate;
extern unsigned long SerialTimer;
extern int currentStep;

// ===== Initialisierung =====


#endif