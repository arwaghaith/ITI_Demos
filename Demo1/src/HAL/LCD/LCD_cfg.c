/**
* 
* @file    : LCD Driver Source Configuration File (HAL)
* @author  : Alaa Ghita
* @date    : April 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
 #include "GPIO.h"
 #include "LCD.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
/********************************************************************************************************/



/************************************************Types***************************************************/
 LCDPins_t const LCD_ControlPins[_ControlPins_num] =
 {
    [Enable_Pin]    = {.Port   = GPIO_PORT_A, .Pin    = GPIO_PIN_0},
                     
    [ReadWrite_Pin] = {.Port   = GPIO_PORT_A, .Pin    = GPIO_PIN_1},

    [RegSelect_Pin] = {.Port   = GPIO_PORT_A, .Pin     = GPIO_PIN_4}
 };

 LCDPins_t const LCD_DataPins[_DataPins_num] =
 {
    [Data_Pin0] = {.Port   = GPIO_PORT_A, .Pin    = GPIO_PIN_0},
                     
    [Data_Pin1] = {.Port   = GPIO_PORT_A, .Pin    = GPIO_PIN_1},

    [Data_Pin2] = {.Port   = GPIO_PORT_A, .Pin    = GPIO_PIN_2},

    [Data_Pin3] = {.Port   = GPIO_PORT_A, .Pin    = GPIO_PIN_3},
                     
    [Data_Pin4] = {.Port   = GPIO_PORT_B, .Pin    = GPIO_PIN_8},

    [Data_Pin5] = {.Port   = GPIO_PORT_B, .Pin    = GPIO_PIN_9},

    [Data_Pin6] = {.Port   = GPIO_PORT_B, .Pin    = GPIO_PIN_10},
                     
    [Data_Pin7] = {.Port   = GPIO_PORT_B, .Pin    = GPIO_PIN_12}
    
 };
/********************************************************************************************************/



/************************************************Variables***********************************************/
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


