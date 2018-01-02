//AD9850 DDS test
/*
 Hitachi HD44780 
 The circuit:
 =================================
 LCD pin              Connect to
 ---------------------------------
 01 - GND             GND, pot
 02 - VCC             +5V, pot
 03 - Contrast        Pot wiper
 04 - RS              Pin8 (P2.0)
 05 - R/W             GND
 06 - EN              Pin9 (P2.1)uint16_t
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

*/
#include <stdint.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(P2_0, P2_1, P2_2, P2_3, P2_4, P2_5);

uint16_t button_press_flag=0;

uint16_t elso_negyed=0;
uint16_t masodik_negyed=0;
uint16_t harmadik_negyed=0;
uint16_t negyedik_negyed=0;


#define DDS_CLOCK 125000000

#define  CLOCK  14//8  //pin connections for DDS
#define  LOAD   15//9 
#define  DATA   18//10
#define  RESET  19//11

uint16_t button_register=0;

void setup()
{
  pinMode (DATA,  OUTPUT); 
  pinMode (CLOCK, OUTPUT); 
  pinMode (LOAD,  OUTPUT); 
  pinMode (RESET, OUTPUT); 
  AD9850_init();
  AD9850_reset();
  lcd.begin(16, 2);
  lcd.print("Hail Hidra!");
  delay(200);
  Serial.begin(9600);
  pinMode(PUSH2, INPUT_PULLUP);
  attachInterrupt(PUSH2, button_press, FALLING);
  lcd.blink();
  lcd.cursor();
    delay(100);


}

void loop()
{
  
  if (button_press_flag){
 button_handler();
 button_press_flag=0;
    }
uint16_t setfx= analogRead(A0);
setfx=  map(setfx,0,1023,0,99);
calculate_freqy(button_register, setfx);

print_lcd();
  
  SetFrequency((elso_negyed * 1000000) + (masodik_negyed * 10000) + (harmadik_negyed * 100) + negyedik_negyed);

delay(100);

}

void SetFrequency(unsigned long frequency)
{
  unsigned long tuning_word = (frequency * pow(2, 32)) / DDS_CLOCK;
  digitalWrite (LOAD, LOW); 

  shiftOut(DATA, CLOCK, LSBFIRST, tuning_word);
  shiftOut(DATA, CLOCK, LSBFIRST, tuning_word >> 8);
  shiftOut(DATA, CLOCK, LSBFIRST, tuning_word >> 16);
  shiftOut(DATA, CLOCK, LSBFIRST, tuning_word >> 24);
  shiftOut(DATA, CLOCK, LSBFIRST, 0x0);
  digitalWrite (LOAD, HIGH); 
}

void AD9850_init()
{

  digitalWrite(RESET, LOW);
  digitalWrite(CLOCK, LOW);
  digitalWrite(LOAD, LOW);
  digitalWrite(DATA, LOW);
}

void AD9850_reset()
{
  //reset sequence is:
  // CLOCK & LOAD = LOW
  //  Pulse RESET high for a few 5uS (use 5 uS here)
  //  Pulse CLOCK high for a few 5uS (use 5 uS here)
  //  Set DATA to ZERO and pulse LOAD for a few 5uS (use 5 uS here)

  // data sheet diagrams show only RESET and CLOCK being used to reset the device, but I see no output unless I also
  // toggle the LOAD line here.

  digitalWrite(CLOCK, LOW);
  digitalWrite(LOAD, LOW);

  digitalWrite(RESET, LOW);
  delay(5);
  digitalWrite(RESET, HIGH);  //pulse RESET
  delay(5);
  digitalWrite(RESET, LOW);
  delay(5);

  digitalWrite(CLOCK, LOW);
  delay(5);
  digitalWrite(CLOCK, HIGH);  //pulse CLOCK
  delay(5);
  digitalWrite(CLOCK, LOW);
  delay(5);
  digitalWrite(DATA, LOW);    //make sure DATA pin is LOW

    digitalWrite(LOAD, LOW);
  delay(5);
  digitalWrite(LOAD, HIGH);  //pulse LOAD
  delay(5);
  digitalWrite(LOAD, LOW);
  // Chip is RESET now
}


void print_lcd(){

lcd.clear();
lcd.setCursor(0, 1);
if(elso_negyed<10)lcd.print("0");
lcd.print(elso_negyed);
lcd.print(".");
if(masodik_negyed<10)lcd.print("0");
lcd.print(masodik_negyed);
lcd.print(".");
if(harmadik_negyed<10)lcd.print("0");
lcd.print(harmadik_negyed);
lcd.print(".");
if(negyedik_negyed<10)lcd.print("0");
lcd.print(negyedik_negyed);

lcd.print("Hz");
if (button_register==0)lcd.setCursor(10, 1);
if (button_register==1)lcd.setCursor(7, 1);
if (button_register==2)lcd.setCursor(4, 1);
if (button_register==3)lcd.setCursor(1, 1);
}

uint16_t calculate_freqy(uint16_t helyiertek, uint16_t potimap){

//long freqy_buffer=0;
//frekvencia=99887766;
  Serial.println("-----------------------");
    Serial.println(potimap);

//freqy_buffer=frekvencia;
//uint16_t  felso = frekvencia / 10000;
//  uint16_t also = frekvencia % 10000;
 /* 
  elso_negyed= felso / 100;
  masodik_negyed = felso % 100;

  harmadik_negyed= also / 100;
  negyedik_negyed = also % 100;
*/
  Serial.println(elso_negyed);
  Serial.println(masodik_negyed);
  Serial.println(harmadik_negyed);
  Serial.println(negyedik_negyed);
Serial.print(button_register);
if (helyiertek==0)negyedik_negyed = potimap;
if (helyiertek==1)harmadik_negyed = potimap;
if (helyiertek==2)masodik_negyed = potimap;
if (helyiertek==3)elso_negyed = potimap;

//frekvencia= ((elso_negyed * 1000000) + (masodik_negyed * 10000) + (harmadik_negyed * 100) + negyedik_negyed);

return 0;

}


void button_press(){
  button_press_flag=1;
}


void button_handler(){
if (button_register==3){
  button_register=0;
  }
else {
  button_register++;
}
delay(50);
}

