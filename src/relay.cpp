#include <Arduino.h>
#include "relay.h"

void setupRelay(){
    pinMode(RELE1, OUTPUT);
    digitalWrite(RELE1, LOW); 
    delay(100);

}

void modifyRelay(bool state){
    digitalWrite(RELE1, state); 
}