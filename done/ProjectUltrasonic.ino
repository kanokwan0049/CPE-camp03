#include "Ultrasonic.h"
#define green D8
#define red D7
Ultrasonic ultrasonic(4);
#define buzzer  5

void setup()
{
	Serial.begin(9600);
 pinMode(red,OUTPUT);
 pinMode(green,OUTPUT);
 pinMode(buzzer,OUTPUT);
}
void loop()
{
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
 
 if(RangeInCentimeters<=15){
  digitalWrite(red,HIGH);
  digitalWrite(green,LOW);
  digitalWrite(buzzer , HIGH);}
  else{
    digitalWrite(red,LOW);
  digitalWrite(green,HIGH);
  digitalWrite(buzzer , LOW);
    } 
}
  
