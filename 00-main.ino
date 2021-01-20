// // batery
 #define BATTERY_PIN  A2
// //RFID
 #define RFID_RST_PIN         A0           // Configurable, see typical pin layout above
 #define RFID_SS_PIN          10          // Configurable, see typical pin layout above
// //LED
 #define LED1    7
 #define LED2    8
 #define BUZZER  9
 //Button
 #define BUTTON 2
// Lora
const char *devAddr = "26011C79";
const char *nwkSKey = "B5C7617898FE02D5B85C96982E7BEA73";
const char *appSKey = "2DAA66D68271DEAAF00FA821B4EEC5F5";
//
#define ID 10

void setup()
 {
    Serial.begin(9600);
    Serial.println("Starting");
    RTCStart();
    RFID_setup();
    LORA_setup();


    pinMode(BUTTON, INPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(BUZZER, OUTPUT);
 }
 void loop()
 {
     if(digitalRead(BUTTON) == 0)
     {
     Serial.println("------------------------");
     Serial.print("Voltage:");
     Serial.println(ReadAnalogVoltage()*2);
     Serial.print("RTC:");
     Serial.println(RTCRead());
     Serial.println("RFID:");
     RFID_loop();
     Serial.println("LORA:");
     LORA_loop();
     buzzer();
     }



     delay(1000);
 }