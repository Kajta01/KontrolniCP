
#include "init.h"
#include <SPI.h>

enum feedbackStatus
{
  OK = 0,
  ERROR = 1,
  FULL_MEMORY = 9999
};

void setup()
{
  LedBlueOn();

  IO_Setup();

  SPI.begin();

  RTC_Start();
  RTC_SetActualTime();
#if DEBUG
  Serial.begin(9600);
  Serial.println("Starting");
#endif
#if CONN_SERIAL
  Serial.begin(9600);
#endif

#if JEN_LORA or M_LORA
  LORA_setup();
#endif

#if JEN_WTD
  delay(1000);
  WDT_setup();
#endif
#if STANOVISTE
  LORA_setup();
#endif
#if STANOVISTE_WTG
  WDT_setup();
#endif

  LedBlueOff();
}
void loop()
{
#if STANOVISTE
  int IDtag = 0;
  int row = 0;
  feedbackStatus result;
#if DEBUG
  Serial.println("Start loop");
  delay(100);
#endif

  LORA_initialize_radio();
  WTG_reset();
  if (RFID_WaitToChip(100))
  {
    LedOn();
    WTG_reset();
    IDtag = RFID_getIDCip();
    if (IDtag != 0XFFFF)
    {
      row = RFID_FreeRow();
      if (row != FULL_MEMORY)
      {
        RTC_ReadActualDateTime();
        result = RFID_NewEntry(row, getIDDevice(), RTC_GetDay(), RTC_GetHour(), RTC_GetMinute(), RTC_GetSecond());
        RFID_Stop();
        if (result == OK)
        {

          WTG_reset();

          LORA_Send(getIDDevice(), IDtag, RTC_GetHour(), RTC_GetMinute(), RTC_GetSecond(),
                    ReadAnalogVoltage() * 2, RTC_GetTemperature());

          feedback(OK);
        }
        else
        {
          feedback(ERROR);
        }
      }
      else
      {
        feedback(FULL_MEMORY);
      }
    }
    else
    {
      //TODO: zapis hodin
    }
  }
  WTG_reset();
  RFID_Stop();
  LORA_Sleep();

  GoingToSleep();

#endif

#if JEN_VYPIS

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

    Serial.println("LORA:");

    LORA_Send(10, 100, 9, 51, 33, 3.51, 23.23);

    delay(1000);
    feedback(OK);
  }
#endif

#if JEN_CTENI // tabulkový výpis

  RFID_WaitToChip();
  RFID_OnlyRead();
#endif

#if JEN_WTD
  feedback(OK);
  WDT_loop();
#endif

#if JEN_LORA
  if (digitalRead(BUTTON) == 1)
  {
    // LORA_Send();

    //LORA_Send(10,100,9,51,33,3.51,23.23);

    RTC_ReadActualDateTime();
    LORA_Send(getIDDevice(), 100, RTC_GetHour(), RTC_GetMinute(), RTC_GetSecond(),
              ReadAnalogVoltage() * 2, RTC_GetTemperature());

    feedback(OK);
  }
#endif

#if CONN_SERIAL

  // while (Serial.available() == 0) {}
  int readValue = 1; //Serial.readString().toInt();
  switch (readValue)
  {
  case 1:
    getRowValue();
    break;
  case 2:
    clearDataAll();
    break;
  case 3:
    zapisIDcipu();
    // zapisHodinPC();
    break;

  default:
    break;
  }

#endif

#if M_RFID
  Serial.println("bb");
  delay(3000);
  Serial.println("aa");
  RFID_WaitToChip(50);
  RFID_Stop();
#endif
#if M_LORA
  delay(2000);
  LORA_Send();
  delay(5000);
  LORA_Sleep();
#endif
#if M_ARDUINO
  digitalWrite(BATTERY_PIN_START_MEASURE, LOW);
  delay(2000);
  Serial.println("aa");
  Serial.println(ReadAnalogVoltage());

  digitalWrite(BATTERY_PIN_START_MEASURE, HIGH);
  delay(2000);
  Serial.println("aa");
  Serial.println(ReadAnalogVoltage());
#endif
#if M_Z5V

  feedback(OK);
  delay(1000);
  feedback(OK);
  delay(1000);
#endif
  delay(2000);
}

void getRowValue()
{
  while (1)
  {
    RFID_WaitToChip();
    RFID_getRowValues();

    delay(3000);
  }
}

void clearDataAll()
{
  while (1)
  {
    RFID_WaitToChip();
    LedOn();
    RFID_ClearAllData();
    bool check = RFID_CheckNullData();
    feedback((int)check);

#if DEBUG
    Serial.println(check);
#endif
    delay(3000);
  }
}

void zapisIDcipu()
{
  while (1)
  {
    LedOn();
    int valueW = RFID_zapisID();
    int valueR = RFID_getIDCip();
    if (valueW == valueR)
    {
      feedback(OK);
    }
    else
    {
      feedback(ERROR);
    }
  }
}
void zapisHodinPC()
{
  //TODO: cip FFFF
}