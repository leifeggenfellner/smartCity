#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>

void sensorsCalibrate();
void lineFollow(uint16_t maximum_speed);
void startCalibration();
void recieveCommandsFromESP(char commands_from_ESP);
 