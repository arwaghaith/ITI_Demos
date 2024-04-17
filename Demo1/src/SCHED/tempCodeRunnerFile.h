#ifndef SCHED_SCHED_H_
#define SCHED_SCHED_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/


#include"LIB/Error_Status.h"
#include"LIB/STD_TYPES.h"

#include "../MCAL/SysTick/SysTick.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef void (*runnableCallBack_t) (void);

typedef struct 
{
    /* data */
    char * runnable_name; 
    uint32_t periodicity;
    uint32_t priority;
    runnableCallBack_t CallBack;

}runnable_t;


/* put names of runnable tasks here */
typedef enum 
{
    
        LCD_TASK_fun,
        lcd_pp,
        // Switch_GetInstant_fun,
        // Display_fun,
        // CLOCK_fun,
        // //{updateSwitch, 10, 5, updateSwitch},
        // stopwatch_fun,
  
_NUM_OF_Runnables
}All_Runnables;



/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/


void Sched_Init(void);
void Sched_Start (void);
#endif // SCHED_SCHED_H_