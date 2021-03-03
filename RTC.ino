#include "init.h"
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"
RTC_DS3231 rtc;
DateTime now;

void RTC_Start()
{
    rtc.begin();
}

void RTC_SetTime(const char *date, const char *time)
{
    rtc.adjust(DateTime((date), (time)));
}
void RTC_SetActualTime()
{
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

float RTC_GetTemperature()
{
    return rtc.getTemperature();
}

void RTC_ReadActualDateTime()
{
    now = rtc.now();
}

int RTC_GetDay()
{
    return now.day();
}

int RTC_GetHour()
{
    return now.hour();
}

int RTC_GetMinute()
{
    return now.minute();
}

int RTC_GetSecond()
{
    return now.second();
}

String RTC_GetTime()
{
    char timeBuffer[11];
    sprintf(timeBuffer, "%02d-%02d:%02d:%02d", now.day(), now.hour(), now.minute(), now.second());
    return timeBuffer;
}
