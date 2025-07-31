#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    //-- 1. Put eUSCI_B0 into software reset
    UCB0CTLW0 |= UCSWRST;

    //-- 2. Configure eUSCI_B0
    UCB0CTLW0 |= UCSSEL__SMCLK;
    UCB0BRW = 10;

    UCB0CTLW0 |= UCMODE_3;
    UCB0CTLW0 |= UCMST;
    UCB0CTLW0 |= UCTR;
    UCB0I2CSA = 0x0068;

    UCB0CTLW1 |= UCASTP_2;
    UCB0TBCNT = 0x01;

    //-- 3. Configure ports
    P1SEL1 &= ~BIT3;
    P1SEL0 |= BIT3;

    P1SEL1 &= ~BIT2;
    P1SEL0 |= BIT2;

    PM5CTL0 &= ~LOCKLPM5;

    //-- 4. Take eUSCI_B0 out of SW reset
    UCB0CTLW0 &= ~UCSWRST;

    //-- 5. Enable Interrupts
    UCB0IE |= UCTXIE0;
    __enable_interrupt();

    int i;
    while (1)
    {
        UCB0CTLW0 |= UCTXSTT;
        for (i = 0; i < 100; i++)
        {
        }
    }

    return 0;
}

#pragma vector=EUSCI_B0_VECTOR
__interrupt void EUSCI_B0_I2C_ISR(void)
{
    UCB0TXBUF = 0xBB;
}
