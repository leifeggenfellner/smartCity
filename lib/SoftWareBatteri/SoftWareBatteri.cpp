#include "SoftWareBatteri.h"
#include <Zumo32U4.h>

// using namespace Batteriet;

// static Zumo32U4Encoders encoders;

SoftwareBattery::SoftwareBattery()
{
  this->battery_health = 100;
  this->battery_level = 100;
  this->battery_capacity = 1200;
}

float SoftwareBattery::batteryDrain(float vehicle_speed)
{
  float Kb = 0.15; // Batterikonstant for hvor mye batteriet skal tappes

  float battery_consumption = Kb * vehicle_speed; // mA
  battery_capacity -= battery_consumption;
  battery_capacity = constrain(battery_capacity, 0, 1200);
  battery_level = (battery_capacity / 1200) * 100; // Gitt i 100%

  return battery_level;
}

// Deklarerer variabler
// float account_balance = 0;
// float charging_cycles = 0;
// float battery_health = 100;
// float charging_cost = 10;
// static float battery_level = 100;
// float battery_capacity = 1200; // mAh
// bool needs_charging = false;
// bool battery_dead = false;

// float batteryDrain(float vehicle_speed)
// {
//   float Kb = 0.15; // Batterikonstant for hvor mye batteriet skal tappes

//   float battery_consumption = Kb * vehicle_speed; // mA
//   battery_capacity -= battery_consumption;
//   battery_capacity = constrain(battery_capacity, 0, 1200);
//   battery_level = (battery_capacity / 1200) * 100; // Gitt i 100%

//   return battery_level;
// }

/*
  if (battery_level < 20)
  {
    needs_charging = true;
  }
  else if (battery_level == 0)
  {
    battery_dead = true;
  }
  else
  {
    needs_charging = false;
  }
  */

/*
void loop(){
  battery_life bl;
  int vehiclespeed;
  bl.batteryDrain(vehiclespeed);

}
*/
