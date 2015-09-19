//Store the pins numbers for sensors (photoresistors) 
const int redSensorPin=A0;
const int greenSensorPin=A1;
const int blueSensorPin=A2;
//Store the pins numbers for LED colors
const int redLEDPin=10;
const int greenLEDPin=9;
const int blueLEDPin=11;
//Sensors' levels 
int redSensorValue=0;
int greenSensorValue=0;
int blueSensorValue=0;
//Mapped (converted to 0-255 range) sensors' levels, which is used for specifying LED colors levels
int redValue=0;
int greenValue=0;
int blueValue=0;
//Logs output counter
int logsOutputTime=0;

void setup() {
  //Initialize the serial port communication at 9600 pbs
  Serial.begin(9600);
  //Set the direction of LED pins as an OUTPUT
  pinMode(redLEDPin,OUTPUT);
  pinMode(greenLEDPin,OUTPUT);
  pinMode(blueLEDPin,OUTPUT);

}

void loop() {
  //
  redSensorValue=analogRead(redSensorPin);
  delay(5);
  greenSensorValue=analogRead(greenSensorPin);
  delay(5);
  blueSensorValue=analogRead(blueSensorPin);
  delay(5);
  /*
  if (logsOutputTime+1<millis()/1000){
  logsOutputTime=millis()/1000;
  //Print to serial port details about the sensors' levels
  Serial.print("Raw Sensor Values:\t Red: ");
  Serial.print(redSensorValue);
  Serial.print("\t Green: ");
  Serial.print(greenSensorValue);
  Serial.print("\t Blue: ");
  Serial.println(blueSensorValue);
  }
  */

  //Convert the levels into the 0-255 range and lowering the signal substracting 50
  redValue=redSensorValue/4;
  greenValue=greenSensorValue/4;
  blueValue=blueSensorValue/4;
  if (logsOutputTime+1<millis()/1000){
  logsOutputTime=millis()/1000;
  //Print to serial port details about the sensors' converted levels
  Serial.print("Mapped Sensor Values:\t Red: ");
  Serial.print(redValue);
  Serial.print("\t Green: ");
  Serial.print(greenValue);
  Serial.print("\t Blue: ");
  Serial.println(blueValue);
  }

  //Set the LED light levels

  //Option #1
  //analogWrite(redLEDPin,abs(redValue-(10000/redValue)));
  //analogWrite(greenLEDPin,abs(greenValue-(10000/greenValue)));
  //analogWrite(blueLEDPin,abs(blueValue-(10000/blueValue)));

  //Option #2
  analogWrite(redLEDPin,(redValue>=80)?map(redValue,80,255,0,255):0);
  analogWrite(greenLEDPin,(greenValue>=80)?map(greenValue,80,255,0,255):0);
  analogWrite(blueLEDPin,(blueValue>=80)?map(blueValue,80,255,0,255):0);

  //delay(10);
}
