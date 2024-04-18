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
                            .Port         = GPIO_PORTB_v2 ,
                            .Pin          = GPIO_PIN0,
                            .Connection   = HSwitch_CONNECTION_FORWARD
                       
                         },
                     
    [SW_Start_Stop]     = {
                            .Port         = GPIO_PORTB_v2,
                            .Pin          = GPIO_PIN1,
                            .Connection   = HSwitch_CONNECTION_REVERSE
                         
                         },

    [SW_Pause_Continue] = {
                            .Port         = GPIO_PORTB_v2,
                            .Pin          = GPIO_PIN2,
                            .Connection   = HSwitch_CONNECTION_REVERSE
                          },

    [SW_Edit]          = {
                            .Port         = GPIO_PORTB_v2,
                            .Pin          = GPIO_PIN3,
                            .Connection   = HSwitch_CONNECTION_REVERSE
                         },

    [SW_Up]             = {
                            .Port         = GPIO_PORTB_v2,
                            .Pin          = GPIO_PIN4,
                            .Connection   = HSwitch_CONNECTION_REVERSE
                            
                          },
    [SW_Down]           = {
                            .Port         = GPIO_PORTB_v2,
                            .Pin          = GPIO_PIN5,
                            .Connection   = HSwitch_CONNECTION_REVERSE
                          },

    [SW_Left]           = {
                            .Port         = GPIO_PORTB_v2,
                            .Pin          = GPIO_PIN6,
                            .Connection   = HSwitch_CONNECTION_REVERSE
                          },

    [SW_Right]          = {
                            .Port         = GPIO_PORTB_v2,
                            .Pin          = GPIO_PIN7,
                            .Connection   = HSwitch_CONNECTION_REVERSE
                          },

    [SW_OK]             = {
                            .Port         = GPIO_PORTB_v2,
                            .Pin          = GPIO_PIN8,
                            .Connection   = HSwitch_CONNECTION_REVERSE
                          }
    /*[PowerON_HSwitch]   = {
                           .Port         = GPIO_PORTB_v2,
                           .Pin          = GPIO_PIN1,
                           .Connection   = HSwitch_CONNECTION_FORWARD
                           },
                     
    [PowerOFF_HSwitch] = {
                          .Port         = GPIO_PORTB_v2,
                          .Pin          = GPIO_PIN2,
                          .Connection   = HSwitch_CONNECTION_REVERSE
                          },*/
 };
/********************************************************************************************************/


/*****************************************Static Functions Prototype*************************************/

/********************************************************************************************************/


/*********************************************APIs Implementation****************************************/

/********************************************************************************************************/
