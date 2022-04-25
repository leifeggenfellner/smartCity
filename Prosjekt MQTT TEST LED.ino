//Libraies
#include <WiFi.h>
#include <PubSubClient.h>

// SSID & Password
const char* ssid = "HUAWEI Mate 20 Pro";  // Enter your SSID here
const char* password = "MQTTWifi";  //Enter your Password here

const char* mqtt_server = "192.168.43.190";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
const char* device_name = "ESP32"; //Navn på enheten

//Terminals
const int LED = 4;

//Channels
int channelLED = 0; //LED pwm channel

// setter tidskonstant
unsigned long previousTime = 0;

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //Sets the datadirection of the specified terminals
pinMode(LED,OUTPUT);

  //ESP PWM
ledcSetup(channelLED, 2000, 8); // (2000) er frekvens,  (8) er bitoppløsning
ledcAttachPin(LED, channelLED); //velger utgangen LED (pin 32)
ledcWrite(channelLED, 0);
}

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
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("Led turned on");
      client.publish("Test_Topic", "LED is on at ESP32");
      ledcWrite(channelLED, 255); 
    }
    else if(messageTemp == "off"){
      Serial.println("LED turned off");
      client.publish("Test_Topic", "LED is off at ESP32");
      ledcWrite(channelLED, 0);
    }
  }
}

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

void loop() {
 if (!client.connected()) {
    reconnect();
  }
  client.loop();
}





