#ifndef SPI0_H
#define SPI0_H
// MOSI = PIN A4 , output
// MISO = PIN A5, input
// SCK = PIN A6, output
// SS_not = PIN A7, output


// PROTOTYPES
void spi_init(); // remember to config SS pin as output first
uint8_t spi_transmitByte(uint8_t Byte); // master sends and gets almost the same time, sometimes transceive())
uint8_t spi_serial_transfer_is_done();

void SS_set();
void SS_cleared();

void spi_enable();
void spi_disable();

#endif
