# DS1821

Arduino library for DS1821 temperature sensor (experimental)

## Description

The DS1821 is a temperature sensor that uses the oneWire protocol.

This library supports one sensor per pin.

As this library is tested minimally please consider it experimental.

## Interface

The interface of the library is an async interface so there are no blocking calls.

The return value **DS1821_RESET_ERROR == -999** means that the oneWire bus failed to reset.


- **DS1821(onewire)** initializes the library with a reference to a oneWire object.  
See examples.
- **int requestTemperature()** this call will trigger a conversion of temperature,
however it does not read the temperature. May return **DS1821_RESET_ERROR**
- **int conversionReady()** when the conversion is ready it returns 1, else 0.  
May return **DS1821_RESET_ERROR**
- **float readTemperature()** when conversion is ready, one can fetch the temperature.  
May return **DS1821_RESET_ERROR**
- **int error()** read the last error.

## Operation

See examples.

