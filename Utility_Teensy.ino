#include <Wire.h>
#include <Servo.h>
#include <Stdint.h>

#define PRESSURE_PIN A0
#define TORPEDO_PIN 8

//declare variables

//declare the buffer
String i2c_read;

Servo marker_dropper;

const int I2C_ADDRESS = 0x08; //I2C_ADDRESS
//I2C_ADDRESS

int pressure;

int pos = 0;    // variable to store the servo position 
uint8_t checksum;
uint16_t temp;
char id;
bool flag = false;

int readPressure();

void setup()
{
  // put your setup code here, to run once:
  marker_dropper.attach(9); 
  pinMode(PRESSURE_PIN, INPUT);
  pinMode(TORPEDO_PIN, OUTPUT);
  //set read pin
  
  Wire.begin(I2C_ADDRESS); //join I2C as slave with I2C_ADDRESS
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  
}

void loop() 
{  
//     for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
//  {                                  // in steps of 1 degree 
//    marker_dropper.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(15);                       // waits 15ms for the servo to reach the position 
//  } 
//  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
//  {                                
//    marker_dropper.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(15);                       // waits 15ms for the servo to reach the position 
//  } 
// 
  
}

int readPressure(){

  return analogRead(PRESSURE_PIN);

}

void receiveEvent(int num) {

  while(Wire.available()) {
    id = Wire.read();
  }
  

  if(!flag) {
    
    switch(id) {
    
     case 'a':
       flag = true;
       Serial.println(id);
       break;

     case 'b':
       pressure = readPressure();
       Wire.write(pressure);
       break;
      
     case 'c':
       Wire.requestFrom(0x40, 3);
       temp = Wire.read() << 8 | Wire.read();
       checksum = Wire.read();
       Wire.write(temp);
       break;
      
     case 'd':
        digitalWrite(TORPEDO_PIN, HIGH);
        break;
    case 'B':
     for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    marker_dropper.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    marker_dropper.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
    break;
     default:
        break;
  
    }
  } 
  
  else {
    
    //marker_dropper.write((int)id);
    marker_dropper.write(180);
    flag = false;
    delay(1000);
    marker_dropper.write(0);
    
  }

}
