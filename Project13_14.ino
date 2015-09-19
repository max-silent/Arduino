#include <CapacitiveSensor.h>

CapacitiveSensor capSensor = CapacitiveSensor(4,2);
int treshold=700;
const int ledPin=8;
//unsigned long lastOutputMoment=0;
boolean touchedWire=false;
boolean turnedOnLed=false;

void setup()                    
{
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop()                    
{
  Serial.write(analogRead(A0)/4);
  //unsigned long start = millis();
  long sensorValue = capSensor.capacitiveSensor(50);
  if (sensorValue>treshold){
    if (!touchedWire){
      touchedWire=true;
      digitalWrite(ledPin,turnedOnLed?LOW:HIGH);
      turnedOnLed=!turnedOnLed;
    }
  }else touchedWire=false;
  /*
  if (millis() - lastOutputMoment>250){
  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug windown spacing
  Serial.print(sensorValue);             // print sensor output 1
  Serial.println("");
  lastOutputMoment=millis();
  }
  */
  delay(1);                             // arbitrary delay to limit data to serial port 
}
