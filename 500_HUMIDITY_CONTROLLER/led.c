/*
 * led.c
 *
 *  Created on: Aug 31, 2019
 *      Author: jhfpi
 */

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "led.h"

//Configure on-board led
/*
 * Function Name: configureLED
 * Inputs:
 * color: It is used to choose wich led is expected to be set. Can have values RED, GREEN, BLUE.
 */
void configureLED(uint32_t ledColor)
{
    SYSCTL_RCGCGPIO_R   |= (1 << 5); //clock to Port F
    while(SYSCTL_RCGCGPIO_R & (1 << 5) == 0xFFFFFFFF & (1 << 5)); //It is always needed a 3 clock ticks to set the clock to the GPIO
    GPIO_PORTF_DIR_R    = (1 << ledColor);
    GPIO_PORTF_AFSEL_R  &= ~(1 << ledColor);
    GPIO_PORTF_DEN_R    = (1 << ledColor); //digital enable
    // For debug
    GPIO_PORTF_DATA_R   |= (1 << ledColor); //turn on LED
}



