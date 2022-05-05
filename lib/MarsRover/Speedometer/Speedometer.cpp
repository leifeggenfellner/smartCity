#include "Speedometer.h"

Speedometer::Speedometer()
{
  this->maximum_velocity = 0;
  this->seconds_passed_in_high_speeds = 0;
  this->currentMillis = millis();
  this->prevMillis = 0;
  this->total_counts = 0;
  this->distance_driven = 0;
  this->maximum_speed = 400;
  this->sampling_count = 0;
}

int Speedometer::currentSpeed(uint16_t countsLeft, uint16_t countsRight)
{
  float vehicleSpeed;
  int16_t counts_both = countsLeft + countsRight;
  if (counts_both >= 0)
  {
    float meanRotation = (countsLeft + countsRight) / 2;
    vehicleSpeed = (meanRotation * 100) / 5000;
  }
  else if (counts_both < 0)
  {
    float meanRotation = (-counts_both) / 2;
    vehicleSpeed = (meanRotation * 100) / 5000;
  }
  return vehicleSpeed;
}

int Speedometer::recordMaxVelocity(float vehicle_speed)
{
  if (vehicle_speed >= maximum_velocity)
  {
    maximum_velocity = vehicle_speed;
  }
  return maximum_velocity;
}

float Speedometer::highSpeedTime(float vehicle_speed)
{
  maximum_velocity = Speedometer::recordMaxVelocity(vehicle_speed);
  if (vehicle_speed >= maximum_velocity * 0.70)
  {
    if (currentMillis - prevMillis >= 100)
    {
      prevMillis = currentMillis;
      seconds_passed_in_high_speeds += 0.1;
    }
  }
  return seconds_passed_in_high_speeds;
}

int Speedometer::averageSpeed(float vehicle_speed)
{
  int total_speed;
  int average_velocity;
  if (currentMillis - prevMillis >= 10 * 1000)
  {
    prevMillis = currentMillis;
    sampling_count += 1;
    int current_speed = vehicle_speed;
    total_speed += current_speed;
  }
  if (sampling_count >= 6)
  {
    average_velocity = total_speed / sampling_count;
    sampling_count = 0;
    total_speed = 0;
  }
  return average_velocity;
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

uint16_t Speedometer::distanceDriven(uint32_t countsLeft, uint32_t countsRight)
{
  long countsBoth = (countsLeft + countsRight) / 2;
  if (countsBoth > 0)
  {
    total_counts += countsBoth;
    distance_driven = total_counts / 500000; // Gir distance i meter
  }
  return distance_driven;
}