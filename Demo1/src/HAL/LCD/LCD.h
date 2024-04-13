#ifndef  LCD_H

#define LCD_H

/**********************************    Including The necessary Libraries   ***********************************************/
//************************************************************************************************************************/

#include "../../LIB/STD_TYPES.h"
//************************************************************************************************************************/


/************************************************* Mapping LCD config  ***************************************************/

#define LCD_FUNCTION_SET_ONE_LINE          0b00110000
#define LCD_FUNCTION_SET_TWO_LINE          0b00111000
#define LCD_DISPLAY_CUSRSOR_OFF_BLINK_OFF  0b00001100
#define LCD_DISPLAY_CUSRSOR_OFF_BLINK_ON   0b00001101
#define LCD_DISPLAY_CUSRSOR_ON_BLINK_OFF   0b00001110
#define LCD_DISPLAY_CUSRSOR_ON_BLINK_ON    0b00001111
#define  DISPLAY_CLEAR                     0b00000001

//************************************************************************************************************************/



/*****************************************        LCD USER REQUEST TYPES          ****************************************/
#define WRITE       0
#define SET_CURSOR  1
#define CLEAR       2
#define LCD_IDLE    3
/************************************************************************************************************************/
/*****************************************        LCD USER REQUEST States        ****************************************/
#define READY 0
#define BUSY 1
/************************************************************************************************************************/
#define CURSOR_OFF 0
#define CURSOR_ON 1
#define BLINK_OFF 0
#define BLINK_ON  1
/************************************************************************************************************************/
#define EN_LOW 0
#define EN_HIGH 1
#define EN_LOW_AGAIN 2
#define EN_HIGH_AGAIN 3
/************************************************************************************************************************/
#define POWER_OFF 0
#define POWER_ON 1
/************************************************************************************************************************/
#define ONE_LINE 0
#define TWO_LINE 1


/*****************************************************************************************************************************************/
/*****************************************************      LCD COMMANDS          ********************************************************/

#define LCD_ON_CURSOR_ON 0x0F
#define LCD_CLEAR_DISPLAY 0x01
#define LCD_RETURN_HOME 0x02
#define LCD_DECREMENT_CURSOR 0x04
#define LCD_INCREMENT_CURSOR 0x06
#define LCD_SHIFT_DISPLAY_RIGHT 0x05
#define LCD_SHIFT_DISPLAY_LEFT 0x07
#define LCD_DISPLAY_ON_CURSOR_BLINKING 0x0E
#define LCD_FORCE_CURSOR_BEGINNING_FIRST_LINE 0x80
#define LCD_FORCE_CURSOR_BEGINNING_SECOND_LINE 0xC0
#define LCD_2_LINES_5x7_MATRIX 0x38
#define LCD_CURSOR_LINE_1_POSITION_3 0x83
#define LCD_ACTIVATE_SECOND_LINE 0x3C
#define LCD_DISPLAY_OFF_CURSOR_OFF 0x08
#define LCD_JUMP_TO_SECOND_LINE_POSITION_1 0xC1
#define LCD_DISPLAY_ON_CURSOR_OFF 0x0C
#define LCD_JUMP_TO_SECOND_LINE_POSITION_2 0xC2

/******************************************************************************************************************************************/
#define command_count_in  (4-(LCD_MODE*2))
#define POWER_DELAY_COUNT 18
/******************************************************************************************************************************************/

/**********************************************************         LCD STATUS        ****************************************************/
typedef enum{

    LCD_NOK,
    LCD_OK


}LCD_enu_Status;




/*********************************************************        LCD State             **************************************************/
typedef enum{

    LCD_INIT,
    LCD_Operational,
    LCD_OFF

}LCD_state;
/*****************************************************************************************************************************************/
/*********************************************************        LCD_INIT_State         *************************************************/
typedef enum 
{
 POWERON,
 FUNCTIONAL_SET,
 ENTRY_MODE,
 DISPLAY_ON_OFF_INIT,
 DISPLAY_CLEAR_INIT,
 END

}LCD_INIT_State;
/*****************************************************************************************************************************************/
/*********************************************************      LCD_Curs_Position       **************************************************/
typedef struct {
   uint8_t LCD_ROW_POS;
   uint8_t LCD_COL_POS ;


}LCD_WRITE;
/*****************************************************************************************************************************************/
/*******************************************************      LCD_usr_string_request           ********************************************/
typedef struct {

    uint8_t*s;
    uint8_t length;
    uint8_t state;
    uint8_t type;
    LCD_WRITE curpos;
    
}user_request_t;


/*****************************************************************************************************************************************/
/****************************************************             LCD APIs        ********************************************************/

/**
 * @brief Initializes the LCD pins.
 * @return The status of the LCD initialization.
 */
/*****************************************************************************************************************************************/
LCD_enu_Status LCD_INIT_PINS();
/*****************************************************************************************************************************************/
/**
 * @brief LCD task function.
 *//*****************************************************************************************************************************************/
void LCD_TASK(void);
/*****************************************************************************************************************************************/
/**
 * @brief Initializes the LCD state machine.
 */
/*****************************************************************************************************************************************/
void LCD_INIT_SM(void);
/*****************************************************************************************************************************************/
/**
 * @brief Writes a command to the LCD.
 * @param command The command to be written.
 * @return The status of the write operation.
 */
/*****************************************************************************************************************************************/
LCD_enu_Status LCD_Write_Command(const uint8_t command);
/*****************************************************************************************************************************************/
/**
 * @brief Writes data to the LCD.
 * @param Data The data to be written.
 * @return The status of the write operation.
 */
/*****************************************************************************************************************************************/
LCD_enu_Status LCD_Write_Data(const uint8_t Data);
/*****************************************************************************************************************************************/
/**
 * @brief Performs the power-on initialization sequence for the LCD.
 * @return The status of the power-on initialization.
 */
/*****************************************************************************************************************************************/
LCD_enu_Status POWERON_INIT();
/*****************************************************************************************************************************************/
/**
 * @brief Performs the functional set initialization for the LCD.
 * @return The status of the functional set initialization.
 */
/*****************************************************************************************************************************************/
LCD_enu_Status FUNCTIONAL_SET_INIT();
/*****************************************************************************************************************************************/
/**
 * @brief Initializes the entry mode for the LCD.
 */
/*****************************************************************************************************************************************/
void ENTRY_MODE_INIT();
/*****************************************************************************************************************************************/
/**
 * @brief Performs the display initialization for the LCD.
 * @return The status of the display initialization.
 */
/*****************************************************************************************************************************************/
LCD_enu_Status DISPLAY_ON_OFF();
LCD_enu_Status DISPLAY_CLR();

/*****************************************************************************************************************************************/
/**
 * @brief Writes a string to the LCD asynchronously.
 * @param str The string to be written.
 * @param length The length of the string.
 * @return The status of the write operation.
 */
/*****************************************************************************************************************************************/
LCD_enu_Status LCD_Write_String_ASYNC(const uint8_t* str, uint8_t length);
/*****************************************************************************************************************************************/
/**
 * @brief Gets the current state of the LCD initialization.
 * @param LCD_state Pointer to the LCD_INIT_State variable to store the state.
 * @return The status of the get operation.
 */
/*****************************************************************************************************************************************/
LCD_enu_Status LCD_GET_State(LCD_INIT_State* LCD_state);
/*****************************************************************************************************************************************/
/**
 * @brief Clears the screen asynchronously.
 * @return The status of the clear operation.
 */
/*****************************************************************************************************************************************/
LCD_enu_Status clearScreenAsync();
/*****************************************************************************************************************************************/
/**
 * @brief Writes a string to the LCD at a specified position asynchronously.
 * @param str The string to be written.
 * @param length The length of the string.
 * @param posX The X position of the cursor.
 * @param posY The Y position of the cursor.
 * @return The status of the write operation.
 */
/*****************************************************************************************************************************************/
LCD_enu_Status LCD_Write_String_POS_ASYNC(const uint8_t* str, uint8_t length, uint8_t posX, uint8_t posY);
/*****************************************************************************************************************************************/
/**
 * @brief Sets the cursor position on the LCD asynchronously.
 * @param posX The X position of the cursor.
 * @param posY The Y position of the cursor.
 * @return The status of the set operation.
 */
/*****************************************************************************************************************************************/
LCD_enu_Status LCD_SET_CURSOR_POS_ASYNC(uint8_t posX, uint8_t posY);
/*****************************************************************************************************************************************/
#endif