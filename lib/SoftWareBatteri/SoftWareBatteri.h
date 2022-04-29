#pragma once

#include <Arduino.h>
//#include "Speedometer.h"

//namespace SoftWareBattery

/*
{
    class battery
    {
    public:
        float batteryDrain(float vehicle_speed);
        float reverseCharge();
        int checkBatteryState(float battery_level);
    };

    class batteryHealth
    {
    public:
        int batteryHealthCheck(float battery_level, float vehicle_speed, float maximum_speed);
    };

}
*/

float batteryDrain(float vehicle_speed);
float reverseCharge();
int checkBatteryState(float battery_level);
int batteryHealthCheck(float battery_level, float vehicle_speed, float maximum_speed);