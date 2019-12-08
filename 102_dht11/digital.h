/**
 * @file
 */

#ifndef DIGITAL_H_
#define DIGITAL_H_

/**
 * @enum colorEnum
 *
 */

#include <stdint.h>
#include "inc/tm4c1230h6pm.h"
#include "inc/hw_memmap.h"

#define PORTA 0b000001
#define PORTB 0b000010
#define PORTC 0b000100
#define PORTD 0b001000
#define PORTE 0b010000
#define PORTF 0b100000

#define CLOCK_TIMEOUT 3

#define SUCCESS 0

//data bit definitions
#define LOW (uint8_t) 0
#define HIGH 1

//Dir definitions
#define INPUT 0
#define OUTPUT 1

//AfSel definitions
#define NO_ALTERNATE 0
#define ALTERNATE 1

//DEN definitons
#define DISABLE 0
#define ENABLE 1


//ERROR CODES
#define CLOCK_TIMEOUT_ERROR 1
#define INPUT_ERROR (uint8_t) 2

typedef enum colorEnum
{
    DARK = 0,   /**< Turn off LED*/
    RED,        /**< Turn LED red*/
    BLUE,       /**< Turn LED blue*/
    GREEN       /**< Turn LED green*/
}colorEnum;

extern void builtInLedInit();

extern void setbuiltinLed(colorEnum color);
extern uint32_t setClockToPort(uint32_t port);
extern uint8_t portFDirection(uint32_t dir, uint8_t pin);
extern uint8_t portFAFSel(uint32_t afSel, uint8_t pin);
extern uint8_t portFDigitalEnable(uint32_t den, uint8_t pin);
extern void digitalWrite(uint8_t pin, uint8_t value);
extern uint32_t digitalRead(uint8_t pin);

#endif /* DIGITAL_H_ */
