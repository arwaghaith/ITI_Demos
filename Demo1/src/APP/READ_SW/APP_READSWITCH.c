/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		     : APP_READSWITCH    */
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

#include "APP_READSWITCH.h"
#include "USART.h"
#include "HSwitch.h"
#include "Typedefs.h"


/***************************************************/
/*               Macros Region                     */
/***************************************************/
#define NO_SW_PRESSED 0XFF
#define SW_CHECK_ID(ID) ((ID >= 0) && (ID <=_DEMO_SW_NUM))
#define SW_PASSWORD_CHECK  0X50
/***************************************************/
/*                   OPTIONS                       */
/***************************************************/
/*  USART_Number        : USART1 - USART2 - USART6.
    USART_ID            : USART1_ID - USART2_ID -
                                USART6_ID.
*****************************************************/
#define SW_USART_CHANNEL_TX      USART1
#define SW_USART_CHANNEL_ID_TX   USART1_ID


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

uint8_t SW_Pressed_ID = NO_SW_PRESSED;
uint8_t SW_Message = 0;


USART_Request_t SW_update_TX_Request;



/***************************************************/
/*       Functions Implementation Region           */
/***************************************************/

void APP_TX_MSG_Init(void)
{
   
   SW_update_TX_Request.USART_DataArraySize = sizeof(SW_Message);
   SW_update_TX_Request.USART_ID            = SW_USART_CHANNEL_ID_TX;
   SW_update_TX_Request.USART_Number        = SW_USART_CHANNEL_TX ;
   SW_update_TX_Request.USART_CBFunc        = SW_TX_Done_CB ;

}

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
   /*Prepare message then send it async*/
   APP_UPDATESWITCH_STATE();
 
}
void APP_UPDATESWITCH_STATE(void)
{
   USART_ErrorStatus_t USART_CHECK;
   /*Filter ID part*/
   SW_Message = 0X0F & SW_Pressed_ID;
   /*Check ID part*/
   if(SW_CHECK_ID(SW_Message))
   {
     /*Assign Password Check bits */
      SW_Message |= SW_PASSWORD_CHECK ;
      /*Assign Tx Request*/
      SW_update_TX_Request.USART_Data = &SW_Message;
      USART_CHECK = USART_TxByte_Async(SW_update_TX_Request);


   }
   else if(SW_Pressed_ID == NO_SW_PRESSED)
   {
      /* F "1111" ID part means NO sw pressed all in released MODE*/
      SW_Message = SW_Pressed_ID & 0x0F;
      /*Assign Password Check bits */
      SW_Message |= SW_PASSWORD_CHECK ;
      /*Assign Tx Request*/
      SW_update_TX_Request.USART_Data = &SW_Message;
       USART_CHECK = USART_TxByte_Async(SW_update_TX_Request);
   }
   if(USART_CHECK)
   {

   }
  
}



void SW_TX_Done_CB(void)
{


}
