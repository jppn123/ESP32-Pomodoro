#include <arduino.h>
#include "relay.h"

void setupRelay(){
    pinMode(RELE1, OUTPUT);
    pinMode(RELE2, OUTPUT);
    modifyRelay(false);
    delay(100);
}
//state = 0 ou 1
void modifyRelay(bool state){
    digitalWrite(RELE1, state); //rele ativa com LOW no vin
    digitalWrite(RELE2, state); //rele ativa com LOW no vin
}