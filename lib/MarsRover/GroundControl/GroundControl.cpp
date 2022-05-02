#include "GroundControl.h"
#include <Zumo32U4Motors.h>
#include "PropulsionSystem.h"

static Zumo32U4Motors motors;


static int _maximum_speed = 400;
static int _car_state = 0;


int updateCarState(char commands_from_ESP){
  if(commands_from_ESP == 'l'){
    _car_state = 1;
  }
  return _car_state;
}




float chooseMaxSpeed(char commands_from_ESP)
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


void ESPdriveCommands(char commands_from_ESP){
  switch (commands_from_ESP) {
    case 'f':
      lineFollow(_maximum_speed);
    break;

    case 'w':
      for (int speed = 0; speed <= _maximum_speed; speed++) {
        motors.setSpeeds(speed, speed);
      }
      break;


    case 'a':
      for (int speed = 0; speed <= _maximum_speed; speed++) {
        motors.setSpeeds(0, speed);
      }
      break;


    case 's':
      for (int speed = 0; speed <= _maximum_speed; speed++) {
        motors.setSpeeds(-speed, -speed);
      }
      break;


    case 'd':
      for (int speed = 0; speed <= _maximum_speed; speed++) {
        motors.setSpeeds(speed, 0);
      }
      break;


    case 'x':
      motors.setSpeeds(0, 0);
      break;

  }
}

