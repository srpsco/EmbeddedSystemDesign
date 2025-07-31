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
    UCA1CTLW0 |= UCSSEL__SMCLK;

    UCA1BRW = 8;
    UCA1MCTLW |= 0xD600;

    //-- 3. Configure Ports
    P4SEL1 &= ~BIT3;
    P4SEL0 |= BIT3;

    PM5CTL0 &= ~LOCKLPM5;

    //-- 4. Take eUSCI_A1 out of software reset
    UCA1CTLW0 &= ~UCSWRST;

    char message[] = "Hello world ";
    int position;
    int i, j;

    while (1)
    {
        for (position = 0; position < sizeof(message); position++)
        {
            UCA1TXBUF = message[position];
            for (i = 0; i < 100; i++) // delay between chars
            {

            }
        }

        for (j = 0; j < 30000; j++) // delay between strings
        {
        }

    }

    return 0;
}
