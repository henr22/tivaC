/**
 * @file
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdbool.h>
#include "inc/tm4c1230h6pm.h"
#include "inc/hw_memmap.h"

extern void configureTimer(void);
extern void setupTime(uint32_t ticks);
extern void startTimer();
extern bool timeExceeded();
extern void timer0Disable(void);
extern void timer0Enable(void);
extern void setTimerClock(uint8_t timer);
extern void clearTimerClock(uint8_t timer);
extern void delayMs(uint32_t time);
extern void delayMicros(uint32_t time);
extern void delayMs(uint32_t time);
extern void oneShotTimerInit(void);
extern uint32_t getMicros();

#endif /* TIMER_H_ */
