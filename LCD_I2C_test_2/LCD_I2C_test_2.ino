/* 
 * Demonstrates the use of Energia to make special characters, print, and do
 * simple animation on an LCD with HD44780 driver and a I2C backpack.
 *
 * Tested with:
 * Addicore 20x4 Character LCD with I2C backpack
 * https://www.addicore.com/2004-20x4-Character-LCD-with-I2C-backpack-p/157.htm
 * Addicore Bi-Directional Logic Level Converter (4 Channel)
 * https://www.addicore.com/Logic-Level-Converter-Bi-Directional-5V-to-3-3V-p/227.htm
 *
 * Tested on Texas Instruments MSP430F5529LP, CC3200, MSP-EXP432P401R
 *
 * NOTE: The LCD is a 5V module! You must translate 3V3 <---> 5V between the
 * LaunchPad and the LCD.  This example uses a level converter module but other
 * ways are possible such as this circuit using 2 BS170 MOSFETs:
 * http://1.bp.blogspot.com/-YFPNzX-u7qw/VV6rlWU5MdI/AAAAAAAAG-Q/S7HydDrpjsk/s1600/LCD_20x4_I2C.JPG
 * 
 * Pin Connections
 * ===============		    MSP430F5529
 * LCD Module    Level Converter    LaunchPad
 * ----------    ---------------    ------------
 * GND           GND                GND
 * VCC           HV                 5V
 * SDA           HV2u
 * SCL           HV1
 *               LV                 3V3
 *               LV2                Pin 15 (SDA)
 *               LV1                Pin 14 (SCL)
 *               GND                GND
 *
 * Microcontroller specific comments
 * ---------------------------------
 * 1) The MSP-EXP430G2  and EXP430FR5969 do not have a 5V pin - supply 5V from elsewhere
 * 2) Some LaunchPads have I2C default on other pins. e.g. for the MSP-EXP432P401R and
 *    CC3200 LaunchPads they are SCL = 9, and SDA = 10     
 * 
 * Adjust the potentiometer on back of the LCD to get good contrast on your display!
 *
 * Example created by Frank Milburn   13 June 2015
 * Released into the public domain
 *
 * Library from DFRobot.com
 */
#include <Wire.h> 
#include "LiquidCrystal_I2C.h"

byte address = 0x38;      // LCD I2C address
int columns = 16;         // number of columns on LCD
int rows = 2;             // number of rows on LCD
LiquidCrystal_I2C lcd(address, columns, rows);  

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();


}

void loop()
{  
  // Clear everything
  lcd.clear();
  
  // Place Energia in first column, first row
  lcd.setCursor(0,0);
  lcd.print("Energia");
  
  // Place rocket ready for launch at right, bottom
 
  lcd.write(0);
  
  // Countdown
   delay(2000); 
}
