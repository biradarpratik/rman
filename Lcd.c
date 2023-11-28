 // LPC2148 port and pin numbers
#define RS_PIN (1 << 4)
#define EN_PIN (1 << 5)

void LCD_Init(void) {
  // Set the RS and EN pins as outputs


  GPIO_SetDir(0, RS_PIN | EN_PIN, GPIO_DIR_OUT);

  // Delay for 100ms

  delay_ms(100);

  // Reset the LCD 
  LCD_SendHigherNibble(0x30);
  LCD_SendCmdSignals();
  delay_ms(100);
  LCD_SendHigherNibble(0x30);
  LCD_SendCmdSignals();
  delay_us(200);
  LCD_SendHigherNibble(0x30);
  LCD_SendCmdSignals();
  delay_us(200);
  LCD_SendHigherNibble(0x20);
  LCD_SendCmdSignals();
  delay_us(200);

  // Initialize the LCD for 4-bit 5x7 matrix type
  LCD_CmdWrite(0x28u);

  // Display ON cursor ON
  LCD_CmdWrite(0x0Eu);

  // Clear the LCD
  LCD_CmdWrite(0x01u);

  // Go to First line First Position
  LCD_CmdWrite(0x80u);
}

void LCD_SendHigherNibble(unsigned char dataByte) {
  // Set the RS pin to low
  GPIO_ClearValue(0, RS_PIN);

  // Set the upper nibble of the data byte on the port pins
  GPIO_SetValue(0, (dataByte >> 4) & 0x0F);

  // Set the EN pin high
  GPIO_SetValue(0, EN_PIN);
  delay_us(100);
  GPIO_ClearValue(0, EN_PIN);
}

void LCD_SendCmdSignals(void) {
  // Set the RS pin to low
  GPIO_ClearValue(0, RS_PIN);

  // Set the EN pin high
  GPIO_SetValue(0, EN_PIN);
  delay_us(100);
  GPIO_ClearValue(0, EN_PIN);
}

void LCD_SendDataSignals(void) {
  // Set the RS pin to high
  GPIO_SetValue(0, RS_PIN);

  // Set the EN pin high
  GPIO_SetValue(0, EN_PIN);
  delay_us(100);
  GPIO_ClearValue(0, EN_PIN);
}
