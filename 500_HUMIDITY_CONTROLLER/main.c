/**
 * main.c
 */

//C libraries
#include <stdint.h>
#include <stdbool.h>

//microcontroller libraries
#include "inc/tm4c123gh6pm.h" //Registers definitions
#include "inc/hw_memmap.h"

//Project libraries
#include "led.h"
#include "timer.h"
#include "adc.h"
#include "uart.h"
#include "string.h"
#include "general.h"

void setup(void);

volatile uint32_t adcResult = 0;

int main(void)
{
    setup();
    char buffer[5];

    adcResult = ADC1_SSFIFO3_R;
    while(1)
    {
        if (TIMER0_RIS_R & 0x00000001 == 1)
        {
            adcResult = ADC1_SSFIFO3_R;

            TIMER0_ICR_R |= (1 << 0);

            if(adcResult > 1500)
            {
                GPIO_PORTF_DATA_R |= (1 << 2);
            }
            else
            {
                GPIO_PORTF_DATA_R &= ~(1 << 2);
            }
            itoa(buffer, adcResult);

            printString(buffer);
            printString("\n\r");
         }
    }
}

void setup(void)
{
    configureLED(BLUE);
    configureTimer();
    configureAdc();
    configureUart(0x1, PORTA);
}


