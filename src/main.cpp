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

// Loop funksjonen består i hovedsak av en switch case med tre ulike tilstander; Startup, Driving og Charging. Noen variabler oppdateres kontinuerlig, men de
// fleste er fordelt i de ulike tilstandene.
// På den måten fungerer koden litt som en tilstandsmaskin. Videre er det ikke brukt noe særlig delay()- eller while() funksjoner i noen av klassene i biblioteket,
// Slik at koden kjører raskt gjennom og ikke henger seg opp uventede plasser
void loop()
{

    // Variabel som tar i mot alle kommandoer fra ESP32
    char ESPcommands = (char)Serial1.read(); // Avleser kommandoer som kommer fra ESP32
    currentMillis = millis();

    // Variabel som oppdaterer hvilken tilstand bilen skal være i. Funksjonen overstyrer hvilken status bilen er i, i tilfelle det er ønskelig å styre manuelt
    car_state = driving.manuallyChangeCarState(buttonA.isPressed(), buttonB.isPressed(), buttonC.isPressed());

    // Switch case / tilstandsendring som styrer hele gangen i programmet, altså hvilken tilstand bilen er i
    switch (car_state)
    {
    case STARTUP:
        // Tilstand hvor bilen er i oppstart. Her vil ikke bilen kjøre eller tappe strøm e.l.
        max_speed = driving.chooseMaxSpeed(ESPcommands); // Velger makshastighet via ESP32 og Node-RED
        car_state = driving.updateCarState(ESPcommands); // Venter på kommando fra Node-RED for å oppdatere status til kjøring
        break;

    case DRIVING:
        // Case hvor bilen er i kjøremodus

        // follow_line er en boolesk variabel som bestemmer om bilen skal være i linjefølgermodus eller ikke. Så lenge den er satt til sann så vil bilen være i linjefølgermodus
        while (driving.follow_line)
        {
            // Funksjon som sørger for at bilen følger linje langs bakken
            driving.followLine();
        }
        // Sjekker om kommandoen 'f' er mottatt fra ESP32, kodeord for at bilen skal gå i linjefølgermodus
        if (ESPcommands == 'f')
        {
            // Setter follow_line til sann og går dermed i linjefølgermodus
            driving.follow_line = true;
        }
        else
        {
            // Dersom bilen ikke er satt til linjefølgermodus vil den ta i mot kjørekommandoer fra ESP32/Node-RED
            driving.ESPdriveCommands(ESPcommands); // Tar imot kjørekommandoer fra ESP
        }
        speedometer.distanceDriven(encoders.getCountsLeft(), encoders.getCountsRight()); // Regner ut hvor langt bilen har kjørt
        max_speed = driving.chooseMaxSpeed(ESPcommands);                                 // Velger makshastighet via ESP
        int averageSpeed = speedometer.averageSpeed(vehicleSpeed);                       // Regner ut gjennomsnittshastigeten. Integrert i funksjonen å telle hvert 60'ende sekund
        int highSpeedTime = speedometer.highSpeedTime(vehicleSpeed);                     // Regner ut hvor mange sekunder bilen har kjørt over 70% av makshastighet

        if (currentMillis - prevMillis >= 1000) // Funksjoner som kjøres hvert sekund
        {
            prevMillis = currentMillis;
            vehicleSpeed = speedometer.currentSpeed(encoders.getCountsAndResetLeft(), encoders.getCountsAndResetRight()); // Sjekker momentanhastigheten ved å telle antall rotasjoner på motoren
            int battery_level = battery.batteryDrain(vehicleSpeed);                                                       // Regner ut batterinivå basert på momentanhastighet
            int battery_health = battery.degradeBattery(battery_level, vehicleSpeed, highSpeedTime);                      // Regner ut batterihelse basert på en rekke variabler
            float maxVelocity = speedometer.recordMaxVelocity(vehicleSpeed);                                              // Oppdaterer den maksimale hastigheten som er målt

            Serial1.print("S");          // Sender først bokstaven 'S' til ESP, kodeord for Speed
            Serial1.print(vehicleSpeed); // Sender momentanfart til ESP
            Serial1.print(";");          // Avslutter strengen med semikolon

            Serial1.print("L");           // Sender først bokstaven 'L' til ESP, kodeord for batteri
            Serial1.print(battery_level); // Sender batterinivå til ESP
            Serial1.print(";");           // Avslutter strengen med semikolon

            Serial1.print("H");            // Sender først bokstaven 'H' til ESP, kodeord for Health
            Serial1.print(battery_health); // Sender helsenivå til ESP
            Serial1.print(";");            // Avslutter strengen med semikolon
        }

        break;

    // Ufullstending skrevet lademodus som setter bilen i ro til den har mottatt nok strøm
    case CHARGING:
        // Så lenge bilen trenger lading
        while (needs_charging)
        {
            // Stopper bilen og leser av informasjon fra ESP
            motors.setSpeeds(0, 0);
            while (Serial1.available())
            {
                // Selve ladingen blir regnet ut på ESP, og bilen oppdateres fra ESP når den er ferdigladet. Går da ut av løkken
                needs_charging = Serial1.readStringUntil(";");
            }
        }
        // Går tilbake til driving når ferdigladet. Klar til å ta imot nye kommandoer
        car_state = 1;
        break;
    }
}
