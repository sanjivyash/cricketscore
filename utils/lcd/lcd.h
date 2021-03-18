/*************************************************
 	lcd.h: Header file for 16x2 LCD interfacing  
**************************************************/

// function declarations
void msdelay(unsigned int time);																	
void lcd_init(void);																				
void lcd_cmd(unsigned int i);																
void lcd_char(unsigned char ch);														
void lcd_string(unsigned char *s);
