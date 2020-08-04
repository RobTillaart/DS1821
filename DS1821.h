#pragma once
//
//    FILE: DS1821.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2014-10-05
// PURPOSE: Arduino library for DS1821 temperature sensor
//     URL: https://github.com/RobTillaart/DS1821
//

#include "Arduino.h"
#include "OneWire.h"

#define DS1821_H_LIB_VERSION     "0.2.0"

#define DS1821_RESET_OK          0
#define DS1821_RESET_ERROR       -999

class DS1821
{
public:
  DS1821(OneWire* ow);
  int        requestTemperature();
  int        conversionReady();
  float      readTemperature();
  int        error()  { return _err; };

private:
  OneWire * _ow;
  int       _err;
  int       _reset()              { return _ow->reset(); };
  void      _command(uint8_t cmd) { _ow->write(cmd); };
  uint8_t   _readByte()           { return _ow->read(); };
};

// -- END OF FILE --
