/*
 AD9850.h - Library for adding simple AD9850 control capabilities on MSP430
 
 Copyright 2012 Yannick DEVOS under GPL 3.0 license
 Any commercial use or inclusion in a kit is subject to author approval
 
 Based on work by G7UVW
 
 ====
 Revision history :
 v1.00    2012-12-16
 First release
 
 ====
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You can download a copy of the GNU General Public License at <http://www.gnu.org/licenses/>
 
 */
 
// include this library's description file
#include <AD9850.h>
//#include <legacymsp430.h>
 
#define DDS_CLOCK 125000000
 
// Constructor /////////////////////////////////////////////////////////////////
uint8_t _DDSpinClock;
uint8_t _DDSpinLoad;
uint8_t _DDSpinData;
uint8_t _DDSpinReset;
 
AD9850::AD9850(uint8_t pinClock, uint8_t pinLoad, uint8_t pinData, uint8_t pinReset)
{
    _DDSpinClock = pinClock;
    _DDSpinLoad = pinLoad;
    _DDSpinData = pinData;
    _DDSpinReset = pinReset;
 
};
 
// Methods /////////////////////////////////////////////////////////////////
 
void AD9850::begin()
{
    pinMode (_DDSpinClock, OUTPUT); 
    pinMode (_DDSpinLoad,  OUTPUT); 
    pinMode (_DDSpinData,  OUTPUT); 
    pinMode (_DDSpinReset, OUTPUT);
 
    digitalWrite(_DDSpinReset, LOW);
    digitalWrite(_DDSpinClock, LOW);
    digitalWrite(_DDSpinLoad, LOW);
    digitalWrite(_DDSpinData, LOW);     
}
 
void AD9850::reset()
{
    //reset sequence is:
    // CLOCK & LOAD = LOW
    //  Pulse RESET high for a few uS (use 5 uS here)
    //  Pulse CLOCK high for a few uS (use 5 uS here)
    //  Set DATA to ZERO and pulse LOAD for a few uS (use 5 uS here)
 
    // data sheet diagrams show only RESET and CLOCK being used to reset the device, but I see no output unless I also
    // toggle the LOAD line here.
 
    digitalWrite(_DDSpinClock, LOW);
    digitalWrite(_DDSpinLoad, LOW);
 
    digitalWrite(_DDSpinReset, LOW);
    delay(5);
    digitalWrite(_DDSpinReset, HIGH);  //pulse RESET
    delay(5);
    digitalWrite(_DDSpinReset, LOW);
    delay(5);
 
    digitalWrite(_DDSpinClock, LOW);
    delay(5);
    digitalWrite(_DDSpinClock, HIGH);  //pulse CLOCK
    delay(5);
    digitalWrite(_DDSpinClock, LOW);
    delay(5);
    digitalWrite(_DDSpinData, LOW);    //make sure DATA pin is LOW
 
    digitalWrite(_DDSpinLoad, LOW);
    delay(5);
    digitalWrite(_DDSpinLoad, HIGH);  //pulse LOAD
    delay(5);
    digitalWrite(_DDSpinLoad, LOW);
    // Chip is RESET now
}
 
void AD9850::SetFrequency(unsigned long frequency, boolean powerdown)
{
    unsigned long tuning_word = (frequency * 4294967296 ) / (DDS_CLOCK*10);  // As frequency is in tens of Hertz, we need to multiply by 10
    digitalWrite (_DDSpinLoad, LOW); 
 
    shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word);
    shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word >> 8);
    shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word >> 16);
    shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, tuning_word >> 24);
    if (powerdown)
        shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, B00000100);   // If powerdown is true then send PowerDown command
    else
        shiftOut(_DDSpinData, _DDSpinClock, LSBFIRST, 0x0);
 
    digitalWrite (_DDSpinLoad, HIGH); 
}
