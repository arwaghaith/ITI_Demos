/**
* 
* @file    : Configuration Source File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Driver   : Switch Driver (HAL)
* Machine  : STM32F401xC 
* 
*/

/************************************************Includes************************************************/
 #include "HSwitch.h"
 #include "GPIO.h"
 /********************************************************************************************************/


/************************************************Defines*************************************************/

/********************************************************************************************************/


/************************************************Types***************************************************/

/********************************************************************************************************/


/************************************************Variables***********************************************/
 const HSwitchcfg_t HSwitches[_DEMO_SW_NUM] =
 { 
    [SW_MODE]          = {
                            .Port         = GPIO_PORT_B ,
                            .Pin          = GPIO_PIN_4,
                            .Connection   = HSwitch_CONNECTION_FORWARD
                       
                         },
                     
    [SW_Start_Stop]     = {
                            .Port         = GPIO_PORT_B,
                            .Pin          = GPIO_PIN_5,
                            .Connection   = HSwitch_CONNECTION_FORWARD
                         
                         },

    [SW_Pause_Continue] = {
                            .Port         = GPIO_PORT_B,
                            .Pin          = GPIO_PIN_6,
                            .Connection   = HSwitch_CONNECTION_FORWARD
                          },

    [SW_Edit]          = {
                            .Port         = GPIO_PORT_B,
                            .Pin          = GPIO_PIN_7,
                            .Connection   = HSwitch_CONNECTION_FORWARD
                         },

    [SW_Up]             = {
                            .Port         = GPIO_PORT_B,
                            .Pin          = GPIO_PIN_8,
                            .Connection   = HSwitch_CONNECTION_FORWARD
                            
                          },
    [SW_Down]           = {
                            .Port         = GPIO_PORT_B,
                            .Pin          = GPIO_PIN_9,
                            .Connection   = HSwitch_CONNECTION_FORWARD
                          },

    [SW_Left]           = {
                            .Port         = GPIO_PORT_B,
                            .Pin          = GPIO_PIN_10,
                            .Connection   = HSwitch_CONNECTION_FORWARD
                          },

    [SW_Right]          = {
                            .Port         = GPIO_PORT_B,
                            .Pin          = GPIO_PIN_12,
                            .Connection   = HSwitch_CONNECTION_FORWARD
                          },

    [SW_OK]             = {
                            .Port         = GPIO_PORT_B,
                            .Pin          = GPIO_PIN_13,
                            .Connection   = HSwitch_CONNECTION_FORWARD
                          }
 };
/********************************************************************************************************/


/*****************************************Static Functions Prototype*************************************/

/********************************************************************************************************/


/*********************************************APIs Implementation****************************************/

/********************************************************************************************************/
