#include "init.h"

#include <MFRC522.h>

MFRC522 mfrc522(RFID_SS_PIN, RFID_RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;



/**
 * Initialize.
 */
void RFID_init() {
 
    mfrc522.PCD_Init();	// Init MFRC522 card

    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

}


void RFID_Write() {
        // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
}


bool RFIDTest(){ 
  if ( ! mfrc522.PICC_IsNewCardPresent()) { return false; }
  if ( ! mfrc522.PICC_ReadCardSerial()) { return false; }
  Serial.println("card selected");
  return true; 
} 

