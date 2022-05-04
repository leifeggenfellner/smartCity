#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include <stdint.h>

#define level_0 0
#define level_1 1
#define level_2 2
#define level_3 3

class SoftwareBattery
{
private:
    uint16_t battery_capacity;
    uint8_t battery_health_level;
    uint8_t charging_cycles;

public:
    uint8_t battery_health;
    int batteryLevel;

    SoftwareBattery();
    int chargingCycles();
    int batteryDrain(int vehicle_speed);
    int reverseCharge(int battery_level);
    int degradeBattery(int battery_level, float vehicle_speed, float seconds_passed_in_high_speeds);
};
