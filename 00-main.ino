#include "init.h"
#include <SPI.h>

enum feedbackStatus
{
   OK,
   ERROR
};

void setup()
 {
    Serial.begin(9600);
    Serial.println("Starting");

   SPI.begin();		// Init SPI bus
   RFID_init();

    RTCStart();
    //LORA_setup();

    IO_Setup();



 }
 void loop()
 {
   

     if(digitalRead(BUTTON) == 0)
     {
         LedOn();
      RFID_init();
     feedback(OK);    
     Serial.println("------------------------");
     Serial.print("Voltage:");
     Serial.println(ReadAnalogVoltage()*2);
     Serial.print("RTC:");
     Serial.println(RTCRead());
     Serial.println("RFID:");
     while(1){
     Serial.println(RFIDTest());
     }
     //if(RFIDTest()){RFID_Write();}
     Serial.println("LORA:");
     //LORA_loop();
     feedback(ERROR); 
     }



     delay(1000);
 }

 