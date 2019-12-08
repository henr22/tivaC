/*
 * digital.c
 *  @file
 *  Created on: Dec 7, 2019
 *      Author: jhfpi
 */

#include <digital.h>

/**
 * @brief Configure builtin led.
 */
void builtInLedInit()
{
    setClockToPort(PORTF);
    portFDirection(OUTPUT, 1);
    portFDirection(OUTPUT, 2);
    portFDirection(OUTPUT, 3);
    portFAFSel(NO_ALTERNATE, 1);
    portFAFSel(NO_ALTERNATE, 2);
    portFAFSel(NO_ALTERNATE, 3);
    portFDigitalEnable(ENABLE, 1);
    portFDigitalEnable(ENABLE, 2);
    portFDigitalEnable(ENABLE, 3);
}
/**
 * \brief Sets data register bit from portF
 */

void digitalWrite(uint8_t pin, uint8_t value)
{
    uint32_t bitMask = 0;
    if(value == LOW)
    {
        bitMask = ~(1 << pin);
        GPIO_PORTF_DATA_R &= bitMask;
    }
    else
    {
        bitMask = (1 << pin);
        GPIO_PORTF_DATA_R |= bitMask;
    }
}

uint32_t digitalRead(uint8_t pin)
{
    return GPIO_PORTF_DATA_R & (1 << pin);
}

/**
 * \brief Sets if portF digital Enable register
 *  @param den 0 to disable digital function, 1 to enable it
 *         pin from 0 to 7 chooses the pin in PORTF to configure
 */

uint8_t portFDigitalEnable(uint32_t den, uint8_t pin)
{
    uint32_t bitMask = 0;
    uint8_t retValue = INPUT_ERROR;

    if (pin < 8 || den < 2) // 7 is the highest value for a pin in a port, 1 because we can only have 1 or 0
    {
        bitMask = (den << pin);
        GPIO_PORTF_DEN_R |= bitMask; /** Set desired pin to 0*/
        retValue = SUCCESS;
    }

    return retValue;
}

/**
 * \brief Sets if portF will use of not the alternative function
 *  @param afSel 0 to normal GPIO function, 1 to use alternative hardware function
 *         pin from 0 to 7 chooses the pin in PORTF to configure
 */

uint8_t portFAFSel(uint32_t afSel, uint8_t pin)
{
    uint32_t bitMask = 0;
    uint8_t retValue = INPUT_ERROR;

    if (pin < 8 || afSel < 2) // 7 is the highest value for a pin in a port, 1 because we can only have 1 or 0
    {
        bitMask = (afSel << pin);
        GPIO_PORTF_AFSEL_R |= bitMask; /** Set desired pin to 0*/
        retValue = SUCCESS;
    }

    return retValue;
}
/**
 * \brief Sets the direction in a pin from PortF
 * @param dir: 1 to output, 0 to input
 *        pin: 0 to 7
 */
uint8_t portFDirection(uint32_t dir, uint8_t pin)
{
    uint32_t bitMask = 0;
    uint8_t retValue = INPUT_ERROR;

    if (pin < 8 || dir < 2) // 7 is the highest value for a pin in a port, 1 because we can only have 1 or 0
    {
        bitMask = (1 << pin);
        if (dir == 0)
        {
            GPIO_PORTF_DIR_R &= ~bitMask; /** Set desired pin to 0*/
        }
        else
        {
            GPIO_PORTF_DIR_R |= bitMask; /** Set desired pin to 1*/
        }
        retValue = SUCCESS;
    }

    return retValue;
}

/**
 * \brief Sets builtin LED color
 *
 * @param ledColor Sets the color. See < see ::colorEnum for colors values.
 */
void setbuiltinLed(colorEnum color)
{
    GPIO_PORTF_DATA_R &= ~0xE;
    GPIO_PORTF_DATA_R |= 1 << color;
}

/**
 * Function: setClockToPort
 * @brief Sets the clock to a digital Port
 * @param port Defines the port which will have its clock set
 */
uint32_t setClockToPort(uint32_t port /**< [in] The number of the port that will be set */)
{
    uint32_t timeout = CLOCK_TIMEOUT;

    SYSCTL_RCGCGPIO_R   |= port;

    while(SYSCTL_RCGCGPIO_R & port != port)
    {
        if(timeout == 0)
        {
            return CLOCK_TIMEOUT_ERROR;
        }
        timeout--;
    }
    return SUCCESS;
}

void setPinIn(uint32_t pin)
{
    //TODO:
}

void setPinOut(uint32_t pin)
{
    //TODO:
}
