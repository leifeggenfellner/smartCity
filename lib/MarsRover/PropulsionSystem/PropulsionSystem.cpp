#include <Arduino.h>
#include "PropulsionSystem.h"

int sun_luminance = 0;

PropulsionSystem::PropulsionSystem(Zumo32U4Motors objMotors, uint16_t objMaxSpeed, Zumo32U4Buzzer objBuzzer, Zumo32U4LineSensors objLineSensors) : motors{objMotors}, maxSpeed{objMaxSpeed}, buzzer{objBuzzer}, lineSensors{objLineSensors}
{
  this->car_state = 0;
  this->lastError = 0;
  this->follow_line = false;
  this->maxSpeed = 400;
};

void PropulsionSystem::Calibrate2()
{
  lineSensors.initFiveSensors();
  for (int i = 0; i < 65; i++)
  {
    lineSensors.calibrate();
    motors.setSpeeds(200, -200);
  }
  motors.setSpeeds(0, 0);
}

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

int PropulsionSystem::manuallyChangeCarState(bool button_A, bool button_B, bool button_C)
{
  if (button_A)
  {
    car_state = 0;
    button_A = false;
  }
  if (button_B)
  {
    car_state = 1;
    button_B = false;
  }
  if (button_C)
  {
    car_state = 2;
    button_C = false;
  }

  return car_state;
}

void PropulsionSystem::followLine()
{
  int Kp = 0.25, Td = 5;

  int16_t position = lineSensors.readLine(lineSensorValues);
  int16_t error = position - 2000;
  int8_t speedDifference = (error *Kp) + Td * (error - lastError);

  lastError = error;

  int8_t leftSpeed = 400 + error;
  int8_t rightSpeed = 400 - error;

  leftSpeed = constrain((leftSpeed), 0, 400);
  rightSpeed = constrain((rightSpeed), 0, 400);
  /*
  Serial.print("Position: ");
  Serial.print(position);
  Serial.print("   ");
  Serial.print("Error: ");
  Serial.print(error);
  Serial.print("   ");
  Serial.print("speed difference: ");
  Serial.print(speedDifference);
  Serial.print("   ");
  Serial.print("Last error: ");
  Serial.print(lastError);
  Serial.print("   ");
  Serial.print("Left speed");
  Serial.print(leftSpeed);
  Serial.print("   ");
  Serial.print("Right speed: ");
  Serial.println(rightSpeed);
 */
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

  case 'c': // Kalibrerer linjesensorene
    // calibrateLightSensors();
    Calibrate2();
    break;
  case '+': // Øker makshastighet med 50
    maxSpeed += 50;
    commands_from_ESP = 3;

    break;

  case '-': // Senker makshastighet med 50
    maxSpeed -= 50;
    commands_from_ESP = 3;

    break;

  case 3: // Tom case som fungerer som deafult

    break;
  }
  return maxSpeed;
}

void PropulsionSystem::ESPdriveCommands(char commands_from_ESP)
{
  float x = 0.025, y = 0.5;
  switch (commands_from_ESP)
  {
    /*
  case 'i':
    sun_luminance = Serial1.readStringUntil(";");
    Serial.println(sun_luminance);
    break;*/
    /*
      case 'f': // Linjefølging
        // followLine();
        break;*/

  case 'w': // Kjører fremover
    for (float speed = 0; speed <= maxSpeed; speed = speed + x)
    {
      motors.setSpeeds(speed, speed);
      follow_line = false;
    }
    break;

  case 'a': // Kjører mot venstre
    for (float speed = 0; speed <= maxSpeed; speed = speed + y)
    {
      motors.setSpeeds(-speed / 4, speed / 4);
      follow_line = false;
    }
    break;

  case 's': // Rygger
    for (float speed = 0; speed <= maxSpeed; speed = speed + x)
    {
      motors.setSpeeds(-speed / 4, -speed / 4);
      follow_line = false;
    }
    break;

  case 'd': // Kjører mot høyre
    for (float speed = 0; speed <= maxSpeed; speed = speed + y)
    {
      motors.setSpeeds(speed / 3, -speed / 3);
      follow_line = false;
    }
    break;

  case 'x': // Bilen stopper
    motors.setSpeeds(0, 0);
    follow_line = false;
    break;
  }
}

int PropulsionSystem::measureSunlight(String string_commands_from_ESP)
{
  int sun_luminance_int;
  if (string_commands_from_ESP[0] == "i")
  {
    String sun_luminance = Serial1.readStringUntil(';');
    sun_luminance_int = sun_luminance.toInt();
  }
  return sun_luminance_int;
}

/*
int PropulsionSystem::findChargingStation(int battery_level, int sun_luminance)
{
  if (battery_level < 50 && sun_luminance > 1800)
  {
    car_state = 2;
  }
  return car_state;
}*/
