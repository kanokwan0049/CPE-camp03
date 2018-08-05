#include "Ultrasonic.h"
#define green D8
#define red D7
Ultrasonic ultrasonic(4);
#define buzzer  5
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "IOT02"; // แก้ ssid
const char* password = "0123456789"; // แก้ password
const char * topic = "/fah"; // topic ชื่อ /server
#define mqtt_server "m14.cloudmqtt.com" // server
#define mqtt_port 18245   // เลข port
#define mqtt_user "kqmmwksc" // user
#define mqtt_password "yggTyMXv5Wun" // password
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // จบการเชื่อมต่อ network

  client.setServer(mqtt_server, mqtt_port); // เชื่อมต่อ mqtt server
}
void loop() {
  if (!client.connected()) {
    Serial.print("MQTT connecting...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) { // ถ้าเชื่อมต่อ mqtt สำเร็จ
      client.subscribe(topic); // ชื่อ topic ที่ต้องการติดตาม
      Serial.println("connected");
    }
    // ในกรณีเชื่อมต่อ mqtt ไม่สำเร็จ
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000); // หน่วงเวลา 5 วินาที แล้วลองใหม่
      return;
    }
  }

  long RangeInInches;
  long RangeInCentimeters;

  Serial.println("The distance to obstacles in front is: ");
  RangeInInches = ultrasonic.MeasureInInches();
  Serial.print(RangeInInches);//0~157 inches
  Serial.println(" inch");
  delay(250);

  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.print(RangeInCentimeters);//0~400cm
  Serial.println(" cm");
  delay(250);
 
  if (RangeInCentimeters >= 5) {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(buzzer , HIGH);
    char b2[50] = "{\"room\":\"room\",\"status\":\"Danger\"}";
    client.publish("room/status", b2);
  }
  else {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(buzzer , LOW);
  }

}

