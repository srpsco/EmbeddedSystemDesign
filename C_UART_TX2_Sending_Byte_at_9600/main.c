#include <msp430.h>

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //-- 1. Put eUSCI_A1 into SW reset
    UCA1CTLW0 |= UCSWRST;

    //-- 2. Configure eUSCI_A1
    UCA1CTLW0 |= UCSSEL__ACLK;

    UCA1BRW = 3;
    UCA1MCTLW |= 0x9200;

    //-- 3. Configure Ports
    P4SEL1 &= ~BIT3;
    P4SEL0 |= BIT3;

    PM5CTL0 &= ~LOCKLPM5;

    //-- 4. Take eUSCI_A1 out of software reset
    UCA1CTLW0 &= ~UCSWRST;

    int i;

    while (1)
    {
        UCA1TXBUF = 0x55;
        for (i = 0; i < 10000; i = i + 1)
        {
        }
    }

    return 0;
}
