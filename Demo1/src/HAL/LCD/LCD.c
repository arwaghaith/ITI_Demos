/*********************************************    Including The necessary libraries      ************************************/
#include "LCD.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/STD_MATH.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "LCD_cfg.h"
/***************************************************************************************************************************/
typedef void (*LCD_CallBack_t)(void);
/**
 * @brief External declarations of LCD_8BIT and LCD_4BIT arrays.
 *
 * These arrays are used to store the LCD_t structures for 8-bit and 4-bit modes respectively.
 * The LCD_t structure represents the pins used for controlling an LCD display.
 * The LCD_PINS_NUM constant specifies the number of pins used for the LCD display.
 */
/*****************************************************************************************************************************/
extern LCD_t LCD_8BIT[LCD_PINS_NUM];
extern LCD_t LCD_4BIT[LCD_PINS_NUM];
/*****************************************************************************************************************************/

/**
 * @file LCD.c
 * @brief This file contains the implementation of the LCD module.
 */

/**
 * @struct curPos
 * @brief Structure representing the current position of the LCD cursor.
 */
typedef struct
{
    uint8_t posX; /**< The X-coordinate of the cursor position. */
    uint8_t posY; /**< The Y-coordinate of the cursor position. */
} curPos;

/**
 * @struct user_Request
 * @brief Structure representing a user request for LCD operations.
 */
typedef struct
{
    curPos pos;              /**< The current position of the LCD cursor. */
    LCD_CallBack_t callBack; /**< Callback function for LCD operations. */
} user_Request;

static LCD_state G_lcd_State = LCD_OFF;         /**< The current state of the LCD module. */
static uint8_t EN_STATE_8_bit = EN_LOW;         /**< The state of the 8-bit enable pin. */
static uint8_t EN_STATE_4_bit = EN_LOW;         /**< The state of the 4-bit enable pin. */
static uint8_t glob_Power_state = POWER_OFF;    /**< The global power state of the LCD module. */
static LCD_INIT_State LCD_INIT_STATE = POWERON; /**< The initialization state of the LCD module. */

user_request_t LCD_user_request =
    {
        "LCD", /**< The name of the LCD module. */
        3,     /**< The number of lines in the LCD display. */
        BUSY, /**< The readiness state of the LCD module. */
        CLEAR, /**< The write mode of the LCD module. */
        {
            1, 1 /**< The initial position of the LCD cursor. */
        }};

/**
 * @brief This function is responsible for writing data to the LCD SYNCRONOUSLY.
 */
static void Write_proc();

/**
 * @brief This function is responsible for clearing the LCD screen SYNCRONOUSLY.
 */
static void clear_proc();

/**
 * @brief This function is responsible for setting the position of the cursor on the LCD screen SYNCRONOUSLY.
 */
static void setPos_Proc();

/************************************************************************************************************/

/**
 * @brief Power on initialization function for the LCD module.
 *
 * This function performs the power on initialization for the LCD module.
 * It sets the LCD power state to POWER_ON and initializes the LCD state to FUNCTIONAL_SET.
 *
 * @return The status of the LCD initialization.
 *         - LCD_OK: Initialization successful.
 *         - LCD_NOK: Initialization failed.
 */
LCD_enu_Status POWERON_INIT()
{

    static uint8_t loc_power_count = 0;
    LCD_enu_Status loc_lcd_status = LCD_NOK;
    switch (glob_Power_state)
    {
    case POWER_OFF:
        glob_Power_state = POWER_ON;
        break;
    case POWER_ON:
        if (loc_power_count < POWER_DELAY_COUNT)
        {
            loc_power_count++;
            loc_lcd_status = LCD_OK;
        }
        else
        {
            LCD_INIT_STATE = FUNCTIONAL_SET;
            loc_power_count = 0;

            loc_lcd_status = LCD_OK;
        }

        break;
    default:
        loc_lcd_status = LCD_NOK;
        break;
    }
    return loc_lcd_status;
}
/***********************************************************************************************************/
/**
 * @brief Initializes the pins for the LCD module.
 *
 * This function initializes the pins required for the LCD module based on the selected mode (8-bit or 4-bit).
 * It iterates through the pins array and calls the GPIO_Init function to initialize each pin.
 *
 * @return The status of the LCD initialization (LCD_OK or LCD_NOK).
 */
/***********************************************************************************************************/
LCD_enu_Status LCD_INIT_PINS()
{
    LCD_enu_Status loc_LCD_status = LCD_NOK;
    uint8_t LCD_loc_iterator = 0;

#if LCD_MODE == LCD_MODE_8_BIT

    for (LCD_loc_iterator = 0; LCD_loc_iterator < LCD_PINS_NUM; LCD_loc_iterator++)
    {
        GPIO_Init(&LCD_8BIT[LCD_loc_iterator]);
    }
    loc_LCD_status = LCD_OK;
#else if LCD_MODE == LCD_MODE_4_BIT

    for (LCD_loc_iterator = 0; LCD_loc_iterator < LCD_PINS_NUM; LCD_loc_iterator++)
    {
        GPIO_Init(&LCD_4BIT[LCD_loc_iterator]);
    }
    loc_LCD_status = LCD_OK;

#endif
    return loc_LCD_status;
}
/***********************************************************************************************************/
/**
 * @brief Initializes the LCD module.
 *
 * This function sets the LCD configuration based on the value of DISPLAY_LINES macro.
 * If DISPLAY_LINES is defined as ONE_LINE, it writes the command LCD_FUNCTION_SET_ONE_LINE to the LCD.
 * If DISPLAY_LINES is defined as TWO_LINE, it writes the command LCD_FUNCTION_SET_TWO_LINE to the LCD.
 *
 * @return The status of the LCD initialization. It can be either LCD_OK or LCD_NOK.
 */
/***********************************************************************************************************/
LCD_enu_Status FUNCTIONAL_SET_INIT()
{
    static uint8_t loc_command_counter = 0;

    LCD_enu_Status loc_LCD_Status = LCD_NOK;
#if DISPLAY_LINES == ONE_LINE
    if (loc_command_counter < command_count_in)
    {
        LCD_Write_Command(LCD_FUNCTION_SET_ONE_LINE);
        loc_command_counter++;
        LCD_enu_Status loc_LCD_Status = LCD_OK;
    }
    else
    {
        loc_command_counter = 0;
        LCD_INIT_STATE = DISPLAY_INIT;
        LCD_enu_Status loc_LCD_Status = LCD_OK;
    }

#else if DISPLAY_LINES == TWO_LINE
    if (loc_command_counter < command_count_in)
    {
        LCD_Write_Command(LCD_FUNCTION_SET_TWO_LINE);
        loc_command_counter++;
        LCD_enu_Status loc_LCD_Status = LCD_OK;
    }
    else
    {
        loc_command_counter = 0;
        LCD_INIT_STATE = DISPLAY_ON_OFF_INIT;
        LCD_enu_Status loc_LCD_Status = LCD_OK;
    }

#endif
    return loc_LCD_Status;
}

/***********************************************************************************************************/
/**
 * @brief Initializes the entry mode of the LCD.
 *
 * This function initializes the entry mode of the LCD by writing the DISPLAY_CLEAR command.
 */
/***********************************************************************************************************/
void ENTRY_MODE_INIT()
{
    static uint8_t loc_command_counter = 0;

    if (loc_command_counter < command_count_in)
    {
        LCD_Write_Command(LCD_INCREMENT_CURSOR);
        loc_command_counter++;
        LCD_enu_Status loc_LCD_Status = LCD_OK;
    }
    else
    {
        loc_command_counter = 0;
        LCD_INIT_STATE = END;
        LCD_enu_Status loc_LCD_Status = LCD_OK;
    }
}

/**
 * @brief Initializes the display settings of the LCD.
 *
 * This function initializes the display settings of the LCD based on the values of the CURSOR and BLINK macros.
 * It writes the appropriate command to the LCD based on the selected options.
 *
 * @return The status of the LCD initialization (LCD_OK or LCD_NOK).
 */
/***********************************************************************************************************/
LCD_enu_Status DISPLAY_ON_OFF()
{
    LCD_enu_Status loc_LCD_status = LCD_NOK;
    volatile uint8_t Display_MODE = LCD_DISPLAY_CUSRSOR_OFF_BLINK_OFF;
    static uint8_t loc_command_counter = 0;

#if CURSOR == CURSOR_OFF

    #if BLINK == BLINK_OFF
        Display_MODE = LCD_DISPLAY_CUSRSOR_OFF_BLINK_OFF;
    #elif BLINK == BLINK_ON
        Display_MODE = LCD_DISPLAY_CUSRSOR_OFF_BLINK_ON;
    #endif

#elif CURSOR == CURSOR_ON

    #if BLINK == BLINK_OFF
        Display_MODE = LCD_DISPLAY_CUSRSOR_ON_BLINK_OFF;
    #elif BLINK == BLINK_ON
        Display_MODE = LCD_DISPLAY_CUSRSOR_ON_BLINK_ON;
    #endif

#endif

    if (loc_command_counter < command_count_in)
    {
        LCD_Write_Command(Display_MODE);
        loc_command_counter++;
        loc_LCD_status = LCD_OK;
    }
    else
    {
        loc_command_counter = 0;
        // Assuming LCD_INIT_STATE is a global variable
        LCD_INIT_STATE = DISPLAY_CLEAR_INIT;
        loc_LCD_status = LCD_OK;
    }

    return loc_LCD_status;
}

LCD_enu_Status DISPLAY_CLR()
{
    static uint8_t loc_command_counter = 0;

    LCD_enu_Status loc_LCD_Status = LCD_NOK;
    if (loc_command_counter < command_count_in)
    {
        LCD_Write_Command(DISPLAY_CLEAR);
        loc_command_counter++;
        LCD_enu_Status loc_LCD_Status = LCD_OK;
    }
    else
    {
        loc_command_counter = 0;
        LCD_INIT_STATE = ENTRY_MODE;
        LCD_enu_Status loc_LCD_Status = LCD_OK;
    }
}

/***********************************************************************************************************/
/**
 * @brief This function is the main task for the LCD module.
 *        It handles the LCD state machine and performs the necessary operations based on the current state.
 */
/***********************************************************************************************************/
void LCD_TASK(void)
{
    switch (G_lcd_State)
    {
    case LCD_INIT:
        LCD_INIT_SM();
        break;
    case LCD_OFF:
        G_lcd_State = LCD_INIT;
        break;
    case LCD_Operational:
        if (LCD_user_request.state == BUSY)
        {
            switch (LCD_user_request.type)
            {
            case WRITE:
                Write_proc();
                break;
            case CLEAR:
                clear_proc();
                break;
            case SET_CURSOR:
                setPos_Proc();
                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }
}
/*****************************************************************************************************************/
/**
 * @brief Initializes the LCD module based on the current state.
 *
 * This function initializes the LCD module based on the current state defined by the LCD_INIT_STATE variable.
 * It switches between different initialization states and calls the corresponding initialization functions.
 * After the initialization process is completed, it sets the LCD state to LCD_Operational.
 */
void LCD_INIT_SM(void)
{
    switch (LCD_INIT_STATE)
    {
    case POWERON:
        POWERON_INIT();
        break;
    case FUNCTIONAL_SET:
        FUNCTIONAL_SET_INIT();
        break;
    case DISPLAY_ON_OFF_INIT:
        DISPLAY_ON_OFF();
        break;
    case DISPLAY_CLEAR_INIT:
        DISPLAY_CLR();
        break;
    case ENTRY_MODE:
        ENTRY_MODE_INIT();
        break;
    case END:
        G_lcd_State = LCD_Operational;
        break;
    default:
        break;
    }
}
/*****************************************************************************************************************/
/**
 * @file LCD.c
 * @brief This file contains the implementation of the LCD_Write_Command function.
 */

/**
 * @brief Writes a command to the LCD.
 *
 * This function writes a command to the LCD based on the selected LCD mode (8-bit or 4-bit).
 *
 * @param command Pointer to the command array.
 * @return LCD_enu_Status The status of the LCD operation (LCD_OK or LCD_NOK).
 */

LCD_enu_Status LCD_Write_Command(const uint8_t command)

{
    uint8_t loc_counter=0;

    LCD_enu_Status local_LCD_Status = LCD_NOK;

#if LCD_MODE == LCD_MODE_8_BIT

    if (EN_STATE_8_bit == EN_LOW)
    {

        /*  write operation*/
        GPIO_SET_PIN_VALUE(LCD_RW_PORT, LCD_RW_PIN, GPIO_LOW);
        /*  Write Command operation*/
        GPIO_SET_PIN_VALUE(LCD_RS_PORT, LCD_RS_PIN, GPIO_LOW);

       for(loc_counter=0;loc_counter<LCD_CD_PINS;loc_counter++)
       {
              GPIO_SET_PIN_VALUE(LCD_8BIT[loc_counter+3].LCD_Port, LCD_8BIT[loc_counter+3].LCD_Pin, ((command>>loc_counter)&1));
       }

        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_HIGH);
        EN_STATE_8_bit = EN_HIGH;
    }

    else
    {
        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_LOW);
        EN_STATE_8_bit = EN_LOW;
    }

    local_LCD_Status = LCD_NOK;

#elif LCD_MODE == LCD_MODE_4_BIT
    /*  write operation*/

    if (EN_STATE_4_bit == EN_LOW)
    {

        GPIO_SET_PIN_VALUE(LCD_RW_PORT, LCD_RW_PIN, GPIO_LOW);
        /*  Write Command operation*/
        GPIO_SET_PIN_VALUE(LCD_RS_PORT, LCD_RS_PIN, GPIO_LOW);

        GPIO_SET_PIN_VALUE(LCD_D0_PORT, LCD_D0_PIN, command[0]);
        GPIO_SET_PIN_VALUE(LCD_D1_PORT, LCD_D1_PIN, command[1]);
        GPIO_SET_PIN_VALUE(LCD_D2_PORT, LCD_D2_PIN, command[2]);
        GPIO_SET_PIN_VALUE(LCD_D3_PORT, LCD_D3_PIN, command[3]);

        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_HIGH);
        EN_STATE_4_bit = EN_HIGH;
    }

    else if (EN_STATE_4_bit == EN_HIGH)
    {

        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_LOW);
        EN_STATE_4_bit = EN_LOW_AGAIN;
    }

    else if (EN_STATE_4_bit == EN_LOW_AGAIN)
    {

        GPIO_SET_PIN_VALUE(LCD_D0_PORT, LCD_D0_PIN, command[5]);
        GPIO_SET_PIN_VALUE(LCD_D1_PORT, LCD_D1_PIN, command[6]);
        GPIO_SET_PIN_VALUE(LCD_D2_PORT, LCD_D2_PIN, command[7]);
        GPIO_SET_PIN_VALUE(LCD_D3_PORT, LCD_D3_PIN, command[8]);

        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_HIGH);
        EN_STATE_4_bit == EN_HIGH_AGAIN;
    }
    else if (EN_STATE_4_bit == EN_HIGH_AGAIN)
    {

        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_LOW);
        EN_STATE_4_bit = EN_LOW;
        local_LCD_Status = LCD_OK;
    }
    else
    {
        local_LCD_Status = LCD_NOK;
    }

#else
    local_LCD_Status = LCD_NOK;

#endif

    return local_LCD_Status;
}
/*************************************************************************************************************************/

/**
 * @brief Writes data to the LCD.
 *
 * This function is used to write data to the LCD display.
 *
 * @param data Pointer to the data to be written.
 * @return The status of the LCD operation.
 */
LCD_enu_Status LCD_Write_Data(const uint8_t data)
{

 uint8_t loc_counter=0;

    LCD_enu_Status local_LCD_Status = LCD_NOK;

#if LCD_MODE == LCD_MODE_8_BIT

    if (EN_STATE_8_bit == EN_LOW)
    {

        /*  write operation*/
        GPIO_SET_PIN_VALUE(LCD_RW_PORT, LCD_RW_PIN, GPIO_LOW);
        /*  Write data operation*/
        GPIO_SET_PIN_VALUE(LCD_RS_PORT, LCD_RS_PIN, GPIO_HIGH);

      for(loc_counter=0;loc_counter<LCD_CD_PINS;loc_counter++)
       {
              GPIO_SET_PIN_VALUE(LCD_8BIT[loc_counter+3].LCD_Port, LCD_8BIT[loc_counter+3].LCD_Pin, ((data>>loc_counter)&1));
       }

        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_HIGH);
        EN_STATE_8_bit = EN_HIGH;
    }

    else
    {
        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_LOW);
        EN_STATE_8_bit = EN_LOW;
    }

    local_LCD_Status = LCD_OK;

    local_LCD_Status = LCD_NOK;

#elif LCD_MODE == LCD_MODE_4_BIT
    /*  write operation*/

    if (EN_STATE_4_bit == EN_LOW)
    {

        GPIO_SET_PIN_VALUE(LCD_RW_PORT, LCD_RW_PIN, GPIO_LOW);
        /*  Write data operation*/
        GPIO_SET_PIN_VALUE(LCD_RS_PORT, LCD_RS_PIN, GPIO_HIGH);

        GPIO_SET_PIN_VALUE(LCD_D0_PORT, LCD_D0_PIN, data[0]);
        GPIO_SET_PIN_VALUE(LCD_D1_PORT, LCD_D1_PIN, data[1]);
        GPIO_SET_PIN_VALUE(LCD_D2_PORT, LCD_D2_PIN, data[2]);
        GPIO_SET_PIN_VALUE(LCD_D3_PORT, LCD_D3_PIN, data[3]);

        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_HIGH);
        EN_STATE_4_bit = EN_HIGH;
    }

    else if (EN_STATE_4_bit == EN_HIGH)
    {

        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_LOW);
        EN_STATE_4_bit = EN_LOW_AGAIN;
    }

    else if (EN_STATE_4_bit == EN_LOW_AGAIN)
    {

        GPIO_SET_PIN_VALUE(LCD_D0_PORT, LCD_D0_PIN, data[5]);
        GPIO_SET_PIN_VALUE(LCD_D1_PORT, LCD_D1_PIN, data[6]);
        GPIO_SET_PIN_VALUE(LCD_D2_PORT, LCD_D2_PIN, data[7]);
        GPIO_SET_PIN_VALUE(LCD_D3_PORT, LCD_D3_PIN, data[8]);

        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_HIGH);
        EN_STATE_4_bit == EN_HIGH_AGAIN;
    }
    else if (EN_STATE_4_bit == EN_HIGH_AGAIN)
    {

        GPIO_SET_PIN_VALUE(LCD_EN_PORT, LCD_EN_PIN, GPIO_LOW);
        EN_STATE_4_bit = EN_LOW;
        local_LCD_Status = LCD_OK;
    }
    else
    {
        local_LCD_Status = LCD_NOK;
    }

#else
    local_LCD_Status = LCD_NOK;

#endif

    return local_LCD_Status;
}
/****************************************************************************************************************************************/
/**
 * @brief Get the current state of the LCD.
 *
 * This function retrieves the current state of the LCD.
 *
 * @param LCD_state Pointer to the variable to store the LCD state.
 * @return LCD_enu_Status The status of the LCD state retrieval operation.
 */
/****************************************************************************************************************************************/
LCD_enu_Status LCD_GET_State(LCD_INIT_State *LCD_state)
{
    LCD_enu_Status loc_LCD_state = LCD_NOK;

    if (LCD_state != NULL)
    {
        loc_LCD_state = LCD_OK;
        *LCD_state = G_lcd_State;
    }
    return loc_LCD_state;
}

/**********************************************************************************************************/
/* @brief Clears the screen asynchronously.
 *
 * This function clears the LCD screen asynchronously by setting the user request type to CLEAR.
 * It returns the status of the LCD operation.
 *
 * @return The status of the LCD operation.
 */
/****************************************************************************************************************************************/

LCD_enu_Status clearScreenAsync()
{
    LCD_enu_Status LCD_loc_Status = LCD_NOK;

    if (G_lcd_State == LCD_Operational && LCD_user_request.state == READY)
    {
        LCD_user_request.state == BUSY;
        LCD_user_request.type = CLEAR;
    }
    else
    {
        // Handle error or invalid state
    }
    return LCD_loc_Status;
}

/**
 * Writes a string to the LCD asynchronously at the specified position.
 *
 * @param str     Pointer to the string to be written.
 * @param length  Length of the string.
 * @param posX    X-coordinate of the starting position.
 * @param posY    Y-coordinate of the starting position.
 * @return        The status of the LCD write operation.
 */
LCD_enu_Status LCD_Write_String_POS_ASYNC(const uint8_t *str, uint8_t length, uint8_t posX, uint8_t posY)
{
   static uint8_t loc_iterator=0;
   static uint8_t flag_type='C';

    LCD_enu_Status loc_Lcd_status = LCD_NOK;
    if(str!=LCD_user_request.s)
    {

    if (G_lcd_State == LCD_Operational && LCD_user_request.state == READY && flag_type=='C')
    {
        
             LCD_user_request.curpos.LCD_COL_POS = posY;
             LCD_user_request.curpos.LCD_ROW_POS = posX;
             LCD_user_request.type = SET_CURSOR;
             LCD_user_request.state = BUSY;
             loc_iterator++;
             flag_type='W';
        }
    
    else if (G_lcd_State == LCD_Operational && LCD_user_request.state == READY && flag_type=='W')
    {

        LCD_user_request.state = BUSY;
        LCD_user_request.s = str;

        LCD_user_request.length = length;
                        LCD_user_request.type = WRITE;

       
        loc_Lcd_status = LCD_OK;
   
        flag_type='C';
    }
    }
    
    return loc_Lcd_status;
}

/**
 * @brief Set the cursor position of the LCD asynchronously.
 *
 * This function sets the cursor position of the LCD asynchronously.
 *
 * @param posX X position of the LCD cursor.
 * @param posY Y position of the LCD cursor.
 * @return LCD_enu_Status The status of the set cursor position operation.
 */
LCD_enu_Status LCD_SET_CURSOR_POS_ASYNC(uint8_t posX, uint8_t posY)
{

    LCD_enu_Status loc_Lcd_status = LCD_NOK;
    if (G_lcd_State == LCD_Operational && LCD_user_request.state == READY)
    {
        LCD_user_request.type = SET_CURSOR;
        LCD_user_request.state = BUSY;

        LCD_user_request.curpos.LCD_COL_POS = posY;
        LCD_user_request.curpos.LCD_ROW_POS = posX;
        loc_Lcd_status = LCD_OK;
    }
    else
    {
    }
    return loc_Lcd_status;
}
/**
 * Writes a string to the LCD asynchronously.
 *
 * This function writes a string of characters to the LCD display asynchronously.
 *
 * @param str     Pointer to the string to be written.
 * @param length  Length of the string.
 *
 * @return The status of the LCD operation.
 */
LCD_enu_Status LCD_Write_String_ASYNC(const uint8_t *str, uint8_t length)

{

    LCD_enu_Status loc_Lcd_status = LCD_NOK;
    if (G_lcd_State == LCD_Operational && LCD_user_request.state == READY)
    {
        LCD_user_request.state = BUSY;
        LCD_user_request.s = str;
        LCD_user_request.length = length;
        LCD_user_request.type=WRITE;

        loc_Lcd_status = LCD_OK;
    }
    else
    {
    }
    return loc_Lcd_status;
}
static void Write_proc()
{
    static uint8_t loc_write_idx = 0;
    static uint8_t loc_command_counter = 0;

    if (loc_write_idx<LCD_user_request.length)
    {

        if (loc_command_counter < command_count_in)
        {
            LCD_Write_Data(LCD_user_request.s[loc_write_idx]);
            loc_command_counter++;
        }
        else
        {
            loc_command_counter = 0;
            loc_write_idx++;
        }
    }
    else
    {

        loc_write_idx = 0;
        LCD_user_request.state = READY;
        LCD_user_request.type = LCD_IDLE;
    }
}
static void clear_proc()
{

    static uint8_t loc_command_counter = 0;
    if (loc_command_counter < command_count_in)
    {
        LCD_Write_Command(DISPLAY_CLEAR);
        loc_command_counter++;
    }
    else
    {
        loc_command_counter = 0;
        LCD_user_request.state = READY;
        LCD_user_request.type = LCD_IDLE;
    }
}
static void setPos_Proc()
{
    static uint8_t loc_command_counter = 0;
    uint8_t loc_POS_Command = LCD_FORCE_CURSOR_BEGINNING_FIRST_LINE + LCD_user_request.curpos.LCD_COL_POS;

    if (LCD_user_request.curpos.LCD_ROW_POS == 1)
    {
        loc_POS_Command = LCD_FORCE_CURSOR_BEGINNING_FIRST_LINE + LCD_user_request.curpos.LCD_COL_POS;
    }
    else if (LCD_user_request.curpos.LCD_ROW_POS == 2)
    {
        loc_POS_Command = LCD_FORCE_CURSOR_BEGINNING_SECOND_LINE + LCD_user_request.curpos.LCD_COL_POS;
    }

    if (loc_command_counter < command_count_in)
    {
        LCD_Write_Command(loc_POS_Command);
        loc_command_counter++;
    }
    else
    {
        loc_command_counter = 0;
        LCD_user_request.state = READY;
        LCD_user_request.type = LCD_IDLE;
    }
}