#include "init.h"

#include <MFRC522.h>

MFRC522 mfrc522(RFID_SS_PIN, RFID_RST_PIN); // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

byte readbackblock[18];
byte writeblock[16] = NullDataS;

int blockID = 1;

/**
 * Initialize.
 */


void RFID_Write()
{
  ZapisDat();
  // Halt PICC
  mfrc522.PICC_HaltA();
  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();
}



// int WriteRow(int row, int ID, String time)
// {
//   char Buffer[3];
//   sprintf(Buffer, "%02d,", ID);
//   Serial.println(Buffer + time);

//   Serial.println("zapis");
//   String message = Buffer + time;
//   byte plain[message.length()];
//   message.getBytes(plain, message.length());
//   writeBlock(radek, plain);
//   //OKDONE(3000);
//   return 1;
// }

// void WriteRow(int radek, int ID, String time)
// {
//   char Buffer[3];
//   sprintf(Buffer, "%02d-", ID);
//   Serial.println(Buffer + time);

//   Serial.println("zapis");
//   String message = Buffer + time;
// byte plain[message.length()];
// message.getBytes(plain, message.length());
// writeBlock(radek, plain);
// tone(bzucak,2000,1000);
//    digitalWrite(led2, HIGH);
//    delay(1000);
//    digitalWrite(led2, LOW);

// }

void ZapisDat()
{
  // attachInterrupt(0,wakeUpW, LOW);
  if (!RFIDTest())
  {
    return;
  }
  for (int i = 62; i > 3; i--)
  {
    Serial.println();
    Serial.println(i);
    switch (readBlock(i, readbackblock))
    {
    case 1:
      mfrc522.PICC_IsNewCardPresent();
      mfrc522.PICC_ReadCardSerial(); //if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.

      i++;
      break;
    case 5: //trailer

      break;
    case 10: // ověření volného řádku;
      String temp = (String((char *)readbackblock)).substring(0, 16);
      Serial.println(temp);
      Serial.println(String(String(temp[0]) + String(temp[1])));

      if (temp == NullDataS)
      {
      //  WriteRow(i, 10, "10:20");
        // detachInterrupt(0);
        return;
      }
      /*  else if(String(String(String(temp[0])+String(temp[1])).toInt())==String(String(ZjistiID()).toInt()))
        {
          
            Serial.println("aa");
            i--;
            if (i > 2 && (i+1)%4 == 0)
            {
              Serial.println("aaa");
              i--;
              }
            
            WriteRow(i, ID, getTime());
            OKDONE(2500);
            detachInterrupt(0);
            return; 
                           
         }   */
      break;
    }
  }
  //plna pamet
  int f = 3000;
  for (int i = 0; i < 5; i++)
  {
    // OKDONE(f);
  }
}




void RFID_ClearAllData()
{
  RFID_init();
    if (!RFIDTest()){
    return;
  }
  memset(writeblock, 0, sizeof(writeblock)); 

  for (int i = 1; i < 64; i++)
  {
    Serial.println(i);

    switch (writeBlock(i, writeblock))
    {
    case 0:
      break;
    case 2:
      break;
    default:
      mfrc522.PICC_IsNewCardPresent();
      mfrc522.PICC_ReadCardSerial(); //if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
      i--;
      break;
    }
  }
}

/******************************************************************
 *                 OSTATNI
 * ****************************************************************/
// tabulkový výpis
void RFID_OnlyRead() // ookk
{
  RFID_init();
    if (!RFIDTest()){ return; }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}

void RFID_zapisID() // ookk
{
    Serial.println("Format: 10 = 0010");
    Serial.println("ID:");
    while (Serial.available() == 0)
    {
    }
    String ss = (String)Serial.readString();
    memset(writeblock, 0, sizeof(writeblock));

    //Serial.println(ss.substring(0, 4));
    writeblock[0] = ss[0];
    writeblock[1] = ss[1];
    writeblock[2] = ss[2];
    writeblock[3] = ss[3];
    for (int j = 0; j < 4; j++) //print the block contents
    {
        Serial.println(j + " - ");
        Serial.write(writeblock[j]); //Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
    }
    Serial.println(";");
    Serial.println("...pokus o zápis...");
    RFID_init();
    do{
        delay(100);
    }while(!RFIDTest());

    /*****************************************writing and reading a block on the card**********************************************************************/

    writeBlock(blockID, writeblock); //the blockcontent array is written into the card block
    Serial.println("zapsáno");

    readBlock(blockID, readbackblock); //read the block back
    Serial.print("read block: ");
    for (int j = 0; j < 16; j++) //print the block contents
    {
        Serial.write(readbackblock[j]); //Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
    }
    Serial.println("");
    Serial.println("______________________________________________________");
}
/******************************************************************
 *                 PROVOZNI
 * ****************************************************************/
void RFID_init()
{
  mfrc522.PCD_Init(); // Init MFRC522 card

  // Prepare the key (used both as key A and as key B)
  // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
}

bool RFIDTest()
{
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return false;
  }
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return false;
  }
  Serial.println("card selected");
  return true;
}

int readBlock(int blockNumber, byte arrayAddress[])
{
  if (blockNumber > 2 && (blockNumber + 1) % 4 == 0)
  {
    Serial.print(blockNumber);
    Serial.println(" is a trailer block:");
    return 5;
  }

  Serial.println("read");
  int trailerBlock = (blockNumber / 4 * 4) + 3;

  /*****************************************authentication of the desired block for access***********************************************************/
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("PCD_Authenticate() failed (read): ");
    return 1; //return "1" as error message
  }

  byte buffersize = 18;                                                 //we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size...
  status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize); //&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("MIFARE_read() failed: ");
    return 1; //return "2" as error message
  }
  Serial.println("block was read");
  return 10;
}

int writeBlock(int blockNumber, byte arrayAddress[])
{
  //this makes sure that we only write into data blocks. Every 4th block is a trailer block for the access/security info.
  int trailerBlock = (blockNumber / 4 * 4) + 3; //determine trailer block for the sector
  if (blockNumber > 2 && (blockNumber + 1) % 4 == 0)
  {
    Serial.print(blockNumber);
    Serial.println(" is a trailer block:");
    return 2;
  } //block number is a trailer block (modulo 4); quit and send error code 2
  Serial.print(blockNumber);
  Serial.println(" is a data block:");

  /*****************************************authentication of the desired block for access***********************************************************/
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("PCD_Authenticate() failed: ");
    return 3; //return "3" as error message
  }

  /*****************************************writing the block***********************************************************/

  status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16); //valueBlockA is the block number, MIFARE_Write(block number (0-15), byte array containing 16 values, number of bytes in block (=16))
  //status = mfrc522.MIFARE_Write(9, value1Block, 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("MIFARE_Write() failed: ");
    return 4; //return "4" as error message
  }
  Serial.println("block was written");
  return 0;
}
