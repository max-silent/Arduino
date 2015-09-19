int switchState=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  switchState=digitalRead(2);
  if (switchState==LOW){
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  else{
    for (int i=0;i<3;i++){
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    delay(500);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    delay(500);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    delay(500);
    }
  }
}
