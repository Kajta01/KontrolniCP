#include "init.h"
#include <avr/sleep.h>

void IO_Setup()
{
   pinMode(BUTTON, INPUT_PULLUP);
   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(BUZZER, OUTPUT);
   pinMode(LORA_RESET, OUTPUT);
}

void LedOn()
{
   digitalWrite(LED1, HIGH);
}
void LedOff()
{
   digitalWrite(LED1, LOW);
}
void LedBlueOn()
{
   digitalWrite(LED2, HIGH);
}
void LedBlueOff()
{
   digitalWrite(LED2, LOW);
}

void feedback(feedbackStatus status)
{
   switch (status)
   {
   case OK:
      digitalWrite(LED2, HIGH);
      digitalWrite(BUZZER, HIGH);
      delay(100);
      digitalWrite(BUZZER, LOW);
      digitalWrite(LED2, LOW);
      break;
   case ERROR:
      for (int i = 0; i < 3; i++)
      {
         digitalWrite(LED2, HIGH);
         digitalWrite(BUZZER, HIGH);
         delay(500);
         digitalWrite(LED2, LOW);
         digitalWrite(BUZZER, LOW);
         delay(100);
      }
      break;
   case FULL_MEMORY:
         for (int i = 0; i < 4; i++)
      {
         digitalWrite(LED2, HIGH);
         digitalWrite(BUZZER, HIGH);
         delay(100);
         digitalWrite(LED2, LOW);
         digitalWrite(BUZZER, LOW);
         delay(100);
      }
      break;

   }
   LedOff();
}

int getIDDevice(){
   return (int)ID_DEVICE;
}

float ReadAnalogVoltage()
{
   return (analogRead(BATTERY_PIN) * (3.3 / 1023.00));
}

void GoingToSleep()
{
#if DEBUG
Serial.println("Go sleep");
delay(2000);
#endif   
   WTG_disable();
   
   
  // LORA_Sleep();
   
   EIFR = (1 << INTF0); //Write 1 to Interrupt Flag 0 to make sure it is reset
   sleep_enable();
   attachInterrupt(0, wakeUp, HIGH);
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);
   delay(100);
   sleep_cpu();

}
void (*resetFunc)(void) = 0;

void wakeUp()
{
   detachInterrupt(0);
#if STANOVISTE_WTG
   WTG_enable();
   WTG_reset();
#endif
#if DEBUG
   Serial.println("Fired!");
   delay(100);
#endif 
   sleep_disable();
   
   
   //resetFunc();
   //hardwareReset();

}
