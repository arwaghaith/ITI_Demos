/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : Scheduler 	       */
/*	Layer	  : MCAL               */
/*	Version   : 1.0                */
/*	Date	  : March 14 , 2024    */
/*	Last Edit : N/A                */
/***********************************/




/*************************************************************************************/
/********************   Scheduler  Runnables configuration  **************************/
/*************************************************************************************/

#include "RUNNABLE_CFG.h"
#include "SCHED.h"


/*************************************************************************************/
/******************    eterns for runnables callback functions  **********************/
/*************************************************************************************/

extern void APP_TRAFFIC_LIGHT(void);
extern void APP_UPDATESWITCH_STATE(void);
extern void APP_READSWITCH(void);
extern void Clock_Runnable(void);
extern void Display_Runnable(void);
/**************************************************************************************/

/*************************************************************************************/
/****************         Setting Runnable Configurations        *********************/
/*************************************************************************************/

const SCHED_runnable_t SCHED_myrunnbles[__SCHED_MAX_Runnables] =
{
   /* [TRAFFIC_LIGHT]={
                        .runnable_name        = "Traffic Light",
                        .SCHED_delayTime_ms   = 0,
                        .SCHED_periodicity_ms = 50,
                        .SCHED_Runnable_CBF   = APP_TRAFFIC_LIGHT
             
                    },*/

    [UPDATESWITCH_STATE]={
                                .runnable_name        = "APP_UPDATESWITCH_STATE",
                                .SCHED_delayTime_ms   = 0,
                                .SCHED_periodicity_ms = 50,
                                .SCHED_Runnable_CBF   = APP_UPDATESWITCH_STATE
                    
                             },
    [READSWITCH]       ={
                                .runnable_name        = "APP READSWITCH",
                                .SCHED_delayTime_ms   = 0,
                                .SCHED_periodicity_ms = 50,
                                .SCHED_Runnable_CBF   = APP_READSWITCH
                    
                            },
    [Clock_Runnable_]       ={
                                .runnable_name        = "LCD clock",
                                .SCHED_delayTime_ms   = 0,
                                .SCHED_periodicity_ms = 50,
                                .SCHED_Runnable_CBF   = Clock_Runnable
                    
                           },
    [Display_Runnable_]={
                                .runnable_name        = "LCD Screen Display",
                                .SCHED_delayTime_ms   = 0,
                                .SCHED_periodicity_ms = 50,
                                .SCHED_Runnable_CBF   = Display_Runnable
             
                          },
    [StopWatch_Runnable_]={
                                .runnable_name        = "StopWatch_Runnable_",
                                .SCHED_delayTime_ms   = 0,
                                .SCHED_periodicity_ms = 50,
                                .SCHED_Runnable_CBF   = Display_Runnable
             
                          }

};