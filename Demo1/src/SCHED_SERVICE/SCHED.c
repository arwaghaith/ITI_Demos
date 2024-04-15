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

/*************************************************************************************/
/********************         Scheduler  includes      *******************************/
/*************************************************************************************/
#include "SCHED.h"
#include "RUNNABLE_CFG.h"
#include "SYSTICK.h"
/*************************************************************************************/
/********************         Scheduler  defines       *******************************/
/*************************************************************************************/

/**************************************************************************************/
/*
** options : 1 - SYTK_AHB_8_CLK
             2 - SYTK_Processor_AHB_CLK
  
*/
#define SCHED_SYSTICK_CLK SYSTICK_AHB_8_CLK

/*************************************************************************************/
/********************         Scheduler  datatypes     *******************************/
/*************************************************************************************/

/*************************************************************************************/
                  /*struct editable features by developers */
/*************************************************************************************/
typedef struct 
{
   SCHED_runnable_t* myrunnable;
   uint32_t runnable_remaing_time;

}SCHED_runnable_Info_t;

const uint32_t SCHED_TICK_TIME_ms = 500;

typedef enum
{
    Runnable_ptr1,
    __SCHED_MAX_Runnables_ptr
    
}Runnable_ptr_list;

extern SCHED_runnable_t SCHED_myrunnbles[__SCHED_MAX_Runnables];
static volatile uint32_t SCHED_PendingTicks = 0;
static SCHED_runnable_Info_t SCHED_Runables_INFO[__SCHED_MAX_Runnables_ptr];

/*****************************************************************************************************/
/********************         Static Functions Prototypes Region       *******************************/
/*****************************************************************************************************/
static void SCHED(void);
static void SCHED_PendingTicksCB(void);
/******************************************************************************************************/

void SCHED_Init()
{
    uint32_t local_runn_iterator = 0;
    /*select clk for systick timer  */
    SYSTICK_SELECT_CLKSRC(SCHED_SYSTICK_CLK);
    /*how often scheduler will be called*/
    SYSTICK_SetTimeMS(SCHED_TICK_TIME_ms);
    /*    Set call back fnction for systick   */
    SYSTICK_SetCallBack(SCHED_PendingTicksCB);
    for ( local_runn_iterator = 0; local_runn_iterator < __SCHED_MAX_Runnables_ptr; local_runn_iterator++)
    {
        SCHED_Runables_INFO[local_runn_iterator].myrunnable = &SCHED_myrunnbles[local_runn_iterator];
        /*Init all runnables with required delay once system start*/
        SCHED_Runables_INFO[local_runn_iterator].runnable_remaing_time = SCHED_myrunnbles[local_runn_iterator].SCHED_delayTime_ms; 
    }
    
}

void SCHED_Start()
{

    /*strart */
    SYSTICK_START();
    /*polling till next tick*/
    while(1)
	{
		if(SCHED_PendingTicks)
		{
			SCHED_PendingTicks--;
			SCHED();
		}
	}

}

static void SCHED_PendingTicksCB(void)
{
    SCHED_PendingTicks++;
}

static void SCHED(void)
{
    uint32_t Current_Runnable_idx;
   
    static uint32_t SCHED_time =0;
    for(Current_Runnable_idx = 0;Current_Runnable_idx<__SCHED_MAX_Runnables;Current_Runnable_idx++)
    {
        /*2 checks required runnable cb is set "not NULL" + 
            Remaing time for this runnabe=0 means its time to be executed*/
            /*
            
            if((SCHED_myrunnbles[Current_Runnable_idx].SCHED_Runnable_CBF)&&(!(SCHED_Runables_INFO[Current_Runnable_idx].runnable_remaing_time)))
            */
        if((SCHED_Runables_INFO[Current_Runnable_idx].myrunnable->SCHED_Runnable_CBF)&&(!(SCHED_Runables_INFO[Current_Runnable_idx].myrunnable->SCHED_periodicity_ms)))
        {
           // SCHED_Runables_INFO[Current_Runnable_idx].myrunnable->SCHED_Runnable_CBF;
            SCHED_Runables_INFO[Current_Runnable_idx].runnable_remaing_time = SCHED_Runables_INFO[Current_Runnable_idx].myrunnable->SCHED_periodicity_ms;

        }
    }
    SCHED_time+=SCHED_TICK_TIME_ms;
}