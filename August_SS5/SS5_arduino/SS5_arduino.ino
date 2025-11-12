/*
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
||               "Serial Read - PIEZO"                    ||
||  Reads from Serial UART one ASCII character at a time  ||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

- Receives data over Serial UART port from P5 sketch
- Compares incoming ASCII characters to play different notes on piezo buzzer
- Hook up Piezo Buzzer to pin 1 for this example

NOTE: We are using the ESP LED Control (LEDC) API on the ESP32S3 to generate our tone.
You can read more here:
https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html

REFERENCE:
- https://docs.arduino.cc/language-reference/en/functions/communication/serial/read/
- https://docs.arduino.cc/language-reference/en/functions/communication/serial/available/
*/

const int pinRGB = 38;      // Built-in RGB LED pin
const int piezoPin = 1;     // Piezo buzzer pin
const int ledc_channel = 0; // LEDC channel (0 is default)
const int bitDepth = 12;    // Bit depth for LEDC

bool toggle[] = {false,false,false,false,false};

int freqs[] = {0, 220, 330, 440, 660, 880}; //array of frequencies, or pitches, for notes
int note = 0;           //currently selected note in our freqs array
int currentTime = 0;    //variable to store current millis
int lastTime = 0;       //variable to store millis at moment of last event
int timerInterval = 50; //amount of milliseconds for comparison
int brightness = 8;     //LED brightness, max is 255, which is very bright!

void setup() 
{
  Serial.begin(9600); // Initialize serial communication at 9600 baud

  // Attach piezoPin to LEDC channel with base frequency 220Hz and bit depth
  ledcAttachChannel(piezoPin, 220, bitDepth, ledc_channel); 
  //ledcAttachChannel(pin, baseFrequency, bitDepth, channel)
}

void loop() 
{
  
  if(Serial.available())  //if there is data available in the serial buffer
  {
    String rawSerial = Serial.readStringUntil("/n") //read and store that received byte
    toggle = strtok(rawSerial,",");
  }

  for(int i = 0; i <=5; i++){
    if(toggle[i]){
      note = i+1;
      ledcWriteTone(piezoPin, freqs[note]); //generate PWM tone on piezo pin at given frequency
      delay(500);
    }

  }


  
}