#include <CapacitiveSensor.h>

CapacitiveSensor capSensor = CapacitiveSensor(4,2);
int treshold=500;
const int ledPin=8;
unsigned long lastOutputMoment=0;

void setup()                    
{
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop()                    
{
  unsigned long start = millis();
  long sensorValue = capSensor.capacitiveSensor(50);
  if (sensorValue>treshold)digitalWrite(ledPin,HIGH);
  else digitalWrite(ledPin,LOW);
  if (millis() - lastOutputMoment>250){
  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug windown spacing
  Serial.print(sensorValue);             // print sensor output 1
  Serial.println("");
  lastOutputMoment=millis();
  }
  delay(100);                             // arbitrary delay to limit data to serial port 
}
