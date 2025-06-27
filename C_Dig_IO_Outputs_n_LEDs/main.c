#include <msp430.h>

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    // Setup Ports
    P1DIR |= BIT0;              // Config P1.0 (LED1) as Output
    PM5CTL0 &= ~LOCKLPM5;       // Turn on GPIO

    while (1)
    {
        P1OUT |= BIT0;          // Turn LED1 On
        P1OUT &= ~BIT0;         // Turn LED1 Off
    }

    return 0;
}
