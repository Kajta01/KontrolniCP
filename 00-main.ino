#include "init.h"

enum feedbackStatus
{
   OK,
   ERROR
};

void setup()
 {
    Serial.begin(9600);
    Serial.println("Starting");
    RTCStart();
    RFID_setup();
    LORA_setup();

    IO_Setup();



 }
 void loop()
 {
     if(digitalRead(BUTTON) == 0)
     {
     feedback(OK);    
     Serial.println("------------------------");
     Serial.print("Voltage:");
     Serial.println(ReadAnalogVoltage()*2);
     Serial.print("RTC:");
     Serial.println(RTCRead());
     Serial.println("RFID:");
     RFID_loop();
     Serial.println("LORA:");
     LORA_loop();
     feedback(ERROR); 
     }



     delay(1000);
 }