#pragma once

#include <Arduino.h>
//#include "Speedometer.h"


namespace SoftWareBattery
/*
// Deklarerer variabler
int account_balance = 0;
int charging_cycles = 0;
int battery_health = 100;
int charging_cost = 10;
int battery_level = 3;
bool needs_charging = false;
bool battery_dead = false;


namespace Batteriet

{
    class ZumoSWBattery
    {
        public:
            int batteryDrain(int vehicle_speed);
    };

}
*/

float batteryDrain(float vehicle_speed); 
float reverseCharge(); 
int checkBatteryState(float battery_level); 
int batteryHealthCheck(float battery_level, float vehicle_speed, float maximum_speed);
