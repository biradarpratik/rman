#include<LPC21xx.h>

void delay_ms1()
{
T1PR = 15000-1;
T1MR3 = 1;
T1TC = 0x00;
T1TCR = 0x01 ; // Start Timer
while (T1TC != T1MR3) ;
T1TCR = 0x02 ; // Stop Timer
}

void delay_ms2()
{
T1PR = 15000-1;
T1MR3 = 200;
T1TC = 0x00;
T1TCR = 0x01 ; // Start Timer
while (T1TC != T1MR3) ;
T1TCR = 0x02 ; // Stop Timer
}

void delay_ms3()
{
T1PR = 15000-1;
T1MR3 = 5;
T1TC = 0x00;
T1TCR = 0x01 ; // Start Timer
while (T1TC != T1MR3) ;
T1TCR = 0x02 ; // Stop Timer
}
void delay_ms4()
{
T1PR = 15000-1;
T1MR3 = 2000;
T1TC = 0x00;
T1TCR = 0x01 ; // Start Timer
while (T1TC != T1MR3) ;
T1TCR = 0x02 ; // Stop Timer
}
//DELAY FUNCTION ENDS
unsigned int mat[3][3] = {{'1','2','3'}, {'4','5','6'},{'7','8','9'},{'0'}};
	
char detect_char(unsigned int r, unsigned int c)
{
	int j;
	switch(c){
		case 1:
			j = 0;	break;
		case 2:
			j = 1;	break;
		case 4:
			j = 2;	break;
		case 8:
			j = 3;	break;
		default:
			return 0;
	}
	return mat[j][r];
}
//CHARACTER DETECTION FUCNTION ENDS
void callen()
{
	IOSET1 = (1 << 24);//SETS ENABLE TO HIGH
	delay_ms1();
	IOCLR1 = (1 << 24);//CLEARS ENABLE PIN TO SEND ENABLE INSTRUCTION TO LCD
}
//LCD ENABLE ENDS
void lcd_cmd(unsigned int cmdcode)
{
	IOCLR1 = (1 << 25); //SET RS = 0; CMD MODE
	IOCLR1 = (255 << 16);//CLEAR 8 BIT DATA PINS
	IOSET1 = (cmdcode << 16);//SET 8 BIT DATA MINS ACCORDING TO COMMAND CODE
	callen();//CALL ENABLE TO SEND 8 BIT DATA
}
//LCD COMMAND SEND ENDS
void lcd_data(unsigned int datacode)
{
	IOSET1 = (1 << 25); //SET RS = 1; DATA MODE
	IOCLR1 = (255 << 16);// CLEAR ALL 8 DATA PINS
	IOSET1 = (datacode << 16);//SET ALL 8 DATA PINS
	callen();// CALL ENABLE TO SEND 8 BIT DATA
	delay_ms2();//DELAY FOR DATA DISPLAY
}
//LCD DATA SEND ENDS
void lcd_init()
{
	lcd_cmd(0x38);	// 2 LINES AND 8 BUTS
	lcd_cmd(0x01);	// CLEAR DISPLAY	
	lcd_cmd(0x06);	// LEFT ENTRY ON LCD
	lcd_cmd(0x0E);	// DISPLAY ON, CURSOR ON
	//lcd_cmd(0x0D);	// DISPLAY ON, CURSOR OFF
	lcd_cmd(0x80);	// MOVE TO 1ST LINE, 1ST CHARACATER
	// lcd_cmd(18); // rotate left
	// lcd_cmd(1C); // rotate right
}
//LCD INITIALISATION ENDS
int main(void){
	int i=0, readr, res;
	PINSEL0 = 0;
	PINSEL2 = 0;
	IODIR1 = 0x0FFF0000;	// first F is 3 for LCD
	IODIR0 = 0x0000000F;	//SET 1ST 4 PINS: 0-3 AS OUTPUT
	lcd_init();//INITIALISE THE LCD
	while(1){
		for(i=0;i<3;i++){
		//lcd_data(i+65);
		IOCLR0 = 15;//CLEAR THE FIRST 4 PINS
		IOSET0 = 1 << i;//SET EACH PIN INDIVIDUALLY AND LEFT SHIFT TO ALTERNATE BETWEEN PINS
		delay_ms3();
		readr = (IOPIN0 >> 4);//READ THE ROWS TO CHECK FOR KEYPRESS DETECTION
		delay_ms3();
		if(readr!=0)//IF KEYPRESS HAS OCCURED,
		{
			res = detect_char(i, readr);//DETECT CHARACTER IN MATRIX DECLARED EARLIER
			if(res!=0)//IF CHARACTER DETECTED IS NON-ZERO
			{
				lcd_data(res);//SEND NON-ZERO CHARACTER TO LCD
				delay_ms4();
			}
		}
	}
}
}
//MAIN ENDS
