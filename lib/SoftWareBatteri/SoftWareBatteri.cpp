#include "SoftWareBatteri.h"

// using namespace Batteriet;

// static Zumo32U4Encoders encoders;

// Deklarerer variabler
float account_balance = 0;
float charging_cycles = 0;
float battery_health = 100;
float charging_cost = 10;
//int battery_health = 2;
static float battery_level = 100;
float battery_capacity = 1200; // mAh
bool needs_charging = false;
bool battery_dead = false;
int charge_mode;

#define level_0 0
#define level_1 1
#define level_2 2

float batteryDrain(float vehicle_speed)
{
  float Kb = 0.15; // Batterikonstant for hvor mye batteriet skal tappes

  float battery_consumption = Kb * vehicle_speed; // mA
  battery_capacity -= battery_consumption;
  battery_capacity = constrain(battery_capacity, 0, 1200);
  battery_level = (battery_capacity / 1200) * 100; // Gitt i 100%

  return battery_level;
}

float reverseCharge()
{
  battery_level += 0.025;
  battery_level = constrain(battery_level, 0, 100);

  return battery_level;
}

int checkBatteryState(int battery_level)
{
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
  return needs_charging;
}

/*
int batteryHealthCheck(float battery_level, float vehicle_speed, float maximum_speed){

    switch (battery_health)
    {
    case level_0:
      /* code */
     // break;
   // case level_1:
      /* code */
      //break;
    
   // case level_2:
      /* code */
     // break;
    
    //default:
     // break;
  //  }

//}   

