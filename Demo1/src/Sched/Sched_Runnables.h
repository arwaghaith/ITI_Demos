#ifndef SCHED_RUNNABLES_H
#define SCHED_RUNNABLES_H

#include "../LIB/STD_TYPES.h"
 

 typedef enum {
  Switch_GetInstant_fun,
  LCD_TASK_fun,
  Display_fun,
  CLOCK_fun,
stopwatch_fun,
ReadSwitch_fun,
updateSwitch_fun,
       MAX_RUNNABLES
 }RunnableID_t;
 typedef void (*RunnableCB_t)(void);
 typedef struct {

    RunnableID_t name;
    uint32_t periodicity_ms;
      RunnableCB_t CB;

 }Runnables_t;

 #endif




    

