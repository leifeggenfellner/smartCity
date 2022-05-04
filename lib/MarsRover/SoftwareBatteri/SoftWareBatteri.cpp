#include "SoftwareBatteri.h"

SoftwareBattery::SoftwareBattery()
{
  this->battery_health = 100;
  this->batteryLevel = 100;
  this->battery_health_level = 3;
  this->battery_capacity = 1200;
  this->charging_cycles = 0;
}


int SoftwareBattery::batteryDrain(int vehicle_speed)
{
  float Kb = 0.01; // Batterikonstant for hvor mye batteriet skal tappes

  float battery_consumption = Kb * vehicle_speed; // mA
  battery_capacity -= battery_consumption;
  battery_capacity = constrain(battery_capacity, 0, 1200);
  batteryLevel = (battery_capacity / 1200) * 100; // Gitt i 100%

  return batteryLevel;
}


int SoftwareBattery::reverseCharge(int battery_level)
{
  battery_level += 0.025;
  battery_level = constrain(battery_level, 0, 100);

  return battery_level;
}

int SoftwareBattery::chargingCycles()
{
  charging_cycles += 1;
}


int SoftwareBattery::degradeBattery(int battery_level, float vehicle_speed, float seconds_passed_in_high_speeds)
{
  int Kbl = 0.5, Kvs = 0.5, Khs = 0.5; // Konstanter for å justere pådrag til batterihelsen
  int battery_health_degrade = (Kbl * battery_level + Kvs * vehicle_speed + Khs * seconds_passed_in_high_speeds);
  battery_health -= battery_health_degrade;

  return battery_health;
}
