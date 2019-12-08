/*
 * dht11.c
 *
 *  Created on: Dec 8, 2019
 *      Author: jhfpi
 */

#include "dht11.h"

void dht11Init(uint8_t pin)
{
    setClockToPort(PORTF);
    portFDirection(OUTPUT, pin);
    portFAFSel(NO_ALTERNATE, pin);
    portFDigitalEnable(ENABLE, pin);
}

uint32_t requestSample(uint8_t pin)
{
    // REQUEST SAMPLE
        //pinMode(pin, OUTPUT);
        portFDirection(OUTPUT, pin);
        digitalWrite(pin, LOW); // T-be


        //delay(wakeupDelay);
        //digitalWrite(pin, HIGH);   // T-go
        //delayMicroseconds(40);
        //pinMode(pin, INPUT);

}
