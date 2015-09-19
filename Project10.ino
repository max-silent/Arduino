const int potPinMotor=A0;
const int potPinLED=A1;
const int enablePin=9;
const int directionSwitchPin=4,onOffSwitchPin=5;
const int controlPin1=2,controlPin2=3;
const int ledPin=6;

int onOffSwitchState=0, prevOnOffSwitchState=0;
int directionSwitchState=0, prevDirectionSwitchState=0;
boolean clockwiseDirection=true,motorEnabled=false;
unsigned long currentMoment,pauseMoment,flashMoment;
int pauseDuration=0,motorSpeed=0,flashDuration=0,flashPeriod=0;

void setup() {
  //Setting up pins directions
  pinMode(directionSwitchPin,INPUT);
  pinMode(onOffSwitchPin,INPUT);
  pinMode(enablePin,OUTPUT);
  pinMode(controlPin1,OUTPUT);
  pinMode(controlPin2,OUTPUT);
  pinMode(ledPin,OUTPUT);
  //Stop the rotation
  digitalWrite(enablePin,LOW);
  //Set initial direction (clockwise)
  digitalWrite(controlPin1,clockwiseDirection);
  digitalWrite(controlPin2,!clockwiseDirection);
  //Store all time triggers to the current time
  currentMoment=pauseMoment=flashMoment=millis();
}

void loop() {
  //Store the current moment time
  currentMoment=millis();
  //Read the motor potentiometer value
  //and convert into the 8-bit value
  //motorSpeed=analogRead(potPin)/4;  //Option 1
  motorSpeed=map(analogRead(potPinMotor),0,1023,32,255);  //Option 2
  //Read the LED potentiometer value
  //and convert to the flash period (in milliseconds)
  flashPeriod=map(analogRead(potPinLED),0,1023,100,25);
  //Calculate the flash duration
  //based on the motor speed and/or flash Period
  //flashDuration=motorSpeed/32;  //Option 1
  flashDuration=flashPeriod/3;  //Option 2
  //Read switches states
  onOffSwitchState=digitalRead(onOffSwitchPin);
  directionSwitchState=digitalRead(directionSwitchPin);
  //On-Off switch state is changed and set to HIGH
  if (onOffSwitchState!=prevOnOffSwitchState){
    if (onOffSwitchState==HIGH) motorEnabled=!motorEnabled;
  }
  //Rotating direction switch state is changed and set to HIGH
  if (directionSwitchState!=prevDirectionSwitchState){
    if (directionSwitchState==HIGH){
      //Invert the value of rotating direction
      clockwiseDirection=!clockwiseDirection;
      //If motor is rotating - give it the time for stopping
      //and store the pause moment
      if (motorEnabled){
        digitalWrite(enablePin,LOW);
        pauseMoment=currentMoment;
      }
      //Set control outputs for changing the rotating direction
      digitalWrite(controlPin1,clockwiseDirection);
      digitalWrite(controlPin2,!clockwiseDirection);
    }
  }
    //If required pause time (calculated based on motorSpeed)
    //is exceeded - start or stop rotation
    //according to the motorEnabled value
    if (currentMoment-pauseMoment>=motorSpeed*(1500/motorSpeed+50)){
      analogWrite(enablePin,motorEnabled?motorSpeed:0);
    }
    //If motorEnabled is true - flash the LED
    //with calculated period and duration
    if (currentMoment-flashMoment<flashPeriod){
      digitalWrite(ledPin,(motorEnabled&&(currentMoment-flashMoment<flashDuration))?HIGH:LOW);
    }
    //if flashPeriod is exceeded - reset it to current value
    else{ 
     flashMoment=currentMoment;
    }

    //Save the current switches states for the next loop
    prevOnOffSwitchState=onOffSwitchState;
    prevDirectionSwitchState=directionSwitchState;
}
