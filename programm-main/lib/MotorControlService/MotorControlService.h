#ifndef MOTORCONTROLSERVICE_H
#define MOTORCONTROLSERVICE_H

enum MotorDirection {
    FORWARD = 1,
    REVERSE = -1
};

enum BreakState{
    released,
    engaged,
};

class MotorControlService {
    public:
        MotorControlService(int avrPin, int dirPin, int breakPin, int hallUPin, int hallVPin, int hallWPin);
        void update();
        void drive(int speed, MotorDirection direction);
        void stop();
        void emergencyStop();
        bool enableAutobreak = false;
        MotorDirection getCurrentDirection();
        int getCurrentSpeed();
    private:
        int AVR_Pin;
        int DIR_Pin;
        int BREAK_Pin;
        int HALLU_Pin;
        int HALLV_Pin;
        int HALLW_Pin;
        BreakState breakState;
        MotorDirection currentDirection;
        MotorDirection targetDirection;
        int targetSpeed;
};
#endif