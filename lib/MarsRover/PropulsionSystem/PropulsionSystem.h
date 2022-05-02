#pragma once

#include <stdint.h>
#include <Wire.h>
#include <Zumo32U4.h>

class PropulsionSystem
{
private:
    uint16_t maxSpeed;
    int16_t lastError;
    unsigned int lineSensorValues[3] = {0, 0, 0};
    Zumo32U4LineSensors lineSensors;
    Zumo32U4Motors motors;
    Zumo32U4ButtonA buttonA;
    Zumo32U4Buzzer buzzer;

public:
    PropulsionSystem(uint16_t maxSpeed, Zumo32U4LineSensors lineSensors, Zumo32U4Motors motors, Zumo32U4Buzzer buzzer);
    void calibrateLightSensors();
    void followLine();
};