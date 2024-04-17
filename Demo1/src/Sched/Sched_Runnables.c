






#include "Sched_Runnables.h"


#include "Sched.h"




extern void Switch_GetInstant(void);
extern void LCD_TASK();
extern void Clock();
extern void stopwatch();
extern void updateSwitch();
extern void ReadSwitch();
extern void Display();




const Runnables_t sys_Runnables[MAX_RUNNABLES]

={

       [0]={Switch_GetInstant_fun,10,Switch_GetInstant},
        [1]={LCD_TASK_fun,2,LCD_TASK},
        
         [2]={Display_fun,100,Display},
        [3]={CLOCK_fun,100,CLOCK_fun},
        [4]={stopwatch_fun,100,stopwatch},
        [5]={ReadSwitch_fun,85,ReadSwitch},
        [6]={ updateSwitch_fun,85,updateSwitch}
       

      

       

    
};