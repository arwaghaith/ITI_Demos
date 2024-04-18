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

extern void APP_UPDATESWITCH_STATE(void);
extern void APP_READSWITCH(void);
extern void Clock_Runnable(void);
extern void Display_Runnable(void);
extern void blinkled_init(void);
extern void app_blinkled_on(void);
extern void app_blinkled_off(void);
/**************************************************************************************/

/*************************************************************************************/
/****************         Setting Runnable Configurations        *********************/
/*************************************************************************************/

const SCHED_runnable_t SCHED_myrunnbles[__SCHED_MAX_Runnables] =
{

    [app_blinkled_on_]={
                                .runnable_name        = "app_blinkled_on_",
                                .SCHED_delayTime_ms   = 0,
                                .SCHED_periodicity_ms = 100,
                                .SCHED_Runnable_CBF   = &app_blinkled_on
                    
                             },
    [app_blinkled_off_]       ={
                                .runnable_name        = "app_blinkled_off_",
                                .SCHED_delayTime_ms   = 100,
                                .SCHED_periodicity_ms = 200,
                                .SCHED_Runnable_CBF   = &app_blinkled_off
                    
                            },
<<<<<<< HEAD
    [UPDATESWITCH_STATE]       ={
                                .runnable_name        = "APP_UPDATESWITCH_STATE",
                                .SCHED_delayTime_ms   = 0,
                                .SCHED_periodicity_ms = 200,
                                .SCHED_Runnable_CBF   = &APP_UPDATESWITCH_STATE
=======
    [Clock_Runnable_]       ={
                                .runnable_name        = "LCD clock",
                                .SCHED_delayTime_ms   = 30,
                                .SCHED_periodicity_ms = 1000,
                                .SCHED_Runnable_CBF   = Clock_Runnable
>>>>>>> b96e4f7cade6ffbbc4ee05d3de7d45424c24c2b7
                    
                           },
    [READSWITCH]            = {
                                .runnable_name        = "APP READSWITCH",
                                .SCHED_delayTime_ms   = 0,
<<<<<<< HEAD
                                .SCHED_periodicity_ms = 100,
                                .SCHED_Runnable_CBF   = &APP_READSWITCH
=======
                                .SCHED_periodicity_ms = 85,
                                .SCHED_Runnable_CBF   = Display_Runnable
>>>>>>> b96e4f7cade6ffbbc4ee05d3de7d45424c24c2b7
             
                          },
    /*[StopWatch_Runnable_]={
                                .runnable_name        = "StopWatch_Runnable_",
                                .SCHED_delayTime_ms   = 35,
                                .SCHED_periodicity_ms = 100,
                                .SCHED_Runnable_CBF   = Display_Runnable
             
                          }*/

};