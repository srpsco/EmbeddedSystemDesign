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

    int i = 0;

    while (1)
    {
        P1OUT ^= BIT0;           // Toggle LED1

        for (i = 0; i < 0xffff; i++)
        {
            // Do nothing but loop to create dealy
        }
    }

    return 0;
}
