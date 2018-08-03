int sensorPin = A0; // select the input pin for the potentiometer
int sensorValue = 0; // variable to store the value coming from the sensor

//code arduino
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "IOT02"; // แก้ ssid
const char* password = "0123456789"; // แก้ password

// Config MQTT Server
const char * topic = "/fah"; // topic ชื่อ /server
#define mqtt_server "m14.cloudmqtt.com" // server
#define mqtt_port 18245  // เลข port
#define mqtt_user "kqmmwksc" // user
#define mqtt_password "Q8MWlb89O1u7" // password

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // เชื่อมต่อ network
  Serial.begin(9600);
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
// read the value from the sensor:

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
  float sensorValue = analogRead(sensorPin);
  delay(1000);
  Serial.print("sensor = " );
  Serial.println(sensorValue);
  String a = String(sensorValue);
  char b[10];
  a.toCharArray(b,10);
  client.publish("/fah", b);
}
