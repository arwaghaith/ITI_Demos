

#include "Sched_Runnables.h"
#include "../../HAL/LED/LED.h"



extern void Switch_GetInstant(void);
extern void LCD_TASK();

extern void  LED_SWITCH_UPDATE();



const Runnables_t sys_Runnables[MAX_RUNNABLES]

={

       [0]={switches,5,Switch_GetInstant},
     

       

    
};