#include <LPC213x.h>
// Check LCD ARM commands
void UART0_init(void)
{
PINSEL0 = PINSEL0 | 0x00000005; /* Enable UART0 Rx0 and Tx0 pins of UART0 */
U0LCR = 0x83; /* DLAB = 1, 1 stop bit, 8-bit character length */
U0DLM = 0x00; /* For baud rate of 9600 with Pclk = 15MHz */
U0DLL = 0x61; /* We get these values of U0DLL and U0DLM from formula */
U0LCR = 0x03; /* DLAB = 0 */
}
unsigned char UART0_RxChar(void) /*A function to receive a byte on UART0 */
{
while( (U0LSR & 0x01) == 0); /*Wait till RDR bit becomes 1 which tells that receiver 
contains valid data */
return U0RBR;
}
void UART0_TxChar(char ch) /*A function to send a byte on UART0 */
{
U0THR = ch;
while( (U0LSR & 0x40) == 0 ); /* Wait till THRE bit becomes 1 which tells that 
transmission is completed */
}
void delay_ms(unsigned int x){
int i=0,j=0,k=0;
for(;k<x;k++){
for(;i<4000;i++){
for(;j<3000;j++)
{} //
}
}
}
void uart_senddata(char *str)
{
int i=0;
while(str[i]!='\0')
{
UART0_TxChar(str[i]);
i++;
}
}
void callen(){
IOSET1 = (1 << 24);
delay_ms(1);
IOCLR1 = (1 << 24);
}
void lcd_cmd(unsigned int cmdcode){
IOCLR1 = (1 << 25); //clear RS
IOCLR1 = (255 << 16);
IOSET1 = (cmdcode << 16);
callen();
}
void lcd_data(unsigned int datacode){
IOSET1 = (1 << 25); //set RS
IOCLR1 = (255 << 16);
IOSET1 = (datacode << 16);
callen();
delay_ms(200);
}
void lcd_init(){
lcd_cmd(0x38); // 2 line 8 bit mode
lcd_cmd(0x01); // display clear
lcd_cmd(0x06); // left entry
lcd_cmd(0x0E); // display on, cursor on
lcd_cmd(0x0D); // display on, cursor off
lcd_cmd(0x80); // 1st line 1st char
// lcd_cmd(18); // rotate left
// lcd_cmd(1C); // rotate right
}
void lcd_datawr(char *str){
int i=0;
while(i<16){
if(str[i]!=0){
lcd_data((unsigned int)str[i]);
i++;
}
else
return;
}
}
unsigned char receive ;
int main(void){
PINSEL2 = 0;
IODIR1 = 0x0FFF0000;// first F is 3 for LCD
lcd_init();
UART0_init();
char namest[]= "Hello ", rollst[]= "Gaikwad Here !";
while(1)
{
lcd_datawr(namest);
// delay_ms(200);
uart_senddata(namest);
// delay_ms(200);
lcd_cmd(0xC0);
receive='0';
while(receive!='1')
{
receive=UART0_RxChar();
}
lcd_datawr(rollst);
// delay_ms(200);
uart_senddata(rollst);
delay_ms(5000);
lcd_cmd(0x01);
}
}