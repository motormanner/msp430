#include <SoftwareSerial.h>


uint8_t uart_incoming_register=0;
uint8_t uart_incoming_register_S0=0;
uint8_t uart_incoming_register_S1=0;
uint8_t uart_incoming_register_S2=0;
uint8_t uart_incoming_register_S3=0;
//uint8_t uart_incoming_register_S4=0;

boolean uart_in_flag =0;
boolean uart_in_flag_S0 =0;
boolean uart_in_flag_S1 =0;
boolean uart_in_flag_S2 =0;
boolean uart_in_flag_S3 =0;
//boolean uart_in_flag_S4 =0;



SoftwareSerial SS_0(P1_4, P1_3); // RX, TX
SoftwareSerial SS_1(P2_0, P1_5); // RX, TX
SoftwareSerial SS_2(P2_2, P2_1); // RX, TX
SoftwareSerial SS_3(P2_4, P2_3); // RX, TX
//SoftwareSerial SS_4(P1_7, P1_6); // RX, TX

void setup()  
{
  Serial.begin(115200);
  SS_0.begin(115200);
  SS_1.begin(115200);
  SS_2.begin(115200);
  SS_3.begin(115200);
//  SS_4.begin(9600);
}

void loop()
{
 uart_check();
 uart_worker();
 /*
 Serial.println("t");
  SS_0.println("te");
  SS_1.println("tes");
  SS_2.println("test1");
  SS_3.println("test22");
 // SS_4.println("test");
  
  delay(333);
  */
}

//other functions------------------------------------------------------------


void uart_check(){
if (Serial.available()>0){
  uart_incoming_register= Serial.read();
  uart_in_flag=1;
  }
if (SS_0.available()>0){
  uart_incoming_register_S0= SS_0.read();
  uart_in_flag_S0=1;
  }
if (SS_1.available()>0){
  uart_incoming_register_S1= SS_1.read();
  uart_in_flag_S1=1;
  }
if (SS_2.available()>0){
  uart_incoming_register_S2= SS_2.read();
  uart_in_flag_S2=1;
  }
  
if (SS_3.available()>0){
  uart_incoming_register_S3= SS_3.read();
  uart_in_flag_S3=1;
  }

  
}  
//------------------------------------------------------------  

void uart_worker(){

if (uart_in_flag != 0){
 // Serial.write(uart_incoming_register);
  SS_0.write(uart_incoming_register);
  SS_1.write(uart_incoming_register);
  SS_2.write(uart_incoming_register);
  SS_3.write(uart_incoming_register);
  uart_in_flag =0;
  }
  

//0----------------------------------------------------------------
if (uart_in_flag_S0 != 0){
  Serial.write(uart_incoming_register_S0);
  //SS_0.write(uart_incoming_register);
  SS_1.write(uart_incoming_register_S0);
  SS_2.write(uart_incoming_register_S0);
  SS_3.write(uart_incoming_register_S0);
  uart_in_flag_S0 =0;
}

//1------------------------------------------------------------------
if (uart_in_flag_S1 != 0){
  Serial.write(uart_incoming_register_S1);
  SS_0.write(uart_incoming_register_S1);
  //SS_1.write(uart_incoming_register);
  SS_2.write(uart_incoming_register_S1);
  SS_3.write(uart_incoming_register_S1);
  uart_in_flag_S1 =0;

}

//2------------------------------------------------------------
if (uart_in_flag_S2 != 0){
  Serial.write(uart_incoming_register_S2);
  SS_0.write(uart_incoming_register_S2);
  SS_1.write(uart_incoming_register_S2);
  //SS_2.write(uart_incoming_register);
  SS_3.write(uart_incoming_register_S2);

  uart_in_flag_S2 =0;
}

//3--------------------------------------------------------------
if (uart_in_flag_S3 != 0){
  Serial.write(uart_incoming_register_S3);
  SS_0.write(uart_incoming_register_S3);
  SS_1.write(uart_incoming_register_S3);
  SS_2.write(uart_incoming_register_S3);
  //SS_3.write(uart_incoming_register);
  uart_in_flag_S3 =0;

}



}
