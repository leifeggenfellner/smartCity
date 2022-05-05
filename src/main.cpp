#include "main.h"

uint32_t currentMillis;
uint32_t prevMillis = 0;
uint32_t prevMillis2 = 0;
float vehicleSpeed;
uint16_t max_speed = 400;

uint16_t distance_driven;
float battery_level;

uint8_t car_state = 0;

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
