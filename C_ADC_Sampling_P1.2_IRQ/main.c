#include <msp430.h>

unsigned int ADC_Value;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    P1DIR |= BIT0;
    P6DIR |= BIT6;

    P1SEL1 |= BIT2;
    P1SEL0 |= BIT2;

    PM5CTL0 &= ~LOCKLPM5;

    ADCCTL0 &= ~ADCSHT;
    ADCCTL0 |= ADCSHT_2;
    ADCCTL0 |= ADCON;

    ADCCTL1 |= ADCSSEL_2;
    ADCCTL1 |= ADCSHP;

    ADCCTL2 &= ~ADCRES;
    ADCCTL2 |= ADCRES_2;

    ADCMCTL0 |= ADCINCH_2;
    ADCIE |= ADCIE0;
    __enable_interrupt();

    while (1)
    {
        ADCCTL0 |= ADCENC | ADCSC;
        while ((ADCIFG & ADCIFG0) == 0)
        {
        }
    }

    return 0;
}

//-- Interrupt Service Routines
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
{
    ADC_Value = ADCMEM0;
    if (ADC_Value > 3613)
    {
        P1OUT |= BIT0;
        P6OUT &= ~BIT6;
    }
    else
    {
        P1OUT &= ~BIT0;
        P6OUT |= BIT6;
    }
}
