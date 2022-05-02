
#pragma once
#include <Arduino.h>

/*
{
    class ZumoVirtualSpeedometer
    {
    public:
        float currentSpeed(unsigned long countsLeft, unsigned long countsRight);
        float maxSpeed(float vehicle_speed);
        float highSpeedTime(float vehicle_speed, float maximum_velocity);
        int distanceDriven(unsigned long countsLeft, unsigned long countsRight);
    };

    class ESPcontrols
    {
    public:
        int updateCarState(char commands_from_ESP);
        float chooseSpeed(char commands_from_ESP);
    };

}
*/

float currentSpeed(unsigned long countsLeft, unsigned long countsRight);
float maxSpeed(float vehicle_speed);
float highSpeedTime(float vehicle_speed, float maximum_velocity);
int distanceDriven(unsigned long countsLeft, unsigned long countsRight);