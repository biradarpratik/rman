 #include <lpc214x.h>  // Header file for LPC214x Series microcontrollers

void delay(int); // Function declaration for delay
int i; // Variable declared as integer

unsigned int temp[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // Integer array with numbers for display

void delay(int k) // Function for making delay
{
  int i, j;
  for (i = 0; i < k; i++)
    for (j = 0; j <= 500; j++);
}

int main()
{
  IO0DIR |= 0xffffffff;
  while (1)
  {
    for (i = 0; i <= 9; i++)
    {
      IO0SET |= temp[i]; // Sets corresponding pins HIGH
      delay(7000); // Calls delay function
      IO0CLR |= temp[i]; // Sets corresponding pins LOW
      delay(500);
    }
  }
  return 0;
}
