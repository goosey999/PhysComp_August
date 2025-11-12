let serial;                                 // variable for instance of the serialport library
let portName = '/dev/tty.usbserial-213320'; // fill in your serial port name
let options = { baudRate: 9600};            // change the baud rate to match your Arduino code
let outByte = 0;                            // 8-bit data to send to microcontroller




let toggle = [false,false,false,false,false];


function setup() {
  createCanvas(800, 800);


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

}

function draw() {
  background(220);
  
  for(let i = 0; i <= 8; i++){
    if(toggle[i]){
    fill(255,0,0);
    } else {
    fill(0,0,255);
    }

    rect(0+(i*width/5),height/2-400,width/5,800);

  }
  



}

function keyPressed() //when a key is pressed...
{
  if(key === 'a'){
    togglej = join(toggle,',');
    serial.write(togglej+"/n"); //send ASCII value of the key pressed via serial port
    console.log(togglej+"/n");
  }
}


function mouseClicked(){
  for(let i = 0; i <= 8; i++){
    if (mouseX > i*width/5 && mouseX < (i+1)*width/5){
    toggle[i] = !toggle[i];
    }


  }
 

}

//Serial Functions

function portOpen() //gets called when the serial port opens
{
  print("SERIAL PORT OPEN");
}

function portClose() //gets called when the serial port closes
{
  print("SERIAL PORT CLOSED");
}

function printList(portList) // gets called when the serial.list() function is called
{
  print("List of Available Serial Ports: ");
  for (var i = 0; i < portList.length; i++) 
  {
    print(i + portList[i]); //print list of available serial ports to console
  }
}

function serialEvent() // gets called when new serial data arrives
{
  //only sending data to microcontroller in this sketch, so not being used
}

function serialError(err) //gets called when there's an error
{
  print('ERROR: ' + err);
}

function serverConnected() //gets called when we connect to the serial server
{
  print("CONNECTED TO SERVER");
}