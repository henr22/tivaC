/**
 * @file
 * @author jpimentel
 * @date November, 10, 2019
 * @brief This software monitors the room temperature and humidity
 */

/** @mainpage Description
 * Software to monitor temperature and humidity of a room
 * @section materials Bill of Materials
 * @subsection material_1 Microcontroller
 * Texas Instruments TM4C1230H6PM
 * @subsection material_2 Sensors
 * DHT11-Temperature-Sensor
 */

#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c1230h6pm.h"

#include "driverlib/uart.h"
#include "../drivers/led.h"
#include "../drivers/timer.h"
#include "../drivers/adc.h"
#include "../drivers/uart.h"
#include "../drivers/string.h"

void setup(void);

volatile uint32_t adcResult = 0;

int main(void)
{
    setup();
    char buffer[5];

    while(1)
{
if(TIMER0_RIS_R & 0x00000001 == 1)
{
    //printString("Time");
    TIMER0_ICR_R |= (1 << 0);
   if(serialAvailable())
   {
        printString("Serial Available");
   }
}
}

    while(0)
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
    builtInLedInit();
    setbuiltinLed(RED);
    configureTimer();
    configureAdc();
    configureUart();
    setbuiltinLed(DARK);
}


