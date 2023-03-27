#include <Arduino.h>
#ifndef EEPROM_HELPER_h
#define EEPROM_HELPER_h

#define EEPROM_SIZE 32
#define EEPROM_PMK_ADDR 0
#define EEPROM_LMK_ADDR 16

static uint8_t addr = 0;

String EEPROM_Read_String(int addr);

void EEPROM_Write_String(uint8_t addr, String setString);
#endif