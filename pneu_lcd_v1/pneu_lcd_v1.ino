/*
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
*/
int uart_incoming_register=0;

char ascii_characters[127]={ '_','!','_','#','$','%','&','_','(',')','*','+','_','-','.','_','0','1','2','3','4','5','6','7','8','9',':','_','<','=','>','?','_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_','_','_','^','_','`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','_','|','_','~'};
int uart_buffer_in[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int uart_buffer_in_counter=0;

//FLAGS--------------------------------------------------

boolean uart_raw_flag=1;
boolean uart_in_flag =0;
boolean uart_echo_flag=0;
boolean verbose_flag=0;

int device_id=50;


#include <LiquidCrystal.h>
LiquidCrystal lcd(P2_0, P2_1, P1_5, P1_4 , P2_2, P2_3, P2_4, P2_5);

void setup() {
  lcd.begin(20, 4);
 Serial.begin(9600);
 Serial.flush();
 Serial.println(" ");
 Serial.println("Device initializing");

  lcd.setCursor(0, 0, 1);
  lcd.print("Screen 1");
  lcd.setCursor(0, 1, 1);
  lcd.print("Initialization...");
  lcd.setCursor(0, 2, 1);
  lcd.print("_++++++++++++++++++_");
  lcd.setCursor(0, 3, 1);
  lcd.print("Please stand by!");
  
  lcd.setCursor(0, 0, 2);
  lcd.print("Screen 2");
  lcd.setCursor(0, 1, 2);
  lcd.print("Initialization...");
  lcd.setCursor(0, 2, 2);
  lcd.print("_++++++++++++++++++_");
  lcd.setCursor(0, 3, 2);
  lcd.print("Please stand by!");
  
  lcd.setCursor(0, 0, 3);
  lcd.print("Screen 3");
  lcd.setCursor(0, 1, 3);
  lcd.print("Initialization...");
  lcd.setCursor(0, 2, 3);
  lcd.print("_++++++++++++++++++_");
  lcd.setCursor(0, 3, 3);
  lcd.print("Please stand by!");
  delay(1000);

}

void loop() {
  /*
  //int d=0;
  for (int d=0;d<=9;d++){
  for(int p=0;p<=19;p++){
  for (int i=1;i<=3;i++){
    for (int o=0;o<=3;o++){
    lcd.setCursor(p, o, i);
    lcd.print(d);
    delay(50);
    }
    
  }
  }
  }
  */

  
//-----mainloop--------------------------------------------------------------------------
uart_check();
//uart_answer();
delay(103);
}

//-----otherfunctions----------------------------------------------------------------------------------
char to_ascii(int x){
  if (x >=32 and x<=126){
  return (ascii_characters[x-32]);
  }
  }

void uart_answer(){
  if(uart_raw_flag==1){
  for (int i=0; i<=31;i++){
    Serial.print(uart_buffer_in[i]);
    Serial.print("_");
    }

  }
  else{
      for (int j=0; j<=31;j++){
    Serial.print(to_ascii(uart_buffer_in[j]));
    Serial.print("_");
    }
    
    }
      Serial.println(" ");
}

void uart_check(){
if (Serial.available()>0){
  uart_incoming_register= Serial.read();
  uart_in_flag=1;
  }
if (uart_in_flag != 0){
  if(uart_incoming_register== 13){
    analyse_buffer();
    uart_buffer_in_counter=0;
    uart_in_flag=0;
  }
  else if (uart_buffer_in_counter<=31 and uart_buffer_in_counter>=0){
  uart_buffer_in[uart_buffer_in_counter]=uart_incoming_register;
  uart_buffer_in_counter++;
  
  //Serial.println(to_ascii(uart_incoming_register));
  uart_in_flag=0;
  }
  else{
   // Serial.println("buffer O F!");
    uart_buffer_in_counter--;
  }
  if (verbose_flag == 1)uart_answer();
  }
  }  
  
  void analyse_buffer(){
 // Serial.println("Execution!");
  if (uart_buffer_in[0]==65 and uart_buffer_in[1]==84){
 // Serial.println("message");
  if (uart_buffer_in[2]==device_id){
   lcd.setCursor(0, 1, 1);
  lcd.print("csocs");
  }
  
  }
  empty_buffer();
  }
  
void empty_buffer(){
for(int i=0; i<=31; i++){
uart_buffer_in[i]=0;
}
}

