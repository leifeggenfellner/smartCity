
#pragma once
#include <Arduino.h>
#include <Zumo32U4.h>
#include <stdint.h>

/*
struct speedFunctions
{
    int average_velocity;
    int seconds_passed_in_high_speeds;
    int maximum_velocity;
};*/

class Speedometer
{
private:
    float maximum_velocity;
    uint32_t seconds_passed_in_high_speeds;
    uint32_t currentMillis;
    uint32_t prevMillis;
    uint32_t totalCounts;
    uint16_t distance_driven;
    uint16_t maximum_speed;
    uint32_t total_counts;
    uint8_t sampling_count;
    // struct speedStruct speedValues;

public:
    Speedometer();
    int currentSpeed(uint16_t countsLeft, uint16_t countsRight);
    int recordMaxVelocity(float vehicle_speed);
    float highSpeedTime(float vehicle_speed);
    int chooseSpeed(bool button_B_pressed, bool button_C_pressed);
    uint16_t distanceDriven(uint32_t countsLeft, uint32_t countsRight);
    int averageSpeed(float vehicle_speed);
    // void updateVariables(float vehicle_speed, uint32_t previous_millis);
};
