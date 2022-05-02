#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include <stdint.h>

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

float batteryDrain(float vehicle_speed);
float reverseCharge();
int checkBatteryState(float battery_level);
int batteryHealthCheck(float battery_level, float vehicle_speed, float maximum_speed);