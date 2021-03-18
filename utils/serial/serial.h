/**********************************************
 	serial.h: Header file for serial ports usage
***********************************************/

// function declarations
void uart_init(void);
void transmit_char(unsigned char ch);
void transmit_string(unsigned char *s);
unsigned char receive_char(void);
void serial_ISR(void);
