#include "init.h"

#include <MFRC522.h>

MFRC522 mfrc522(RFID_SS_PIN, RFID_RST_PIN); // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

byte readbackblock[18];
byte writeblock[16] = NullDataS;

const int blockID = 1;

const int StartRow = 4;
const int EndRow = 64;

feedbackStatus RFID_FreeRow() //ok 03_03
{
#ifdef DEBUG
  Serial.println("************************************************");
  Serial.println("RFID - Search free row");
#endif

  for (int i = StartRow; i < EndRow; i++)
  {
    #ifdef DEBUG
    Serial.println("***");
    Serial.println(i);
    #endif
    switch (readBlock(i, readbackblock))
    {
    case 2: //error auth, read/write
    case 3:
      mfrc522.PICC_IsNewCardPresent();
      mfrc522.PICC_ReadCardSerial(); //if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
      i--;
      break;

    case 1: //trailer
      break;

    case 0: //ok -  ověření volného řádku;
      String data = (String((char *)readbackblock)).substring(0, 16);

      if (data == "")
      { // Data s null
        Serial.println("Null");
        return i;
      }
      else
      {
        Serial.println("Full");
      }
      break;
    }
  }

  //plna pamet
  return FULL_MEMORY;
}

feedbackStatus RFID_NewEntry(int row, byte ID, byte Day, byte Hour, byte Minute, byte Second)
{

  RFID_WriteRow(row, ID, Day, Hour, Minute, Second);

  return RFID_checkRowVal(row);


}

void RFID_WriteRow(int row, byte ID, byte Day, byte Hour, byte Minute, byte Second)
{
  int checkSum = ID + Day + Hour + Minute + Second;
  memset(writeblock, 0, sizeof(writeblock));
  writeblock[0] = ID;
  writeblock[1] = Day;
  writeblock[2] = Hour;
  writeblock[3] = Minute;
  writeblock[4] = Second;

  writeblock[7] = checkSum;
  writeBlock(row, writeblock);

#if DEBUG
  Serial.println(" ************************************************* ");
  Serial.println("RFID zápis");
  Serial.print("Row: ");
  Serial.print(row);
  Serial.print(" ID: ");
  Serial.print(ID);
  Serial.print(", day: ");
  Serial.print(Day);
  Serial.print(", hour: ");
  Serial.print(Hour);
  Serial.print(", minute: ");
  Serial.print(Minute);
  Serial.print(", second: ");
  Serial.print(Second);
  Serial.print(", checkSum: ");
  Serial.print(checkSum);
  Serial.println("");
#endif
}
feedbackStatus RFID_checkRowVal(int row)
{
#if DEBUG
  Serial.print("Read row ");
  Serial.println(row);
#endif

  while(readBlock(row, readbackblock)!=0);

  int checkSum = 0;
  for (int i = 0; i < 5; i++)
  {
    checkSum += readbackblock[i];
  }
  if (checkSum == readbackblock[7])
  {
#if DEBUG
    Serial.println("checkSum id OK");
#endif
    return OK;
  }
  else
  {
#if DEBUG
    Serial.println("checkSum id NOok");
#endif
    return ERROR;
  }
}

void RFID_getRowValues()
{
  LedOn();
  for (int i = StartRow; i < EndRow; i++)
  {
    RFID_getRowVal(i);

  }
  Serial.write(0xFF);
  Serial.write(0xFF);
  LedOff();
}
void RFID_getRowVal(int row)
{
  #if DEBUG
  Serial.print("Read row");
  Serial.println(row);
  #endif

  readBlock(row, readbackblock);
  if(readbackblock[0] != 0)
  {
    Serial.write(0x4);
    Serial.write(0x57);
    for(int i = 0;i<=4;i++){
      Serial.write(readbackblock[i]);
    }
    Serial.write(readbackblock[7]);


  int checkSum = 0;
  for (int i = 0; i < 5; i++)
  {
    checkSum += readbackblock[i];
  }
  if (checkSum == readbackblock[7])
  {
    #if DEBUG
    Serial.println("checkSum id OK");
    #endif
  }
  else
  {
    #if DEBUG
    Serial.println("checkSum id NOok");
    #endif
  }
  }
}

int RFID_getIDCip()
{
  RFID_init();
  if (!RFIDTest())
  {
    return;
  }
  readBlock(blockID, readbackblock); //read the block back
  int vysledek = (readbackblock[0] << 8) + readbackblock[1];
#ifdef DEBUG
  Serial.println("ID čipu:");
  Serial.println(vysledek);
#endif
  return (int)vysledek;
}

/******************************************************************
 *                 OSTATNI
 * ****************************************************************/

// tabulkový výpis
void RFID_OnlyRead() // ookk
{
  RFID_init();
  if (!RFIDTest())
  {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}

int RFID_zapisID() // ookk
{
  memset(writeblock, 0, sizeof(writeblock));
  Serial.println("ID (max 65535):");
  while (Serial.available() == 0)
  {
  }
  int readValue = Serial.readString().toInt();

  Serial.println("B:");
  Serial.println(readValue);

  writeblock[0] = (byte)(readValue >> 8) & 0xFF; // high byte (0x12)
  writeblock[1] = (byte)readValue & 0xFF;        // low byte  (0x34)

  Serial.println(";");
  Serial.println("...pokus o zápis...");

  RFID_WaitToChip();

  /*****************************************writing and reading a block on the card**********************************************************************/

  writeBlock(blockID, writeblock); //the blockcontent array is written into the card block
  Serial.println("zapsáno");
  return readValue;
}

void RFID_ClearAllData()
{
  RFID_init();
  if (!RFIDTest())
  {
    return;
  }
  memset(writeblock, 0, sizeof(writeblock));

  for (int i = 4; i < 64; i++)
  {
    #ifdef DEBUG
    Serial.println(i);
    #endif

    switch (writeBlock(i, writeblock))
    {
    case 0: //okk
      break;
    case 1:
      break;
    default:
      mfrc522.PICC_IsNewCardPresent();
      mfrc522.PICC_ReadCardSerial(); //if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
      i--;
      break;
    }
  }
}

bool RFID_CheckNullData()
{
  String data;
  RFID_init();
  if (!RFIDTest())
  {
    return 1;
  }
  for (int i = 4; i < 64; i++)
  {
    Serial.println(i);

    switch (readBlock(i, readbackblock))
    {
    case 0: // vyčtené data
      data = (String((char *)readbackblock)).substring(0, 16);

      if (data != "")
      {
        return 1; //Error
      }
      break;
    case 1:
      break;
    default:
      mfrc522.PICC_IsNewCardPresent();
      mfrc522.PICC_ReadCardSerial(); //if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
      i--;
      break;
    }
  }
  return 0; //ok
}

/******************************************************************
 *                 PROVOZNI
 * ****************************************************************/
boolean RFID_WaitToChip(int time)
{
  int i = time;
  RFID_init();
  do
  {
    LedOn();
    delay(50);
    LedOff();
    if ((i--) < 0)
      return false;
  } while (!RFIDTest());
  return true;
}
void RFID_WaitToChip()
{

  RFID_init();
  do
  {
    LedOn();
    delay(50);
    LedOff();
  } while (!RFIDTest());
}

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
#if DEBUG
  Serial.println("card selected");
#endif
  return true;
}

int readBlock(int blockNumber, byte arrayAddress[])
{
  if (blockNumber > 2 && (blockNumber + 1) % 4 == 0)
  {
    #if DEBUG
    Serial.print(blockNumber);
    Serial.println(" is a trailer block:");
    #endif
    return 1; // trailer
  }
#if DEBUG
  Serial.println("read");
  #endif
  int trailerBlock = (blockNumber / 4 * 4) + 3;

  /*****************************************authentication of the desired block for access***********************************************************/
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("PCD_Authenticate() failed (read): ");
    return 2; //error aut
  }

  byte buffersize = 18;                                                 //we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size...
  status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize); //&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("MIFARE_read() failed: ");
    return 3; // read error
  }
  #if DEBUG
  Serial.println("block was read");
  #endif
  return 0; // ok
}

int writeBlock(int blockNumber, byte arrayAddress[])
{
  //this makes sure that we only write into data blocks. Every 4th block is a trailer block for the access/security info.
  int trailerBlock = (blockNumber / 4 * 4) + 3; //determine trailer block for the sector
  if (blockNumber > 2 && (blockNumber + 1) % 4 == 0)
  {
    #if DEBUG
    Serial.print(blockNumber);
    Serial.println(" is a trailer block:");
    #endif
    return 1; // trailer
  }           //block number is a trailer block (modulo 4); quit and send error code 2
  #if DEBUG
  Serial.print(blockNumber);
  Serial.println(" is a data block:");
  #endif

  /*****************************************authentication of the desired block for access***********************************************************/
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
    #if DEBUG
    Serial.print("PCD_Authenticate() failed: ");
    #endif
    return 2; //error aut
  }

  /*****************************************writing the block***********************************************************/

  status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16); //valueBlockA is the block number, MIFARE_Write(block number (0-15), byte array containing 16 values, number of bytes in block (=16))
  //status = mfrc522.MIFARE_Write(9, value1Block, 16);
  if (status != MFRC522::STATUS_OK)
  {
    #if DEBUG
    Serial.print("MIFARE_Write() failed: ");
    #endif
    return 3; //error write
  }
  #if DEBUG
  Serial.println("block was written");
  #endif
  return 0; // ok
}

// 0 - OK
// 1 - trailer
// 2 - F auten
// 3 - F write/read


void RFID_Stop() {
    // Halt PICC
    mfrc522.PICC_HaltA();
  // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
    mfrc522.PCD_SoftPowerDown();

      SPI.endTransaction();
      SPI.end();
}