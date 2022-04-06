#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>


Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors linesensor;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4Encoders encoders;

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  motors.setSpeeds(0, 0);
}

void driveCommands(char commands_from_ESP) {

  switch (commands_from_ESP) {
    case 'w':
      for (int speed = 0; speed <= 100; speed++) {
        motors.setSpeeds(speed, speed);
      }
      break;


    case 'a':
      for (int speed = 0; speed <= 100; speed++) {
        motors.setSpeeds(0, speed);
      }
      break;


    case 's':
      for (int speed = 0; speed <= 100; speed++) {
        motors.setSpeeds(-speed, -speed);
      }
      break;


    case 'd':
      for (int speed = 0; speed <= 100; speed++) {
        motors.setSpeeds(speed, 0);
      }
      break;


    case 'x':
      motors.setSpeeds(0, 0);
      break;

  }
}

void loop() {

  while (Serial1.available()) {
    char ESPcommands = (char)Serial1.read();
    Serial.println(ESPcommands);
    driveCommands(ESPcommands);
  }

}