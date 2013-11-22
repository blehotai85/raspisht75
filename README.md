raspisht75
==========

SHT7x support for Raspberry Pi

This source provides support to use SHT71 and 75 temperature and humidity sensors on a Raspberry Pi. 
Since the sensor's I2C implementation doesn't make it possible to chain multiple sensors to an I2C bus,
there is an opportunity to use up to 15 sensors using the RasPi's GPIO header and Gordon's WiringPi library.

Prereqs:
-
- have a Raspberry Pi model A or B
- have wiringPi installed
- have an SHT75

Installation:
-
- fork this source from Github
- wire SHT75 to the GPIO (see the header file, pin7 is used for SCL, so you can use pins 0-6 or 8-15 for SDA
- place a 10kOhm pullup resistor between +3.3V and SDA
- include the sht7x.h in your code
- use the float measure(unsigned char dataPin, unsigned char value) to measure, where dataPin is th SDA pin and value
is 1 (READTEMPERATURE) for temp reading or 2 (READHUMIDITY) for humidity reading
- compile it with the lwiringpi flag, such like: gcc -o main -liwiringPi mycode.c sht7x.c
