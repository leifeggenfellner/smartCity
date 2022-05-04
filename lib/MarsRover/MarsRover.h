#include <Arduino.h>
#include <Zumo32U4.h>
#include "Ladestasjon/Ladestasjon.h"
#include "SoftwareBatteri/SoftWareBatteri.h"
#include "Speedometer/Speedometer.h"
#include "PropulsionSystem/PropulsionSystem.h"

#define STARTUP 0
#define DRIVING 1
#define CHARGING 2