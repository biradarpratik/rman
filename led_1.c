//Led_Blinking//
#include <LPC214X.h>

void delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
    {
        for (j = 0; j < 7500; j++)
        {
            // Do nothing, just waste time
        }
    }
}

int main()
{
    PINSEL0 = 0x00000000;  // Set all pins of PORT0 as GPIO
    IODIR0 = 0xFF;        // Set PORT0 pins as output

    while (1)
    {
        IOSET0 = 0xFF;    // Set all pins of PORT0 high
        delay(100);      // Delay for 100 iterations
        IOCLR0 = 0xFF;    // Clear all pins of PORT0 low
        delay(100);      // Delay for 100 iterations
    }

    return 0;
}