#include <avr/wdt.h>

//https://wolles-elektronikkiste.de/en/watchdog-timer


void WDT_setup(){
  watchdogSetup();
}

void WDT_loop(){
  delay(500);
  wdt_reset();
  endlessLoop(); 
}

void watchdogSetup(void){
  wdt_reset();
  wdt_enable(WDTO_8S); 
  WDTCSR = (1<<WDIE); // interrupt
}

void hardwareReset(){
  pinMode(RESET,OUTPUT);
  digitalWrite(RESET,HIGH);
}

void endlessLoop(){
  int j = 0;
  while(2 < 5){
    Serial.println(j++);   
    delay(1000);
  }
}

ISR(WDT_vect){
  hardwareReset();
}