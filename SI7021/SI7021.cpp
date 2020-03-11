/*
SI7021 Temperature Sensory Library
Leo Zhuang, USC AUV, 2/23/20
*/
//#include "Arduino.h"
#include "SI7021\SI7021.h"
#include <Wire.h>



SI7021::SI7021(){
//Constructor
  limit = 30;
  requestReady = true;
  saveTemp = 0;
  newRead = false;
}

double SI7021::temp_convert(double temp_code){
  //converts temperature code recieved in I2C into Celcius
  return ((175.72*temp_code/65536)-46.85);  
}

void SI7021::requestTemp(){
  Wire1.beginTransmission(ADDRESS);
  Wire1.write(READ_TEMP);
  Wire1.endTransmission();
}

double SI7021::readTemp(){
//read temperature
  int temp_code = 0;
  if(requestReady){
    requestTemp();
    requestReady = false;
  }


  Wire1.requestFrom(ADDRESS,2,true);
    //read one byte, shift up, read another byte
    if (2 <= Wire1.available()) {
      temp_code = Wire1.read();
      temp_code = temp_code << 8;
      temp_code |= Wire1.read();
      requestReady = true;
      //Serial.println(temp_convert(temp_code)); //Prints the current temp;
      //Wire.endTransmission();
      saveTemp = temp_convert(temp_code);
    }
    return saveTemp;

}

void SI7021::setLimit(double lim){
  limit = lim;
}

bool SI7021::overLimit(){
  //Checks if temp is over limit
  double temp = readTemp();
  return(temp > limit);
}

bool SI7021::isNewValue(){
	//checks if last reading was new;
	return requestReady;
}