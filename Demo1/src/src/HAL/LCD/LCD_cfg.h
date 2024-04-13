#ifndef LCD_CFG_H
#define LCD_CFG_H

#include  "../../MCAL/GPIO/GPIO.h"
#include  "../../MCAL/GPIO/GPIO.h"



/************************************************************************************************************************/
/******************************************************  LCD MODES  *****************************************************/
#define LCD_MODE_4_BIT 0
#define LCD_MODE_8_BIT 1

//************************************************************************************************************************/

/********************** Choosing The mode of the LCD  **************/

#define LCD_MODE LCD_MODE_8_BIT

/********************   The no. of PINS of The LCD   **************/
#define LCD_PINS_NUM 3+(1+LCD_MODE)*4
/***********************]*******************************************/
#define LCD_CD_PINS  (1+LCD_MODE)*4
/*************** Choosing The no/ of lines to be displayed ********/
#define DISPLAY_LINES TWO_LINE
/******************************************************************/
/**************** Choosing Cursor On or Cursor Off  ***************/
#define CURSOR CURSOR_OFF
/******************************************************************/
/*************** Choosing Blinking On or Blinking Off  ************/
/******************************************************************/
#define BLINK  BLINK_OFF
/******************************************************************/
                         /*Control Pins*/
/******************************************************************/

#define LCD_RS_PORT GPIO_PORTB
#define LCD_RS_PIN GPIO_PIN8
/******************************************************************/
#define LCD_RW_PORT GPIO_PORTB
#define LCD_RW_PIN GPIO_PIN9
/******************************************************************/
#define LCD_EN_PORT  GPIO_PORTB
#define LCD_EN_PIN GPIO_PIN10
/******************************************************************/
/******************************************************************/

/******************************************************************/
#define LCD_D0_PORT GPIO_PORTB
#define LCD_D0_PIN  GPIO_PIN0
/******************************************************************/
/******************************************************************/
#define LCD_D1_PORT  GPIO_PORTB
#define LCD_D1_PIN  GPIO_PIN1
/******************************************************************/
/******************************************************************/
#define LCD_D2_PORT GPIO_PORTB
#define LCD_D2_PIN  GPIO_PIN2
/******************************************************************/
/******************************************************************/
#define LCD_D3_PORT GPIO_PORTB
#define LCD_D3_PIN  GPIO_PIN3
/******************************************************************/
/******************************************************************/
#define LCD_D4_PORT  GPIO_PORTB
#define LCD_D4_PIN  GPIO_PIN4
/******************************************************************/
/******************************************************************/
#define LCD_D5_PORT  GPIO_PORTB
#define LCD_D5_PIN  GPIO_PIN5
/******************************************************************/
/******************************************************************/
#define LCD_D6_PORT  GPIO_PORTB
#define LCD_D6_PIN  GPIO_PIN6
/******************************************************************/
/******************************************************************/
#define LCD_D7_PORT GPIO_PORTB
#define LCD_D7_PIN  GPIO_PIN7
/******************************************************************/
/**
 * @brief Structure representing the configuration of an LCD.
 */
/******************************************************************/

typedef struct 
{
    uint32_t LCD_Port;       /**< GPIO port connected to the LCD. */
    uint32_t LCD_Pin;        /**< GPIO pin connected to the LCD. */
    uint32_t LCD_PIN_MODE;   /**< GPIO pin mode for the LCD. */
    uint32_t LCD_PIN_SPEED;  /**< GPIO pin speed for the LCD. */
    uint32_t LCD_PIN_CFG;    /**< GPIO pin configuration for the LCD. */
    volatile uint32_t LCD_State; /**< State of the LCD. */
} LCD_t;
#endif