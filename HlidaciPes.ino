#include <avr/wdt.h>

//https://wolles-elektronikkiste.de/en/watchdog-timer

void WDT_setup()
{
  watchdogSetup();
}

void WDT_loop()
{
  delay(500);
  wdt_reset();
  endlessLoop();
}

void watchdogSetup(void)
{
#if DEBUG
  Serial.println("watchdogSetup - Start");
  delay(100);
#endif
  wdt_reset();
  wdt_enable(WDTO_8S);
  WDTCSR = (1 << WDIE); // interrupt
}

void hardwareReset()
{
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, HIGH);
}

void endlessLoop()
{
  int j = 0;
  while (2 < 5)
  {
    Serial.println(j++);
    delay(1000);
  }
}

ISR(WDT_vect)
{
#if DEBUG
  Serial.println("hardwareReset");
  delay(100);
#endif
  hardwareReset();
}

void WTG_disable()
{
#if DEBUG
  Serial.println("wdt_disable");
  delay(100);
#endif
  wdt_disable();
}

void WTG_enable()
{
#if DEBUG
  Serial.println("WTG_enable");
  delay(100);
#endif
  watchdogSetup();
}

void WTG_reset()
{
#if DEBUG
  Serial.println("wdt_reset");
  delay(100);
#endif
  wdt_reset();
}