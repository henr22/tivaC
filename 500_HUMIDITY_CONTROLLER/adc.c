/*
 * adc.c
 *
 *  Created on: Sep 1, 2019
 *      Author: jhfpi
 */
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "adc.h"

void configureAdc(void)
{
    //1. Enable the ADC clock using the RCGCADC register (see page 350).
        SYSCTL_RCGCADC_R    = (1 << 1); //clock ADC1
        while(SYSCTL_RCGCADC_R & (1 << 1) == MAX32 & (1 << 1)); //Wait for clock being set
        //2. Enable the clock to the appropriate GPIO modules via the RCGCGPIO register (see page 338).
        //To find out which GPIO ports to enable, refer to “Signal Description” on page 798.
        SYSCTL_RCGCGPIO_R   |= (1 << 4); //clock to Port E
        while(SYSCTL_RCGCGPIO_R & (1 << 4) == MAX32 & (1 << 4)); //Wait for clock being set
        GPIO_PORTE_DIR_R    &= ~(1 << 1);//set Port E as input    PE1

        //3. Set the GPIO AFSEL bits for the ADC input pins (see page 668). To determine which GPIOs to
        //configure, see Table 23-4 on page 1337.
        GPIO_PORTE_AFSEL_R = (1 << 1); //use PE1 with the alternate function that is an ADC

        //4. Configure the AINx signals to be analog inputs by clearing the corresponding DEN bit in the
        //GPIO Digital Enable (GPIODEN) register (see page 679).
        GPIO_PORTE_DEN_R &= ~(1 << 1); //all ports but PE1

        //5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
        //the appropriate bits of the GPIOAMSEL register (see page 684) in the associated GPIO block.
        GPIO_PORTE_AMSEL_R  = (1 << 1);

        //6. If required by the application, reconfigure the sample sequencer priorities in the ADCSSPRI
    //register. The default configuration has Sample Sequencer 0 with the highest priority and Sample
    //Sequencer 3 as the lowest priority.

        //Configuration of the sample sequencers is slightly more complex than the module initialization
    //because each sample sequencer is completely programmable.
    //The configuration for each sample sequencer should be as follows:

        //1. Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
    //ADCACTSS register. Programming of the sample sequencers is allowed without having them
    //enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
    //event were to occur during the configuration process.
        ADC1_ACTSS_R &= ~(1 << 3); //sequencer 3 because we only want one sampler

        //2. Configure the trigger event for the sample sequencer in the ADCEMUX register.
        //ADC1_EMUX_R = (0xF << 12);
        ADC1_EMUX_R = (0x5 << 12); //to use the timer


        //3. When using a PWM generator as the trigger source, use the ADC Trigger Source Select
    //(ADCTSSEL) register to specify in which PWM module the generator is located. The default
    //register reset selects PWM module 0 for all generators.

        //4. For each sample in the sample sequence, configure the corresponding input source in the
    //ADCSSMUXn register.
        ADC1_SSMUX3_R = 2; //AIN2
        //5. For each sample in the sample sequence, configure the sample control bits in the corresponding
    //nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
    //is set. Failure to set the END bit causes unpredictable behavior.
        ADC1_SSCTL3_R = 0x6; //0110When the sample finishes, uses an interrupt

        //6. If interrupts are to be used, set the corresponding MASK bit in the ADCIM register.
        ADC1_IM_R = (1 << 3);
        //7. Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS
    //register.
        ADC1_ACTSS_R |= (1 << 3);

        ADC1_ISC_R = (1 << 3); //Clears the interrupt flag

        //NVIC_EN1_R |= (1 << 19); //will be done after all configurations
}
