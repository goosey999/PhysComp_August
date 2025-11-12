//Flappy ellipse

let serial; // declare variable for an instance of the serialport library
let portName = '/dev/tty.usbserial-2110';  // fill in your serial port name here
let options = { baudRate: 9600}; // change the baud rate to match your Arduino code

let inData = 0; // variable for storing incoming serial data
let sensors = [0, 0, 0, 0]; // array to hold sensor values: [button1, button2, pot1, pot2]





let gravity = -5;
let positionY = 400;
let scrollSpeed = 2;
let rectX = 450;
let gapY = 400;
let playerS = 80;
let score = 0;

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

  //TYPICAL P5.JS SETUP
  createCanvas(400, 800); //set size of canvas
  textSize(64); // set text size
  textAlign(CENTER, CENTER);  // set text alignment
  strokeWeight(10); // set stroke weight
  stroke(0); // set stroke color
  rectMode(CENTER);
  
}

function draw() //draw function loops forever at frame rate
{

  positionY -= gravity;
 
  background(0,200,200);


  if (sensors[0] || keyIsDown(UP_ARROW)) //if button 1 is pressed...
  {
     gravity = 10;
  } else { 
    gravity = -5;
  }

  if (positionY >= height || positionY <= 0){
   
   gameOver();

  }  

  // scrollSpeed = score + 1

  rectX -= scrollSpeed;
    if(rectX < -50){
      rectX = width;
      gapY = random(170,630);
    }
  //create "pipes" with gap between them. each pipe moves across the screen and resets when it reaches the end
  fill(0,255,0);
  noStroke();
  rect(rectX,height/2,50,height);

  //gap position
  fill(0,200,200);
  rect(rectX,gapY,50,300);

  // //hitbox visualize
  // fill(255,0,0);
  // rect(rectX,gapY,50,300);
  // fill(0,20,20);

  //create player
  stroke(1);
  fill(255,255,0);
  circle(width/2, positionY, playerS);

//if player is touching the "pipe" and !the gap then game over

  if(width/2 == rectX){ 
    if(positionY <= gapY + 150 && positionY >= gapY - 150){
      score ++; 
    } else{
      gameOver();
    }
    
  }

    fill(255); // set fill color for text
    text(score, width/2, 100); // display incoming serial data as text

}

function gameOver(){
 //console.log("end");
  score = 0;
  rectX = 450;


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
  if (inString.length > 0) //if there's something there, a value, some data...
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
