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
    char ESPcommands = (char)Serial1.read(); // Avleser kommandoer som kommer fra ESP32
    // String ESPstringCommands = (String)Serial1.read();

    switch (car_state)
    {
    case STARTUP:
        // Case hvor bilen er i oppstart.
        if (ESPcommands == 'c') // Kalibrerer linjesensorene
        {
            driving.calibrateLightSensors();
        }
        max_speed = driving.chooseMaxSpeed(ESPcommands); // Velger makshastighet via ESP32 og Node-RED
        car_state = driving.updateCarState(ESPcommands); // Venter på kommando fra Node-RED for å oppdatere status til kjøring

        break;

    case DRIVING:
        // Case hvor bilen er i kjøremodus
        speedometer.distanceDriven(encoders.getCountsLeft(), encoders.getCountsRight()); // Regner ut hvor langt bilen har kjørt
        driving.ESPdriveCommands(ESPcommands);                                           // Tar imot kjørekommandoer fra ESP
        max_speed = driving.chooseMaxSpeed(ESPcommands);                                 // Velger makshastighet via ESP

        if (currentMillis - prevMillis >= 1000) // Funksjoner som kjøres hvert sekund
        {
            prevMillis = currentMillis;
            vehicleSpeed = speedometer.currentSpeed(encoders.getCountsAndResetLeft(), encoders.getCountsAndResetRight()); // Sjekker hastigheten ved å telle antall rotasjoner på motoren
            battery_level = battery.batteryDrain(vehicleSpeed);                                                           // Tapper batteriet
            // float maxVelocity = speedometer.recordMaxVelocity(vehicleSpeed);
            Serial1.print("b");                                                    // Sender først bokstaven 'b' til ESP, kodeord for batteri
            Serial1.print((String)battery_level);                                  // Sender batterinivå til ESP
            Serial1.print(";");                                                    // Avslutter strengen med semikolon
            int sun_luminance = analogRead(14);                                    // Måler sollysforhold
            car_state = driving.findChargingStation(battery_level, sun_luminance); // Sjekker om bilen må lade
            Serial1.print("i");                                                    // Sender først bokstaven 'i' til ESP, kodeord for lysforhold
            Serial1.print(String(sun_luminance));                                  // Sender lysforhold til ESP
            Serial1.print(";");                                                    // Avslutter strengen med semikolon
        }

        if (currentMillis - prevMillis2 > 60 * 1000) // Funksjoner som kjører hvert minutt
        {
        }

        break;

    case CHARGING:

        while (battery_level < 100)
        {
            battery_level = Serial1.readStringUntil(';');
            motors.setSpeeds(0, 0);
        }
        car_state = 1;

        break;
    }
}
