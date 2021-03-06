#pragma once

#include <stdint.h>
#include <Wire.h>
#include <Zumo32U4.h>

class PropulsionSystem
{
private:
    int16_t maxSpeed;
    Zumo32U4Motors motors;
    Zumo32U4Buzzer buzzer;
    Zumo32U4LineSensors lineSensors;
    unsigned int lineSensorValues[5] = {0, 0, 0, 0, 0};
    int16_t lastError;
    uint8_t car_state;

public:
    PropulsionSystem(Zumo32U4Motors objMotors, uint16_t objMaxSpeed, Zumo32U4Buzzer objBuzzer, Zumo32U4LineSensors objLineSensors);
    void calibrateLightSensors();
    void followLine();
    int updateCarState(char commands_from_ESP);
    float chooseMaxSpeed(char commands_from_ESP);
    void ESPdriveCommands(char commands_from_ESP);
    int PropulsionSystem::findChargingStation(int battery_level, int sun_luminance);
};

/*
class ESPcommands
{
private:

protected:
    int16_t maxSpeed;
    Zumo32U4Motors motors;
    Zumo32U4Buzzer buzzer;
    Zumo32U4LineSensors lineSensors;
    unsigned int lineSensorValues[5] = {0, 0, 0, 0, 0};

public:
    ESPcommands(Zumo32U4Motors motors, uint16_t maxSpeed, Zumo32U4Buzzer buzzer, Zumo32U4LineSensors lineSensors);
    void calibrateLightSensors();
    void followLine();
    int updateCarState(char commands_from_ESP);
    float chooseMaxSpeed(char commands_from_ESP);
    void ESPdriveCommands(char commands_from_ESP);
};
*/