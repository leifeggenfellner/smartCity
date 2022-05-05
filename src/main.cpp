#include "Marsrover.h"

unsigned long currentMillis;
unsigned long prevMillis = 0;
unsigned long prevMillis2 = 0;
int vehicleSpeed;
int max_speed = 400;

uint32_t distance_driven;

int car_state = 0;
bool needs_charging = false;

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

void loop()
{
    char ESPcommands = (char)Serial1.read(); // Avleser kommandoer som kommer fra ESP32
    currentMillis = millis();

    car_state = driving.manuallyChangeCarState(buttonA.isPressed(), buttonB.isPressed(), buttonC.isPressed()); // Funksjon som overstyrer hvilken status bilen er i

    switch (car_state)
    {
    case STARTUP:
        // Case hvor bilen er i oppstart.

        max_speed = driving.chooseMaxSpeed(ESPcommands); // Velger makshastighet via ESP32 og Node-RED
        car_state = driving.updateCarState(ESPcommands); // Venter på kommando fra Node-RED for å oppdatere status til kjøring
        break;

    case DRIVING:
        // Case hvor bilen er i kjøremodus

        while (driving.follow_line) // Når bilen skal være i linjefølgemodus
        {
            driving.followLine();
        }
        if (ESPcommands == 'f')
        {
            driving.follow_line = true;
        }
        else
        {
            driving.ESPdriveCommands(ESPcommands); // Tar imot kjørekommandoer fra ESP
        }

        speedometer.distanceDriven(encoders.getCountsLeft(), encoders.getCountsRight()); // Regner ut hvor langt bilen har kjørt
        max_speed = driving.chooseMaxSpeed(ESPcommands);                                 // Velger makshastighet via ESP
        int averageSpeed = speedometer.averageSpeed(vehicleSpeed);
        int highSpeedTime = speedometer.highSpeedTime(vehicleSpeed);

        if (currentMillis - prevMillis >= 1000) // Funksjoner som kjøres hvert sekund
        {
            prevMillis = currentMillis;
            vehicleSpeed = speedometer.currentSpeed(encoders.getCountsAndResetLeft(), encoders.getCountsAndResetRight()); // Sjekker hastigheten ved å telle antall rotasjoner på motoren
            int battery_level = battery.batteryDrain(vehicleSpeed);
            Serial.println(battery_level); // Tapper batteriet
            int battery_health = battery.degradeBattery(battery_level, vehicleSpeed, highSpeedTime);
            float maxVelocity = speedometer.recordMaxVelocity(vehicleSpeed);

            Serial1.print("S");
            Serial1.print(vehicleSpeed);
            Serial1.print(";");

            Serial1.print("L");           // Sender først bokstaven 'L' til ESP, kodeord for batteri
            Serial1.print(battery_level); // Sender batterinivå til ESP
            Serial1.print(";");           // Avslutter strengen med semikolon

            Serial1.print("H");
            Serial1.print(battery_health);
            Serial1.print(";");
        }

        break;

    case CHARGING:
        while (!needs_charging)
        {
            while (Serial1.available())
            {
                needs_charging = Serial1.readStringUntil(";");
            }
            motors.setSpeeds(0, 0);
        }
        car_state = 1;
        break;
    }
}
