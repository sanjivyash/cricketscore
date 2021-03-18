#include "stdio.h"
#include "string.h" 
#include "at89c5131.h"
#include "defs.h"
#include "utils/lcd/lcd.h"
#include "utils/serial/serial.h"

unsigned int runs, wickets, overs, balls;
unsigned char status[17];
bit new_over = 0;

void main(void) {
	unsigned char score[16];
	unsigned char ch;
	
	lcd_init();
	uart_init();
	init();
	
	// throw away erroneous first character
	receive_char();
	
	while(1) {
		sprintf(score, "%d/%d (%d.%d)", runs, wickets, overs, balls);
		
		lcd_cmd(0x80);
		lcd_string(score);
		lcd_cmd(0x0C0);
		lcd_string(status);
		
		if(overs == 20 || wickets == 10){
			reset();
			continue;
		}
		
		ch = receive_char();
		
		switch(ch) {
			case '6': runs ++;
			case '5': runs ++;
			case '4': runs ++;
			case '3': runs ++;
			case '2': runs ++;
			case '1': runs ++;
			case '.': balls ++;
								break;
			
			case 'e': 
			case 'n': runs ++;
								ch -= 32;
								break;
			
			case 'w': wickets ++;
								balls ++;
								ch -= 32;
								break;
			
			default: transmit_char(ch);
							 transmit_string(" - Invalid character sent\r\n");
							 continue;
		}
		
		update(ch);
	}
}

void init() {
/*******************************************************
  DESC: initialization of global variables and messages
*******************************************************/
	// initial messages
	transmit_string("*******************************\r\n");
	transmit_string("********Cricketscore***********\r\n");
	transmit_string("*******************************\r\n");
	transmit_string("Press a character to start game\r\n");
	
	// global vars
	runs = 0;
	wickets = 0, overs = 0, balls = 0;
	status[0] = 0;
}

void update(unsigned char ch) {
/***********************************************************
  DESC: updation of global variables after a ball is bowled
	ARGS:
		ch: character received from keyboard
***********************************************************/
	if(new_over == 1) {
		status[0] = 0;
		lcd_cmd(0x01);
		msdelay(100);
		new_over = 0;
	}
	
	if(balls == 6) {
		balls = 0;
		overs ++;
		new_over = 1;
	}
	
	strncat(status, &ch, 1);
}

void reset() {
/*************************************************
  DESC: denote end of innings and reset variables
*************************************************/
	lcd_cmd(0x0C0);
	lcd_string("Innings Ends");
	msdelay(5000);
	lcd_cmd(0x01);
	msdelay(100);
	init();
}