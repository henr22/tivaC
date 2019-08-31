

/**
 * main.c
 */
#include <stdint.h>
#include "inc/tm4c1230h6pm.h"
#include "led.h"

int main(void)
{
    configureLED(BLUE);
    configureLED(RED);

	return 0;
}
