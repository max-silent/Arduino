//Tilt switch pin
int switchPin=8;
//Last an Current states of the tilt switch
int currentSwitchState, lastSwitchState;
//Current time and the time of last lighting up of the LED
unsigned long currentTime, lastLedOnTime;
//Periods between LEDs lighting up and Alert Flash period
int ledOnPeriod=10000,exceedAlertPeriod=1000;
//Pin of the next LED to be lighted up
int ledToLight=2;
//Next LEDs state for the Alert Flash
boolean alertStateOn=false;

void setup() {
  // Set up the LEDs pins and tilt switch pin modes
for (int i=2; i<8; i++){
  pinMode(i,OUTPUT);
}
  pinMode(switchPin,INPUT);
  //Ser all LEDs to LOW
  reset();
  //Initialize lastSwitchState and lastLedOnTime to the current values
  lastSwitchState=digitalRead(switchPin);
  lastLedOnTime=millis();
}

void loop() {
  // Set currentSwitchState to the current value
  currentSwitchState=digitalRead(switchPin);
  switch (currentSwitchState){
  case HIGH:  //Circuit is closed (tilt switch in regular state)
    if (currentSwitchState==lastSwitchState){  //Switch state is HIGH (closed) and NOT CHANGED between the previous and current loop cycles
      currentTime=millis();
      if (ledToLight<8){  //If there are non-lighted LEDs left
        if (currentTime-lastLedOnTime>=ledOnPeriod){
          digitalWrite(ledToLight,HIGH);
          ledToLight++;
          lastLedOnTime=currentTime;
        };
      } else if (currentTime-lastLedOnTime>=exceedAlertPeriod){  //If all of the LEDs are lighted and exceedAlertPeriod is passed
        //Change state of the LEDs
        for(int i=2;i<8;i++){
          digitalWrite(i,alertStateOn?HIGH:LOW);
        }
        //Set LEDs state for the next moment of the exceedAlertPeriod
        alertStateOn=(alertStateOn?false:true);
        lastLedOnTime=currentTime;
      };
    } else{  //Switch state is changed from LOW (opened) at previous loop cycle to HIGH (closed) at current loop cycle
      lastLedOnTime=millis();
      lastSwitchState=currentSwitchState;
    }
    break;
  case LOW:  //Tilt switch is in LOW (open) state (reset-state)
    if (currentSwitchState!=lastSwitchState){
      reset();
      lastSwitchState=currentSwitchState;
    };
    break;
  }
}

void reset(){
//Set all LEDs to LOW (switch off)
for (int i=2; i<8; i++){
  digitalWrite(i,LOW);
}
//Set pin of first LED to light on to "2"
ledToLight=2;
}
