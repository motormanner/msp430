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
/*
CONNECTOR:

0  :GND          -/GND
0  :Vcc          3.3V
0  :CLK          pin6/L_clk
0  :CLR(!)       pin7/L_clr
0  :B(SIGNAL)    pin8/L_signal
0  :A(SIGNAL)    3.3V
0  :NC
0  :NC
0  :NC
x  :(NO CABLE)
*/

boolean clr_flag=1; 

int L_clk=19;
int L_clr=18;
int L_serial=2;

int delay_whait=500;
int delay_clk=5;
int delay_serial=5;

int uart_incoming_register=0;

char ascii_characters[127]={ ' ','!','_','#','$','%','&','_','(',')','*','+','_','-','.','_','0','1','2','3','4','5','6','7','8','9',':','_','<','=','>','?','_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_','_','_','^','_','`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','_','|','_','~'};
int uart_buffer_in[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int uart_buffer_in_counter=0;

char LCD_operate_buffer[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int LCD_1_0[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int LCD_1_1[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int LCD_1_2[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int LCD_1_3[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int LCD_2_0[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int LCD_2_1[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int LCD_2_2[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int LCD_2_3[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int LCD_3_0[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int LCD_3_1[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int LCD_3_2[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int LCD_3_3[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//FLAGS--------------------------------------------------

boolean uart_raw_flag=1;
boolean uart_in_flag =0;
boolean uart_echo_flag=0;
boolean verbose_flag=1;

int line_pointer=0;
int device_pointer=1;

int device_id=50;//device2


#include <LiquidCrystal.h>
LiquidCrystal lcd(P2_0, P2_1, P1_5, P1_4 , P2_2, P2_3, P2_4, P2_5);

void setup() {
    pinMode(L_clk, OUTPUT);     
  pinMode(L_serial, OUTPUT);     
 if (clr_flag) pinMode(L_clr, OUTPUT);     
led_7_segment_clear();

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
//-----mainloop--------------------------------------------------------------------------
uart_check();
//uart_answer();
  led_7_segment_main();

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
    Serial.println("buffer O F!");
    uart_buffer_in_counter--;
  }
  if (verbose_flag == 1)uart_answer();
  }
  }  
  
  void analyse_buffer(){
  Serial.println("Execution!");
  if (uart_buffer_in[0]==65 and uart_buffer_in[1]==84){
  Serial.println("message");
  if (uart_buffer_in[2]==device_id){
  if (uart_buffer_in[3]==48)line_pointer=0;
  else if (uart_buffer_in[3]==49)line_pointer=1;
  else if (uart_buffer_in[3]==50)line_pointer=2;
  else if (uart_buffer_in[3]==51)line_pointer=3;
  else Serial.println("line error");
  Serial.print("Line number : ");
  Serial.println(line_pointer);
  if (uart_buffer_in[4]==49)device_pointer=1;
  else if (uart_buffer_in[4]==50)device_pointer=2;
  else if (uart_buffer_in[4]==51)device_pointer=3;
  else Serial.println("device error");
  Serial.print("Device number : ");
  Serial.println(device_pointer);
  for (int i=0;i<=19;i++){
  LCD_operate_buffer[i]=0;
  }
  for(int i=0;i<=19;i++){
  LCD_operate_buffer[i]=to_ascii(uart_buffer_in[i+5]);
  }
  for (int i=0; i<=19;i++){
    Serial.print(LCD_operate_buffer[i]);
    Serial.print("_");
    }
          Serial.println(" ");

   lcd.setCursor(0, line_pointer, device_pointer);
  // for (int i=0;i<=19;i++){
  lcd.print(LCD_operate_buffer);
  //}
  
  }
  
  }
  empty_buffer();
  }
  
void empty_buffer(){
for(int i=0; i<=31; i++){
uart_buffer_in[i]=0;
}
}


void led_7_segment_clear(){
if(clr_flag){
digitalWrite(L_clr, HIGH);
delay(1);
digitalWrite(L_clr, LOW); 
delay(1);
digitalWrite(L_clr, HIGH);
delay(1);
}
else{  
for (int i=0;i<=6;i++){
led_7_segment_cycle_L();
delayMicroseconds(delay_serial);

}
}
}

void led_7_segment_cycle(){
digitalWrite(L_clk, LOW);
  delayMicroseconds(delay_clk);
  digitalWrite(L_clk, HIGH);
  delayMicroseconds(delay_clk);
}

void led_7_segment_cycle_H(){
  digitalWrite(L_serial, HIGH);
  delayMicroseconds(delay_serial);
  led_7_segment_cycle();
}

void led_7_segment_cycle_L(){
  digitalWrite(L_serial, LOW);
  delayMicroseconds(delay_serial);
  led_7_segment_cycle();
}

void led_7_segment_n0(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
}

void led_7_segment_n1(){
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
}

void led_7_segment_n2(){
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n3(){
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n4(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
}

void led_7_segment_n5(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n6(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n7(){
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
}

void led_7_segment_n8(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n9(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n10(){
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_nE(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_print(int x){
  switch (x){
  case 0:led_7_segment_n0();
  break;
  case 1:led_7_segment_n1();
  break;
  case 2:led_7_segment_n2();
  break;
  case 3:led_7_segment_n3();
  break;
  case 4:led_7_segment_n4();
  break;
  case 5:led_7_segment_n5();
  break;
  case 6:led_7_segment_n6();
  break;
  case 7:led_7_segment_n7();
  break;
  case 8:led_7_segment_n8();
  break;
  case 9:led_7_segment_n9();
  break;
  case 10:led_7_segment_n10();
  break;
  default:led_7_segment_nE();
  }
}

void led_7_segment_main(){

for (int i=0;i<=11;i++){
  led_print(i);
delay(delay_whait);
led_7_segment_clear();
delay(delay_whait);
}
}

