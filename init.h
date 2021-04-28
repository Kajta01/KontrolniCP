#define ID_DEVICE 10
// Lora
#define LORA_DEV_ADDR "26013E5E"
#define LORA_NWKS_KEY "3F89B93C069B1224B6C0656470269989"
#define LORA_APPS_KEY "61000EE5191DB1E5B1F334E80B0D4EAF"

// // batery
#define BATTERY_PIN A2
#define BATTERY_PIN_START_MEASURE A3
// //RFID
#define RFID_RST_PIN A0 // Configurable, see typical pin layout above
#define RFID_SS_PIN 10  // Configurable, see typical pin layout above
                        // //LED
#define LED1 8
#define LED2 9
#define BUZZER 5
//Button
#define BUTTON 2
#define RESET 3
//Lora
#define LORA_RESET 4
#define LORA_RX 6
#define LORA_TX 7

#define NullDataS "000000000000000"
#define NullDataB 0x0


/**************************Mode*******************************************************************/
#define STANOVISTE                  0
#define STANOVISTE_WTG              0


#define CONN_SERIAL                 1

#define JEN_CTENI                   0 // tabulkový výpis 
#define JEN_VYPIS                   0
#define JEN_WTD                     0
#define JEN_LORA                    0

/////////////////////////////////
#define DEBUG                       0

//////////////////////////////////// jednotlive moduly

#define M_RFID    0
#define M_LORA    0
#define M_ARDUINO 0
#define M_Z5V 0