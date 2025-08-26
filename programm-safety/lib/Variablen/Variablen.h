#ifndef VARIABLEN_H
#define VARIABLEN_H

//pins
#define NOTAUS 2
#define Q1 4
#define Q2 7

//Konstanten
const short DEBOUNCE_DELAY = 50;
const short MAX_UPDATE_INTERVAL = 100;
const short MAX_LATENCY = 5;

//Variablen
extern bool notausState;
extern bool lastNotausState;
extern int latency; //in ms
extern unsigned long lastDebounceTime;
extern unsigned long sentCommunicationTime;

#endif