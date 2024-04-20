/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : Scheduler 	       */
/*	Layer	  : MCAL               */
/*	Version   : 1.0                */
/*	Date	  : March 14 , 2024    */
/*	Last Edit : N/A                */
/***********************************/


#ifndef RUNNABLE_CFG_H_
#define RUNNABLE_CFG_H_

/*************************************************************************************/
/********************         Runnables  list          *******************************/
/*************************************************************************************/


/*       List of runnables of my system        */
/*      Here where you can add new Runnable   */

typedef enum
{
    LCD_Runnable_,
    //HSwitch_Runnable_,
    Clock_Runnable_,
    StopWatch_Runnable_,
    Display_Runnable_,
    UPDATESWITCH_STATE,
    READSWITCH,
    __SCHED_MAX_Runnables

}SCHED_runnables_list_t;


#endif