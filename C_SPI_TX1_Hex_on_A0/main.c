#include <msp430.h>

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    //-- 1. Put eUSCI_A0 into SW reset
    UCA0CTLW0 |= UCSWRST;

    //-- 2. Configure eUSCI_A0
    UCA0CTLW0 |= UCSSEL__SMCLK;
    UCA0BRW = 10;

    UCA0CTLW0 |= UCSYNC;
    UCA0CTLW0 |= UCMST;

    //-- 3. Configure Ports
    P1SEL1 &= ~BIT5;
    P1SEL0 |= BIT5;

    P1SEL1 &= ~BIT7;
    P1SEL0 |= BIT7;

    P1SEL1 &= ~BIT6;
    P1SEL0 |= BIT6;

    PM5CTL0 &= ~LOCKLPM5;

    //-- 4. Take eUSCI_A0 out of software reset
    UCA0CTLW0 &= ~UCSWRST;

    int i;

    while (1)
    {
        UCA0TXBUF = 0x4D;
        for (i = 0; i < 10000; i++)
        {
        }
    }

    return 0;
}
