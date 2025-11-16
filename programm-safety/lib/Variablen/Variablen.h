#ifndef VARIABLEN_H
#define VARIABLEN_H

//pins
#define NOTAUS 2
#define Q1 4
#define Q2 7
#define TASTER 8
#define MOTORSCHUTZ 3

//Konstanten
const short DEBOUNCE_DELAY = 50;
const short MAX_UPDATE_INTERVAL = 120;
const short MAX_LATENCY = 5;
const short UPDATE_INTERVAL = 100;

//Variablen
extern bool notausState;
extern bool lastNotausState;
extern bool motorschutzState;
extern int latency; //in ms
extern unsigned long lastDebounceTime;
extern unsigned long sentCommunicationTime;
extern unsigned long receivedCommunicationTime;
extern unsigned long sendTimer;
extern bool Systemstarted;

#endif