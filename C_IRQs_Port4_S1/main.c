#include <msp430.h>

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    //-- Setup Ports
    P1DIR |= BIT0;          // Set P1.0 (LED1) Direction = out
    P1OUT &= ~BIT0;         // Clear P1.0 to start

    P4DIR &= ~BIT1;         // Clear P4.1 (S1) Direction = in
    P4REN |= BIT1;          // Enable Pull up/down resistor
    P4OUT |= BIT1;          // make resistor a pull up
    P4IES |= BIT1;           // Config IRQ Sensitivity H-to-L

    PM5CTL0 &= ~LOCKLPM5;   // Turn on GPIO

    //-- Setup IRQ
    P4IFG &= ~BIT1;         // Clear Port 4.1 IRQ Flag
    P4IE |= BIT1;           // Enable Port 4.1 IRQ
    __enable_interrupt();   // Enable Maskable IRQs

    //-- Main Loop
    while (1)
    {
    }

    return 0;
}

//-- Interrupt Service Routines
#pragma vector = PORT4_VECTOR
__interrupt void ISR_Port4_s1(void)
{
    P1OUT ^= BIT0;
    P4IFG &= ~BIT1;
}
