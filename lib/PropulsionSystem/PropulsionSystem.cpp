#include <Wire.h>
#include <Zumo32U4.h>

// static const uint16_t maxSpeed = 400;

static Zumo32U4LineSensors lineSensors;
static Zumo32U4Motors motors;
static Zumo32U4ButtonA buttonA;
static Zumo32U4LCD display;

int16_t lastError = 0;
static int _maximum_speed = 400;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

void sensorsCalibrate()
{
  delay(1000);
  for (uint16_t i = 0; i < 120; i++)
  {
    motors.setSpeeds(200, -200);
    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}

void startCalibration()
{
  lineSensors.initFiveSensors();

  // buzzer.play(">g32>>c32");

  /*
    display.clear();
    display.print(F("Press A"));
    display.gotoXY(0, 1);
    display.print(F("to calib"));
    buttonA.waitForButton();
  */
  sensorsCalibrate();

  lineSensors.readCalibrated(lineSensorValues);

  display.clear();
  display.print(F("Press A"));
  display.gotoXY(0, 1);
  display.print(F("to start"));
  // buttonA.waitForButton();
  display.clear();
}

float chooseSpeed2(char commands_from_ESP)
{
  switch (commands_from_ESP)
  {
  case 'c':
    sensorsCalibrate();
    break;
  case '+':
    _maximum_speed += 50;
    commands_from_ESP = 3;

    break;

  case '-':
    _maximum_speed -= 50;
    commands_from_ESP = 3;

    break;

  case 3:

    break;
  }
  return _maximum_speed;
}

void lineFollow(uint16_t _maximum_speed)
{

  int16_t position = lineSensors.readLine(lineSensorValues);
  int16_t error = position - 2000;
  int16_t speedDifference = error / 4 + 6 * (error - lastError);

  lastError = error;

  int16_t leftSpeed = (int16_t)_maximum_speed + speedDifference;
  int16_t rightSpeed = (int16_t)_maximum_speed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)_maximum_speed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)_maximum_speed);

  motors.setSpeeds(leftSpeed, rightSpeed);
}

void recieveCommandsFromESP(char commands_from_ESP)
{

  switch (commands_from_ESP)
  {
  case 'f':
    lineFollow(_maximum_speed);
    break;

  case 'w':
    for (int speed = 0; speed <= _maximum_speed; speed++)
    {
      motors.setSpeeds(speed, speed);
    }
    break;

  case 'a':
    for (int speed = 0; speed <= _maximum_speed; speed++)
    {
      motors.setSpeeds(0, speed);
    }
    break;

  case 's':
    for (int speed = 0; speed <= _maximum_speed; speed++)
    {
      motors.setSpeeds(-speed, -speed);
    }
    break;

  case 'd':
    for (int speed = 0; speed <= _maximum_speed; speed++)
    {
      motors.setSpeeds(speed, 0);
    }
    break;

  case 'x':
    motors.setSpeeds(0, 0);
    break;
  }
}
