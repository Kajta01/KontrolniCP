
#include "init.h"
#include <SPI.h>

enum feedbackStatus
{
  OK,
  ERROR
};

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting");

  //SPI.begin(); // Init SPI bus
  //RFID_init();
  /****************RTC**********/
  RTC_Start();
  RTC_SetActualTime();

  //LORA_setup();

  //RFID_setup();

  //IO_Setup();
}
void loop()
{
  //attachInterrupt(0,wakeUpW, LOW);

  if (digitalRead(BUTTON) == 0)
  {
    LedOn();
    //RFID_init();
    //feedback(OK);
    Serial.println("------------------------");
    //Serial.print("Voltage:");
    //Serial.println(ReadAnalogVoltage() * 2);

    Serial.println("RTC:");
    Serial.println(RTC_GetTemperature());
    Serial.println(RTC_ReadDateTime());


    //Serial.println(RTCRead());
    //Serial.println("RFID:");

    //if (RFIDTest())
    //{
    //  RFID_Write();
    //}
    //Serial.println("LORA:");

    //LORA_loop();

    feedback(ERROR);
  }

  delay(1000);
}

/*
 
#include <avr/sleep.h>
#define interruptPin 2

int ID ;

int dipPins[] = {9, 8, 7, 6, 5, 4};  // DIP Switch Pins
int pocet = 6;

#define led  A1
#define led2  A2
#define bzucak  A0

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10  //slave select pin
#define RST_PIN 3  //reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);        // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;//create a MIFARE_Key struct named 'key', which will hold the card information


// připojení potřebných knihoven
#include <Wire.h>
#include <DS3231.h>
// inicializace RTC z knihovny
DS3231 rtc;
// vytvoření proměnné pro práci s časem
RTCDateTime datumCas;

byte blockcontent[16] = NullData;
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < pocet; i++) {
    pinMode(dipPins[i], INPUT);      // set the digital pins (defined above) as input
    digitalWrite(dipPins[i], HIGH);  // set internal pullup resistor on
     pinMode(interruptPin, INPUT_PULLUP);
  }
  rtc.begin();
  SPI.begin();            // Init SPI bus
  mfrc522.PCD_Init();     // Init MFRC522
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }
 pinMode(led, OUTPUT);
 pinMode(led2, OUTPUT);
 pinMode(bzucak, OUTPUT);
 Serial.println(F("Scan PICC to see UID, type, and data blocks..."));
 //rtc.setDateTime(__DATE__,__TIME__);   
}

void loop() {
  digitalWrite(led,LOW);
  digitalWrite(led2,LOW);
   ID = ZjistiID();
    Serial.println(ID);
    initRFID();
   if(ID == 0) { UpdateTime(); }
    else
    {
      digitalWrite(led, HIGH);
      getTime();
      ZapisDat();
      digitalWrite(led, LOW);
      delay(1000);
      Serial.println(digitalRead(interruptPin));
      if(digitalRead(interruptPin) == 1) { GoingToSleep();  }
  }
}
 
 
 
 */
/*void UpdateTime()
{
  digitalWrite(led2,HIGH);
  Serial.println(getTime());
  if (!RFIDTest()) { return;  }
  digitalWrite(led2,HIGH);
  byte timee[18];
  byte datee[18];
  readBlock(1, timee);
  readBlock(2, datee);
  rtc.setDateTime(datee,timee);
  Serial.println(getTime());
  digitalWrite(led2,LOW);
  OKDONE(2000);
}*/
