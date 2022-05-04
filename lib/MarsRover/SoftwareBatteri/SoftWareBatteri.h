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

public:
    uint8_t battery_health;
    uint8_t battery_level;

    SoftwareBattery();
    float batteryDrain(float vehicle_speed);
    float reverseCharge();
    int checkBatteryState(int battery_level);
    int batteryHealthCheck(int battery_level, float vehicle_speed, float maximum_speed);
};
