#include <Wire.h>
#include <Arduino.h>
#include <Zumo32U4.h>

Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors linesensor;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4Encoders encoders;

int car_state = 0;    // Styrer hele gangen i programmet

int maxSpeed = 400;
float batteryCapacity = 1200; // mAh
unsigned long batteryConsumption;
bool needs_charging;
int charging_port_count = 0;
int new_motor_counts = 0;


int Kp = 0.25;
int Td = 5;
int error;
int last_error;

int positions;
unsigned long countsLeft;
unsigned long countsRight;
unsigned long snittRotasjon = 1;
unsigned long forrige_snittRotasjon;
int vehicleSpeed;

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long batteryMillis = 0; 

// Tar i bruk alle 5 sensorer
unsigned int lineSensorValues[5];

#define STARTUP 0
#define DRIVING 1
#define CHARGING 2

Zumo32U4LCD display;


void setup() {
  Serial.begin(9600);
  linesensor.initFiveSensors();

  initialize();
}


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
  display.gotoXY(0,0);
  display.print(F("TRYKK A"));
}



void calibrate() {
  for (int i = 0; i < 55; i++) {
    linesensor.calibrate();
    motors.setSpeeds(200, -200);
  }
    motors.setSpeeds(0, 0);
}


 


int checkSensors() {
  positions = linesensor.readLine(lineSensorValues);
  return positions;
}


void speedometer() {
  snittRotasjon = (countsLeft + countsRight) / 2;
  countsRight = encoders.getCountsAndResetRight();
  countsLeft = encoders.getCountsAndResetLeft();
}




void displayFunc() {
   /*
  // Display counts
  display.clear();
  display.gotoXY(0, 0);
  display.print(charging_port_count);
  */

 
  // Display speed
  vehicleSpeed = (snittRotasjon *100) / 5000 ;
  display.clear();
  display.gotoXY(0, 0);
  display.print(vehicleSpeed);
  display.print(" cm/s");
  
  // Display battery
  float batteryPercent = (batteryCapacity / 1200) * 100; 
  display.gotoXY(0,1);
  display.print(batteryPercent);
  display.print(" %");
}



void motorRegulation(){
  checkSensors();       // Sjekker sensorene

  int wanted_positions = 2000;
  error = positions - wanted_positions;
  int speed_difference = (error * Kp) + Td *(error - last_error);
  int left_speed = maxSpeed + error;
  int right_speed = maxSpeed - error;

  left_speed = constrain((left_speed - speed_difference), 0, 400);
  right_speed = constrain((right_speed - speed_difference), 0, 400);

  motors.setSpeeds(left_speed, right_speed);
  }


void batteryDrain(){
    batteryConsumption = 2 * vehicleSpeed + 10; // mA 
    batteryCapacity -= batteryConsumption;

    if(batteryCapacity <= 300){
       needs_charging = true;      
      }
    else{
      needs_charging = false;
      }
  } 


void chargingStation(){

  int motor_counts = (encoders.getCountsLeft() + encoders.getCountsRight() ) / 2;

  // Restarer en teller hver gang motoren har rullet mer enn 1000 runder
  if(motor_counts - new_motor_counts >= 1000){
    new_motor_counts = motor_counts;

    charging_port_count = 0;
    }

  // Sjekker om sensorene registerer en verdi på 0 eller 4000
  if(positions == 0){
    delay(10);
    if(positions == 4000){
        charging_port_count += 1;
      }
    }
  
  if(needs_charging && charging_port_count >= 3){
      car_state = CHARGING;
      }
    
  }


void chargeBattery(){
    motors.setSpeeds(0,0);
    batteryCapacity += 5;
    
    // Display counts
    display.clear();
    display.gotoXY(0, 0);
    display.print(charging_port_count);


    // Display battery
    float batteryPercent = (batteryCapacity / 1200) * 100; 
    display.gotoXY(0,1);
    display.print(batteryPercent);
    display.print(" %");
    
    delay(100);
  }
  

void chooseSpeed(){
  if (buttonA.isPressed() ){
    
    display.clear();
    display.gotoXY(0, 0);
    display.print(maxSpeed);
        
    delay(1000);
    car_state = DRIVING;
    }
    
  while (buttonB.getSingleDebouncedPress() ){
    maxSpeed -= 50;
    
    display.clear();
    display.gotoXY(0, 0);
    display.print(maxSpeed);
    }
    
  while (buttonC.getSingleDebouncedPress() ){
    maxSpeed += 50;
    
    display.clear();
    display.gotoXY(0, 0);
    display.print(maxSpeed);
    }
  }



void loop() {
  
  currentMillis = millis();
  last_error = error;

  switch (car_state){
    case STARTUP:
    chooseSpeed();

    break;
    
    case DRIVING:  
      
      if (currentMillis - prevMillis >= 1000) {
        prevMillis = currentMillis;
        
        batteryDrain();          // Tapper batteriet
        speedometer();   // Sjekker hastigheten ved å telle antall rotasjoner på motoren
        displayFunc();            // Viser informasjon på displayet 
        
      }

      motorRegulation();        // Motorreguleringen som kjører bilen
      chargingStation();        // Sjekker om bilen trenger lading

    

    

    break;
    
    case CHARGING:

    chargeBattery();

    if(batteryCapacity >= 1100){
      needs_charging = false;
      car_state = DRIVING;
      break;

    break;
    
    }

  }


}