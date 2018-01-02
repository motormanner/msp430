//8  7  6  5  4  3  2  1
//RS RW E  BL D4 D5 D6 D7

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;

  uint8_t _initialized;

  uint8_t _numlines,_currline;
  
  
uint8_t PFC8574A=0x3f;
uint8_t device_address=0x3f;
uint8_t D7=0b10000000;
uint8_t D6=0b01000000;
uint8_t D5=0b00100000;
uint8_t D4=0b00010000;
uint8_t BL=0b00001000;
uint8_t E= 0b00000100;
uint8_t RW=0b00000010;
uint8_t RS=0b00000001;

int w1;
int w2;
int value;

uint8_t endStatus;

uint8_t flag_BL=1;
uint8_t flag_iic_ACK;
#include <Wire.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("Start!");
  
  _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
//end of i2c init----------------------------------------------------------------------
  _displayfunction |= LCD_2LINE;
  _numlines = 2;
  _currline = 0;
  
  
  Wire.setModule(0);
  Wire.begin();
  

  delayMicroseconds(50000); 
  sendFragment(0b0000);
  sendFragment(0b0011);
  delayMicroseconds(4500); // wait min 4.1ms
  sendFragment(0b0011);
  delayMicroseconds(4500); // wait min 4.1ms
  sendFragment(0b0011);
  delayMicroseconds(150);
  sendFragment(0b0010);
  //--------------------------------------------------------------------
 
  
  value=LCD_FUNCTIONSET | _displayfunction;
  send4bit(value);
  
  _displaycontrol = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKON;
  _displaycontrol |= LCD_DISPLAYON;
  
  
  value=LCD_DISPLAYCONTROL | _displaycontrol;
  send4bit(value);
 


  value=LCD_CLEARDISPLAY;
  send4bit(value);
  

  delayMicroseconds(2000);

  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  
  //command(LCD_ENTRYMODESET | _displaymode);
  
  value=LCD_ENTRYMODESET | _displaymode;
  send4bit(value);
 
  
  value=LCD_RETURNHOME;
  send4bit(value);
 
  delayMicroseconds(2000);
}


void loop()
{
   // sendFragment(0b0011);
delay(3);

}


void send4bit(uint8_t message){
Serial.print("mesage: ");
Serial.println(message,BIN);
  
int highBits =message>>4;
int lowBits  =message&0b00001111;
  Serial.print("high: ");
  Serial.print(highBits,BIN);
  Serial.print(" low: ");
  Serial.println(lowBits,BIN);
  sendFragment(highBits);
  sendFragment(lowBits);
  

}

void sendFragment(uint8_t fragment){
  Serial.println(">-------------");
  int temp_rs=0;
  i2c_LCD_packet(fragment,0,temp_rs);
  delayMicroseconds(1);
  
  i2c_LCD_packet(fragment, 1,temp_rs);
  delayMicroseconds(1);
  
  i2c_LCD_packet(fragment,0,temp_rs);
  delayMicroseconds(100);
  Serial.println("<---------");
}

void i2c_LCD_packet(uint8_t fragment, boolean E_active, boolean RS_active){

  uint8_t message=fragment<<4;
  Wire.beginTransmission(device_address);
  if (E_active)message|=E;
  if (RS_active)message|=RS;
  message|=BL;
  Wire.write(message);
  Serial.print("fragment: ");
  Serial.print(message,BIN);
  flag_iic_ACK = Wire.endTransmission();
  if (flag_iic_ACK)Serial.println(" OK");
  else Serial.println("E!");
}
