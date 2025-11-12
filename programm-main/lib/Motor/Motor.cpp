#include "Motor.h"

Motor::Motor(int pwmPin, int directionPin, int breakPin, int speedPin) {
    _PWM = pwmPin;
    _direction = directionPin;
    _break = breakPin;
    _speed = speedPin;

    pinMode(_PWM, OUTPUT);
    pinMode(_direction, OUTPUT);
    pinMode(_break, OUTPUT);
    pinMode(_speed, INPUT);

    lastUpdateTime = millis();
    lastSpeedImpulseTime = micros();

    targetSpeed = 0;
    currentSpeed = 0;
    controlOutput = 0;
}

void Motor::applyBrake(bool enable) {
    if (enable && !brakeActive) {
        digitalWrite(_break, HIGH);  // Bremse aktivieren
        analogWrite(_PWM, 0);        // sicherheitshalber PWM aus
        brakeActive = true;
    } 
    else if (!enable && brakeActive) {
        digitalWrite(_break, LOW);   // Bremse lösen
        brakeActive = false;
    }
}

void Motor::drive(float target, Direction direction) {
    targetSpeed = target;

    // Richtung setzen
    digitalWrite(_direction, direction == FORWARD ? HIGH : LOW);

    // Bremse lösen, falls deaktiviert oder Motor soll laufen
    if (autobreak) {
        if (targetSpeed > 1.0f) applyBrake(false);
    } else {
        applyBrake(false);
    }
}

void Motor::update() {
    unsigned long now = millis();
    float dt = (now - lastUpdateTime) / 1000.0f;
    if (dt <= 0) return;
    lastUpdateTime = now;

    // Geschwindigkeit über Tacho bestimmen (nicht-blockierend)
    if (digitalRead(_speed)) {
        unsigned long nowMicros = micros();
        unsigned long delta = nowMicros - lastSpeedImpulseTime;
        if (delta > 0) {
            float freq = 1000000.0 / delta;      // Hz
            currentSpeed = (freq / 12.0) * 4.0;  // Beispiel: 12 Imp./U, 4mm/U
        }
        lastSpeedImpulseTime = nowMicros;
    }

    // --- PID-Regelung ---
    float error = targetSpeed - currentSpeed;
    integral += error * dt;
    float derivative = (error - lastError) / dt;
    lastError = error;

    float output = Kp * error + Ki * integral + Kd * derivative;

    // Begrenzen
    if (output > maxPWM) output = maxPWM;
    if (output < 0) output = 0;

    controlOutput = output;
    analogWrite(_PWM, (int)controlOutput);

    // --- Bremse automatisch aktivieren ---
    if (autobreak) {
        // Wenn Motor stillsteht (Ist & Soll fast 0)
        if (fabs(currentSpeed) < 0.5f && fabs(targetSpeed) < 0.5f) {
            applyBrake(true);
        }
    }
}

void Motor::emergencyStop() {
    targetSpeed = 0;
    controlOutput = 0;
    analogWrite(_PWM, 0);
    applyBrake(true);
}