#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

WiFiClient client;
const char* ssid = "BKIT_LUGIA_CS2";
const char* password = "cselabc5c6";

int counter = 20;
int led_status = 0;

#define LED_PIN 2

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 1);
  led_status = 1;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    // Serial.println("Đang kết nối Wi-Fi...");
  }

  // Serial.println("Đã kết nối Wi-Fi");
  digitalWrite(LED_PIN, 0);
  led_status = 0;
}

void loop() {
  if (Serial.available()){
    // Serial.println("Vao....");
    int msg = Serial.read();
    if (msg == 't'){
      // Serial.println('O');
      //lấy dữ liệu giờ quốc tế ngay khi chạy set up (lấy 1 lần duy nhất).
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(client, "http://worldtimeapi.org/api/timezone/Asia/Ho_Chi_Minh"); // Thay đổi URL nếu cần

        int httpCode = http.GET();

        if (httpCode > 0) {
          String payload = http.getString();
          //Serial.println(payload);

          // Parse JSON
          DynamicJsonDocument doc(1024);
          deserializeJson(doc, payload);
          const char* datetime = doc["datetime"];
          String data = 'O'+ doc["datetime"].as<String>() + 'K';
          // Serial.println(datetime);
          // int year = (datetime[2] - '0')*10 + (datetime[3] - '0');
          // int month = (datetime[5] - '0')*10 + (datetime[6] - '0');
          // int date = (datetime[8] - '0')*10 + (datetime[9] - '0');
          // int hour = (datetime[11] - '0')*10 + (datetime[12] - '0');
          // int min = (datetime[14] - '0')*10 + (datetime[15] - '0');
          // int sec = (datetime[17] - '0')*10 + (datetime[18] - '0');
          
          // Serial.println(datetime);
          Serial.println(data);
          // Serial.println('K');
        } else {
          Serial.println("Lỗi HTTP");
        }

        http.end();
      }
    }
  }
  if (counter <= 0){
    counter = 20;
    if (led_status == 1){
      digitalWrite(LED_PIN, 0);
      led_status = 0;
    }
    else {
      digitalWrite(LED_PIN, 1);
      led_status = 1;
    }
  }
  else {
    counter--;
  }
  delay(50); // Lấy thời gian mỗi phút
}
