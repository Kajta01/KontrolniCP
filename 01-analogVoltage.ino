#include "init.h"

float ReadAnalogVoltage(){
    return (analogRead(BATTERY_PIN)*(3.3/1023.00));
}
