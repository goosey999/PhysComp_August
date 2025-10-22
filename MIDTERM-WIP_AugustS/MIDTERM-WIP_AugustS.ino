/*
Create A 3x3 grid of LEDS that can be indiviually toggled on and off through the use of a Pot and LED


  The project at least should compile without errors, and circuits should be tested.
  If you are having technical issues, these should be well documented and presented so they can be addressed before the midterm final version due date.
  We will playtest in class, so you should integrate that feedback into next iteration.
  WIP should show around 4-5 hours of work at minimum.
  Save as "MIDTERM-WIP_YourName" and push to your GitHub repo before start of class


*/
//add Debounce protection?

const int cursorBrightness = 127;
const int buttonPin = 1;
const int potPin = 2;

bool ledMatrix[] = {0,0,0,0,0,0,0,0,0}; //LED digital value
const int ledPinArray[] = {4,5,6,7,15,16,17,18,8}; //array of led arduino pins

void setup() {
  Serial.begin(115200);

  //set led Pins to OUTPUT
  for (int i = 0; i <= 8; i++){
    pinMode(ledPinArray[i], OUTPUT);
  }

  //set button pin to INPUT Pullup (remember values are reveresed)
  pinMode(buttonPin,INPUT_PULLUP);

  //set read resolution (12bit means 0-4095)
  analogReadResolution(12);

  Serial.println("Initiating!");
}


void loop() {
  //map pot value to value between 0 and 8
  int knobValue = map(analogRead(potPin),0,4095,0,8);
  bool buttonValue = !digitalRead(buttonPin);
  Serial.println(knobValue);
  Serial.println(buttonValue);    

  
  for (int i = 0; i <= 8; i++){
    if (knobValue != i){
      //set led pin to value stored in array
      digitalWrite(ledPinArray[i],ledMatrix[i]);

    } else{
      Serial.printf("LED %i is set to %b ",knobValue,ledMatrix[i]);
      //dim currently selected led
      analogWrite(ledPinArray[i],cursorBrightness); 
    }
  }

  //toggle value of currently selected LED when button is pressed
  if (buttonValue = true) {
    ledMatrix[knobValue] = !ledMatrix[knobValue];
  }
}
