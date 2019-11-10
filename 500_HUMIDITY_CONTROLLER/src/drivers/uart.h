/**
 * @file
 */

#ifndef UART_H_
#define UART_H_

/**
 * @brief UART Configuration
 *
 * @warning This functions must be called before using other UART functions.
 */
extern void configureUart(void);

/**
 * @brief Sends one through UART
 * @param c Char to be printed
 */
extern void printChar(char c);

/**
 * @brief Sends an array of characters through UART
 * @param c Char to be printed
 */
extern void printString (char *s);

/**
 * @brief Reads a character from UART
 * @return Character read from buffer
 */
extern char readChar (void);

/**
 * @brief Checks if there is any data available in UART
 * @return 1 - there is data available
 * @return 0 - uart is empty
 */
extern int serialAvailable(void);

#endif /* UART_H_ */
