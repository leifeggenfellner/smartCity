
#pragma once
#include <Arduino.h>
#include <Zumo32U4.h>

/*
unsigned long currentMillis;
unsigned long prevMillis = 0;
unsigned long prevMillis2 = 0;
*/
/*
namespace Speedometeret

{
    class ZumoSpeedometer
    {
    public:
        int gjennomsnittsHastighet();
        int maksHastighet(float vehicle_speed);
        void sekunderOver70(float vehicle_speed, float maximum_velocity);
    };

}
*/

float gjennomsnittsHastighet(unsigned long countsLeft, unsigned long countsRight);
float maksHastighet(float vehicle_speed);
float highSpeedTime(float vehicle_speed, float maximum_velocity);
int chooseSpeed(bool button_B_pressed, bool button_C_pressed);
int distanceDriven(unsigned long countsLeft, unsigned long countsRight);
int updateCarState(bool button_A_pressed);
//void initialize();