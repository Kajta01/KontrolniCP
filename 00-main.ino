
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

  SPI.begin();

  #if STANOVISTE

   // Init SPI bus
  RTC_Start();
  RTC_SetActualTime();

  // RFID_init();
  // LORA_setup();



  /****************RTC**********/
  RTC_Start();
  RTC_SetActualTime();

  LORA_setup();

  //RFID_setup();

#endif
}
void loop()
{
   RFID_init();

#if STANOVISTE

  if (digitalRead(BUTTON) == 1)
  {
    LedOn();
    //RFID_init();
    //feedback(OK);
    Serial.println("------------------------");
    Serial.print("Voltage:");
    Serial.println(ReadAnalogVoltage() * 2);

    Serial.println("RTC:");
    Serial.println(RTC_GetTemperature());
    Serial.println(RTC_ReadDateTime());

    //Serial.println("RFID:");

    //if (RFIDTest())
    // {
    //  Serial.println("vložena karta");
    //  RFID_Write();
    // }

    // Serial.println("LORA:");

    // LORA_loop();

    delay(1000);
    feedback(OK);
  }
#endif

#if CLEAR_DATA

  RFID_OnlyRead();

  RFID_ClearAllData();

  feedback(OK);
#endif

#if JEN_CTENI // tabulkový výpis
  RFID_OnlyRead();
#endif

#if ZAPIS_ID_CIPU
  RFID_zapisID();
  feedback(OK);
#endif

#if JEN_MERENI

  Serial.print("Voltage:");
  Serial.println(ReadAnalogVoltage());

#endif

#if JEN_ZVUK_LED
  if (digitalRead(BUTTON) == 1)
  {
    LedOn();
    delay(1000);
    feedback(OK);
  }
#endif

#if JEN_SPANEK
  LedOn();
  delay(5000);
  LedOff();
  GoingToSleep();
#endif
  delay(1000);
}
