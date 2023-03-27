#include "Arduino.h"
#ifndef TimeE_h
#define TimeE_h
void Time_vSetup();
void Time_vGetSeconds();
void Time_vGetMinutes();
void Time_vGetHours();
void Time_vChangeUnit(bool format);
void Time_vSendTimeToHMI();

static struct stSendTime
{
    uint8_t seconds :6;
    uint8_t minutes:6;
    uint8_t hours:5;
} timeStclock;
#endif