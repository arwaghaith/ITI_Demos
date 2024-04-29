

#include "Sched_Runnables.h"
#include "../../HAL/LED/LED.h"




extern void Switch_GetInstant(void);
extern void LCD_TASK();

extern void  LED_SWITCH_Task();

extern void UART_SEND_STATE(void);


const Runnables_t sys_Runnables[MAX_RUNNABLES]

={

         [0]={switches,5,0,Switch_GetInstant},
         [1]={ LED_SWITCH_UPDATE_fun,10,0,LED_SWITCH_Task},
         [2]={BUTTON_PRESS_fun,1000,0,UART_SEND_STATE}
         
     

       

    
};