
#pragma once
#include <Arduino.h>
#include <Zumo32U4.h>
#include <stdint.h>

class Speedometer
{
private:
    float maximum_velocity;
    uint32_t seconds_passed_in_high_speeds;
    uint32_t currentMillis;
    uint32_t prevMillis2;
    uint32_t totalCounts;
    uint16_t distance_driven;
    uint16_t maximum_speed;

public:
    Speedometer();
    float currentSpeed(uint32_t countsLeft, uint32_t countsRight);
    float maksHastighet(float vehicle_speed);
    float highSpeedTime(float vehicle_speed);
    int chooseSpeed(bool button_B_pressed, bool button_C_pressed);
    void distanceDriven(uint32_t countsLeft, uint32_t countsRight);
};

// void initialize();
