#include "init.h"
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"
RTC_DS3231 rtc;
DateTime now;
char timeBuffer[11];

void RTC_Start(){ 
    rtc.begin();
   
}

void RTC_SetTime(const char * date, const char *time){
     rtc.adjust(DateTime((date), (time)));
}
void RTC_SetActualTime(){
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

float RTC_GetTemperature(){
    return rtc.getTemperature();
}

String RTC_ReadDateTime(){
    now = rtc.now();
    sprintf(timeBuffer, "%02d-%02d:%02d:%02d", now.day(), now.hour(), now.minute(), now.second());
    return timeBuffer;

}




