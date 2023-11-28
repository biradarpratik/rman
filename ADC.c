#include<LPC213x.h>
void delay_ms(unsigned int x)
{
int i=0,j=0,k=0;
for(;k<x;k++){
for(;i<4000;i++){
for(;j<3000;j++)
{} // Just passing time
}
}
}
void callen(){  // enable lcd pin 24 for sending instructions to lcd
IOSET1 = (1 <<24);
delay_ms(1);
IOCLR1 = (1 <<24);
}
void lcd_cmd(unsigned int cmdcode){
IOCLR1 = (1 << 25); //clear RS=0 so cmd sends   
IOCLR1 = (255 <<16); // 111111110000000000000000
IOSET1 = (cmdcode <<16); // cmdcode left shift by 16 bits 
callen();  // function calls
}
void lcd_data(unsigned int datacode){
IOSET1 = (1 << 25); //set RS=1
IOCLR1 = (255 <<16);
IOSET1 = (datacode << 16);
callen();
delay_ms(200);
}
void lcd_init(){
lcd_cmd(0x38); // 2 line 8 bit mode
lcd_cmd(0x01); // display clear
lcd_cmd(0x06); // left entry
// lcd_cmd(0x0E); // display on, cursor on
lcd_cmd(0x0D); // display on, cursor off
lcd_cmd(0x80); // 1st line 1st char
// lcd_cmd(18); // rotate left
// lcd_cmd(1C); // rotate right
}

void lcd_datawr(char *str){
int i=0;
while(i<16){
if(str[i]!=0){  // passing index for accessing letter
lcd_data((unsigned int)str[i]);
i++;
}
else
return;

}
}

unsigned int ADC_read(){
unsigned int rdr = 0;
AD0CR &= ~(1<<24); // Start ADC clear pin 24, 24th pin is 0
AD0CR |= (1 <<24); // Set one to pin 24, ADC is operational,  24th pin is 1
while(!(AD0DR>> 31)); //while ( !(AD0DR1 &amp; 0x80000000) ); /* Wait till DONE */
rdr = (AD0DR & 0x0000FFC0); // 10 bits at positions 15....6 are made 1 and then AND for masking,    corresponding bits are 1 then 1 else 0
rdr = rdr >>6; // right shift the ADC result by 6 positions
return rdr;
}

int main(void){
PINSEL1 = 0x01000000; // for ADC0.1 = P0.28
AD0DR = 0; // for setting up ADC – data register is made zero
AD0CR = 0x00200402; // for setting up ADC control register
PINSEL2 = 0; // for setting up the LCD as GPIO
IODIR1 = 0x0FFF0000; // first F is 3 for LCD – setting the direction as output for Port 1
lcd_init();
char datstr[5];
while(1){
unsigned int res, i=1;
res = ADC_read();
int q = res, r;
while(q>0){
r = q % 10;
q = q / 10;
datstr[i] = (char)r;

i++;

}
lcd_data(datstr[i]);
}
}

