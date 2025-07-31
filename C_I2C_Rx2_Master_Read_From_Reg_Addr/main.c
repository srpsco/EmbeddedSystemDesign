#include <msp430.h>

int Data_In = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //-- 1. Put eUSCI_B0 into software reset
    UCB0CTLW0 |= UCSWRST;

    //-- 2. Configure eUSCI_B0
    UCB0CTLW0 |= UCSSEL__SMCLK;
    UCB0BRW = 10;

    UCB0CTLW0 |= UCMODE_3;
    UCB0CTLW0 |= UCMST;
    UCB0I2CSA = 0x0068;

    UCB0TBCNT = 0x01;
    UCB0CTLW1 |= UCASTP_2;

    //-- 3. Configure Ports
    P1SEL1 &= ~BIT3;
    P1SEL0 |= BIT3;

    P1SEL1 &= ~BIT2;
    P1SEL0 |= BIT2;

    PM5CTL0 &= ~LOCKLPM5;

    //-- 4. Take eUSCI_B0 out of SW reset
    UCB0CTLW0 &= ~UCSWRST;

    //-- 5. Enable Interrupts
    UCB0IE |= UCTXIE0;
    UCB0IE |= UCRXIE0;
    __enable_interrupt();

    while (1)
    {
        UCB0CTLW0 |= UCTR;
        UCB0CTLW0 |= UCTXSTT;

        while ((UCB0IFG & UCSTPIFG) == 0)
        {
        }
        UCB0IFG &= ~UCSTPIFG;

        UCB0CTLW0 &= ~UCTR;
        UCB0CTLW0 |= UCTXSTT;

        while ((UCB0IFG & UCSTPIFG) == 0)
        {
        }
        UCB0IFG &= ~UCSTPIFG;
    }
    return 0;
}

//-- Interrupt service routines
#pragma vector=EUSCI_B0_VECTOR
__interrupt void EUSCI_B0_I2C_ISR(void)
{
    switch (UCB0IV)
    {
    case 0x16:
        Data_In = UCB0RXBUF;
        break;
    case 0x18:
        UCB0TXBUF = 0x03;
        break;

    default:
        break;

    }
}

