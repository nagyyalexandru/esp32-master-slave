#include "Arduino.h"
#include "TimeE.h"
#include "TimeI.h"
#include "EEPROM.h"

void Time_vSetup()
{
}
void Time_vGetMinutes()
{
    if (millis() >= Time__previousMillisMinutes)
    {
        Time__previousMillisMinutes = Time__previousMillisMinutes + 60000;
        Time__Minutes++;
    }
    Time__Minutes = Time__Minutes % 60;
    timeStclock.minutes = Time__Minutes;
}
void Time_vGetSeconds()
{
    if (millis() >= Time__previousMillisSeconds)
    {
        Time__Seconds++;
        Time__previousMillisSeconds = Time__previousMillisSeconds + 1000;
    }
    Time__Seconds = Time__Seconds % 60;
    timeStclock.seconds = Time__Seconds;
}
void Time_vGetHours()
{
    if (millis() >= Time__previousMillisHours)
    {
        Time__previousMillisHours = Time__previousMillisHours + 3600000;
        Time__Hours++;
    }
    timeStclock.hours = Time__Hours;
}

void Time_vSendTimeToHMI()
{
    String Time__secunde;
    String Time__minute;
    String Time__ore;
    String Time__ExtraZero = "0";

    EEPROM.get(0, timeStclock);

    if (millis() >= Time__previousMillisSeconds)
    {
        timeStclock.seconds++;
        Time__previousMillisSeconds += 1000;
    }
    timeStclock.seconds %= 60;

    if (timeStclock.seconds == 0 && Time__okMinutes)
    {
        timeStclock.minutes++;
        Time__okMinutes = 0;
    }
    timeStclock.minutes %= 60;

    if (timeStclock.seconds == 1)
    {
        Time__okMinutes = 1;
    }
    if (timeStclock.minutes % 60 == 0 && Time__okHours)
    {
        timeStclock.hours++;
        Time__okHours = 0;
    }
    timeStclock.hours %= 24;
    if (timeStclock.minutes == 2)
    {
        Time__okHours = 1;
    }
    //````````````````````````````````````````````````````````````````````
    if (timeStclock.seconds < 10)
    {
        Time__secunde += Time__ExtraZero;
        Time__secunde += timeStclock.seconds;
    }
    else
    {
        Time__secunde += timeStclock.seconds;
    }
    if (timeStclock.minutes < 10)
    {
        Time__minute += Time__ExtraZero;
        Time__minute += timeStclock.minutes;
    }
    else
    {
        Time__minute += timeStclock.minutes;
    }
    if (timeStclock.hours < 10)
    {
        Time__ore += Time__ExtraZero;
        Time__ore += timeStclock.hours;
    }
    else
    {
        Time__ore += timeStclock.hours;
    }

    Time__StringToDisplay += Time__ore;
    Time__StringToDisplay += Time__minute;
    Time__StringToDisplay += Time__ore;

    EEPROM.put(0, timeStclock);
    EEPROM.commit();
}