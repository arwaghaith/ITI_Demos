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
#include "HSwitch.h"
#include "APP_UPDATESWITCH.h"
#include "USART.h"


/***************************************************/
/*                   OPTIONS                       */
/***************************************************/
/*  USART_Number        : USART1 - USART2 - USART6.
    USART_ID            : USART1_ID - USART2_ID -
                                USART6_ID.
****************************************************/
#define SW_USART_CHANNEL_RX      USART1
#define SW_USART_CHANNEL_ID_RX   USART1_ID

/***************************************************/
/*               DataTypes Region                  */
/***************************************************/
/*This variable value bit is 1 corrsponds to pressed SW
  0b0000000000000100
  SW_Pause_Continue -> pressed
    */

USART_Request_t SW_update_RX_Request;

uint8_t  SW_RX_Message;
uint8_t  Received_SW_Pressed_ID ;

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
/*

  Received message 

*/
void APP_RX_MSG_Init(void)
{
   /*Size of the sent message which is 1Byte*/
   SW_update_RX_Request.USART_DataArraySize = sizeof(SW_RX_Message);
   SW_update_RX_Request.USART_ID            = SW_USART_CHANNEL_ID_RX;
   SW_update_RX_Request.USART_Number        = SW_USART_CHANNEL_RX ;
   SW_update_RX_Request.USART_CBFunc        = READ_RX_SWITCH_CB;
   
   
   /*I will filter this message here to get the ID of the pressed SW */


}
void APP_RECEIVE_SW_ID(void)
{
  USART_RxByte_Async(SW_update_RX_Request);
}
void READ_RX_SWITCH_CB(void)
{
  /*Read ID part from the received message*/
  SW_update_RX_Request.USART_Data[0] &= 0X0F;
  Received_SW_Pressed_ID = SW_update_RX_Request.USART_Data[0];

}  