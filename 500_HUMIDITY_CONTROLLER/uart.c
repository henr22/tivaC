/*
 * uart.c
 *
 *  Created on: Sep 1, 2019
 *      Author: jhfpi
 */

#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"

#include "uart.h"

/*
 * uartEnable
 * input: from 0x00 to 0x10000000 depending on which uart we want to enable from 0 to 7
 * multiple bits probably will enable multiple UART Ports. Did not tested
 */
bool uartEnable(uint32_t uart)
{
    if (uart > 0x10000000)
    {
        return false;
    }

    SYSCTL_RCGCUART_R |= uart; //Enable correspondent uart

    return true;
}

void uartPort(uint32_t port)
{
    SYSCTL_RCGCGPIO_R |= (1 << 0); // Clock to Port A
    while((SYSCTL_RCGCGPIO_R & (1 << 0)) != (1 << 0));
}

/*
 * Input information:
 * uart2Enable: 0x00 to 0x1000 0000
 *
 */


void configureUart(uint32_t uart2Enable, uint32_t port)
{
    uartEnable(uart2Enable);
    //    2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 338).
    //    To find out which GPIO port to enable, refer to Table 23-5 on page 1344.
    uartPort(port);
    //    3. Set the GPIO AFSEL bits for the appropriate pins (see page 668). To determine which GPIOs to
    //    configure, see Table 23-4 on page 1337.

    GPIO_PORTA_AFSEL_R = (1 << 1) | (1 << 0); // Pins 17 and 18  corresponding to U0Rx and U0Tx

    //    4. Configure the GPIO current level and/or slew rate as specified for the mode selected (see
    //    page 670 and page 678).
        //Not needed for this project
    //    5. Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate
    //    pins (see page 685 and Table 23-5 on page 1344).
        GPIO_PORTA_PCTL_R = (1 << 0) | (1 << 4); //This sets to PMC

        GPIO_PORTA_DEN_R = (1 << 1) | (1 << 0); // We need to set the pins are digital pins

        // Find the baudrate
        // BRD = 16.000.000 / (16 * 9600) = 104.16666666
        // FBRD = 0.166666666 * 64 + 0.5

    //    1. Disable the UART by clearing the UARTEN bit in the UARTCTL register.
        UART0_CTL_R &= ~(1 << 0);
    //    2. Write the integer portion of the BRD to the UARTIBRD register.
        UART0_IBRD_R = 104;
    //    3. Write the fractional portion of the BRD to the UARTFBRD register.
        UART0_FBRD_R = 11;
    //    4. Write the desired serial parameters to the UARTLCRH register (in this case, a value of
    //    0x0000.0060).
        UART0_LCRH_R = (0x3 << 5);  //8 bit, no parity bit, 1 stop bit
    //    5. Configure the UART clock source by writing to the UARTCC register.
        UART0_CC_R = 0x0;
    //    6. Optionally, configure the DMA channel (see “Micro Direct Memory Access (DMA)” on page 583)
    //    and enable the DMA option(s) in the UARTDMACTL register.
    //    7. Enable the UART by setting the UARTEN bit in the UARTCTL register.
        UART0_CTL_R = (1 << 9) | (1 << 8) | (1 << 0); //enables tx, rx and uart itself
}

char readChar (void)
{
    char c;
    while ((UART0_FR_R & (1 << 4)) != 0);
    c = UART0_DR_R & 0xFF;

    return c;
}

void printChar(char c)
{
    while ((UART0_FR_R & (1 << 5)) != 0);
    UART0_DR_R = c;
}

void printString (char *s)
{
    while (*s != 0)
    {
        printChar(*s);
        s++;
    }
}

