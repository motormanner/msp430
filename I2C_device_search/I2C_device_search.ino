#include <Wire.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("Start!");
  
  Wire.setModule(0);
  Wire.begin();
}

void loop()
{
  findAddress();
  delay(50);
}

uint8_t fromAddress = 0;
uint8_t toAddress = 127;

void findAddress()
{
  for (uint8_t a = fromAddress; a < toAddress; a++)
  {
    Wire.beginTransmission(a);
    int endStatus = Wire.endTransmission();

    if (endStatus == 0)
    {
      Serial.print("Found device at: 0x");
      Serial.println(a, BIN);
    }
  }
}
