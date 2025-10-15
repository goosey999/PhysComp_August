/*
<><><><><><><><><><><><><><><><><>
|||||||||||||||||||||||||||||||||
||         "LED BLink"         ||
||          MTEC 2280          ||
|||||||||||||||||||||||||||||||||
<><><><><><><><><><><><><><><><><>
*/

/* 
using 4 leds create at least 6 unique patterns



*/
// pin numbers
const int ledPin0 = 4; //constant integer set to GPIO pin for LED
const int ledPin1 = 5;
const int ledPin2 = 6;
const int ledPin3 = 7;
int sequenceNumber = 0;

const int buttonPin = 15;
const int potPin = 1; //subject to change

bool ledState = false; //1-bit variable

void setup() {
Serial.begin(115200);
pinMode(ledPin0, OUTPUT); //set LED pin to output voltage
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);

pinMode(buttonPin,INPUT_PULLUP);

analogReadResolution(12);//alocates number of bits for analog read - max value of 4095

Serial.println("Initiating!");

}

void loop() {
float knobValue = analogRead(potPin);
Serial.println(knobValue);
Serial.println(!digitalRead(buttonPin));

if (!digitalRead(buttonPin) == 1){ //set sequence # to position of knob after pressing the button

  if (potPin <= 682.5) {
    sequenceNumber = 0;
  } else if (potPin > 682.5 && potPin <= 1365) {
    sequenceNumber = 1;
  } else if (potPin > 1365 && potPin <= 2047.5){
    sequenceNumber = 2;
  } else if (potPin > 2047.5 && potPin <= 2730){
    sequenceNumber = 3;
  } else if (potPin > 2730 && potPin <= 3412.5){
    sequenceNumber = 4;
  } else { // if (potPin > 3412.5)
    sequenceNumber = 5;
  } 

}

//set sequence to sequence number
  if (sequenceNumber <= 0) {
  //sequence 0
  Serial.println("Sequence 0");
  digitalWrite(ledPin0,1); //set LED pin to HIGH, 3.3V
  digitalWrite(ledPin1,0);
  digitalWrite(ledPin2,0); 
  digitalWrite(ledPin3,1);
  delay(500);
  digitalWrite(ledPin0,0); //set LED pin to HIGH, 3.3V
  digitalWrite(ledPin1,1);
  digitalWrite(ledPin2,1); 
  digitalWrite(ledPin3,0);
  delay(500);

  } else if (sequenceNumber == 1){
  //sequence 1
  Serial.println("Sequence 1");
  digitalWrite(ledPin3,0);
  digitalWrite(ledPin0,1);
  delay(250);
  digitalWrite(ledPin0,0);
  digitalWrite(ledPin1,1);
  delay(250);
  digitalWrite(ledPin1,0);
  digitalWrite(ledPin2,1);
  delay(250);
  digitalWrite(ledPin2,0);
  digitalWrite(ledPin3,1);
  delay(250);

  } else if (sequenceNumber == 2){
    //sequence 2
    Serial.println("Sequence 2");
     digitalWrite(ledPin1,0);
    digitalWrite(ledPin3,0);
    digitalWrite(ledPin0,1);
    digitalWrite(ledPin2,1);
    delay(250);
    digitalWrite(ledPin0,0);
    digitalWrite(ledPin2,0);
    digitalWrite(ledPin1,1);
    digitalWrite(ledPin3,1);
    delay(250);
     


  } else if(sequenceNumber == 3){
    //sequence 3
    Serial.println("Sequence 3");
    digitalWrite(ledPin0,0);
    digitalWrite(ledPin1,0);
    digitalWrite(ledPin2,1);
    digitalWrite(ledPin3,1);
    delay(500);
    digitalWrite(ledPin0,1);
    digitalWrite(ledPin1,1);
    digitalWrite(ledPin2,0);
    digitalWrite(ledPin3,0);
    delay(500);
  } else if(sequenceNumber == 4){
    Serial.println("Sequence 4");
    digitalWrite(ledPin0,1);
    digitalWrite(ledPin1,1);
    digitalWrite(ledPin2,1);
    digitalWrite(ledPin3,1);
    delay(250);
    digitalWrite(ledPin0,0);
    digitalWrite(ledPin1,0);
    digitalWrite(ledPin2,0);
    digitalWrite(ledPin3,0);
    delay(250);


  } else if(sequenceNumber >=5){
    Serial.println("Sequence 5");
    digitalWrite(ledPin0,0);
    digitalWrite(ledPin1,1);
    digitalWrite(ledPin2,1);
    digitalWrite(ledPin3,1);
    delay(250);
    digitalWrite(ledPin0,1);
    digitalWrite(ledPin1,0);
    digitalWrite(ledPin2,1);
    digitalWrite(ledPin3,1);
    delay(250);
    digitalWrite(ledPin0,1);
    digitalWrite(ledPin1,1);
    digitalWrite(ledPin2,0);
    digitalWrite(ledPin3,1);
    delay(250);
    digitalWrite(ledPin0,1);
    digitalWrite(ledPin1,1);
    digitalWrite(ledPin2,1);
    digitalWrite(ledPin3,0);
    delay(250);
    
 

  }




}
