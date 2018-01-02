/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.

 The circuit:
 =================================
 LCD pin              Connect to
 ---------------------------------
 01 - GND             GND, pot
 02 - VCC             +5V, pot
 03 - Contrast        Pot wiper
 04 - RS              Pin8 (P2.0)
 05 - R/W             GND
 06 - EN1             Pin9 (P2.1)
 -    EN2             pin7  P1.5
 -    EN3             pin6  P1.4
 07 - DB0             GND
 08 - DB1             GND
 09 - DB2             GND
 10 - DB3             GND
 11 - DB4             Pin10 (P2.2)
 12 - DB5             Pin11 (P2.3)
 13 - DB6             Pin12 (P2.4)
 14 - DB7             Pin13 (P2.5)
 15 - BL+             +5V
 16 - BL-             GND
 =================================

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(P2_0, P2_1, P1_5, P1_4 , P2_2, P2_3, P2_4, P2_5);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(20, 4);
  lcd.setCursor(0, 1, 3);
  // Print a message to the LCD.
 //lcd.print("hello, world!");
}

void loop() {
  //int d=0;
  for (int d=0;d<=9;d++){
  for(int p=0;p<=19;p++){
  for (int i=1;i<=3;i++){
    for (int o=0;o<=3;o++){
    lcd.setCursor(p, o, i);
    lcd.print("fasz!");
    delay(10);
    }
    
  }
  }
  }
}
