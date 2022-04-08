#include <Wire.h>
#include <Zumo32U4.h>

unsigned long currentMillis;
unsigned long prevMillis = 0;
unsigned long prevMillis2 = 0;

int teitVariabel = 0;
float millis_passed_in_high_speeds = 0;


int motorPaadrag = 0;

Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors linesensor;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4Encoders encoders;

void setup() {
  Serial.begin(9600);

}



int gjennomsnittsHastighet() {
  float countsRight = encoders.getCountsAndResetRight();
  float countsLeft = encoders.getCountsAndResetLeft();
  float meanRotation = (countsLeft + countsRight) / 2;
  float vehicleSpeed = (meanRotation * 100) / 5000;

  return vehicleSpeed;
}


int maksHastighet(float vehicle_speed) {
  float maximum_velocity;
  if (vehicle_speed >=  maximum_velocity) {
    maximum_velocity = vehicle_speed;
  }
  return maximum_velocity;
}


void sekunderOver70(float vehicle_speed, float maximum_velocity) {
  //static int millis_passed_in_high_speeds;
  //float seconds_passed_in_high_speeds = millis_passed_in_high_speeds / 100;

  if (vehicle_speed >= 70 * 0.70) {

    if (currentMillis - prevMillis2 >= 1) {
      prevMillis2 = currentMillis;

      millis_passed_in_high_speeds += 1;

    }

  }

  //return millis_passed_in_high_speeds;
}



void mainFunc() {
  int vehicleSpeed;
  int maxVelocity;
  int highSpeedTime;


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


void loop() {

  currentMillis = millis();

  int vehicleSpeed;
  int maxVelocity;
  int highSpeedTime;


  // resetter variabler i starten av programmet
  if (currentMillis < 100) {
    maxVelocity = 50;
    vehicleSpeed = 0;
    highSpeedTime = 0;
  }


  if (currentMillis - prevMillis >= 2000) {
    prevMillis = currentMillis;

    // returnerer gjennomsnittshastighet (vehicleSpeed)
    vehicleSpeed = gjennomsnittsHastighet();

    motorPaadrag = random(300);

  }

  maxVelocity = maksHastighet(vehicleSpeed);


  // Tar inn (momentanfarten til bilen, maksfarten som er målt under kjøring)
  //highSpeedTime = sekunderOver70(vehicleSpeed, maxVelocity);
  //Serial.println(highSpeedTime);



  sekunderOver70(vehicleSpeed, maxVelocity);
  Serial.println(millis_passed_in_high_speeds);

  /*
    if (currentMillis > 3000) {
    teitVariabel += 1;

    Serial.println(teitVariabel);
    }
  */

  motors.setSpeeds(motorPaadrag, motorPaadrag);

  //mainFunc();


}