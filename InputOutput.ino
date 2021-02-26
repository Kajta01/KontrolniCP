#include "init.h"
#include <avr/sleep.h>

void IO_Setup()
{
   pinMode(BUTTON, INPUT_PULLUP);
   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(BUZZER, OUTPUT);
}

void LedOn()
{
   digitalWrite(LED1, HIGH);
}
void LedOff()
{
   digitalWrite(LED1, LOW);
}

void feedback(feedbackStatus status)
{
   switch (status)
   {
   case OK:
      digitalWrite(LED2, HIGH);
      digitalWrite(BUZZER, HIGH);
      delay(1000);
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
   }
   digitalWrite(LED1, LOW);
}

float ReadAnalogVoltage()
{
   return (analogRead(BATTERY_PIN) * (3.3 / 1023.00));
}

void GoingToSleep()
{
   sleep_enable();
   attachInterrupt(0, wakeUp, HIGH);
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);
   delay(1000);
   sleep_cpu();
}
void (*resetFunc)(void) = 0;

void wakeUp()
{
   Serial.println("Fired!");
   sleep_disable();
   detachInterrupt(0);
}
