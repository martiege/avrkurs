/*
 * spi.h
 *
 * Created: 23.02.2017 00:25:51
 *  Author: Petter
 */ 


#ifndef SPI_H_
#define SPI_H_


// Function for initializing SPI
void spi_init(void);

// Function for transmitting SPI data
void spi_transmit(char cData);


#endif /* SPI_H_ */
