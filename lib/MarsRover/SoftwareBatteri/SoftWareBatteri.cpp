#include "SoftwareBatteri.h"

SoftwareBattery::SoftwareBattery()
{
  this->battery_health = 100;
  this->battery_level = 100;
  this->battery_health_level = 3;
  this->battery_capacity = 1200;
  this->charging_cycles = 0;
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

float SoftwareBattery::reverseCharge()
{
  battery_level += 0.025;
  battery_level = constrain(battery_level, 0, 100);

  return battery_level;
}

int SoftwareBattery::chargingCycles()
{
  charging_cycles += 1;
}

int SoftwareBattery::batteryHealthCheck(int battery_level, float vehicle_speed, float maximum_speed)
{

  if (battery_health > 70)
  {
    battery_health_level = level_3;
  }
  else if (battery_health < 70 && battery_health >= 40)
  {
    battery_health_level = level_2;
  }
  else if (battery_health < 40 && battery_health >= 10)
  {
    battery_health_level = level_1;
    // Batteriet må på service
  }
  else if (battery_health < 10)
  {
    battery_health_level = level_0;
    // Batteriet må byttes
  }

  switch (battery_health_level)
  {
  case level_0:
    // Batteriet må byttes
    break;
  case level_1:
    /* code */
    break;

  case level_2:
    /* code */
    break;

  case level_3:
    /* code */
    break;

  default:
    break;
  }
  return battery_health;
}
