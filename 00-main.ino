
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


  // LORA_setup();

#endif
}
void loop()
{
   RFID_init();

#if STANOVISTE

  if (digitalRead(BUTTON) == 1)
  {
    LedOn();

    Serial.println("------------------------");
    Serial.print("Voltage:");
    Serial.println(ReadAnalogVoltage() * 2);

    Serial.println("RTC:");
    Serial.println(RTC_GetTemperature());
    Serial.println(RTC_ReadDateTime());

    Serial.println("RFID:");

    if (RFIDTest())
    {
      Serial.println("vložena karta");
      Serial.println(RFID_getIDCip());

    //  RFID_Write();
    }
    Serial.println("*********************");

    // Serial.println("LORA:");

    // LORA_loop();

    delay(1000);
    feedback(OK);
  }
#endif

#if CLEAR_DATA

  RFID_WaitToChip();

  RFID_OnlyRead();

  RFID_ClearAllData();

  if(!RFID_CheckNullData())
  {
    Serial.println("OK");
    feedback(OK);
  }
  else{
    Serial.println("NOK");
    feedback(ERROR);
  }
delay(2000);
  
#endif

#if JEN_CTENI // tabulkový výpis
  RFID_WaitToChip();
  RFID_OnlyRead();
#endif

#if ZAPIS_ID_CIPU
  LedOn();
  int valueW = RFID_zapisID();
  int valueR = RFID_getIDCip();
  Serial.println(valueR);
  if(valueW == valueR)
  {
    feedback(OK);
  }
  else{
    feedback(ERROR);
  }
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
    delay(1000);
    feedback(ERROR);
  }
#endif

#if JEN_SPANEK
  Serial.println("loop");
  LedOn();
  delay(5000);
  LedOff();
  GoingToSleep();
#endif
  delay(1000);
}
