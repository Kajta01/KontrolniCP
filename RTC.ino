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
// void loop () {
//     DateTime now = rtc.now();

//     Serial.print(now.year(), DEC);
//     Serial.print('/');
//     Serial.print(now.month(), DEC);
//     Serial.print('/');
//     Serial.print(now.day(), DEC);
//     Serial.print(" (");
//     Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//     Serial.print(") ");
//     Serial.print(now.hour(), DEC);
//     Serial.print(':');
//     Serial.print(now.minute(), DEC);
//     Serial.print(':');
//     Serial.print(now.second(), DEC);
//     Serial.println();

//     Serial.print(" since midnight 1/1/1970 = ");
//     Serial.print(now.unixtime());
//     Serial.print("s = ");
//     Serial.print(now.unixtime() / 86400L);
//     Serial.println("d");

//     // calculate a date which is 7 days and 30 seconds into the future
//     DateTime future (now + TimeSpan(7,12,30,6));

//     Serial.print(" now + 7d + 30s: ");
//     Serial.print(future.year(), DEC);
//     Serial.print('/');
//     Serial.print(future.month(), DEC);
//     Serial.print('/');
//     Serial.print(future.day(), DEC);
//     Serial.print(' ');
//     Serial.print(future.hour(), DEC);
//     Serial.print(':');
//     Serial.print(future.minute(), DEC);
//     Serial.print(':');
//     Serial.print(future.second(), DEC);
//     Serial.println();

//     Serial.print("Temperature: ");
//     Serial.print(rtc.getTemperature());
//     Serial.println(" C");

//     Serial.println();
//     delay(3000);
// }
