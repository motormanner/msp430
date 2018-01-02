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

//character set starts from 0x20 and it is " "(space)
//numbers starts from 0x30
//capitals starts from 0x41
//letters start from 0x61

char ascii_characters[127]={ '_','!','_','#','$','%','&','_','(',')','*','+','_','-','.','_','0','1','2','3','4','5','6','7','8','9',':','_','<','=','>','?','_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_','_','_','^','_','`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','_','|','_','~'};

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
  sendFragment(0b0000,0);
  sendFragment(0b0011,0);
  delayMicroseconds(4500); // wait min 4.1ms
  sendFragment(0b0011,0);
  delayMicroseconds(4500); // wait min 4.1ms
  sendFragment(0b0011,0);
  delayMicroseconds(150);
  sendFragment(0b0010,0);
  //--------------------------------------------------------------------
  value=LCD_FUNCTIONSET | _displayfunction;
  send4bit(value,0);
  _displaycontrol = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKON;
  _displaycontrol |= LCD_DISPLAYON;
  value=LCD_DISPLAYCONTROL | _displaycontrol;
  send4bit(value,0);
  value=LCD_CLEARDISPLAY;
  send4bit(value,0);
  delayMicroseconds(2000);
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  //command(LCD_ENTRYMODESET | _displaymode);
  value=LCD_ENTRYMODESET | _displaymode;
  send4bit(value,0);
  value=LCD_RETURNHOME;
  send4bit(value,0); 
  delayMicroseconds(2000);

}


void loop()
{
   // sendFragment(0b0011);
delay(3);
test_pattern_2(2000);
setCursor(0,0);
char cucc='b';
value=0x41;
for (int i=0; i<=127;i++){
  char bigyo =ascii_characters[i];
if (bigyo==cucc) value=i;
}
  send4bit(value,1);
delay(4000);

}


void send4bit(uint8_t message, uint8_t print_to_screen){
  //divide the 8 bit data to 2 four bit packets
int highBits =message>>4;
int lowBits  =message&0b00001111;
  sendFragment(highBits, print_to_screen);
  sendFragment(lowBits, print_to_screen);
}

void sendFragment(uint8_t fragment, uint8_t RS_bit){
  //sending 4 bits of data to the LCD
  int temp_rs=0;
  //the following 3 steps pulsating E to tell LCD circuit it is a message
  i2c_LCD_packet(fragment,0,RS_bit);
  delayMicroseconds(1);
  i2c_LCD_packet(fragment, 1,RS_bit);
  delayMicroseconds(1);
  i2c_LCD_packet(fragment,0,RS_bit);
  delayMicroseconds(100);
}

void i2c_LCD_packet(uint8_t fragment, boolean E_active, boolean RS_active){
//assembling the i2c packet to create the right output according to the LCD pinout
  uint8_t message=fragment<<4;//moving the data to the right position
  Wire.beginTransmission(device_address);//open i2c connection
  if (E_active)message|=E;//set E pin's bit if necessary
  if (RS_active)message|=RS;//set RS pin's bit if necessary
  message|=BL;//set Back Light pin's bit
  Wire.write(message);//sending i2c message
  flag_iic_ACK = Wire.endTransmission(); //closing connection and saving acknowledgement
  if (flag_iic_ACK);
}

void setCursor(uint8_t col, uint8_t row)
{
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if ( row >= _numlines ) {
    row = _numlines-1;    // we count rows starting w/0
  }
  
  send4bit(LCD_SETDDRAMADDR | (col + row_offsets[row]),0);
}


void i2c_lcd_clear(){
send4bit(LCD_CLEARDISPLAY,0);  // clear display, set cursor position to zero
  delayMicroseconds(2000);
}

//--------------------------------------------------------------------------------------------------

// Turn the display on/off (quickly)
void i2c_lcd_set_display(uint8_t control) {
  if(control){
  _displaycontrol &= ~LCD_DISPLAYON;
  send4bit(LCD_DISPLAYCONTROL | _displaycontrol,0);
}
if(!control) {
  _displaycontrol |= LCD_DISPLAYON;
  send4bit(LCD_DISPLAYCONTROL | _displaycontrol,0);
}
}

// Turns the underline cursor on/off
void i2c_lcd_set_cursor(uint8_t control) {
  if(control){
  _displaycontrol &= ~LCD_CURSORON;
  send4bit(LCD_DISPLAYCONTROL | _displaycontrol,0);
}
if(!control) {
  _displaycontrol |= LCD_CURSORON;
  send4bit(LCD_DISPLAYCONTROL | _displaycontrol,0);
}
}

// Turn on and off the blinking cursor
void i2c_lcd_set_cursor_blink(uint8_t control) {
  if (control){
  _displaycontrol &= ~LCD_BLINKON;
  send4bit(LCD_DISPLAYCONTROL | _displaycontrol,0);
}
if(!control) {
  _displaycontrol |= LCD_BLINKON;
  send4bit(LCD_DISPLAYCONTROL | _displaycontrol,0);
}
}
// These commands scroll the display without changing the RAM
void i2c_lcd_scroll_right() {
  send4bit(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT,0);
}
void i2c_lcd_scroll_left() {
  send4bit(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT,0);
}

// This is for text that flows Left to Right
void i2c_lcd_flow_left() {
  _displaymode |= LCD_ENTRYLEFT;
  send4bit(LCD_ENTRYMODESET | _displaymode,0);
}

// This is for text that flows Right to Left
void i2c_lcd_flow_right() {
  _displaymode &= ~LCD_ENTRYLEFT;
  send4bit(LCD_ENTRYMODESET | _displaymode,0);
}







//-----------------------------------------------------------------------------------
void test_pattern_1(){
  value=0x32;
  send4bit(value,1); 
  value=0x33;
  send4bit(value,1); 
  value=0x34;
  send4bit(value,1);
 value=0x44;
  send4bit(value,1); 
  value=0x45;
  send4bit(value,1); 
  value=0x46;
  send4bit(value,1); 
  value=0x47;
  send4bit(value,1);
 value=0x48;
  send4bit(value,1);  
    value=0x49;
  send4bit(value,1); 
  value=0x50;
  send4bit(value,1); 
  value=0x51;
  send4bit(value,1);
 value=0x52;
  send4bit(value,1); 
    value=0x53;
  send4bit(value,1); 
  value=0x54;
  send4bit(value,1); 
  value=0x55;
  send4bit(value,1);
 value=0x56;
  send4bit(value,1); 
    value=0x57;
  send4bit(value,1); 
  setCursor(1,1);
  value=0x58;
  send4bit(value,1); 
  value=0x59;
  send4bit(value,1);
 value=0x60;
  send4bit(value,1); 
  
  
    value=0x61;
  send4bit(value,1); 
  value=0x62;
  send4bit(value,1); 
  value=0x63;
  send4bit(value,1);
 value=0x64;
  send4bit(value,1); 
}


void test_pattern_2(int tick){

  for(int j=1; j<=4;j++){
    setCursor(0,0);
  for (int i=0; i<=15;i++){
  value = (32 * j) + i;
  send4bit(value,1);
  }
  setCursor(0,1);
  for (int i=16; i<=31;i++){
  value = (32 * j) + i;
  send4bit(value,1);
  }
 // setCursor(0,0);
  delay(tick);
  }

}
