#include "init.h"



void IO_Setup()
{
   pinMode(BUTTON, INPUT);
   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(BUZZER, OUTPUT);
}

void LedOn()
{
   digitalWrite(LED1, HIGH);
}

void feedback(feedbackStatus status)
{
   switch (status)
   {
   case OK:
      digitalWrite(LED2, HIGH);
      tone(BUZZER, 2000, 500);
      delay(500);
      digitalWrite(LED2, LOW);
      break;
   case ERROR:
      digitalWrite(LED2, HIGH);
      tone(BUZZER, 2000, 500);
      delay(500);
      tone(BUZZER, 1000, 500);
      delay(500);
      tone(BUZZER, 2000, 500);
      delay(500);
      digitalWrite(LED2, LOW);
      break;
   }
   digitalWrite(LED1, LOW);
}
