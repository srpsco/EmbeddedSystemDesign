#include <msp430.h>

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //-- Setup Ports
    P1DIR |= BIT0;              // Config P1.0 (LED1) as output
    P1OUT &= ~BIT0;             // Clear P1.0 (LED1) to start
    PM5CTL0 &= ~LOCKLPM5;       // Turn on GPIO

    //-- Setup Timer
    TB0CTL |= TBCLR;            // Clear timer and dividers
    TB0CTL |= TBSSEL__ACLK;    // Source = ACLK
    TB0CTL |= MC__UP;           // Mode = UP
    TB0CCR0 = 16384;            // CCR0 = 16384

    //-- Setup Timer Overflow IRQ
    TB0CCTL0 &= ~CCIFG;         // Clear CCR0 flag
    TB0CCTL0 |= CCIE;           // Enable TB0 CCR0 Overflow IRQ
    __enable_interrupt();       // Enable maskable IRQs

    //-- Main Loop
    while (1)
    {
    }

    return 0;
}

//-- Interrupt Service Routines
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P1OUT ^= BIT0;          // toggle LED1
    TB0CCTL0 &= ~CCIFG;     // Clear CCR0 flag
}

