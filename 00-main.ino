
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
  IO_Setup();

  SPI.begin(); // Init SPI bus
  RFID_init();

#if ZAPIS

  /****************RTC**********/
  RTC_Start();
  RTC_SetActualTime();

  //LORA_setup();

  //RFID_setup();

#endif
}
void loop()
{
  RFID_init();
#if STANOVISTE


  if (digitalRead(BUTTON) == 0)
  {
    LedOn();
    //RFID_init();
    //feedback(OK);
    Serial.println("------------------------");
    //Serial.print("Voltage:");
    //Serial.println(ReadAnalogVoltage() * 2);

    Serial.println("RTC:");
    Serial.println(RTC_GetTemperature());
    Serial.println(RTC_ReadDateTime());

    Serial.println("RFID:");

    //if (RFIDTest())
    //{
    //  RFID_Write();
    //}

    //Serial.println("LORA:");

    //LORA_loop();

    feedback(ERROR);
  }
#endif

#if CLEAR_DATA
  if (!RFIDTest())
  {
    return;
  }
    RFID_OnlyRead();
RFID_init();
  if (!RFIDTest())
  {
    return;
  }
  RFID_ClearAllData();


  feedback(OK);
#endif

#if JEN_CTENI // tabulkový výpis
  RFID_OnlyRead();
#endif

#if ZAPIS_ID_CIPU

#endif

  delay(1000);
}


 
