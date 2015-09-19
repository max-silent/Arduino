int notes[]={262,294,330,349,392,440,494};
int inputSignalValue;
int outputLogCounter=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  inputSignalValue=analogRead(A0);
  if (millis()%1000==0){
    if (outputLogCounter==0){
     Serial.println(inputSignalValue);
     outputLogCounter++;
    }
  } else{
    outputLogCounter=0;
  }
  if (inputSignalValue>=1015){
    tone(8,notes[0]);
  } else if (inputSignalValue>=995&&inputSignalValue<=1010){
    tone(8,notes[1]);
  } else if (inputSignalValue>=975&&inputSignalValue<=990){
    tone(8,notes[2]);
  } else if (inputSignalValue>=955&&inputSignalValue<=970){
    tone(8,notes[3]);
  } else if (inputSignalValue>=935&&inputSignalValue<=950){
    tone(8,notes[4]);
  } else if (inputSignalValue>=915&&inputSignalValue<=930){
    tone(8,notes[5]);
  } else if (inputSignalValue>=900&&inputSignalValue<=910){
    tone(8,notes[6]);
  } else {
    noTone(8);
  }
}
