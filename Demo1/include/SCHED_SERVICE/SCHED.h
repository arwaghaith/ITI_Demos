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

#ifndef SCHED_H_
#define SCHED_H_

/*************************************************************************************/
/********************         Scheduler  datatypes     *******************************/
/*************************************************************************************/

typedef unsigned int uint32_t;
typedef  void (*runnable_CBF_t)(void);

/*Features defined for each runnable */
/*        Can be modified            */

typedef struct 
{
    char           *runnable_name ;
    uint32_t       SCHED_periodicity_ms;
    uint32_t       SCHED_priority_level;
    uint32_t       SCHED_delayTime_ms;
    runnable_CBF_t SCHED_Runnable_CBF;

}SCHED_runnable_t;

/*************************************************************************************/
/********************          Scheduler  APIs         *******************************/
/*************************************************************************************/
/***********************  SCHED_Init  ******************
 * 
 * Functionality  : 1 - Select systick clock source
 *                  2 - Select Systick ms to set 
 *                      scheduler periodicity.
 *                  3 - Set systick cbf to be 
 *                      scheduler.
 *                  4 - Init Array of Runnables info 
 *                      which has a- pointer to your 
 *                                   Runnable
 *                                b- Remainig timems
 *                                   for this runnable.
 * 
********************************************************/
void SCHED_Init();
/******************  SCHED_Start  ******************
 * 
 * Functionality  : 1- call systick_start function
 *                     to start my system
 *                  2- polling for next tick.
****************************************************/
void SCHED_Start();


#endif