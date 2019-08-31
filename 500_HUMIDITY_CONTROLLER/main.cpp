

/**
 * main.c
 */
#include <stdint.h>
#include "inc/tm4c1230h6pm.h"
#include "led.h"
#include "timer.h"

//Configurar timer

int main(void)
{
    configureLED(BLUE);
    configureTimer();

    while(1)
    {
    if (TIMER0_RIS_R & 0x00000001 == 1)
           {
                TIMER0_ICR_R |= (1 << 0);
                GPIO_PORTF_DATA_R ^= (1 << 2); //turn on red led
            }
    }
}
