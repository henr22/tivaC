/**
 * @file
 */
#include <stdint.h>
#include "timer.h"

void timerInit()
{
    //TODO: Initialise a timer to count delays.
}

void delayMs(uint32_t time)
{
    setupTime(16000 * time); // 16000 is the number of clock ticks in one milisecond
    startTimer();
    while(!timeExceeded());
    return;
}

void delayMicros(uint32_t time)
{
    setupTime(16 * time); // 16000 is the number of clock ticks in one milisecond
    startTimer();
    while(!timeExceeded());
}

void startTimer()
{
    timer0Disable();
    timer0Enable();

}

bool timeExceeded()
{
    return TIMER0_TAR_R == 0;
    //TODO: Checks when timee has been exceeded
}
/**
 * \brief Sets the time which timer will start counting
 * @param value to start the clock
 */

void setupTime(uint32_t ticks)
{
    TIMER0_CTL_R &= ~((uint32_t) 1); //Disable Timer A
    TIMER0_TAILR_R = ticks;
    TIMER0_CTL_R |= ((uint32_t) 1); //Enable Timer A
}

void oneShotTimerInit(void)
{
    setTimerClock(0);
    timer0Disable();
    TIMER0_CFG_R = 0x00000000; //32 bits timer
    TIMER0_TAMR_R |= (0x1 << 0); //one shot mode
    TIMER0_TAMR_R |= (0x1 << 4); //up count
    timer0Enable();
}


void periodicTimerInit(void)
{
    setTimerClock(1);
    TIMER1_CTL_R &= ~(1 << 0);
    TIMER1_CFG_R = 0x00000000; //32 bits timer
    TIMER1_TAMR_R |= (0x2 << 0); //periodic timer
    TIMER1_TAMR_R |= (0x1 << 4); //up count
    TIMER1_TAILR_R = 0xFFFFFFFF;
    TIMER1_CTL_R |= (1 << 0);
}

uint32_t getMicros()
{
    return TIMER1_TAR_R / 16;
}

void timer0Disable(void)
{
    TIMER0_CTL_R &= ~(1 << 0);
}

void timer0Enable(void)
{
    TIMER0_CTL_R |= (1 << 0);
}

void setTimerClock(uint8_t timer)
{
    SYSCTL_RCGCTIMER_R |= 1 << timer; //give clock to timer
    while(SYSCTL_RCGCTIMER_R & (1 << timer) == 0xFFFFFFFF & (1 << timer));
}

void clearTimerClock(uint8_t timer)
{
    SYSCTL_RCGCTIMER_R &= ~(1 << timer); // give clock to timer 0
}
