#include <msp430.h>

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //-- Setup Ports
    P1DIR |= BIT0;              // Config P1.0 (LED1) as utput
    P1OUT &= ~BIT0;             // Clear P1.0 (LED1) to start
    PM5CTL0 &= ~LOCKLPM5;       // Turn on GPIO

    //-- Setup Timer
    TB0CTL |= TBCLR;            // Clear timer and dividers
    TB0CTL |= TBSSEL__ACLK;     // Source = ACLK
    TB0CTL |= MC__CONTINUOUS;   // Mode = conyinuus
    TB0CTL |= CNTL_1;           // Length = 12-bit

    //-- Setup Timer Overflow IRQ
    TB0CTL &= ~TBIFG;           // Clear TB0 flag
    TB0CTL |= TBIE;             // Enable TB0 overflow IRQ
    __enable_interrupt();       // Enable maskable IRQs

    //-- Main Loop
    while (1)
    {
    }

    return 0;
}

//-- Interrupt Service Routines
#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_Overflow(void)
{
    P1OUT ^= BIT0;          // toggle LED1
    TB0CTL &= ~TBIFG;
}

