

/**
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c1230h6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/uart.h"

#include "led.h"
#include "timer.h"
#include "adc.h"
#include "uart.h"
#include "string.h"

void setup(void);

volatile uint32_t adcResult = 0;

int main(void)
{
    setup();
    char buffer[5];

    while(1)
    {

        adcResult = ADC1_SSFIFO3_R;

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
    configureUart();
}


