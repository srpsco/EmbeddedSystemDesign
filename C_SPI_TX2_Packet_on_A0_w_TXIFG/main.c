#include <msp430.h>

char packet[] = { 0XF0, 0XF0, 0XF0, 0X40 };
unsigned int position;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    //-- 1. Put eUSCI_AO into software reset
    UCA0CTLW0 |= UCSWRST;

    //-- 2. Configure eUSCI_A0
    UCA0CTLW0 |= UCSSEL__SMCLK;
    UCA0BRW = 10;

    UCA0CTLW0 |= UCSYNC;
    UCA0CTLW0 |= UCMST;

    //-- 3. Configure ports
    P4DIR &= ~BIT1;
    P4REN |= BIT1;
    P4OUT |= BIT1;
    P4IES |= BIT1;

    P1SEL1 &= ~BIT5;
    P1SEL0 |= BIT5;

    P1SEL1 &= ~BIT7;
    P1SEL0 |= BIT7;

    P1SEL1 &= ~BIT6;
    P1SEL0 |= BIT6;

    PM5CTL0 &= ~LOCKLPM5;

    //-- 4. Take eUSCI_A0 out of SW reset
    UCA0CTLW0 &= ~UCSWRST;

    //-- 5. Enable IRQs
    P4IFG &= ~BIT1;
    P4IE |= BIT1;

    UCA0IFG &= ~UCTXIFG;
    UCA0IE |= UCTXIE;
    __enable_interrupt();

    while (1)
    {
    }

    return 0;
}

//-- Interrupt service routines
#pragma vector = PORT4_VECTOR
__interrupt void ISR_Port4_S1(void)
{
    position = 0;
    UCA0TXBUF = packet[position];
    P4IFG &= ~BIT1;
}

#pragma vector = EUSCI_A0_VECTOR
__interrupt void ISR_EUSCI_A0(void)
{
    position++;

    if (position < sizeof(packet))
    {
        UCA0TXBUF = packet[position];
    }
    else
    {
        UCA0IFG &= ~UCTXIFG;
    }
}

