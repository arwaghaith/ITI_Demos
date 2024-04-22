

#include "Sched_Runnables.h"
#include "APP/DEMO.h"
#include "../HAL/HSWITCH/HSWITCH.h"



extern void Display();
extern void Clock();
extern void stopwatch();
extern void Switch_GetInstant();
extern void LCD_TASK();
extern void updateSwitch();
extern void  ReadSwitch(void);

void UART_init();





 Runnables_t sys_Runnables[MAX_RUNNABLES]

={


     [0]={LCD_APP_1,1,0,LCD_TASK},
     [1]={display_app,85,0,Display},
     [4]={ Clock_app,1000,0,Clock},
     [5]={ stopWatch_app,100,0,stopwatch},
     [2]={ Switch_GetInstant_fun,5,0,Switch_GetInstant},
    [6]={updateSwitch_fun,500,0,updateSwitch},
   [3]={read_fun,1000,0,ReadSwitch},
   // [7]={ Uart_app, 1000 , 0 ,UART_init}


    
};