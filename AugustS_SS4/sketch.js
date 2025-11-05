//etch-a-sketch


let serial; // declare variable for an instance of the serialport library
let portName = '/dev/tty.usbserial-213320';  // fill in your serial port name here
let options = { baudRate: 9600}; // change the baud rate to match your Arduino code

let inData = 0; // variable for storing incoming serial data
let sensors = [0, 0, 0, 0]; // array to hold sensor values: [button1, button2, pot1, pot2]

let r, g, b; // variables for background color
let diameter = 100; // initial diameter of circle
let grow = 5; // amount to grow or shrink circle diameter

let xPos = 400;
let yPos = 400;

function setup() //setup function runs once at beginning
{
  //P5 SerialPort Setup
  serial = new p5.SerialPort();             // make a new instance of the serialport library

  serial.on('list', printList);             // set a callback function for the serialport list event
  serial.on('connected', serverConnected);  // set callback for connecting to the server
  serial.on('open', portOpen);              // set callback for the port opening
  serial.on('data', serialEvent);           // set callback for when new data received
  serial.on('error', serialError);          // set callback for errors
  serial.on('close', portClose);            // set callback for closing the port

  serial.list();                            // list the serial ports
  serial.open(portName, options);           // open a serial port

  // P5.JS SETUP
  createCanvas(800, 800); //set size of canvas
  textSize(64); // set text size
  textAlign(CENTER, CENTER);  // set text alignment
  strokeWeight(10); // set stroke weight
  stroke(0); // set stroke color
  background(255);  // fill frame w/ background color
  r = 0;
  g = 0;
  b = 0;
}

function draw() //  draw function loops forever at frame rate
{
  
  stroke(r,g,b)
  ellipse(xPos,yPos,10);

  if(keyIsDown(RIGHT_ARROW)){
    xPos +=5;
  }
  if(keyIsDown(LEFT_ARROW)){
    xPos -=5;
  }
  if(keyIsDown(UP_ARROW)){
    yPos -=5;
  }
  if(keyIsDown(DOWN_ARROW)){
    yPos +=5;
  }
  //xPos = map(sensors[2],0,255,0,width); //map pot to x axis
  //yPos = map(sensors[3],0,255,0,height); //map pot to y axis

  if (sensors[0] || keyIsDown(90)){ // if button 1 is pressed...
    r = random(0,255);
    g = random(0,255);
    b = random(0,255);
  }

  if (sensors[1]|| keyIsDown(88)){ // if button 2 is pressed shake
    background(255);
  }

  
  text(sensors, width/2, height - 100); // display incoming serial data as text
}

function printList(portList) // gets called when the serial.list() function is called
{
  print("List of Available Serial Ports: ");
  for (var i = 0; i < portList.length; i++) 
  {
    print(i + portList[i]); //print list of available serial ports to console
  }
}

function serverConnected() //gets called when we connect to the serial server
{
  print("CONNECTED TO SERVER");
}
 
function portOpen() //gets called when the serial port opens
{
  print("SERIAL PORT OPEN");
}
 
function serialEvent() //gets called when new data arrives
{
  let inString = serial.readStringUntil('\n'); // read until newline character
  if (inString.length > 0) //if there's data in the string
  {
    sensors = split(inString, ','); // split the string at commas and store in array
    
    for (let i = 0; i < sensors.length; i++) 
    {
      // Number() function converts string to number
      sensors[i] = Number(sensors[i]); // convert every element in array to numbers

      // You can also use parseInt() function, which takes a second argument for the base (radix).
      // A base of 10 is for decimal numbers, base of 16 is for hexadecimal, base of 2 is for binary.
      // sensors[i] = parseInt(sensors[i], 10); // converts every element in array to decimal number
    }
    //print(sensors);
  } 
}
 
function serialError(err) //gets called when there's an error
{
  print('ERROR: ' + err);
}
 
function portClose() //gets called when the serial port closes
{
  print("*____SERIAL PORT CLOSED");
}