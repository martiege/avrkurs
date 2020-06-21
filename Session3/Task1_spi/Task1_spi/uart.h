/*
 * uart.h
 *
 * Created: 10.03.2020 18:20:40
 *  Author: Martin
 */ 


#ifndef UART_H_
#define UART_H_


// Function for initializing UART
void uart_init(void);

// Function for transmitting UART data
void uart_transmit(char cData);

// Function for printing string with UART
void uart_print(char* data);

#endif /* UART_H_ */
