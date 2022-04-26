#include <Arduino.h>
#include <Zumo32U4.h>
//#include "Ladestasjon.h"
#include "SoftWareBatteri.h"
#include "SpeedoMeter.h"
#include "Linjefolger.h"
#include "Display.h"

#define STARTUP 0
#define DRIVING 1
#define CHARGING 2

// Speedometeret::ZumoSpeedometer speedometer;