#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors linesensor;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4Encoders encoders;

// Liste over variabler som er gitt i oppgaven
int battery_level = 100;
int charging_cycles = 0;
int battery_health = 100;
int battery_health_counter = 3; 
int account_balance = 2000 ; // Kr
int charging_cost;


    int batteryConsumption;
    int batteryCapacity;
    int vehicleSpeed;
    bool needs_charging;

// Definerer ting
#define level_3 3
#define level_2 2
#define level_1 1 
#define level_0 0 

void setup() {
  // put your setup code here, to run once:

}


void batteryDrain(){

    batteryConsumption = 2 * vehicleSpeed + 10; // mA 
    battery_level -= batteryConsumption;  

    if(batteryCapacity <= 300){
       needs_charging = true;      
      }
    else{
      needs_charging = false;
      }
  
  }




void loop() {

  switch (battery_health_counter){
    case level_3:

    break;


    case level_2:

    break;

    case level_1:

    break;

    case level_0:

    break;


    
    }

}