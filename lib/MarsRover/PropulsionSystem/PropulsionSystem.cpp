#include <Arduino.h>
#include "PropulsionSystem.h"

PropulsionSystem::PropulsionSystem(Zumo32U4Motors objMotors, uint16_t objMaxSpeed, Zumo32U4Buzzer objBuzzer, Zumo32U4LineSensors objLineSensors) : motors{objMotors}, maxSpeed{objMaxSpeed}, buzzer{objBuzzer}, lineSensors{objLineSensors}
{
  this->car_state = 0;
  this->lastError = 0;
};

void PropulsionSystem::calibrateLightSensors()
{
  lineSensors.initFiveSensors();
  // buzzer.playFrequency(440, 200, 15);

  for (uint16_t i = 0; i < 60; i++)
  {
    if (i == 15 || i == 44)
    {
      motors.setSpeeds(0, 0);
    }
    else if (i > 15 && i <= 43)
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
  int8_t speedDifference = error / 4 + 6 * (error - lastError);

  lastError = error;

  int8_t leftSpeed = (int8_t)maxSpeed + speedDifference;
  int8_t rightSpeed = (int8_t)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int8_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int8_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
}

int PropulsionSystem::updateCarState(char commands_from_ESP)
{
  if (commands_from_ESP == 'l')
  {
    car_state = 1;
  }
  return car_state;
}

float PropulsionSystem::chooseMaxSpeed(char commands_from_ESP)
{
  switch (commands_from_ESP)
  {
  case 'c':
    calibrateLightSensors();
    break;
  case '+':
    maxSpeed += 50;
    commands_from_ESP = 3;

    break;

  case '-':
    maxSpeed -= 50;
    commands_from_ESP = 3;

    break;

  case 3:

    break;
  }
  return maxSpeed;
}

void PropulsionSystem::ESPdriveCommands(char commands_from_ESP)
{
  switch (commands_from_ESP)
  {
  case 'f':
    followLine();
    break;

  case 'w':
    for (int speed = 0; speed <= maxSpeed; speed++)
    {
      motors.setSpeeds(speed, speed);
    }
    break;

  case 'a':
    for (int speed = 0; speed <= maxSpeed; speed++)
    {
      motors.setSpeeds(0, speed);
    }
    break;

  case 's':
    for (int speed = 0; speed <= maxSpeed; speed++)
    {
      motors.setSpeeds(-speed, -speed);
    }
    break;

  case 'd':
    for (int speed = 0; speed <= maxSpeed; speed++)
    {
      motors.setSpeeds(speed, 0);
    }
    break;

  case 'x':
    motors.setSpeeds(0, 0);
    break;
  }
}

int PropulsionSystem::findChargingStation(int battery_level, int sun_luminance)
{
  if (battery_level < 50 && sun_luminance > 1800)
  {
    car_state = 2;
  }
  return car_state;
}