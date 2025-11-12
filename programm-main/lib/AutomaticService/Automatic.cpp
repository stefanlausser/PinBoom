#include "Automatic.h"
#include "Variablen.h"

void automatic_init(){
    currentStep = 0;
}

void automatic_run(bool Button, bool End_1, bool End_2, bool End_3){
    if(emergencystate);
    switch (currentStep)
    {
    case 0:
        if(!End_3){
            /*
            fahre an Position 3
            Zylinder einfahren
            */
        }
        if(End_3 && Button) currentStep = 1;
        break;
    case 1:
        if(!End_2){
            /*
            fahre an Position 2
            Zylinder ausfahren
            */
        } else {
            currentStep = 2;
        }
        break;
    case 2:
        if(!End_1){
            /*
            Fahre an Position 1
            Zylinder einfahren
            */
        }else{
            currentStep = 3;
        }
        break;
    case 3:
        if(!End_3){
            /*
            fahre an Position 3
            Zylinder ausfahren
            */
        }else{
            currentStep = 4;
        }
        break;
    case 4:
        if(!End_1){
            /*
            Fahre an Position 1
            Zylinder einfahren
            */
        } else{
            currentStep = 5;
        }
        break;
    case 5:
        if(!End_3){
            /*
            fahre an Position 3
            verweile dort 5s
            */
        } else {
            currentStep = 6;
        }
        break;
    case 6:
        if(!End_1){
            /*
            fahre an Position 1 
            Zylinder ausfahren
            */
        } else {
            currentStep = 7;
        }
        break;
    case 7:
        if(!End_3){
            /*
            Fahre an Position 3 
            Zylinder einfahren
            */
        } else {
            currentStep = 8;
        }
        break;
    case 8:
        if(!End_1){
            /*
            Fahre an Position 1 
            Zylinder ausfahren
            */
        } else {
            currentStep = 9;
        }
        break;
    case 9:
        if(!End_2){
            /*
            Fahre an Position 2
            Zylinder einfahren
            */
        } else {
            currentStep = 0;
        }
        break;
    default:
        currentStep = 0;
        break;
    }
}