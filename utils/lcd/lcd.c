#include "at89c5131.h"
#include "lcd.h"

// global variables
sbit RS=P0^0;
sbit RW=P0^1;
sbit EN=P0^2;

void msdelay(unsigned int time) {
/******************************************
	DESC: simulate delays using software
	ARGS:
		time: number of milliseconds of delay
******************************************/
	unsigned int i, j;
	
	for(i=0; i<time; i++)
		for(j=0; j<355; j++);
}

void lcd_init(void) {
/****************************************
	DESC: initial configuration of the lcd
****************************************/
	P2=0x00;
	EN=0;
	RS=0;
	RW=0;
	
	lcd_cmd(0x38);
	msdelay(4);
	lcd_cmd(0x06);
	msdelay(4);
	lcd_cmd(0x0C);
	msdelay(4);
	lcd_cmd(0x01);
	msdelay(4);
	lcd_cmd(0x80);
}

void lcd_cmd(unsigned int i) {
/*******************************
	DESC: command mode of LCD
	ARGS:
		i: command code to execute
*******************************/
	RS=0;
	RW=0;
	EN=1;
	P2=i;
	msdelay(10);
	EN=0;
}

void lcd_char(unsigned char ch) {
/**********************************
	DESC: character mode of LCD
	ARGS:
		ch: character to be displayed 
**********************************/
	RS = 1;
	RW = 0;
	EN = 1;
	P2 = ch;
	msdelay(10);
	EN = 0;
}

void lcd_string(unsigned char *s) {
/**************************************************
	DESC: display strings on LCD
	ARGS:
		s: reference to the start of the string array
**************************************************/
	while(*s != 0)
		lcd_char(*s++);
}
