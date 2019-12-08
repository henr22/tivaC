
/**
 * main.c
 */
#include <stdint.h>
#include "inc/tm4c1230h6pm.h"
#include "timer.h"

#include <digital.h>


void setup(void);

#define DHT11_PIN 1
#define WAKE_UP_DELAY 18
#define DHTLIB_TIMEOUT (16000000/40000)
#define DHTLIB_ERROR_TIMEOUT    -2

uint8_t status = LOW;
uint8_t mask = 128;
uint8_t idx = 0;
uint8_t i;
uint8_t bits[5];  // buffer to receive data

int main(void)
{
    setup();

    while(1)
    {
        portFDirection(OUTPUT, DHT11_PIN);
        digitalWrite(DHT11_PIN, HIGH);
        delayMs(1000);

        //Request sample
        digitalWrite(DHT11_PIN, LOW);
        delayMs(WAKE_UP_DELAY);
        digitalWrite(DHT11_PIN, HIGH);
        delayMicros(40);

        portFDirection(INPUT, DHT11_PIN);

        // GET ACKNOWLEDGE or TIMEOUT
        uint16_t loopCntLOW = DHTLIB_TIMEOUT;
        uint16_t loopCntHIGH = DHTLIB_TIMEOUT;

        while((GPIO_PORTF_DATA_R & (1 << DHT11_PIN)) == 0)
        {
            if (--loopCntLOW == 0) return DHTLIB_ERROR_TIMEOUT;
        }

        while ((GPIO_PORTF_DATA_R & (1 << DHT11_PIN)) != 0)  // T-reh
        {
            if (--loopCntHIGH == 0) return DHTLIB_ERROR_TIMEOUT;
        }

        // READ THE OUTPUT - 40 BITS => 5 BYTES
        for (i = 40; i != 0; i--)
        {
            loopCntLOW = DHTLIB_TIMEOUT;
            while ((GPIO_PORTF_DATA_R & (1 << DHT11_PIN)) == 0)
            {
                if (--loopCntLOW == 0) return DHTLIB_ERROR_TIMEOUT;
            }

            uint32_t t = getMicros();

            loopCntHIGH = DHTLIB_TIMEOUT;
            while ((GPIO_PORTF_DATA_R & (1 << DHT11_PIN)) == 0)
            {
                if (--loopCntHIGH == 0) return DHTLIB_ERROR_TIMEOUT;
            }

            if ((getMicros() - t) > 40)
            {
                bits[idx] |= mask;
            }
            mask >>= 1;
            if (mask == 0)   // next byte?
            {
                mask = 128;
                idx++;
            }
        }

    }
}

void setup(void)
{
    builtInLedInit();
    dht11Init(DHT11_PIN);
    //configureTimer();
    oneShotTimerInit();
    //edgeCountModeTimerInit();
    periodicTimerInit();

    digitalWrite(DHT11_PIN, HIGH);
}
