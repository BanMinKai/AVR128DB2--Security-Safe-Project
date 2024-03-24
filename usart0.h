#ifndef USART0_H
#define USART0_H

#define BAUD_RATE 9600
#define USART0_BAUD_RATE(BAUD_RATE) (((float)4000000 * 64 / (16 * (float)BAUD_RATE)))
// that formular to calculate the Baudrate :> 
// from the datasheets

// PROTOTYPES
void usart_init(); // somehow shouldnt use argument uint32_t baudrate here
void usart_transmitByte(uint8_t Byte);
uint8_t usart_receiveByte(uint8_t Byte);
void usart_printf(uint8_t *string); // use \r\n to enter 
int usart_ready_to_transmit(); // return true false
int usart_Rxisready();

#endif