#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

enum Direction { FORWARD, BACKWARD };

class Motor {
private:
    int _PWM, _direction, _break, _speed;
    unsigned long lastUpdateTime;
    unsigned long lastSpeedImpulseTime;

    float targetSpeed;     // Sollgeschwindigkeit (mm/s)
    float currentSpeed;    // Istgeschwindigkeit (mm/s)
    float controlOutput;   // PWM-Ausgang

    // PID-Parameter
    float Kp = 0.8;
    float Ki = 0.2;
    float Kd = 0.05;
    float integral = 0;
    float lastError = 0;

    // Begrenzungen
    int maxPWM = 255;
    bool autobreak = false;
    bool brakeActive = false;

    // interner Helper
    void applyBrake(bool enable);

public:
    Motor(int pwmPin, int directionPin, int breakPin, int speedPin);

    void drive(float target, Direction direction);
    void emergencyStop();
    void update();

    void setPID(float p, float i, float d) { Kp = p; Ki = i; Kd = d; }
    void setAutoBreak(bool enabled) { autobreak = enabled; }

    float getCurrentSpeed() const { return currentSpeed; }
    float getTargetSpeed() const { return targetSpeed; }
    bool isBrakeActive() const { return brakeActive; }
};

#endif
