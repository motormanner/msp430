#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(P2_0, P2_1, P2_2, P2_3, P2_4, P2_5);

int poti=0;
int sensor_1=0;
int sensor_2=0;
int on_time=0;
int heat_flag=0;

// 5 6 7 
// the setup routine runs once when you press reset:
void setup() {
  
    lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hail hidra!");
  
  // initialize serial communication at 9600 bits per second:
 // Serial.begin(9600); // msp430g2231 must use 4800
   pinMode(5, OUTPUT);      
    pinMode(6, OUTPUT);      
     pinMode(7, OUTPUT);      
}

// the loop routine runs over and over again forever:
void loop() {
  
  read_sensors();
  print_LCD();
  caculate_on_time();
  set_output();
  
}


void read_sensors(){
  poti = analogRead(2);
  sensor_1 = analogRead(14);
  sensor_2 = analogRead(15);

}

void print_LCD(){
 lcd.setCursor(0, 0);
 lcd.print("Temp: ");
 lcd.print(sensor_1);
 lcd.print(" / ");
 lcd.print(sensor_2);
 lcd.print("                =");
 lcd.setCursor(0, 1);
 lcd.print("Target:");
 lcd.print(poti);
 lcd.print("                =");

}

void  caculate_on_time(){
    if (sensor_1 >poti|| sensor_2>poti){
      on_time=250;
     heat_flag=1;
    }
    if (sensor_1<=poti || sensor_2<=poti){
      on_time=0;
      heat_flag=0;
    }
  }
  
void  set_output(){
  if (heat_flag){
      lcd.setCursor(15, 1);
 lcd.print("H");
  digitalWrite(5, 1);
  digitalWrite(6, 1);
  digitalWrite(7, 1);

  delay(on_time);

  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 0);

  delay(500);

  }
  else {
       lcd.setCursor(15, 1);
 lcd.print("L");
 digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 0);
 delay (500);
  }
 
  }
