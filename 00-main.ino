
#include "init.h"
#include <SPI.h>

enum feedbackStatus
{
  OK,
  ERROR,
  FULL_MEMORY
};

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting");
  IO_Setup();

  SPI.begin();

   RTC_Start();
  RTC_SetActualTime();

#if STANOVISTE

   // Init SPI bus
  RTC_Start();
  RTC_SetActualTime();


  // LORA_setup();

#endif
#if JEN_WTD
  WDT_setup();
#endif
}
void loop()
{
#if RFID_GET_ROW_VALUES
RFID_WaitToChip();
RFID_getRowValues();
#endif

#if RFID_NEW_ENTRY
RFID_WaitToChip();

RTC_ReadDateTime();

int r = RFID_NewEntry(RFID_FreeRow(), getIDDevice(), 
              RTC_GetDay(), RTC_GetHour(),RTC_GetMinute(), RTC_GetSecond());

delay(1000);
feedback(r);


#endif


#if STANOVISTE

  if (digitalRead(BUTTON) == 1)
  {
    LedOn();

    Serial.println("------------------------");

    Serial.print("Device:");
    Serial.println(ID_DEVICE);

    Serial.print("Voltage:");
    Serial.println(ReadAnalogVoltage() * 2);

    Serial.println("RTC:");
    Serial.println(RTC_GetTemperature());
    RTC_ReadDateTime();

   Serial.println(RTC_GetTime());
  Serial.println(RTC_GetDay());
  Serial.println(RTC_GetHour());
  Serial.println(RTC_GetMinute());
  Serial.println(RTC_GetSecond());

    Serial.println("RFID:");

    RFID_WaitToChip();

      Serial.println("vložena karta");
      Serial.println(RFID_getIDCip());

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

#if JEN_WTD
  feedback(OK);
  WDT_loop();
#endif

  delay(1000);
}
