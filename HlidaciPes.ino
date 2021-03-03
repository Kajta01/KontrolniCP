#include <avr/wdt.h>

// void WDT_setup(){
//   wdt_enable(WDTO_2S);
// }

// void WDT_loop(){
//   Serial.println("LOOP started ! ");
//   delay(1000);
//   for(int i=0; i<=5; i++){
      
//     Serial.print("Loop : ");
//     Serial.print(i);
//     Serial.println();
//     delay(1000);
//     wdt_reset();
//   }
//   //infinity loop to hang MCU
//   while(1){
//       Serial.print("o");
//   }
// }

///////////////////////////////////////////////////////////úú
//https://wolles-elektronikkiste.de/en/watchdog-timer

const int resetPin = 3;

void WDT_setup(){
   Serial.println("S");
   delay(100);

  watchdogSetup();
}

void WDT_loop(){
   Serial.println("L");
   delay(100);
  LedOn();
  delay(1000);
  LedOff();
  delay(500);
  wdt_reset();
  endlessLoop(); 
  

}

void watchdogSetup(void){
   Serial.println("ws");
   delay(100);
  cli(); // disable all interrupts
  wdt_reset();
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = (1<<WDIE) | (0<<WDE) | (1<<WDP3); // 4s / no interrupt, system reset
  sei();
}

void hardwareReset(){
   Serial.println("hr");
   delay(100);
  pinMode(RESET,OUTPUT);
  digitalWrite(RESET,HIGH);
}

void endlessLoop(){
   Serial.println("el");
   delay(100);
  int i = 0;
  while(i < 5){
    delay(1000);
  }
}

ISR(WDT_vect){
   Serial.println("isr");
   delay(100);
  hardwareReset();
}