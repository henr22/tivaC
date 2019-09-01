

/**
 * main.c
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>



#include "inc/tm4c1230h6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/uart.h"


#include "led.h"
#include "timer.h"
#include "adc.h"
#include "uart.h"

void setup(void);

volatile uint32_t adcResult = 0;

void ADCSS3_Handler(void)
{
    adcResult = ADC1_SSFIFO3_R;
    ADC1_ISC_R = (1 << 3);
}

int main(void)
{
    setup();

    while(1)
    {
            if (TIMER0_RIS_R & 0x00000001 == 1)
            {
                TIMER0_ICR_R |= (1 << 0);

                if(adcResult > 1500)
                {
                    GPIO_PORTF_DATA_R |= (1 << 2);
                }
                else
                {
                    GPIO_PORTF_DATA_R &= ~(1 << 2);
                }
                //GPIO_PORTF_DATA_R ^= (1 << 2); //turn on red led
                //printString("Ola\n\r");
                //UARTCharPut(UART0_BASE, "!");
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
