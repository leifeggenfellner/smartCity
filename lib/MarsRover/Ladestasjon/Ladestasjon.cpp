

#include "Ladestasjon.h"

static int battery_level = 100;
static int account_balance;

int chargeMode(String serialCommand)
{
  int chosenMode;
  if (serialCommand == "full charge" || serialCommand == "100")
  {
    chosenMode = 1;
  }
  else if (serialCommand == "charge up to")
  {
    chosenMode = 2;
  }
  else if (serialCommand == "charge until stop")
  {
    chosenMode = 3;
  }
  else if (serialCommand == "charge on credit")
  {
    chosenMode = 4;
  }
  else if (serialCommand == "battery service")
  {
    chosenMode = 5;
  }
  else if (serialCommand == "battery replace")
  {
    chosenMode = 6;
  }
  else
  {
    chosenMode = 0;
  }
  return chosenMode;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int lading_zumo(int chargeMode)
{
  switch (chargeMode)
  {
  case 0: // error

    break;

  case 1: // fullCharge
    battery_level = fullCharge(battery_level);
    break;

  case 2: // chargeUpTo
    if (Serial.available() == 0)
    {
      while (Serial.available() == 0)
      {
      }
      // read the incoming byte:
      String percentage = Serial.readStringUntil('\n');
      battery_level = chargeUpTo(battery_level, percentage.toInt());
    }
    break;

  case 3: // chargeUntilStop
    battery_level = chargeUntilStop(battery_level, account_balance);
    break;

  case 4: // batteryService
    // Serial.println("Service have been done on the battery");
    break;

  case 5: // batteryReplace
    // Serial.println("Battery has been replaced");
    break;
  }
  return battery_level;
}

/////////////////////////////////////////////////////////////////////////////////

// Mulig funksjon for å sende informasjon fra ESP til Zumo
String sendToZumo(String information_to_send)
{
  information_to_send = String(information_to_send);
  Serial.print(information_to_send);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int fullCharge(int battery_level)
{
  unsigned long currentMillis = millis();
  while (battery_level < 100)
  {
    if (millis() - currentMillis == 200)
    {
      battery_level++;
      currentMillis = millis();
    }
  }
  return battery_level;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int chargeUpTo(int battery_level, int chargeCap)
{
  unsigned long currentMillis = millis();
  while (battery_level < chargeCap)
  {
    if (millis() - currentMillis == 200)
    {
      battery_level++;
      currentMillis = millis();
    }
  }
  return battery_level;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int chargeUntilStop(int battery_level, int money)
{
  unsigned long currentMillis = millis();
  while (battery_level < 100 && money > 0)
  {
    if (millis() - currentMillis == 200)
    {
      battery_level++;
      money--;
      currentMillis = millis();
    }
  }
  account_balance = money; // sendes til nettsky
  return battery_level;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
