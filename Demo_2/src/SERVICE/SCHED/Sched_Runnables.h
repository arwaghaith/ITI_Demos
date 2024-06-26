#ifndef SCHED_RUNNABLES_H
#define SCHED_RUNNABLES_H

#include "../../LIB/STD_TYPES.h"
 

 typedef enum {
     switches,
     LED_SWITCH_UPDATE_fun,
     BUTTON_PRESS_fun,
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




    


