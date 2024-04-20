/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : APP_UPDATESWITCH   */
/*	Layer	  : APP                */
/*	Version   : 1.0                */
/*	Date	  : April 14 , 2024    */
/*	Last Edit : N/A                */
/***********************************/


                    /**************************************************/
                    /**          APP_UPDATESWITCH driver             **/
                    /**************************************************/

#ifndef APP_UPDATESWITCH_H_
#define APP_UPDATESWITCH_H_

/**************************************************/
/**             APP_READSWITCH APIs              **/
/**************************************************/
void APP_RX_MSG_Init(void);
void APP_RECEIVE_SW_ID(void);
void READ_RX_SWITCH_CB(void);
#endif