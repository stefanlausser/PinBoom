#ifndef ZYLINDERCONTROLSERVICE_H
#define ZYLINDERCONTROLSERVICE_H

enum Zylinderstate{
    expanded,
    retracted
};

class ZylinderControlService {
    public:
        ZylinderControlService(int ctrlPin);
        void expand();
        void retract();
        Zylinderstate getState();
    private:
        int CTRL_Pin;
        Zylinderstate state;
};
#endif