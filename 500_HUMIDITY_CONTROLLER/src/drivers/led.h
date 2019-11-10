/**
 * @file
 */

#ifndef LED_H_
#define LED_H_

/**
 * @enum colorEnum
 *
 */
typedef enum colorEnum
{
    DARK = 0,   /**< Turn off LED*/
    RED,        /**< Turn LED red*/
    BLUE,       /**< Turn LED blue*/
    GREEN       /**< Turn LED green*/
}colorEnum;

extern void builtInLedInit();

extern void setbuiltinLed(colorEnum color);

#endif /* LED_H_ */
