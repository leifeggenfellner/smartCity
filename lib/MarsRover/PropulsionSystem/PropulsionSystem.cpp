#include <Arduino.h>
#include "PropulsionSystem.h"

PropulsionSystem::PropulsionSystem(uint16_t maxSpeed, Zumo32U4LineSensors lineSensors, Zumo32U4Motors motors, Zumo32U4Buzzer buzzer)
{
  this->maxSpeed = maxSpeed;
  this->lineSensors = lineSensors;
  this->motors = motors;
  this->buzzer = buzzer;
  this->lastError = 0;
}

void PropulsionSystem::calibrateLightSensors()
{
  lineSensors.initThreeSensors();
  // buzzer.playFrequency(440, 200, 15);

  for (uint16_t i = 0; i < 120; i++)
  {
    if (i == 30 || i == 88)
    {
      motors.setSpeeds(0, 0);
    }
    else if (i > 30 && i <= 87)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }
    lineSensors.calibrate();
    delay(20);
  }
  // buzzer.playFrequency(600, 200, 15);
  motors.setSpeeds(0, 0);

  lineSensors.readCalibrated(lineSensorValues);
}

void PropulsionSystem::followLine()
{
  int16_t position = lineSensors.readLine(lineSensorValues);
  int16_t error = position - 2000;
  int16_t speedDifference = error / 4 + 6 * (error - lastError);

  lastError = error;

  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
}
