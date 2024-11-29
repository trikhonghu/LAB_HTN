#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <string.h>

//Wifi name
#define WLAN_SSID       "BKIT_CS2"
//Wifi password
#define WLAN_PASS       "cselabc5c6"

//setup Adafruit
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
//fill your username                   
#define AIO_USERNAME    "vtri0976"
//fill your key
#define AIO_KEY         ""

//setup MQTT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

//setup publish
Adafruit_MQTT_Publish temp_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp");
Adafruit_MQTT_Publish humi_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish wind_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/wind");

//setup subcribe
// Adafruit_MQTT_Subscribe light_sub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/light", MQTT_QOS_1);

int led_counter = 0;
int led_status = HIGH;

String temp_str = "";
String humid_str = "";
String wind_str = "";

uint32_t temp_int = 0;
uint32_t humid_int = 0;
uint32_t wind_int = 0;

double temp = 0;
double humid = 0;
double wind = 0;

// void lightcallback(char* value, uint16_t len){
//   if(value[0] == '0') Serial.print('a');
//   if(value[0] == '1') Serial.print('A');
// }

void setup() {
  // put your setup code here, to run once:
  //set pin 2,5 as OUTPUT
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  //set busy pin HIGH
  digitalWrite(5, HIGH);

  Serial.begin(115200);

  //connect Wifi
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //subscribe light feed
  // light_sub.setCallback(lightcallback);
  // mqtt.subscribe(&light_sub);

  //connect MQTT
  while (mqtt.connect() != 0) { 
    mqtt.disconnect();
    delay(500);
  }

  //finish setup, set busy pin LOW
  digitalWrite(5, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  //receive packet
  mqtt.processPackets(1);
  
  //read serial
  if(Serial.available()){
    int msg = Serial.read();
    Serial.println(msg);
    // start reading
    if (msg == 'S'){
      msg = Serial.read();
      // start receive temperature
      if (msg == 'T') {
        msg = Serial.read();
        temp_int = 0;
        while(msg != '#') {
          temp_int = temp_int * 10 + (msg - '0');
          msg = Serial.read();
        }
        temp = (double) (temp_int / 100.00);
        temp_pub.publish(temp, 2);
        // temp_str = "";
      }
      msg = Serial.read();
      // start receive humid
      if (msg == 'H') {
        msg = Serial.read();
        humid_int = 0;
        while(msg != '#') {
          humid_int = humid_int * 10 + (msg - '0');
          msg = Serial.read();
        }
        Serial.print(humid_int);
        humid = (double) (humid_int / 10.00);
        humi_pub.publish(humid);
      }
      msg = Serial.read();
      // start receive wind speed
      if (msg == 'W') {
        msg = Serial.read();
        wind_int = 0;
        while(msg != '#') {
          wind_int = wind_int * 10 + (msg - '0');
          msg = Serial.read();
        }
        wind = (double) (wind_int / 10.00);
        wind_pub.publish(wind);
      }
    }
  }

  led_counter++;
  if(led_counter == 100){
    // every 1s
    led_counter = 0;
    //toggle LED
    if(led_status == HIGH) led_status = LOW;
    else led_status = HIGH;

    digitalWrite(2, led_status);
    Serial.print("loop");
  }
  delay(10);
}
