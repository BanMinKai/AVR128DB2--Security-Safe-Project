/*
 * we use SPI0 on AVR128db28
 * master, mode 1
 */

#include <avr/io.h>
#include <stdint.h>
#include "spi0.h"

// MOSI = PIN A4 , output
// MISO = PIN A5, input
// SCK = PIN A6, output
// SS_not = PIN A7, output

// DEFINITIONS
void spi_init()
{
    // remember that you need to config direction of SS pin as OUTPUT and HIGH first
    // also config MOSI as output as well
   // set PIN4, 6, 7 as outputs
   // set PIN 7 initially high, so SS = low
    
   
    SPI0.CTRLA = 0x21; // MSB first, Master, CLK2X disabled, SPI clock = CPU clock /4, SPI_ENABLED!!!
}

uint8_t spi_transmitByte(uint8_t Byte)
{
    SPI0.DATA = Byte; // load Byte into DATA register, then start sending
    while (!spi_serial_transfer_is_done()); // check if already sent
    return SPI0.DATA;
}

uint8_t spi_serial_transfer_is_done()
{
    return (SPI0.INTFLAGS & SPI_IF_bm);
}

void SS_set()
{
    PORTA.OUT &= ~(1 << PIN7);
}
void SS_cleared()
{
    PORTA.OUT |= (1 << PIN7);
}

// somehow I saw people always disable SPI when not in use
void spi_enable()
{
    SPI0.CTRLA |= 0x1;
}

void spi_disable()
{
    SPI0.CTRLA &= ~0x1;
}