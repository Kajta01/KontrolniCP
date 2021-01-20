#include "init.h"
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"
RTC_DS3231 rtc;
DateTime now;
char timeBuffer[11];

void RTCStart(){ 
    rtc.begin();
   
}

void RTCSetTime(const char * date, const char *time){
     rtc.adjust(DateTime((date), (time)));
}
void RTCSetActualTime(){
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

float getTemperature(){
    return rtc.getTemperature();
}



String RTCRead(){
    now = rtc.now();
    sprintf(timeBuffer, "%02d-%02d:%02d:%02d", now.day(), now.hour(), now.minute(), now.second());
    return timeBuffer;
}


/*void UpdateTime()
{
  digitalWrite(led2,HIGH);
  Serial.println(getTime());
  if (!RFIDTest()) { return;  }
  digitalWrite(led2,HIGH);
  byte timee[18];
  byte datee[18];
  readBlock(1, timee);
  readBlock(2, datee);
  rtc.setDateTime(datee,timee);
  Serial.println(getTime());
  digitalWrite(led2,LOW);
  OKDONE(2000);
}*/


