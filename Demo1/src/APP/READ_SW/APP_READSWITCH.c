/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : APP_READSWITCH       */
/*	Layer	     : APP               */
/*	Version    : 1.0               */
/*	Date	     : April 14 , 2024   */
/*	Last Edit  : N/A               */
/***********************************/


                /**************************************************/
                /**            APP_READSWITCH driver             **/
                /**************************************************/
                
/***************************************************/
/*                Includes Region                  */
/***************************************************/
#include "DEMO1_Data_cfg.h"
#include "APP_READSWITCH.h"
#include "USART.h"
#include "HSwitch.h"


/***************************************************/
/*               Macros Region                     */
/***************************************************/
#define NO_SW_PRESSED 0XFF
/***************************************************/
/*                   OPTIONS                       */
/***************************************************/
/*  USART_Number        : USART1 - USART2 - USART6.
    USART_ID            : USART1_ID - USART2_ID -
                                USART6_ID.
****************************************************/
#define SW_USART_CHANNEL_RX      USART1
#define SW_USART_CHANNEL_ID_RX   USART1_ID
/*
  1 - Need to know periodicity of readding sw
  2 - Need to know mechaanism of pressed SW periority to be updated 
  
  */
/*
                                        SW_Pressed_Key
    8          7          6           5         4         3             2                 1             0
-----------------------------------------------------------------------------------------------------------
|SW_OK | SW_Right | SW_Left  | SW_Down | SW_Up | SW_Edit  | SW_Pause_Continue  |  SW_Start_Stop | SW_MODE |
-----------------------------------------------------------------------------------------------------------
|  0   |     0    |     0    |   0     |   0   |    0     |           1        |      0         |    0    | -> 0x04 "SW_Pause_Continue" SW
-----------------------------------------------------------------------------------------------------------    PRESSED means update current state

*/ 
/***************************************************/
/*               Datatypes Region                  */
/***************************************************/
typedef unsigned char uint8_t;
uint8_t SW_Pressed_ID = NO_SW_PRESSED;
USART_Request_t SW_update_RX_Request;
uint16_t SW_RX_Message;
uint8_t  Received_SW_Pressed_ID;

/***************************************************/
/*       Functions Implementation Region           */
/***************************************************/

void APP_READSWITCH(void)
{

   uint16_t APP_local_idx = 0;
   uint8_t SW_Current_Pressed = NO_SW_PRESSED;
   uint8_t local_flag=1;
   /*First taken ID is first pirority ID for SW updated*/
   for(APP_local_idx = 0 ;local_flag && (APP_local_idx < _DEMO_SW_NUM ); APP_local_idx++)
   {
       HSwitch_GetStatus(APP_local_idx,&SW_Current_Pressed);
       if(SW_Current_Pressed == enuHSwitch_Pressed)
       {
         SW_Pressed_ID      = APP_local_idx;
         local_flag         = 0;
       }
   }
   if(SW_Current_Pressed == enuHSwitch_Released)
   {
      /*Zero values means no SW is pressed*/
      SW_Pressed_ID = NO_SW_PRESSED;
   }

}
/*

  Received message 

*/
void APP_RX_MSG_Init(void)
{
   
   SW_update_RX_Request.USART_DataArraySize = sizeof(SW_RX_Message);
   SW_update_RX_Request.USART_ID            = SW_USART_CHANNEL_ID_RX;
   SW_update_RX_Request.USART_Number        = SW_USART_CHANNEL_RX ;
   SW_update_RX_Request.USART_CBFunc        = READ_RX_SWITCH_CB;

   USART_RxByte_Async(SW_update_RX_Request);
   /*I will filter this message here to get the ID of the pressed SW */


}
void READ_RX_SWITCH_CB(void)
{
  uint8_t EXTRACTED_ID;
  /*filter data to get ID ->STILL NOT HANDLED */
  //SW_update_RX_Request.USART_Data -> EXTRACTED ID;
  Received_SW_Pressed_ID = EXTRACTED_ID;

}  