/*
 * uart.h
 *
 *  Created on: Sep 1, 2019
 *      Author: jhfpi
 */

#ifndef UART_H_
#define UART_H_

extern void configureUart(void);
extern void printString (char *s);
extern void printChar(char c);
extern char readChar (void);

#endif /* UART_H_ */
