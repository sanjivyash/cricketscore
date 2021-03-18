#include "at89c5131.h"
#include "serial.h"

// global variables
bit tx_complete = 0;
bit rx_complete = 0;

void uart_init(void) {
/**********************************************
  DESC: initial configuration of serial ports
***********************************************/	
	TMOD = 0x20;
	TH1 = 0xCC;       // baud rate = 1200
	SCON = 0x53;
	TR1 = 1;
	ES = 1;
	EA = 1;
}
	
void transmit_char(unsigned char ch) {
/************************************************
	DESC: transmit a character to the serial port
	ARGS:
		ch: character to be transmitted
************************************************/
	SBUF=ch;
	while(!tx_complete);
	tx_complete = 0;
}
	
void transmit_string(unsigned char *s) {
/***************************************************
	DESC: transmit a string to the serial port
	ARGS:
		s: reference to the start of the string array
***************************************************/
	while(*s != 0)
		transmit_char(*s++);
}
	
unsigned char receive_char(void) {
/*******************************************************
	DESC: receive a character transmitted by serial port
	RETURN:
		ch: character received from the serial port
*******************************************************/	
	unsigned char ch = 0;
	while(!rx_complete);				//Wait for rx_complete(interrupt to complete)
	rx_complete = 0;
	ch = SBUF;					//Read data from SBUF
	return ch;					//Return read character
}

void serial_ISR(void) interrupt 4 {
/**********************************************************
   Serial_ISR(): 
	Interrupt service routine for UART interrupt.
	Determines whether it is a transmit or receive
	interrupt and raise corresponding flag.
	Transmit or receive functions (defined above) monitor
	for these flags to check if data transfer is done.
***********************************************************/	
	if(TI == 1) {
		TI = 0;
		tx_complete = 1;
	} 
	else if(RI == 1) {
		RI = 0;
		rx_complete = 1;
	}
}
