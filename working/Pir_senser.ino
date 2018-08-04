int pirPin = 2; //digital 2
int ledPin = 13;

void setup(){
 Serial.begin(9600); 
 pinMode(pirPin, INPUT);
 pinMode(ledPin, OUTPUT);
}

void loop(){
  int pirVal = digitalRead(pirPin);
  Serial.println(pirVal); 
  if(pirVal == LOW){ //was motion detected
    Serial.println("Motion Detected");
    digitalWrite(ledPin, HIGH);
    delay(2000); 
  }
  digitalWrite(ledPin, LOW);
}
