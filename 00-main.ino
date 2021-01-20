#include "init.h"

void setup()
 {
    Serial.begin(9600);
    Serial.println("Starting");
    RTCStart();
    RFID_setup();
    LORA_setup();


    pinMode(BUTTON, INPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(BUZZER, OUTPUT);
 }
 void loop()
 {
     if(digitalRead(BUTTON) == 0)
     {
     Serial.println("------------------------");
     Serial.print("Voltage:");
     Serial.println(ReadAnalogVoltage()*2);
     Serial.print("RTC:");
     Serial.println(RTCRead());
     Serial.println("RFID:");
     RFID_loop();
     Serial.println("LORA:");
     LORA_loop();
     buzzer();
     }



     delay(1000);
 }