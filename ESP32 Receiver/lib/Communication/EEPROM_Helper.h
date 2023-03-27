#include <Arduino.h>
#ifndef EEPROM_HELPER_h
#define EEPROM_HELPER_h

#define EEPROM_SIZE 32
#define EEPROM_PMK_ADDR 0
#define EEPROM_LMK_ADDR 16

static uint8_t addr = 0;
static String EEPROM_Read_PMK;
static String EEPROM_Read_LMK;

String EEPROM_Read_String(int addr);

void EEPROM_Write_String(int addr, String word2);
#endif