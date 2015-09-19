int potPin=A0,motorPin=9,potValue;

void setup() {
  // put your setup code here, to run once:
  //pinMode(potPin,INPUT);
  pinMode(motorPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValue=analogRead(potPin);
  analogWrite(motorPin,(potValue>1)?map(potValue,5,1023,64,255):0);
  Serial.println(potValue);
  delay(50);
}
