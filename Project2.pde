import processing.serial.*;
Serial serialPort;
PImage logo;
int prevBgcolor=0, bgcolor=0;

void setup(){
  colorMode(HSB,255);
  logo=loadImage("https://www.arduino.cc/en/pub/skins/arduinoWide/img/logo.png");
  //size(logo.width,logo.height);
  size(210,146);
  println("Available serial ports:");
  println(Serial.list());
  println("Logo size: "+logo.width+"   "+logo.height);
  serialPort=new Serial (this,Serial.list()[0],9600);
}

void draw(){
  if (serialPort.available()>0){
    prevBgcolor=bgcolor;
    bgcolor=serialPort.read();
    if (bgcolor!=prevBgcolor)  println("Current bgcolor: "+bgcolor);
  }
  background(bgcolor,255,255);
  image(logo,20,20);
}
