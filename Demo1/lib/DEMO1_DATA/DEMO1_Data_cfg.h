
/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : switches_demo      */
/*	Layer	  : HAL                */
/*	Version   : 1.0                */
/*	Date	  : April 11 , 2024    */
/*	Last Edit : N/A                */
/***********************************/

/*USART Frame check Design
Only send at the end 
*/
/************************************************************************************/
/**************************       Switches  DRIVER    *******************************/
/************************************************************************************/
#ifndef DEMO1_DATA_CFG_H_
#define DEMO1_DATA_CFG_H_

#include "Typedefs.h"

 typedef enum
 {
    SW_MODE,
    SW_Start_Stop,
    SW_Pause_Continue,
    SW_Edit,
    SW_Up,
    SW_Down,
    SW_Left,
    SW_Right,
    SW_OK,
   _DEMO_SW_NUM           /*MUST KEEP IT AS IT IS*/

 }Switches_t;


 #endif