#include "init.h"

/*
 * Author: JP Meijers
 * Date: 2016-02-07
 * Previous filename: TTN-Mapper-TTNEnschede-V1
 *
 * This program is meant to be used with an Arduino UNO or NANO, conencted to an RNxx3 radio module.
 * It will most likely also work on other compatible Arduino or Arduino compatible boards, like The Things Uno, but might need some slight modifications.
 *
 * Transmit a one byte packet via TTN. This happens as fast as possible, while still keeping to
 * the 1% duty cycle rules enforced by the RN2483's built in LoRaWAN stack. Even though this is
 * allowed by the radio regulations of the 868MHz band, the fair use policy of TTN may prohibit this.
 *
 * CHECK THE RULES BEFORE USING THIS PROGRAM!
 *
 * CHANGE ADDRESS!
 * Change the device address, network (session) key, and app (session) key to the values
 * that are registered via the TTN dashboard.
 * The appropriate line is "myLora.initABP(XXX);" or "myLora.initOTAA(XXX);"
 * When using ABP, it is advised to enable "relax frame count".
 *
 * Connect the RN2xx3 as follows:
 * RN2xx3 -- Arduino
 * Uart TX -- 10
 * Uart RX -- 11
 * Reset -- 12
 * Vcc -- 3.3V
 * Gnd -- Gnd
 *
 * If you use an Arduino with a free hardware serial port, you can replace
 * the line "rn2xx3 myLora(mySerial);"
 * with     "rn2xx3 myLora(SerialX);"
 * where the parameter is the serial port the RN2xx3 is connected to.
 * Remember that the serial port should be initialised before calling initTTN().
 * For best performance the serial port should be set to 57600 baud, which is impossible with a software serial port.
 * If you use 57600 baud, you can remove the line "myLora.autobaud();".
 *
 */
#include <rn2xx3.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(LORA_RX, LORA_TX); // RX, TX

//create an instance of the rn2xx3 library,
//giving the software serial as port to use
rn2xx3 myLora(mySerial);

// the setup routine runs once when you press reset:
void LORA_setup()
{

  // Open serial communications and wait for port to open:
  mySerial.begin(9600); //serial port to radio
  Serial.println("Startup");

  initialize_radio();
  //transmit a startup message
  Serial.println("Tx T");
  myLora.tx("T");

  delay(100);
}
void LORA_initialize_radio()
{
  //reset rn2483

  myLora.autobaud();
}

void initialize_radio()
{
  //reset rn2483

  digitalWrite(LORA_RESET, LOW);
  delay(500);
  digitalWrite(LORA_RESET, HIGH);

  delay(100); //wait for the RN2xx3's startup message
  mySerial.flush();

  //Autobaud the rn2483 module to 9600. The default would otherwise be 57600.
  myLora.autobaud();

//check communication with radio
#if 0 //DEBUG
  String hweui = myLora.hweui();
  while (hweui.length() != 16)
  {
    Serial.println("Communication with RN2xx3 unsuccessful. Power cycle the board.");
    Serial.println(hweui);
    delay(10000);

    hweui = myLora.hweui();
  }

  //print out the HWEUI so that we can register it via ttnctl
  Serial.println("When using OTAA, register this DevEUI: ");
  Serial.println(myLora.hweui());
  Serial.println("RN2xx3 firmware version:");
  Serial.println(myLora.sysver());
#endif
  //configure your keys and join the network
  Serial.println("Trying to join TTN");

  myLora.initABP((char *)LORA_DEV_ADDR, (char *)LORA_APPS_KEY, (char *)LORA_NWKS_KEY);

  Serial.println("Joined");
}

// the loop routine runs over and over again forever:
void LORA_Send()
{

  //myLora.tx(String(ID_DEVICE)); //one byte, blocking function
  byte writeLora[10] = {0x0};
  memset(writeLora, 0, sizeof(writeLora));
  writeLora[0] = ID_DEVICE;
  writeLora[1] = 4;
  writeLora[2] = 9;
  writeLora[3] = 31;
  writeLora[4] = 55;

  myLora.txBytes(writeLora, sizeof(writeLora));

  delay(1000);
}
void LORA_Send(byte ID_Device, byte ID_TAG, byte Hour, byte Minute, byte Second, float Battery, float Temperature)
{
  int checkSum = 0;
  int TemperatureI = (int)((Temperature + 273) * 10);
  byte writeLora[10] = {0x0};
  memset(writeLora, 0, sizeof(writeLora));
  writeLora[0] = 0x11; // send data
  writeLora[1] = ID_Device;
  writeLora[2] = (byte)(ID_TAG >> 8) & 0xFF;
  writeLora[3] = (byte)ID_TAG & 0xFF;
  writeLora[4] = Hour;
  writeLora[5] = Minute;
  writeLora[6] = Second;
  writeLora[7] = Battery * 10;
  writeLora[8] = (byte)(TemperatureI >> 8) & 0xFF;
  writeLora[9] = (byte)TemperatureI & 0xFF;

  for (int i = 0; i < sizeof(writeLora); i++)
  {
    checkSum += writeLora[i];
  }
  Serial.println("tx");
  myLora.txBytes(writeLora, sizeof(writeLora));

#if DEBUG
  Serial.println(" ************************************************* ");
  Serial.println("LORA zápis");
  Serial.print("IDcip: ");
  Serial.print(ID_TAG);
  Serial.print(" IDdev: ");
  Serial.print(ID_Device);
  Serial.print(", hour: ");
  Serial.print(Hour);
  Serial.print(", minute: ");
  Serial.print(Minute);
  Serial.print(", second: ");
  Serial.print(Second);
  Serial.print(", Temperature: ");
  Serial.print(Temperature);
  Serial.print(", Battery: ");
  Serial.print(Battery);
  Serial.print(", checkSum: ");
  Serial.print(checkSum);
  Serial.println("");
#endif

  delay(1000);
}
void LORA_Sleep()
{
  myLora.sleep(9000000);
}