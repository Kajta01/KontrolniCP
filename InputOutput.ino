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
      digitalWrite(BUZZER, HIGH);
      delay(1000);
      digitalWrite(BUZZER, LOW);
      digitalWrite(LED2, LOW);
      break;
   case ERROR:
      digitalWrite(LED2, HIGH);
      tone(BUZZER, 2000, 500);
      delay(500);
      tone(BUZZER, 1000, 500);
      delay(500);
      tone(BUZZER, 2000, 50);
      delay(500);
      digitalWrite(LED2, LOW);
      break;
   }
   digitalWrite(LED1, LOW);
}

/*

void GoingToSleep()
{
  sleep_enable();
  attachInterrupt(0,wakeUp, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  digitalWrite(led,LOW);
  delay(1000);
  sleep_cpu();
  Serial.println("just woke");
  digitalWrite(led,HIGH);
}
void(* resetFunc) (void) = 0;

void wakeUp()
{
    Serial.println("Fired!");
    sleep_disable();
    detachInterrupt(0);
    resetFunc();
}
void wakeUpW()
 {
  detachInterrupt(0);
    resetFunc();
 }*/