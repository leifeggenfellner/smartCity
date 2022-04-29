#include "MarsRover.h"


unsigned long currentMillis;
unsigned long prevMillis = 0;
unsigned long prevMillis2 = 0;
float vehicleSpeed;
int max_speed = 400;

int distance_driven;
float battery_level;

int car_state = 0;
int display_mode = 0;

Zumo32U4Encoders encoders;
Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors linesensor;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
Zumo32U4LCD display;


void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);
}



void loop()
{

    char ESPcommands = (char)Serial1.read();
    String ESPstringCommands = (String)Serial1.read();
    currentMillis = millis();

    switch (car_state)
    {
    case STARTUP:
        max_speed = chooseMaxSpeed(ESPcommands);
        car_state = updateCarState(ESPcommands);

        /* //Dette er bare brukt for debugging
        Serial.print("Car state  ");
        Serial.print(car_state);
        Serial.print("     Recieved from ESP  ");
        Serial.print(ESPcommands);
        Serial.print("     Max speed  ");
        Serial.println(max_speed);
        */

        break;

    case DRIVING:

        distance_driven = distanceDriven(encoders.getCountsLeft(), encoders.getCountsRight()); // Regner ut hvor langt bilen har kjørt
        ESPdriveCommands(ESPcommands);    // Tar imot kjørekommandoer fra ESP
        max_speed = chooseMaxSpeed(ESPcommands);   // Velger makshastighet via ESP
        

        if (currentMillis - prevMillis >= 1000)
        {
            prevMillis = currentMillis;

            vehicleSpeed = currentSpeed(encoders.getCountsAndResetLeft(), encoders.getCountsAndResetRight()); // Sjekker hastigheten ved å telle antall rotasjoner på motoren
            battery_level = batteryDrain(vehicleSpeed);                                                                 // Tapper batteriet
        }

        break;

    case CHARGING:

        break;

    default:
        break;
    }

}
