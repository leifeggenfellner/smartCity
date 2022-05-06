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

// Funksjon som regner ut momentanhastigheten til bilen. Tar inn countsLeft og countsRight som parametere
int Speedometer::currentSpeed(uint16_t countsLeft, uint16_t countsRight)
{
  float vehicleSpeed;
  int16_t counts_both = countsLeft + countsRight;
  // Sjekker om bilen kjører fremover ved å sjekke at summen av tellinger på hjulene ikke er under 0
  if (counts_both >= 0)
  {
    // Dersom bilen ikke rygger så er snittrotasjonen på hjulene lik summen delt på 2
    float meanRotation = (countsLeft + countsRight) / 2;
    // Funksjonen kjøres hvert sekund i hovedfilen, dermed blir farten [cm/s] gitt som snittrotasjonen delt på 5000 [rotasjoner per meter]
    // Ganget med 100 cm for å oppnå enheten centimeter per sekund
    vehicleSpeed = (meanRotation * 100) / 5000;
  }
  // Sjekker om bilen rygger
  else if (counts_both < 0)
  {
    // Hvis bilen rygger vil snittrotasjonen fortsatt være summen av rotasjonene, men med omvendt fortegn
    float meanRotation = (-counts_both) / 2;
    // Farten regnes ut på samme vis
    vehicleSpeed = (meanRotation * 100) / 5000;
  }
  return vehicleSpeed;
}

// Funksjon som registrerer den høyest målte farten
int Speedometer::recordMaxVelocity(float vehicle_speed)
{
  // Sjekker om momentanfarten er høyere enn tidligere registrert maksfart
  if (vehicle_speed >= maximum_velocity)
  {
    // Oppdaterer da høyest registrert fart
    maximum_velocity = vehicle_speed;
  }
  return maximum_velocity;
}

// Funksjon som regner ut hvor lenge bilen har kjørt over 70% av makshastighet
float Speedometer::highSpeedTime(float vehicle_speed)
{
  // Makshastigheten blir oppdatert og lagret lokalt i klassen
  maximum_velocity = Speedometer::recordMaxVelocity(vehicle_speed);
  // Sjekker om momentanfarten er større eller lik maksfarten ganget med 70%
  if (vehicle_speed >= maximum_velocity * 0.70)
  {
    // Går inn i if-setningen hvert 100 millisekund for å registrere målinger
    if (currentMillis - prevMillis >= 100)
    {
      prevMillis = currentMillis;
      // Legger til 0.1 sekund hvor hvert 100 millisekund som har passert i høy fart
      seconds_passed_in_high_speeds += 0.1;
    }
  }
  return seconds_passed_in_high_speeds;
}

// Funksjon som regner ut gjennomsnittshastighet over 60 sekunder
int Speedometer::averageSpeed(float vehicle_speed)
{
  int total_speed;
  int average_velocity;
  // Går inn i if-setningen hvert 10ende sekund
  if (currentMillis - prevMillis >= 10 * 1000)
  {
    prevMillis = currentMillis;
    // Oppdaterer en variabel med 1 for hvert tiende sekund
    sampling_count += 1;
    // Tar da en måling av momentanhastigheten
    int current_speed = vehicle_speed;
    // Legger til alle målinger i en totalsum
    total_speed += current_speed;
  }
  // Sjekker etter det er foretatt 6 målinger, dvs 6 ganger 10 sekunder (60 sekunder)
  if (sampling_count >= 6)
  {
    // Regner ut gjennomsnittshastigheten som totalsummen av fart delt på antall målinger
    average_velocity = total_speed / sampling_count;
    // Tilbakestiller målevariabel og totalsummen av fart
    sampling_count = 0;
    total_speed = 0;
  }
  return average_velocity;
}

// Funksjon hvor man kan velge maksfart på bilen. Ble hovedsakelig brukt før skykommunikasjon ble opprettet
int Speedometer::chooseSpeed(bool button_B_pressed, bool button_C_pressed)
{
  while (button_B_pressed)
  {
    // Reduserer maksfart med 50 dersom man trykker knapp B
    maximum_speed -= 50;
  }
  while (button_C_pressed)
  {
    // Øker maksfart med 50 dersom man trykker knapp A
    maximum_speed += 50;
  }
  return maximum_speed;
}

// Funksjon for å registrere hvor langt bilen har kjørt
uint16_t Speedometer::distanceDriven(uint32_t countsLeft, uint32_t countsRight)
{
  // Snitt av hvor mange rotasjoner som er gjort på hjulene
  long countsBoth = (countsLeft + countsRight) / 2;
  // Sjekker at bilen ikke rygger
  if (countsBoth > 0)
  {
    // legger til all rotasjoner så lenge bilen kjører fremover
    total_counts += countsBoth;
    // Avstand blir regnet ut basert på at det er 5000 rotasjoner per meter. Derfor er det ingen som skjønner hvorfor man skal
    // dele på 500 000, men det gir ut ca en meter så vi er fornøyd med det
    distance_driven = total_counts / 500000; // Gir distance i meter
  }
  return distance_driven;
}