
#include "Speedometer.h"
#include <Zumo32U4.h>

// using namespace Speedometeret;

/*
int teitVariabel = 0;
float millis_passed_in_high_speeds = 0;
*/

Speedometer::Speedometer()
{
  this->maximum_velocity = 0;
  this->seconds_passed_in_high_speeds = 0;
  static unsigned long currentMillis = millis();
  static unsigned long prevMillis2 = 0;
  uint32_t totalCounts;
  uint16_t distance_driven = 0;
  int maximum_speed = 400;
}
// static unsigned long backingUpCounts;
// long distanceBackedUp;

float Speedometer::gjennomsnittsHastighet(uint32_t countsLeft, uint32_t countsRight)
{
  float meanRotation = (countsLeft + countsRight) / 2;
  float vehicleSpeed = (meanRotation * 100) / 5000;

  return vehicleSpeed;
}

float Speedometer::maksHastighet(float vehicle_speed)
{
  if (vehicle_speed >= maximum_velocity)
  {
    maximum_velocity = vehicle_speed;
  }
  return maximum_velocity;
}

float Speedometer::highSpeedTime(float vehicle_speed)
{
  Serial.println(currentMillis);

  // static int millis_passed_in_high_speeds;
  // float seconds_passed_in_high_speeds = millis_passed_in_high_speeds / 100;

  if (vehicle_speed >= maximum_velocity * 0.70)
  {

    if (currentMillis - prevMillis2 >= 1000)
    {
      prevMillis2 = currentMillis;
      Serial.println("Hei");
      seconds_passed_in_high_speeds += 1;
    }
  }
  Serial.println(seconds_passed_in_high_speeds);

  return seconds_passed_in_high_speeds;
}

int Speedometer::chooseSpeed(bool button_B_pressed, bool button_C_pressed)
{
  while (button_B_pressed)
  {
    maximum_speed -= 50;
  }

  while (button_C_pressed)
  {
    maximum_speed += 50;
  }
  return maximum_speed;
}

void Speedometer::distanceDriven(uint32_t countsLeft, uint32_t countsRight)
{

  long countsBoth = (countsLeft + countsRight) / 2;

  if (countsBoth > 0)
  {
    totalCounts += countsBoth;
    distance_driven = totalCounts / 500000; // Gir distance i meter
  }
  /*

  // Sjekker om bilen rygger
  else if (countsBoth < 0)
  {
    backingUpCounts -= countsBoth;
    distanceBackedUp = backingUpCounts / 5000; // Gitt i cm

    if (needs_charging)
    {
      _car_state = CHARGING;
      charge_mode = BACKING;
      display_mode = 2;
    }
  }

  // Hvis bilen ikke rygger og nødlading ikke er aktivert
  else if (countsBoth > 0 && charge_mode != EMERGENCY)
  {
    charge_mode = CHARGEPORT;
    _car_state = DRIVING;
    display_mode = 0;
  }
*/
}

/*
void initialize() {

  display.clear();
  display.gotoXY(0, 0);
  display.print(F("KALIBRER"));
  display.gotoXY(0, 1);
  display.print(F("TRYKK A"));

  buttonA.waitForButton();

  delay(1000);

  display.clear();
  display.gotoXY(0, 0);
  display.print(F("Kalibrerer"));
  display.gotoXY(0, 1);
  display.print(F("..."));

  calibrate();
  display.clear();
  display.gotoXY(0, 0);
  display.print(F("TRYKK A"));
}
*/

/*
void mainFunc() {
  float vehicleSpeed;
  float maxVelocity;
  float highSpeedTime;


  // resetter variabler i starten av programmet
  if (currentMillis < 100) {
    maxVelocity = 50;
    vehicleSpeed = 0;
    highSpeedTime = 0;
  }


  if (currentMillis - prevMillis >= 1000) {
    prevMillis = currentMillis;

    // returnerer gjennomsnittshastighet (vehicleSpeed)
    vehicleSpeed = gjennomsnittsHastighet();

    motorPaadrag = random(300);

  }

  maxVelocity = maksHastighet(vehicleSpeed);


  // Tar inn (momentanfarten til bilen, maksfarten som er målt under kjøring)
  //highSpeedTime = sekunderOver70(vehicleSpeed, maxVelocity);
  //Serial.println(highSpeedTime);


}
*/