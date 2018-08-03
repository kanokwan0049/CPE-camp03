int sensorPin = A0; //ชื้น

#define RedPin D1   //กำหนดขา 

#define GreenPin D2 //กำหนดขา 

#define BluePin D3  //กำหนดขา 

#define Sound D4    //กำหนดขา 

void setup() {

  Serial.begin(9600); // set up serial port for 9600 baud (speed)

//RGB

  pinMode(RedPin, OUTPUT);

  pinMode(GreenPin, OUTPUT);
}

void loop() {

  int sensorValue;

  sensorValue = analogRead(sensorPin); //อ่านค่าความชื้น

  sensorValue = map(sensorValue, 0, 1023, 0, 100);

  Serial.print("Soil moisture: ");

  Serial.print(sensorValue);

  Serial.println(" %");

  if(sensorValue >=20 && sensorValue <=40){

    setColor(0, 255);  // ไฟสี green

                          //ไม่มีเสียงเตือน
  }

    else if(sensorValue >=41){

        setColor(255, 0);    // red

        digitalWrite(RedPin,HIGH);

        delay(1000);

        digitalWrite(RedPin,LOW);

        delay(1000);

      }

     else if (sensorValue <=19){

        setColor(0,255);    // Green

        digitalWrite( GreenPin ,HIGH);

        delay(1000);

        digitalWrite( GreenPin ,LOW);

        delay(1000);
 }

        delay(1000);

 }

void setColor(int red, int green)  //ส่วนของสี

{

  #ifdef COMMON_ANODE

    red = 255 - red;

    green = 0 - green;

  #endif

  analogWrite(RedPin, red);

  analogWrite(GreenPin, green);
}
