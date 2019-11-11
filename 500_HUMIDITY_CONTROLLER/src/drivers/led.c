/**
 * @file
 */

#include <stdint.h>
#include "inc/tm4c1230h6pm.h"
#include "led.h"

/**
 * @brief Configure builtin led.
 */
void builtInLedInit()
{
    SYSCTL_RCGCGPIO_R   |= (1 << 5); //clock to Port F
    while(SYSCTL_RCGCGPIO_R & (1 << 5) == 0xFFFFFFFF & (1 << 5)); //It is always needed a 3 clock ticks to set the clock to the GPIO
    GPIO_PORTF_DIR_R    = 0xE;
    GPIO_PORTF_AFSEL_R  &= ~0xE;
    GPIO_PORTF_DEN_R    = 0xE; //digital enable
}

/**
 * @brief Sets builtin LED color
 *
 * @param ledColor Sets the color. See < see ::colorEnum for colors values.
 */
void setbuiltinLed(colorEnum color)
{
    GPIO_PORTF_DATA_R &= ~0xE;
    GPIO_PORTF_DATA_R |= color << 1;
}
