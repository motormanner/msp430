
// The AIR430BoostFCC library uses the SPI library internally. Energia does not
// copy the library to the output folder unless it is referenced here.
// The order of includes is also important due to this fact.
#include <SPI.h>
#include <AIR430BoostFCC.h>

// -----------------------------------------------------------------------------
/**
 *  Global data
 */

// Data to write to radio TX FIFO (60 bytes MAX.)
unsigned char txData[6] = { 0x30, 'A', 'i', 'r', '!', '\0' };    

// Data to read from radio RX FIFO (60 bytes MAX.)
unsigned char rxData[6] = { '\0', '\0', '\0', '\0', '\0', '\0' };

// -----------------------------------------------------------------------------
// Debug print functions

void printTxData()
{
  Serial.print("TX (DATA): ");
  Serial.println((char*)txData); 
}

void printRxData()
{
  /**
   *  The following illustrates various information that can be obtained when
   *  receiving a message. This includes: the received data and associated 
   *  status information (RSSI, LQI, and CRC_OK bit).
   */
  Serial.print("RX (DATA, RSSI, LQI, CRCBIT): ");
  Serial.print("(");
  Serial.print((char*)rxData);
  Serial.print(", ");
  Serial.print(Radio.getRssi());
  Serial.print(", ");
  Serial.print(Radio.getLqi());
  Serial.print(", ");
  Serial.print(Radio.getCrcBit());
  Serial.println(")");
}
void set_A1(){
  digitalWrite(6, LOW);   // set the LED on
  digitalWrite(9, LOW);   // set the LED on
  digitalWrite(10, LOW);   // set the LED on
  digitalWrite(5, HIGH);   // set the LED on
}
void set_A1B1(){
  digitalWrite(6, LOW);   // set the LED on
  digitalWrite(10, LOW);   // set the LED on
  digitalWrite(9, HIGH);   // set the LED on
  digitalWrite(5, HIGH);   // set the LED on
}
void set_A2(){
  digitalWrite(5, LOW);   // set the LED on
  digitalWrite(9, LOW);   // set the LED on
  digitalWrite(10, LOW);   // set the LED on
  digitalWrite(6, HIGH);   // set the LED on
}
void set_A2B2(){
  digitalWrite(5, LOW);   // set the LED on
  digitalWrite(9, LOW);   // set the LED on
  digitalWrite(10, HIGH);   // set the LED on
  digitalWrite(6, HIGH);   // set the LED on
}
void set_B1(){
  digitalWrite(5, LOW);   // set the LED on
  digitalWrite(6, LOW);   // set the LED on
  digitalWrite(10, LOW);   // set the LED on
  digitalWrite(9, HIGH);   // set the LED on
}
void set_B1A2(){
  digitalWrite(5, LOW);   // set the LED on
  digitalWrite(10, LOW);   // set the LED on
  digitalWrite(6, HIGH);   // set the LED on
  digitalWrite(9, HIGH);   // set the LED on
}
void set_B2(){
  digitalWrite(5, LOW);   // set the LED on
  digitalWrite(6, LOW);   // set the LED on
  digitalWrite(9, LOW);   // set the LED on
  digitalWrite(10, HIGH);   // set the LED on
}
void set_B2A1(){
  digitalWrite(9, LOW);   // set the LED on
  digitalWrite(6, LOW);   // set the LED on
  digitalWrite(5, HIGH);   // set the LED on
  digitalWrite(10, HIGH);   // set the LED on
}
void clear_output(){
  digitalWrite(5, LOW);   // set the LED on
  digitalWrite(6, LOW);   // set the LED on
  digitalWrite(9, LOW);   // set the LED on
  digitalWrite(10, LOW);   // set the LED on
}
// -----------------------------------------------------------------------------
// Main example
int stp_halt=1000;
boolean spinup_dir=1;


void setup()
{
  Radio.begin(0x02, CHANNEL_1, POWER_MAX);
//  Radio.begin(0x03, CHANNEL_1, POWER_MAX);
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(RED_LED, LOW);   // set the LED on
  digitalWrite(5, LOW);   // set the LED on
  digitalWrite(6, LOW);   // set the LED on
  digitalWrite(9, LOW);   // set the LED on
  digitalWrite(10, LOW);   // set the LED on
}

void loop()
{
int serial_buffer=Serial.available();
Serial.println(serial_buffer);
 Serial.println("cuuc");
  
  
  
  
int lng_halt=0;
  
  for(int k=0;k<=250;k++){
    
    for(int j=0;j<=1;j++){
              serial_buffer=Serial.available();
         if (serial_buffer){
  int serial_inbyte=Serial.read();
  if ( serial_inbyte=='f') Serial.println("FWD");
  else if( serial_inbyte=='b')Serial.println("BWD");
  else Serial.println("BST");
  Serial.print("Serial buffer: ");
  Serial.println(serial_buffer);
  
  
  
  }
      for(int i=0;i<=9;i++){

        set_A1();
        if(!lng_halt)delayMicroseconds(stp_halt);
        if(lng_halt)delay(stp_halt);
        set_A1B1();
        if(!lng_halt)delayMicroseconds(stp_halt);
        if(lng_halt)delay(stp_halt);
        set_B1();
        if(!lng_halt)delayMicroseconds(stp_halt);
        if(lng_halt)delay(stp_halt);
        set_B1A2();
        if(!lng_halt)delayMicroseconds(stp_halt);
        if(lng_halt)delay(stp_halt);
        set_A2();
        if(!lng_halt)delayMicroseconds(stp_halt);
        if(lng_halt)delay(stp_halt);
        set_A2B2();
        if(!lng_halt)delayMicroseconds(stp_halt);
        if(lng_halt)delay(stp_halt);
        set_B2();
        if(!lng_halt)delayMicroseconds(stp_halt);
        if(lng_halt)delay(stp_halt);
        set_B2A1();
        if(!lng_halt)delayMicroseconds(stp_halt);
        if(lng_halt)delay(stp_halt);
          //Serial.println("i");
    
      }
      //Serial.println("j");
  
    }
    //Serial.println(k);

  if(spinup_dir)stp_halt=stp_halt-1;
      else{
        stp_halt=stp_halt+10;
        k=k+9;
      }
  }
  //Serial.println(spinup_dir);
if (spinup_dir)spinup_dir=0;
else spinup_dir=1;
delay(0);
  //------------------
}

void thing(){
  
  //--------------
  if (Radio.receiverOn(rxData, sizeof(rxData), 1000) > 0)
  {
    digitalWrite(RED_LED, HIGH);
    //printRxData();                  // RX debug information
    //Serial.println("");
    //Serial.println(rxData[1]);
    //Serial.println(rxData[2]);
    
    if (rxData[1]==65){
          //Serial.println("A");

      if(rxData[2]==49){
        set_A1();
        delay(1);
        //Serial.println("111");
      }
      else if(rxData[2]==50){
        set_A2();
        delay(1);
        //Serial.println("222");
      }
    }
    else if (rxData[1]==66){
          Serial.println("B");

      if(rxData[2]==49){
        set_B1();
        delay(1);
        //Serial.println("1111");

      }
      else if(rxData[2]==50){
        set_B2();
        delay(1);
        //Serial.println("2222");

      }
    }

    
    
  }
  digitalWrite(RED_LED, LOW);
  //clear_output();
}
