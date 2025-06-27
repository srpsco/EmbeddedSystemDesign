#include <msp430.h>

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    int e = 0b1111111111110000;
    int f = 0x0001;

    while (1)
    {
        e = ~e;
        e = e | BIT7;
        e = e & ~BIT0;
        e = e ^ BIT4;

        e |= BIT6;
        e &= ~BIT1;
        e ^= BIT3;

        f = f << 1;
        f = f << 2;
        f = f >> 1;
    }

    return 0;
}
