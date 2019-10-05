/*
 * uart.h
 *
 *  Created on: Sep 1, 2019
 *      Author: jhfpi
 */

#ifndef UART_H_
#define UART_H_

extern void configureUart(uint32_t uart2Enable, uint32_t port);
extern void printChar(char c);
extern void printString (char *s);
extern char readChar (void);

#endif /* UART_H_ */
