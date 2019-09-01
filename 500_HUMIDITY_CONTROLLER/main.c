

/**
 * main.c
 */
#include <stdint.h>
#include "inc/tm4c1230h6pm.h"
#include "led.h"
#include "timer.h"
#include "adc.h"

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
            }
    }
}

void setup(void)
{
    configureLED(BLUE);
    configureTimer();
    configureAdc();
}
