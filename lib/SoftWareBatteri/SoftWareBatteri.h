#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include <stdint.h>
//#include "Speedometer.h"

class SoftwareBattery
{
private:
    uint16_t battery_capacity;

public:
    uint8_t battery_health;
    uint8_t battery_level;

    SoftwareBattery();
    float batteryDrain(float vehicleSpeed);
};

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
