#include "SoftwareBatteri.h"

SoftwareBattery::SoftwareBattery()
{
  this->battery_health = 100;
  this->batteryLevel = 100;
  this->battery_health_level = 3;
  this->battery_capacity = 1200;
  this->charging_cycles = 0;
}

// Funksjon som tapper batteriet basert på momentanfart. Funksjonen kjøres hvert sekund i hovedfilen
int SoftwareBattery::batteryDrain(int vehicle_speed)
{
  float Kb = 0.01; // Batterikonstant for hvor mye batteriet skal tappes

  // Regner ut hvor mye batteriet skal tappes
  float battery_consumption = Kb * vehicle_speed; // mA
  // Trekker fra selve batteriet
  battery_capacity -= battery_consumption;
  battery_capacity = constrain(battery_capacity, 0, 1200);
  // Regner ut hvor mye batterikapasiteten er på i prosent
  batteryLevel = (battery_capacity / 1200) * 100; // Gitt i 100%

  return batteryLevel;
}

// Funksjon som lader opp bilen dersom den rygger. Blir kjørt dersom det registreres at bilen rygger og den har aktivert ryggelading
int SoftwareBattery::reverseCharge(int battery_level)
{
  // Øker sakte batteriprosenten
  battery_level += 0.025;
  battery_level = constrain(battery_level, 0, 100);

  return battery_level;
}

// Uferdig funksjon som skulle regne ut hvor mange runder batteriet har ladet. Var uvisst om funksjonen i seg selv skulle regne ut, eller om den skulle kalles på hver gang
// batteriet var ferdig med å motta lading
int SoftwareBattery::chargingCycles()
{
  charging_cycles += 1;
}

// Ufullstendig funksjon som tapper på batterihelsen basert på batterinivå, momentanfart og hvor lenge bilen har kjørt i høy hastighet
int SoftwareBattery::degradeBattery(int battery_level, float vehicle_speed, float seconds_passed_in_high_speeds)
{
  int Kbl = 0.5, Kvs = 0.5, Khs = 0.5; // Konstanter for å justere pådrag til batterihelsen
  // Regner ut hvor mye batteriet skal tape seg basert på de tre parameterene ganget med hvor mye hvert pådrag skal veie
  int battery_health_degrade = (Kbl * battery_level + Kvs * vehicle_speed + Khs * seconds_passed_in_high_speeds);
  // Trekker fra batterihelsen med det som er regnet ut
  battery_health -= battery_health_degrade;

  return battery_health;
}
