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
extern void StopWatch_Runnable(void);
extern void LCD_Runnable(void);
extern void HSwitch_Runnable(void);
extern void APP_USART_Init(void);

/**************************************************************************************/

/*************************************************************************************/
/****************         Setting Runnable Configurations        *********************/
/*************************************************************************************/

const SCHED_runnable_t SCHED_myrunnbles[__SCHED_MAX_Runnables] =
{
    [LCD_Runnable_]        ={
                                .runnable_name        = "LCD Runnable",
                                .SCHED_delayTime_ms   = 0,
                                .SCHED_periodicity_ms = 2,
                                .SCHED_Runnable_CBF   = LCD_Runnable
                    
                           },
    [HSwitch_Runnable_]     ={
                                .runnable_name        = "HSwitch Runnable",
                                .SCHED_delayTime_ms   = 0,
                                .SCHED_periodicity_ms = 5,
                                .SCHED_Runnable_CBF   = HSwitch_Runnable
                            },
    [Display_Runnable_]    ={
                                .runnable_name        = "Display Runnable",
                                .SCHED_delayTime_ms   = 35,
                                .SCHED_periodicity_ms = 85,
                                .SCHED_Runnable_CBF   = Display_Runnable
                            },
    [Clock_Runnable_]       ={
                                .runnable_name        = "Clock Runnable",
                                .SCHED_delayTime_ms   = 35,
                                .SCHED_periodicity_ms = 1000,
                                .SCHED_Runnable_CBF   = Clock_Runnable
                            },
    [StopWatch_Runnable_]  ={
                                .runnable_name        = "StopWatch_Runnable_",
                                .SCHED_delayTime_ms   = 35,
                                .SCHED_periodicity_ms = 100,
                                .SCHED_Runnable_CBF   = StopWatch_Runnable
                            },
    [UPDATESWITCH_STATE]       ={
                                .runnable_name        = "APP_UPDATESWITCH_STATE",
                                .SCHED_delayTime_ms   = 0,
                                .SCHED_periodicity_ms = 200,
                                .SCHED_Runnable_CBF   = &APP_UPDATESWITCH_STATE
                    
                           },
    [READSWITCH]           = {
                                .runnable_name        = "APP READSWITCH",
                                .SCHED_delayTime_ms   = 0,
                                .SCHED_periodicity_ms = 100,
                                .SCHED_Runnable_CBF   = &APP_READSWITCH
             
                          }

};