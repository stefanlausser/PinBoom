#include <Arduino.h>
#include "Variablen.h"

// ===== Globale Zustände =====
bool NOTAUS = false;
bool emergencystate = false;
int currentStep = 0;

// ===== Timer =====
unsigned long SerialTimer = 0;