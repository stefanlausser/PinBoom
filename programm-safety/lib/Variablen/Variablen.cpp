#include "Variablen.h"

bool notausState = false;
bool lastNotausState = false;
unsigned long lastDebounceTime = 0;
int latency = 0; //in ms
unsigned long sentCommunicationTime = 0;

