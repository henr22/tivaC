/**
 * @file
 */
#include <stdint.h>
<<<<<<< HEAD:500_HUMIDITY_CONTROLLER/timer.c
#include "inc/tm4c123gh6pm.h"
=======
#include <stdbool.h>
#include "inc/tm4c1230h6pm.h"
>>>>>>> 08e3c9a03ea052d25e7c35bed6f1e5e3cbdc78ae:500_HUMIDITY_CONTROLLER/src/drivers/timer.c
#include "timer.h"

void timerInit()
{
    //TODO: Initialise a timer to count delays.
}

void setTimer(uint32_t time)
{
    //TODO: Sets the time the counter should pass until raise the flag
}

void delayMs(uint32_t time)
{
    setTimer(time);
    startTimer();
    while(!timeExceeded());
    return;
}

void startTimer()
{
    //TODO: Starts counting the time
}

bool timeExceeded()
{
    return true;
    //TODO: Checks when timee has been exceeded
}

void configureTimer(void)
{
    SYSCTL_RCGCTIMER_R |= 0x1; // give clock to timer 0
    while(SYSCTL_RCGCTIMER_R & 1 == 0xFFFFFFFF & 1);
    //1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making
   //any changes.
    TIMER0_CTL_R &= ~(1 << 0); //This will clear the last bit

    //2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.
    TIMER0_CFG_R = 0x00000000;
    //3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
    //a. Write a value of 0x1 for One-Shot mode.
    //b. Write a value of 0x2 for Periodic mode.
    TIMER0_TAMR_R |= (0x2 << 0);

    //4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
    //to select whether to capture the value of the free-running timer at time-out, use an external
//    trigger to start counting, configure an additional trigger or interrupt, and count up or down.
    TIMER0_TAMR_R &= ~(1 << 4); // set TACDIR field to count down

    //    5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
    TIMER0_TAILR_R = 0x00F42400; //16 000 000 This is value is chosen because we want 1 second and clock speed is 16MHz
    //    6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register
//    (GPTMIMR).

    //To enable ADC samples with the timer
    TIMER0_CTL_R |= (1 << 5);

    //    7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
    TIMER0_CTL_R |= (1 << 0);
    //    8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
//    the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
//    Register (GPTMICR).
}


