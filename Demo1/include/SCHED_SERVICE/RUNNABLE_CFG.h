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
/********************         Scheduler  DRIVER        *******************************/
/*************************************************************************************/


/*       List of runnables of my system        */
/*      Here where you can add new Runnable   */

typedef enum
{
    runn,
    __SCHED_MAX_Runnables
}SCHED_runnables_list_t;


#endif