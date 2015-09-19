int sensorValue;
int sensorLow=1023;
int sensorHigh=0;
const int calibratingLEDPin=13;
int pitch;

void setup() {
  // put your setup code here, to run once:
  pinMode(calibratingLEDPin,OUTPUT);
  digitalWrite(calibratingLEDPin,HIGH);
  while(millis()<5000){
    sensorValue=analogRead(A0);
    if (sensorValue<sensorLow){
      sensorLow=sensorValue;
    }
    if (sensorValue>sensorHigh){
      sensorHigh=sensorValue;
    }
  }
  digitalWrite(calibratingLEDPin,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue=analogRead(A0);
  pitch=map(sensorValue,sensorLow,sensorHigh,50,4000);
  tone(8,pitch,20);
  delay(10);
}
