int notes[]={262,294,330,349};
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
  if (inputSignalValue>=4&&inputSignalValue<=20){
    tone(8,notes[0]);
  } else if (inputSignalValue>=500&&inputSignalValue<=520){
    tone(8,notes[1]);
  } else if (inputSignalValue>=990&&inputSignalValue<=1010){
    tone(8,notes[2]);
  } else if (inputSignalValue>=1020){
    tone(8,notes[3]);
  } else {
    noTone(8);
  }
}
