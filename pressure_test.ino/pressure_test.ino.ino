
// Include Required Libraries
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#define ARRAY_LEN     6000
#define ANALOG_PIN    A22
#define LED_PIN       13
#define SAMPLE_TIME   100 //in ms
#define INIT_DELAY    25//in seconds

int data;
bool inital=false;
File myFile;
const int chipSelect = BUILTIN_SDCARD;

void setup() {

  Serial.begin(9600);
  analogReference(0);
  analogReadRes(16);

  
  pinMode(LED_PIN,OUTPUT);
  pinMode(ANALOG_PIN,INPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN, HIGH);
  delay(15000);
  digitalWrite(LED_PIN, LOW);

  delay(1000*INIT_DELAY);
  digitalWrite(LED_PIN, HIGH);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    digitalWrite(LED_PIN, LOW);
    return;
  }
  
  Serial.println("initialization done.");
  myFile = SD.open("realfle.txt", FILE_WRITE);
  for(int i=0;i<ARRAY_LEN;i++){
    delay(SAMPLE_TIME);
    data=analogRead(ANALOG_PIN);  
  // if the file opened okay, write to it:
     if (myFile) {
       myFile.print(data);
       myFile.print(", ");
  // close the file:
     } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    }
  }
  myFile.close();
  Serial.println("done.");
  digitalWrite(LED_PIN, LOW);
  while (!Serial) {;} // wait for serial port to connect
  Serial.println("Connected: awaiting command");
 
}






// ----------------------------------------------------------//
//                    Normal Program Flow
// ----------------------------------------------------------//

void loop(){
while (!Serial) {;} // wait for serial port to connect
  if(!inital){
      Serial.println("Actually made it, send command");
      inital=true;

  }
  int chunk=0;
  char serial_command=0;
  
    if (Serial.available() > 0) {
       // Serial.println("Connected: awaiting commansdefrgtd");

      serial_command=processIncomingByte (Serial.read ());
      switch (serial_command){
        case '1':
         for(int i=0;i<ARRAY_LEN;i++){
           // Serial.print(data[i]);
            Serial.print(", ");
        }
        break;
        
        case '2':
         for(int i=0;i<ARRAY_LEN;i++){
          //  Serial.println(data[i]);
          }
        break;
        
        case '3':
         for(int i=chunk;i<chunk+100;i++){
          //  Serial.print(data[i]);
            Serial.print(", ");
        }
        break;
      }   
    }
}

inline char process_data (const char * data)
  {
  return *data;
  }  // end of process_data
  
inline char processIncomingByte (const byte inByte)
  {
  static char input_line [50];
  static unsigned int input_pos = 0;
  char data=0;
  switch (inByte)
    {

    case '\n':   // end of text
      input_line [input_pos] = 0;  // terminating null byte
      
      // terminator reached! process input_line here ...
      data=process_data (input_line);
      
      // reset buffer for next time
      input_pos = 0;  
      break;

    case '\r':   // discard carriage return
      break;

    default:
      // keep adding if not full ... allow for terminating null byte
      if (input_pos < (50 - 1))
        input_line [input_pos++] = inByte;
      break;

    }  // end of switch
   return data;
  } // end of processIncomingByte  
  
