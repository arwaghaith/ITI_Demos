#ifndef SCHED_RUNNABLES_H
#define SCHED_RUNNABLES_H

#include "LIB/STD_TYPES.h"
 

 typedef enum {

       LCD_APP_1,
       display_app,
       Clock_app,
       stopWatch_app,
       Switch_GetInstant_fun,
       updateSwitch_fun,
       readSwitch_fun,
       read_fun,
       Uart_app,
       MAX_RUNNABLES
       

 }RunnableID_t;
 
 typedef void (*RunnableCB_t)(void);
 typedef struct {

    RunnableID_t name;
    uint32_t periodicity_ms;
    uint32_t delay;
      RunnableCB_t CB;

 }Runnables_t;

 #endif




    


