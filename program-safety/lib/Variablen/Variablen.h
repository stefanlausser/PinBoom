#ifndef VARIABLEN_H
#define VARIABLEN_H

// Pins
#define NOTAUS 2
#define Q1 4
#define Q2 7

// Konstanten (readonly, direkt hier okay)
const long MAX_LATENCY = 5; // Maximale Latenzzeit in ms
const int DEBOUNCE_DELAY = 50; // Entprellzeit in ms

// Variablen
extern bool notausStatus;
extern bool lastNotausStatus;
extern unsigned long latency;
extern unsigned long lastDebounceTime;

#endif // VARIABLEN_H
