#ifndef ZYLINDER_H
#define ZYLINDER_H

class Zylinder {
public:
    Zylinder(int pin);
    void ausfahren();
    void einfahren();
private:
    int controlPin;
    unsigned long timer = 0;
};

#endif