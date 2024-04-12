/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : Scheduler 	       */
/*	Layer	  : MCAL               */
/*	Version   : 1.0                */
/*	Date	  : March 14 , 2024    */
/*	Last Edit : N/A                */
/***********************************/




/*************************************************************************************/
/********************         Scheduler  DRIVER        *******************************/
/*************************************************************************************/

#include "RUNNABLE_CFG.h"
#include "SCHED.h"

extern void APP_BlinkLed(void);

/*           Setting Runnable Configurations         */
const SCHED_runnable_t SCHED_myrunnbles[__SCHED_MAX_Runnables] =

{
    [runn]={
             .runnable_name = "blinking led",
             .SCHED_delayTime_ms=40,
             .SCHED_periodicity_ms=34,
             .SCHED_Runnable_CBF=APP_BlinkLed
             
            }

};