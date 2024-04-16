/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : APP_UPDATESWITCH   */
/*	Layer	     : APP                */
/*	Version    : 1.0                */
/*	Date	     : April 14 , 2024    */
/*	Last Edit  : N/A                */
/***********************************/


                           /**************************************************/
                           /**          APP_UPDATESWITCH driver             **/
                           /**************************************************/
                           
/***************************************************/
/*                Includes Region                  */
/***************************************************/
#include "DEMO1_Data_cfg.h"
#include "APP_UPDATESWITCH.h"
#include "USART.h"

/***************************************************/
/*               Macros Region                     */
/***************************************************/
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
#define NO_SW_PRESSED         0xFF


/***************************************************/
/*               DataTypes Region                  */
/***************************************************/
/*This variable value bit is 1 corrsponds to pressed SW
  0b0000000000000100
  SW_Pause_Continue -> pressed
    */
extern uint16_t SW_Pressed_ID;
uint8_t SW_Message = 0;
USART_Request_t SW_update_TX_Request;


/*
                                      **    SW_STATUS_INFO   **
                                      --------------------------

     8           7          6           5         4          3              2                    1           0
--------------------------------------------------------------------------------------------------------------------
|  SW_OK  |  SW_Right |  SW_Left  |  SW_Down |  SW_Up   | SW_Edit    | SW_Pause_Continue  |  SW_Start_Stop | SW_MODE |
--------------------------------------------------------------------------------------------------------------------
| NPressed |  NPressed |  NPressed  | NPressed | NPressed | NPressed |      Pressed       |    NPressed    | NPressed |
---------------------------------------------------------------------------------------------------------------------
ID SW->
1 messages -> MSB is the check password 

ID OF MCU PASSED IN START BYTE
  *Password Check in 4 MSB*
   -------------------
   | 7 | 6  | 5  | 4 |
   -------------------
   | 0 |  1 | 0  | 1 |
   -------------------
1 - my MCU Number is 1 [7 : 6]
2 - Check number   1
                                                0XAID 
--------------------------------------------------------------------------------------------------
|        password  [4 bits ]  2 bits ID      |                    ID                             |
--------------------------------------------------------------------------------------------------
|          "5"   check  password             |     0     |     0       |     0       |    0      |
--------------------------------------------------------------------------------------------------
*/ 

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
