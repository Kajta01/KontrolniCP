void buzzer()
{
   digitalWrite(LED1, HIGH);
   digitalWrite(LED2, HIGH);
   tone(BUZZER,2000,10);
   delay(1000);
   digitalWrite(LED1, LOW);
   digitalWrite(LED2, LOW);
   delay(250);
  }