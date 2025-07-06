#include <msp430.h>

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //-- Setup Ports
    P1DIR |= BIT0;              // Config P1.0 (LED1) as output
    P1OUT |= BIT0;        // LED1 = 1 to start for PWMClear P1.0 (LED1) to start
    PM5CTL0 &= ~LOCKLPM5;       // Turn on GPIO

    //-- Setup Timer B0
    TB0CTL |= TBCLR;            // Clear timer and dividers
    TB0CTL |= TBSSEL__ACLK;     // Source = ACLK
    TB0CTL |= MC__UP;           // Mode = UP
    TB0CCR0 = 32768;            // CCR0 = 32768
    TB0CCR1 = 16384;             // CCR1 = 1638

    //-- Setup Timer Compare IRQ for CCR0 and CCR1
    TB0CCTL0 &= ~CCIFG;         // Clear CCR0 flag
    TB0CCTL0 |= CCIE;           // Enable TB0 CCR0 Overflow IRQ
    TB0CCTL1 &= ~CCIFG;         // Clear CCR1 flag
    TB0CCTL1 |= CCIE;           // Enable TB0 CCR1 Overflow IRQ
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
    P1OUT |= BIT0;              // LED1 = 1
    TB0CCTL0 &= ~CCIFG;         // Clear CCR0 flag
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_CCR1(void)
{
    P1OUT &= ~BIT0;             // LED1 = 0
    TB0CCTL1 &= ~CCIFG;         // Clear CCR1 flag
}
