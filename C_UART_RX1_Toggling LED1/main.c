#include <msp430.h>

char message[] = "Hello World ";
unsigned int position;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //-- 1. Put eUSCI_A1 into software reset
    UCA1CTLW0 |= UCSWRST;

    //-- 2. Configure eUSCI_A1
    UCA1CTLW0 |= UCSSEL__SMCLK;
    UCA1BRW = 8;
    UCA1MCTLW |= 0xD600;

    //-- 3. Configure Ports

    P4SEL1 &= ~BIT2;
    P4SEL0 |= BIT2;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    PM5CTL0 &= ~LOCKLPM5;

    //-- 4. Take eUSCI_A1 out of SW reset
    UCA1CTLW0 &= ~UCSWRST;

    //-- 5. Enable IRQs
    UCA1IE |= UCRXIE;
    __enable_interrupt();

    while (1)
    {
    }
    return 0;
}

//-- Interrupt service routines
#pragma vector = EUSCI_A1_VECTOR
__interrupt void EUSCI_A1_RX_ISR(void)
{
    if (UCA1RXBUF == 't')
    {
        P1OUT ^= BIT0;
    }
}

