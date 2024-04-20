/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : APP_READSWITCH     */
/*	Layer	  : APP                */
/*	Version   : 1.0                */
/*	Date	  : April 14 , 2024    */
/*	Last Edit : N/A                */
/***********************************/


                    /**************************************************/
                    /**            APP_READSWITCH driver             **/
                    /**************************************************/
#ifndef APP_READSWITCH_H_
#define APP_READSWITCH_H_

/**************************************************/
/**            APP_READSWITCH APIs               **/
/**************************************************/
void APP_TX_MSG_Init(void);
void APP_READSWITCH(void);
void APP_UPDATESWITCH_STATE(void);
void SW_TX_Done_CB(void);

#endif
