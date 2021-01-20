#include "init.h"
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"
RTC_DS3231 rtc;
DateTime now;

void RTCStart(){ 
    rtc.begin();
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void RTCSetTime(){
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}



String RTCRead(){
    now = rtc.now();
    return  String(now.minute()) + ":" + String(now.second());
}

