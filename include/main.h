#pragma once

#include <stdint.h>
#include "Marsrover.h"

Zumo32U4Encoders encoders;
Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors linesensor;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4LCD display;
Speedometer speedometer;
SoftwareBattery battery;
PropulsionSystem driving(motors, max_speed, buzzer, linesensor);