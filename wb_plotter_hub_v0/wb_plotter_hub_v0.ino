#include <SPI.h>
#include <AIR430BoostETSI.h>
#define ADDRESS_LOCAL    0x01
struct sPacket
{
  uint8_t from;           // Local node address that message originated from
  uint8_t message[59];    // Local node message [MAX. 59 bytes]
};
struct sPacket rxPacket;

void setup()
{
  Radio.begin(ADDRESS_LOCAL, CHANNEL_1, POWER_MAX);
  rxPacket.from = 0;
  txPacket.from = ADDRESS_LOCAL;
  memset(rxPacket.message, 0, sizeof(rxPacket.message));
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);       // Use red LED to display message reception
  digitalWrite(RED_LED, LOW);
}

void loop()
{
  // Turn on the receiver and listen for incoming data. Timeout after 1 seconds.
  // The receiverOn() method returns the number of bytes copied to rxData.
  if (Radio.receiverOn((unsigned char*)&rxPacket, sizeof(rxPacket), 1000) > 0)
  {
    digitalWrite(RED_LED, HIGH);
    Serial.print("FROM: ");
    Serial.print(rxPacket.from);
    Serial.print(" MSG: ");
    Serial.println((char*)rxPacket.message);
		digitalWrite(RED_LED, LOW);
  }

  // Note: This sketch never transmits so no additional delay required to meet ETSI
  // requirements.
}
