int ErrorCnt = 0;

void ErrorHdlAdd(){
    ErrorCnt++;
}
void ErrorHdlNull(){
    ErrorCnt = 0;
}
void ErrorHdlCheck(){
    if(ErrorCnt > 20)
    {
        Serial.println("RRRREEEEEESSSSEEERETTTTTTT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        pinMode(RESET,OUTPUT);         
        digitalWrite(RESET,HIGH);
    }
}
void ErrorHdlReset(){
    pinMode(RESET,OUTPUT);         
    digitalWrite(RESET,HIGH);
}