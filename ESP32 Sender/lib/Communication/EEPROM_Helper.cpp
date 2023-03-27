#include <Arduino.h>
#include "EEPROM_Helper.h"
#include "EEPROM.h"

String EEPROM_Read_String(int addr)
{
  String getString;
  char readChar;
  uint8_t i = addr;

  while (readChar != '\0')  /*  \0 - end of string  */
  {
    readChar = char(EEPROM.read(i));
    i++;

    if (readChar != '\0')
    {
      getString += readChar;
    }
  }

  return getString;
}

void EEPROM_Write_String(uint8_t addr, String setString)
{
  uint8_t str_length = setString.length() + 1;

  for (uint8_t i = addr; i < str_length + addr; i++)
  {
    EEPROM.write(i, setString.charAt(i - addr));
  }

  EEPROM.write(str_length + addr, '\0');
  EEPROM.commit();
}