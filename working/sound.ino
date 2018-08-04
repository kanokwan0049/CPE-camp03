int buzzer = D1;
void setup() {
  Serial.begin(115200);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(buzzer ,OUTPUT);
}
void loop() {
  int value = analogRead(A0);
  Serial.println(value);
  if (value<200){
  digitalWrite(D5, LOW); 
  digitalWrite(D6, HIGH);
  digitalWrite(D7, LOW);
  digitalWrite(buzzer , HIGH); 
  delay(1000); 
  digitalWrite(buzzer , LOW);
  delay(1000); 
 

}else if (value >= 200 and value <= 400 ){
  digitalWrite(D5, LOW); 
  digitalWrite(D7, HIGH);
  digitalWrite(D6, LOW);
  digitalWrite(buzzer , HIGH); 
  delay(500); 
  digitalWrite(buzzer , LOW);
  delay(500); 
  }else if (value > 400){
  digitalWrite(D6, LOW); 
  digitalWrite(D5, HIGH);
  digitalWrite(D7, LOW);
  digitalWrite(buzzer , HIGH);
  delay(250); 
  digitalWrite(buzzer , LOW);
  delay(250); 
  }
  delay(1000);
  }
