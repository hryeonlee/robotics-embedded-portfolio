int Led = 2;
int FSRsensor = A4; // A0~A5까지의 값을 변경하여 
int value = 0;


void setup() {
  pinMode(Led, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  value = analogRead(FSRsensor);

  Serial.println(value);

  value = map(value, 0, 1023, 0, 255);

  analogWrite(Led, value);

  delay(100);


}

