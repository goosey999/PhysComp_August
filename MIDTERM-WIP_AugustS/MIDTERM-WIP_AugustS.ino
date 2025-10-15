/*
Create A 3x3 grid of LEDS that can be indiviually toggled on and off through the use of a Pot and LED


  The project at least should compile without errors, and circuits should be tested.
  If you are having technical issues, these should be well documented and presented so they can be addressed before the midterm final version due date.
  We will playtest in class, so you should integrate that feedback into next iteration.
  WIP should show around 4-5 hours of work at minimum.
  Save as "MIDTERM-WIP_YourName" and push to your GitHub repo before start of class


*/

const int buttonPin = 1;
const int potPin = 2;

bool ledMatrix[] = {0,0,0,0,0,0,0,0,0};

//Row 1
const int ledPin0 = 4;
const int ledPin1 = 5;
const int ledPin2 = 6;
//Row 2
const int ledPin3 = 7;
const int ledPin4 = 15;
const int ledPin5 = 16;

//Row 3
const int ledPin6 = 17;
const int ledPin7 = 18;
const int ledPin8 = 8;

void setup() {
  Serial.begin(115200);
  //Row 1
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  //Row 2
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  //Row 3
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);
  pinMode(ledPin8, OUTPUT);

  pinMode(buttonPin,INPUT_PULLUP);
  analogReadResolution(12);

  Serial.println("Initiating!");
}

void loop() {

  int knobValue = map(analogRead(potPin),0,4095,0,8);//maps pot value to value between 0 and 8
  bool buttonValue = !digitalRead(buttonPin);
  Serial.println(knobValue);
  Serial.println(buttonValue);  
  //Could be replaced with a for loop eventually
  //Row 1
  digitalWrite(ledPin0,ledMatrix[0]);
  digitalWrite(ledPin1,ledMatrix[1]);
  digitalWrite(ledPin2,ledMatrix[2]);
  //Row 2
  digitalWrite(ledPin3,ledMatrix[3]);
  digitalWrite(ledPin4,ledMatrix[4]);
  digitalWrite(ledPin5,ledMatrix[5]);
  //Row 3
  digitalWrite(ledPin6,ledMatrix[6]);
  digitalWrite(ledPin7,ledMatrix[7]);
  digitalWrite(ledPin8,ledMatrix[8]);

  // for (int i = 0; i <= 8; i++){
  //   if (knobValue != i) {


  //   } else {
  //     analogWrite()
  //   }

  // }

  //toggle value of currently selected LED when button is pressed
  if (buttonValue = true) {
    ledMatrix[knobValue] = !ledMatrix[knobValue];
  }
}
