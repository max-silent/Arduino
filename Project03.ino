const int switchPin=2;
const int sensorPin=A0;
int switchState=0;
float baselineTemp=0;
int sensorValue, baselineValue;
float currentVoltage;
float currentTemp;

void setup() {
  //Set input pin connected to the switch
  pinMode(switchPin,INPUT);
  //Set the output pins for the LEDs related to calibration
  for(int i=3;i<=5;i++){
    pinMode(i,OUTPUT);
  }
  //Set the output pins for the LEDs related to temperature measuring
  for(int i=8;i<=11;i++){
    pinMode(i,OUTPUT);
  }
  //Open a serial port for the monitoring via IDE's monitor
  Serial.begin(9600);
  //Wait for a 5 seconds so the circuits and temperature sensor could achieve stable state
  while (millis()<2500){
  }
  //Convert through the ADC -> Voltage -> Degrees and set the result as a baselineTemp
  baselineValue=analogRead(sensorPin);
  baselineTemp=(baselineValue/1024.0*5.0-0.5)*100;
  Serial.print("Baseline Sensor Value is: ");
  Serial.print(baselineValue);
  Serial.print(", Baseline temperature is: ");
  Serial.println(baselineTemp);
}

void loop() {
  // Store the button state
  switchState=digitalRead(switchPin);
  //Check if the button is pressed
  if (switchState==LOW){    //Not pressed - just turn on the green LED
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  else{                      //Pressed - blink the LEDs separately and then calibrate the temperature and output its current value to the serial port
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
    //Store current Sensor Value and temperature as a baseline
    baselineValue=analogRead(sensorPin);
    baselineTemp=(baselineValue/1024.0*5.0-0.5)*100;
    //Output the current value to the serial port
    Serial.print("Baseline Sensor Value is: ");
    Serial.print(baselineValue);
    Serial.print(", Baseline temperature is: ");
    Serial.println(baselineTemp);
  }
  //Read the temperature sensor's value
  sensorValue=analogRead(sensorPin);
  //Calculate current Voltage and Temperature based on sensor's value
  currentVoltage=sensorValue/1024*5;
  currentTemp=(sensorValue/1024.0*5.0-0.5)*100;
  //Output the sensor-related data into the serial port for the monitoring
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(", Volts: ");
  Serial.print(currentVoltage);
  Serial.print(", degrees C: ");
  Serial.println(currentTemp);
  //Handle the LEDs states according to the current temperature
  //if (currentTemp<baselineTemp+1.6){
  if (sensorValue<baselineValue+4){
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }
  //else if (currentTemp>=baselineTemp+1.8&&currentTemp<baselineTemp+2.3){
  else if (sensorValue>=baselineValue+5&&sensorValue<baselineValue+6){
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }
  //else if (currentTemp>=baselineTemp+2.5&&currentTemp<baselineTemp+2.9){
  else if (sensorValue>=baselineValue+7&&sensorValue<baselineValue+8){
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }
  //else if (currentTemp>=baselineTemp+3.1&&currentTemp<baselineTemp+3.4){
  else if (sensorValue>=baselineValue+9&&sensorValue<baselineValue+10){
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
  //else if (currentTemp>=baselineTemp+3.6){
  else if (sensorValue>=baselineValue+11){
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
  }
  delay(500);
}
