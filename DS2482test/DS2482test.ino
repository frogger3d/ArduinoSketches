#include <Wire.h>
#include "DS2482.h"

#define DS2482_I2C_ADDRESS 0x18

DS2482 ds(0);

void setup()
{
  Wire.begin(0x2f);
  Serial.begin(9600);
  
  ds.reset();
}

byte result;

void loop()
{
   byte addr[8];

   if (ds.wireSearch(addr))
   {
     Serial.print("Found device at: ");
     for(int i = 0; i < 8; i++)
     {
       Serial.print(addr[i], HEX);
       Serial.print(" ");
     }
     Serial.print("\n");
   }
   else
   {
       Serial.print("No more addresses.\n");
       delay(5000);
       ds.wireResetSearch();
       return;
   }
  
  
  /*
  Wire.beginTransmission(DS2482_I2C_ADDRESS);
  Wire.write(0xb4); // reset
  Wire.endTransmission();
  delay(500);
  Wire.beginTransmission(DS2482_I2C_ADDRESS);
  Wire.write(0xe1); // read register
  Wire.write(0xc3); // configuration register
  Wire.requestFrom(DS2482_I2C_ADDRESS,1);
  result = Wire.read();
//  Wire.endTransmission();
  
  Serial.write(result);
  
  delay(1000);
  
  */
}
