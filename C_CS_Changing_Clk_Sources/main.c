#include <msp430.h>

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P3DIR |= BIT0;
    P3SEL1 &= ~BIT0;
    P3SEL0 |= BIT0;

    P3DIR |= BIT4;
    P3SEL1 &= ~BIT4;
    P3SEL0 |= BIT4;

    P1DIR |= BIT1;
    P1SEL1 |= BIT1;
    P1SEL0 &= ~BIT1;

    CSCTL4 |= SELMS__REFOCLK;

    CSCTL5 |= DIVS__2;

    CSCTL4 &= ~SELA__REFOCLK;
    CSCTL4 |= SELA__VLOCLK;

    while (1)
    {
    }

    return 0;
}
