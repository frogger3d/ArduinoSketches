#include <Wire.h>
#include "DS2482.h"

#define DS2482_I2C_ADDRESS 0x18

#define DS18S20_ID 0x10
#define DS18B20_ID 0x28

DS2482 ds(0);

void setup()
{
  pinMode(13, OUTPUT);
  Wire.begin(0x2f);
  Serial.begin(9600);

  ds.reset();
}

void loop()
{
    while (!ds.wireReset())
    {
        delay(5);
    }

    Serial.print("Starting temperature conversion ..\n\n");

    // SKIP ROM, select all OneWire devices
    ds.wireWriteByte(0xCC);
    // Instruct DS18B20s to convert temperature value
    ds.wireWriteByte(0x44);

    // we need to wait for the conversion to finish.
    // no idea how much time passes, so lets wait a while
    delay(750);

    // oneWire address
    byte addr[8];
    
    while (ds.wireSearch(addr))
    {
        Serial.print("Found device at: ");
        for (int i = 0; i < 8; i++)
        {
            char hex[2];
            sprintf (hex, "%02x", addr[i]);
            Serial.print(hex);
            Serial.print(" ");
        }
        Serial.print("\n");

        if (addr[0] == DS18S20_ID)
        {
            Serial.print("DS18S20: 1-Wire Parasite-Power Digital Thermometer\n");
        }
        else if(addr[0] == DS18B20_ID)
        {
            Serial.print("DS18B20: Programmable Resolution 1-Wire Digital Thermometer\n");
        }
        
        // Only try to read out DS18S20 or DS18B20 devices
        if (addr[0] == DS18S20_ID || addr[0] == DS18B20_ID)
        {
            // we got an address, let's do some temperature reading
            if (ds.wireReset())
            {
                readSensor(addr);
            }
            else
            {
                Serial.print("Could not read, OneWire bus busy");
            }
        }
        else
        {
            Serial.print("Not a compatible OneWire device");
        }
    }
    
    Serial.print("No more addresses, starting over ..\n\n");    
    ds.wireResetSearch();
    
    ledWait(5000);    
}

void readSensor(byte* addr)
{
    ds.wireSelect(addr);
    // Instruct DS18B20 to send scratchpad
    ds.wireWriteByte(0xBE);
  
    // holds DS18x20 scratchpad
    byte scratchPad[9];
  
    // Read scratchpad                
    for (int j = 0; j < 9; j++)
    {
        scratchPad[j] = ds.wireReadByte();
    }
  
    float temp = convertTemperature(addr[0], scratchPad);
    
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" C\n\n");
}

float convertTemperature(byte onewireFamily, byte* scratchPad)
{
    int otemp = ((scratchPad[1] << 8) + scratchPad[0]);
    float temp;
  
    // check for negative temperatures
    if (otemp > 2047)
    {
        // convert 2s complement negative number
        otemp = -(~(otemp - 1));
    }
    
    if (onewireFamily == DS18S20_ID)
    {
        temp = otemp / 2.0;
    }
    else if(onewireFamily == DS18B20_ID)
    {
        temp = otemp / 16.0;
    }
    return temp;
}

void ledWait(int milliseconds)
{
    bool low = true;
    while (milliseconds > 0)
    {
        if (low)
        {
          digitalWrite(13, HIGH);
        }
        else
        {
          digitalWrite(13, LOW);
        }
        low = !low;

        if (milliseconds > 500)
        {
            delay(500);
        }
        else
        {
            delay(milliseconds);
        }
        milliseconds -= 1000;
    }    
    digitalWrite(13, LOW);
}

