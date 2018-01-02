#include <SPI.h>
#include <AIR430BoostETSI.h>
#define ADDRESS_LOCAL    0x03
#define ADDRESS_REMOTE   0x01
struct sPacket
{
  uint8_t from;           // Local node address that message originated from
  uint8_t message[59];    // Local node message [MAX. 59 bytes]
};
struct sPacket txPacket;

void setup()
{
  Radio.begin(ADDRESS_LOCAL, CHANNEL_1, POWER_MAX);
  rxPacket.from = 0;
  txPacket.from = ADDRESS_LOCAL;
  memset(txPacket.message, 0, sizeof(txPacket.message));
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);       // Use red LED to display message reception
  digitalWrite(RED_LED, LOW);
}

void loop()
{
  int i, j;
  
  delay(1000);    // Send every second
  for (i = 0, j = '0'; i <= 0x2A; i++, j++)
  { 
    txPacket.message[i] = j;
  }
  Radio.transmit(ADDRESS_REMOTE, (unsigned char*)&txPacket, sizeof(txPacket));
  delay(500);
}
