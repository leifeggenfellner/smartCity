#include "MarsRover.h"

// Batteriet::ZumoSWBattery battery;

unsigned long currentMillis;
unsigned long prevMillis = 0;
unsigned long prevMillis2 = 0;
float vehicleSpeed;
int maxSpeed = 400;

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

    currentMillis = millis();

    switch (car_state)
    {
    case STARTUP:

        maxSpeed = chooseSpeed2(ESPcommands);
        car_state = updateCarState2(ESPcommands);

        Serial.print("Car state  ");
        Serial.print(car_state);
        Serial.print("     Recieved from ESP  ");
        Serial.print(ESPcommands);
        Serial.print("     Max speed  ");
        Serial.println(maxSpeed);

        // maxSpeed = chooseSpeed(buttonB.getSingleDebouncedPress(), buttonC.getSingleDebouncedPress());
        // displayTopScreen(maxSpeed);
        // car_state = updateCarState(buttonA.isPressed());
        break;

    case DRIVING:

        distance_driven = distanceDriven(encoders.getCountsLeft(), encoders.getCountsRight()); // Regner ut hvor langt bilen har kjørt
                                                                                               // lineFollow(maxSpeed);                                                                          // Motorreguleringen som kjører bilen
                                                                                               //  chargingStation();        // Sjekker om bilen trenger lading
                                                                                               //  displayFunc();            // Viser informasjon på displayet

        recieveCommandsFromESP(ESPcommands);
        maxSpeed = chooseSpeed2(ESPcommands);

        // displayTopScreen(vehicleSpeed);
        // display.print(" cm/s");

        if (currentMillis - prevMillis >= 1000)
        {
            prevMillis = currentMillis;

            vehicleSpeed = gjennomsnittsHastighet(encoders.getCountsAndResetLeft(), encoders.getCountsAndResetRight()); // Sjekker hastigheten ved å telle antall rotasjoner på motoren
            battery_level = batteryDrain(vehicleSpeed);                                                                 // Tapper batteriet
        }

        break;

    case CHARGING:

        break;

    default:
        break;
    }
}
