#include <msp430.h>

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P3DIR |= BIT0;
    P3SEL1 &= ~BIT0;
    P3SEL0 |= BIT0;

    CSCTL1 |= DCORSEL_3;

    CSCTL2 &= ~FLLD_1;

    CSCTL2 &= ~FLLN;
    CSCTL2 |= 244;

    while (1)
    {
    }

    return 0;
}
