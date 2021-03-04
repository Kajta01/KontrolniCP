#define ID_DEVICE 10
// Lora
#define LORA_DEV_ADDR "26011C79"
#define LORA_NWKS_KEY "B5C7617898FE02D5B85C96982E7BEA73"
#define LORA_APPS_KEY "2DAA66D68271DEAAF00FA821B4EEC5F5"

// // batery
#define BATTERY_PIN A2
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
#define STANOVISTE_BEZ_LORY         0

#define CLEAR_DATA                  0
#define ZAPIS_ID_CIPU               0

#define JEN_CTENI                   0 // tabulkový výpis // ok
#define JEN_MERENI                  0
#define JEN_ZVUK_LED                0
#define JEN_SPANEK                  0

#define JEN_WTD                     0
#define JEN_LORA                    1

#define RFID_NEW_ENTRY              0
#define RFID_GET_ROW_VALUES         0

#define TEMP                        0