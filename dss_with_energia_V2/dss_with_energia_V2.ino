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
 06 - EN              Pin9 (P2.1)
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

#include <LiquidCrystal.h>
LiquidCrystal lcd(P2_0, P2_1, P2_2, P2_3, P2_4, P2_5);

int millios=0;
int ezres=0;
int egyes=0;
long int frekvencia=0;
unsigned elso_negyed=0;
unsigned masodik_negyed=0;
unsigned harmadik_negyed=0;
unsigned negyedik_negyed=0;


#define DDS_CLOCK 125000000

#define  CLOCK  14//8  //pin connections for DDS
#define  LOAD   15//9 
#define  DATA   18//10
#define  RESET  19//11

int button_register=0;

void setup()
{
  pinMode (DATA,  OUTPUT); 
  pinMode (CLOCK, OUTPUT); 
  pinMode (LOAD,  OUTPUT); 
  pinMode (RESET, OUTPUT); 
  //AD9850_init();
  //AD9850_reset();
  lcd.begin(16, 2);
  lcd.print("Hail Hidra!");
  delay(200);
  Serial.begin(9600);
  pinMode(PUSH2, INPUT_PULLUP);
  attachInterrupt(PUSH2, button_press, FALLING);
  lcd.blink();
  lcd.cursor();

}

void loop()
{
  delay(1000);
int setfx= analogRead(A0);
setfx=  map(setfx,0,1023,0,99);

long int test = calculate_freqy(button_register, setfx);

print_lcd(test);
  
//  SetFrequency(40000);

delay(100);

}
/*
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

*/
void print_lcd(long int setfx){

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

long calculate_freqy(int helyiertek, int potimap){
long a=0;
long buffer=0;
long freqy_buffer=0;
//frekvencia=99887766;
  Serial.println("-----------------------");
  
freqy_buffer=frekvencia;
a=  freqy_buffer / 10000000;
buffer= freqy_buffer % 10000000;
elso_negyed= (a * 10) + (buffer / 1000000);

long m =(elso_negyed * 1000000);
long n = freqy_buffer - m;
Serial.println(m);
Serial.println(freqy_buffer);
Serial.println(n);

a=  n / 100000;
buffer= n % 100000;
masodik_negyed= (a * 10) + (buffer / 10000);

long g= ((100 * elso_negyed) + masodik_negyed) * 10000; 
int k= frekvencia-g;
a=  k / 1000;
buffer= k % 1000;
harmadik_negyed= (a * 10) + (buffer / 100);

int h= (harmadik_negyed * 100);
negyedik_negyed= k - h;

  Serial.println(elso_negyed);
  Serial.println(masodik_negyed);
  Serial.println(harmadik_negyed);
  Serial.println(negyedik_negyed);
Serial.print(button_register);
if (helyiertek==0)negyedik_negyed = potimap;
if (helyiertek==1)harmadik_negyed = potimap;
if (helyiertek==2)masodik_negyed = potimap;
if (helyiertek==3)elso_negyed = potimap;

frekvencia= ((elso_negyed * 1000000) + (masodik_negyed * 10000) + (harmadik_negyed * 100) + negyedik_negyed);

return elso_negyed;

}


void button_press(){
if (button_register==3){
  button_register=0;
  }
else {
  button_register++;
}

}



