#include <Arduino.h>
#include <Zumo32U4.h>
#include "Ladestasjon.h"
#include "SoftWareBatteri.h"
#include "SpeedoMeter.h"
#include "PropulsionSystem.h"
#include "Display.h"

enum State
{
    STARTUP = 0,
    DRIVING = 1,
    CHARGING = 2
}

// Speedometeret::ZumoSpeedometer speedometer;