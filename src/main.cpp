#include "Marsrover.h"

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
Speedometer speedometer;
SoftwareBattery battery;
PropulsionSystem driving(motors, max_speed, buzzer, linesensor);

void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);
}

/* //Dette er bare brukt for debugging
Serial.print("Car state  ");
Serial.print(car_state);
Serial.print("     Recieved from ESP  ");
Serial.print(ESPcommands);
Serial.print("     Max speed  ");
Serial.println(max_speed);
*/

void loop()
{
    currentMillis = millis();
    // int sun_luminance = analogRead(14);
    char ESPcommands = (char)Serial1.read();
    // String ESPstringCommands = (String)Serial1.read();

    switch (car_state)
    {
    case STARTUP:
        max_speed = driving.chooseMaxSpeed(ESPcommands);
        car_state = driving.updateCarState(ESPcommands);

        break;

    case DRIVING:

        speedometer.distanceDriven(encoders.getCountsLeft(), encoders.getCountsRight()); // Regner ut hvor langt bilen har kjørt
        driving.ESPdriveCommands(ESPcommands);                                           // Tar imot kjørekommandoer fra ESP
        max_speed = driving.chooseMaxSpeed(ESPcommands);                                 // Velger makshastighet via ESP

        if (currentMillis - prevMillis >= 1000)
        {
            prevMillis = currentMillis;

            vehicleSpeed = speedometer.currentSpeed(encoders.getCountsAndResetLeft(), encoders.getCountsAndResetRight()); // Sjekker hastigheten ved å telle antall rotasjoner på motoren
            battery_level = battery.batteryDrain(vehicleSpeed);                                                           // Tapper batteriet
            Serial1.print((String)battery_level);
            Serial1.print(";");
        }

        break;

    case CHARGING:

        break;

    default:
        break;
    }
}
