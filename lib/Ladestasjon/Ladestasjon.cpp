/*
//ALT SKJER PÅ BETINGELSENE RFID_KOBLING == true && SW-BATTERI < 5%
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "HUAWEI Mate 20 Pro";
const char* password = "MQTTWifi";

const char* mqtt_server = "192.168.43.190";

WiFiClient espClient;
PubSubClient client(espClient);
const char* device_name = "ESP32_ladestasjon"; //Navn på enheten

int SW_battery = 5;       //variabel for batteriprosent, hentes fra Zumo
int account_balance = 34; //variabel for penger på konto, hentes fra nettsky
int credit_account = 0;   //variabel for penger på krita, hentes fra nettsky
int UpTo;                 //variabel for mye batteriet skal lades i chargeUpTo()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup_wifi() {
  Serial.print(9600);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);
  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // If a message is received on the topic Test_Topic, you check if the message is either "blink" or "stop".
  // Changes the output state according to the message
  if (String(topic) == "Test_Topic") {
    lading_zumo(chargeMode(messageTemp));
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(device_name)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("Test_Topic");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int chargeMode(String serialCommand) {
  int chosenMode;
  if (serialCommand == "full charge" || serialCommand == "100") {
    chosenMode = 1;
  }
  else if (serialCommand == "charge up to") {
    chosenMode = 2;
  }
  else if (serialCommand == "charge until stop") {
    chosenMode = 3;
  }
  else if (serialCommand == "charge on credit") {
    chosenMode = 4;
  }
  else if (serialCommand == "battery service") {
    chosenMode = 5;
  }
  else if (serialCommand == "battery replace") {
    chosenMode = 6;
  }
  else {
    chosenMode = 0;
  }
  return chosenMode;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int lading_zumo(int chargeMode) {
  switch (chargeMode) {
    case 0: //error
      Serial.println("Check your spelling, m8");
      break;

    case 1: //fullCharge
      SW_battery = fullCharge(SW_battery);
      Serial.print("Battery at ");
      Serial.print(SW_battery);
      Serial.println("%");
      break;

    case 2: //chargeUpTo
      if (Serial.available() == 0) {
        while (Serial.available() == 0) {}
        // read the incoming byte:
        String percentage = Serial.readStringUntil('\n');

        // say what you got:
        Serial.print("I received: ");
        Serial.println(percentage);

        SW_battery = chargeUpTo(SW_battery, percentage.toInt());
        Serial.print("Battery at ");
        Serial.print(SW_battery);
        Serial.println("%");
      }
      break;

    case 3: //chargeUntilStop
      SW_battery = chargeUntilStop(SW_battery, account_balance);
      Serial.print("Battery at ");
      Serial.print(SW_battery);
      Serial.println("%");
      break;

    case 4: //ChargeOnCredit
      Serial.println("Charging on credit");
      break;

    case 5: //batteryService
      Serial.println("Service have been done on the battery");
      break;

    case 6: //batteryReplace
      Serial.println("Battery has been replaced");
      break;
  }
  return SW_battery;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int fullCharge(int battery) {
  unsigned long currentMillis = millis();
  while (battery < 100) {
    if (millis() - currentMillis == 200) {
      battery++;
      Serial.println(battery);
      currentMillis = millis();
    }
  }
  return battery;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int chargeUpTo(int battery, int chargeCap) {
  unsigned long currentMillis = millis();
  while (battery < chargeCap) {
    if (millis() - currentMillis == 200) {
      battery++;
      Serial.println(battery);
      currentMillis = millis();
    }
  }
  return battery;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int chargeUntilStop(int battery, int money) {
  unsigned long currentMillis = millis();
  while (battery < 100 && money > 0) {
    if (millis() - currentMillis == 200) {
      battery++;
      money--;
      currentMillis = millis();
      Serial.print(battery);
      Serial.print("        ");
      Serial.println(money);
    }
  }
  account_balance = money; //sendes til nettsky
  return battery;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ChargeOnCredit(int battery) {
  int creditCharge = 0;
  switch (creditCharge) {
    case 1:
      credit_account += 100; //sendes til nettsky
      SW_battery = fullCharge(SW_battery);
      break;

    case 2:
      if (Serial.available() == 0) {
        while (Serial.available() == 0) {}
        // read the incoming byte:
        String percentage = Serial.readStringUntil('\n');

        // say what you got:
        Serial.print("I received: ");
        Serial.println(percentage);

        SW_battery = chargeUpTo(SW_battery, percentage.toInt());
        Serial.print("Battery at ");
        Serial.print(SW_battery);
        Serial.println("%");
      }
      break;
  }
  return SW_battery;
}
*/
