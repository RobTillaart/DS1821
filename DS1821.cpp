//
//    FILE: DS1821.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2014-10-05
// PURPOSE: Arduino library for DS1821 temperature sensor
//     URL: https://github.com/RobTillaart/DS1821
//
// HISTORY:
// 0.0.1    2014-10-05 initial version
// 0.1.00   2015-05-14 added prescale support
// 0.2.0    2020-08-05 initial release; refactored ad fundum.
//


#include "DS1821.h"

#define START_CONVERT        0xEE
#define READ_CONFIG_REG      0xAC
#define READ_TEMPERATURE     0xAA
#define READ_COUNT           0xA0
#define GET_SLOPE            0x41


DS1821::DS1821(OneWire *ow)
{
  _ow = ow;
  _err = DS1821_RESET_OK;
};


int DS1821::requestTemperature()
{
  _err = _reset();
  if (_err == DS1821_RESET_OK)
  {
    _command(START_CONVERT);
    return DS1821_RESET_OK;
  }
  return DS1821_RESET_ERROR;
};


int DS1821::conversionReady()
{
  _err = _reset();
  if (_err == DS1821_RESET_OK)
  {
    _command(READ_CONFIG_REG);
    return ((_readByte() & 0x80) > 0);  // true = 1 / false = 0
  }
  return DS1821_RESET_ERROR;
};


float DS1821::readTemperature()
{
  _err = _reset();
  if (_err != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(READ_TEMPERATURE);
  int temperature = _readByte();
  
  // Handle negative values: >= 200 ==> subtract 256;
  if (temperature >= 200) temperature -= 256;

  _err = _reset();
  if (_err != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(READ_COUNT);
  int countRemain = _readByte() * 256;
  countRemain += _readByte();

  // Load counter to populate the slope accumulator
  _err = _reset();
  if (_err != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(GET_SLOPE);

  _err = _reset();
  if (_err != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(READ_COUNT);

  int countC = _readByte() * 256;
  countC += _readByte();

  return temperature + 0.5 - (1.0 * countRemain) / countC;
};


// -- END OF FILE --
