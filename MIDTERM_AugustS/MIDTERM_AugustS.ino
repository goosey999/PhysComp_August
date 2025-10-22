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
const int buttonPin = 40;
const int potPin = 39;

bool ledMatrix[] = {1,1,1,1,1,1,1,1,1}; //LED digital value

int ledRowPins[] = {1,2,42};

int ledColumnPins[] = {6,5,4};


void setup() {
  Serial.begin(115200);

  //setup Row Pins
  for(int i = 0; i < 3; i++){
    pinMode(ledRowPins[i],OUTPUT);
    digitalWrite(ledRowPins[i],HIGH);
  } 

  //setup Column Pins
  for(int i = 0; i < 3; i++){
    pinMode(ledColumnPins[i],OUTPUT);
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

  multiplexer(ledMatrix);
  


  //toggle value of currently selected LED when button is pressed
  if (buttonValue = true) {
    ledMatrix[knobValue] = !ledMatrix[knobValue];
  }

  

}




void multiplexer(bool stateArray[]){

//for each row:
// 1. Turn off all rows except the current one
// 2. Turn on or off Column Pins based on Binary array
// 3. add delay (eventually based on a timer)

int numberOfRows = 3;
int numberOfColumns = 3;

  //for each row
  for (int i = 0; i < numberOfRows; i++){ //i starts at 0; i has a max of numberOfRows-1; i increased by 1 each time
    
    //Turn off all rows except current one
    for (int k = 0; k < numberOfColumns; k++){
    digitalWrite(ledColumnPins[k], HIGH);
    }

    for (int j = 0; j < numberOfRows; j++){ //j starts at 0; j has a max of numberOfRows-1; j increases by 1 each time
      if(i != j){
        digitalWrite(ledRowPins[j],HIGH);//use j here because i != j
      } else{
        digitalWrite(ledRowPins[i],LOW);//use i here because i = j
      }
    }
    //Turn on or off Column Pins based on Binary array
    for(int k = 0; k < numberOfColumns; k++){//k starts at 0; k has a max of numberOfColumns-1; k increases by 1 each time
      if(stateArray[(numberOfColumns*i)+k]){ //k has to match the current row
       digitalWrite(ledColumnPins[k],LOW); //enable Column Pin k
      } else{
        digitalWrite(ledColumnPins[k],HIGH); // disable Column Pin k
      }
    }
    //add delay (eventually based on a timer)
    delay(5);

  }

 }
