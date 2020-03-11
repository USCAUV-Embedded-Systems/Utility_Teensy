/*
  SI7021 Temperature Sensory Library
  Leo Zhuang, USC AUV, 2/23/20
*/
#ifndef SI7021_h
#define SI7021_h

#include "Arduino.h"

#define ADDRESS 0x40 
#define READ_TEMP 0xF3


class SI7021
{
  private:
  		double limit;
      double saveTemp;
      bool requestReady;
      double temp_convert(double temp_code);
      bool newRead;
  public:
  	SI7021();
    void requestTemp();
    double readTemp();
    bool overLimit();
    void setLimit(double lim);
    bool isNewValue();
};

#endif