/*
 we use USART0 on AVR128DB28
 baurate = 9600
 async mode, 8bit data
 otherwise LOW
 */
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include "usart0.h"

// DEFINITIONS

void usart_init() 
{
    USART0.BAUD = (uint16_t) USART0_BAUD_RATE(BAUD_RATE); // baud rate = 9600 bps
    USART0.CTRLC = 0x03; // Async + 8Bit
    USART0.CTRLB = 0xC0; // Tx Enabled + Rx Enabled
    USART0.CTRLA = 0x00; // all interrupts disabled
}

void usart_transmitByte(uint8_t Byte)
{
    while (!usart_ready_to_transmit()); // very important to have, check transmit buffer if empty
    USART0.TXDATAL = Byte;
}

uint8_t usart_receiveByte(uint8_t Byte)
{
    while (!usart_received()) // very important to have, check receive buffer if full
    return USART0.RXDATAL;
}
void usart_printf(uint8_t *string)
{
    while (*string != '\0')
    {
        usart_transmitByte(*string);
        string++;
    }
}

int usart_received()
{
    return USART0.STATUS & USART_RXCIF_bm;
}

int usart_ready_to_transmit()
{
    return USART0.STATUS & USART_DREIF_bm;
}