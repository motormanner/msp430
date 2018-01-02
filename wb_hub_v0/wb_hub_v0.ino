
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
unsigned char A1m[6] = { 0x30, 'A', '1', 'r', '!', '\0' };    
unsigned char A2m[6] = { 0x30, 'A', '2', 'r', '!', '\0' };    
unsigned char B1m[6] = { 0x30, 'B', '1', 'r', '!', '\0' };    
unsigned char B2m[6] = { 0x30, 'B', '2', 'r', '!', '\0' };    
int d_time=0;

// Data to read from radio RX FIFO (60 bytes MAX.)
unsigned char rxData[6] = { '\0', '\0', '\0', '\0', '\0', '\0' };

void send_A1(){
  Radio.transmit(0x02, A1m, 6);
  while (Radio.busy());
  delay(d_time);
  Radio.transmit(0x03, A1m, 6);
  while (Radio.busy());
  delay(d_time);
}

void send_A2(){
  Radio.transmit(0x02, A2m, 6);
  while (Radio.busy());
  delay(d_time);
  Radio.transmit(0x03, A2m, 6);
  while (Radio.busy());
  delay(d_time);
}
void send_B1(){
  Radio.transmit(0x02, B1m, 6);
  while (Radio.busy());
  delay(d_time);
  Radio.transmit(0x03, B1m, 6);
  while (Radio.busy());
  delay(d_time);
}
void send_B2(){
  Radio.transmit(0x02, B2m, 6);
  while (Radio.busy());
  delay(d_time);
  Radio.transmit(0x03, B2m, 6);
  while (Radio.busy());
  delay(d_time);
}

void setup()
{
  Radio.begin(0x01, CHANNEL_1, POWER_MAX);
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);   // set the LED on
}

void loop()
{
send_A1();
send_B2();
send_A2();
send_B1();
/*
Radio.transmit(0x02, txData, 6);
  while (Radio.busy());
  delay(300);
  Radio.transmit(0x03, txData, 6);
  while (Radio.busy());
  delay(700);*/
}
