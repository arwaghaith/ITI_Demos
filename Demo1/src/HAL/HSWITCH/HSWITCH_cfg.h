#ifndef HSWITCH_CFG_H
#define HSWITCH_CFG_H

#include  "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO.h"

/******************************************************/
/*               Switch Names                */
#define  Switch_NUM 8
typedef enum
{

  START_STOP ,
    PAUSE_CONT,
    EDIT ,
    MODE ,
    UP ,
    DOWN ,
    LEFT ,
    RIGHT 
}Switch_ChannelType;
/******************************************************/
/*               Switch Configuration                */
typedef struct 
{
     uint32_t Switch_Port;
    uint32_t Switch_Pin;
    uint32_t Switch_Mode;
    volatile uint32_t Switch_State;
    volatile uint32_t counter_debounce;
    volatile uint8_t current;
    volatile uint8_t previous;
    }Switch_t;

/******************************************************/
/*               Switch  Connection                */
#define  SWITCH_PULL_OFFSET  0x00000001
#define  SWITCH_PULLUP    0x00000000
#define  SWITCH_PULLDOWN  0x00000001
/******************************************************/
/*               Switch status                */

#define  SWITCH_PRESSED 0x00000000
#define  SWITCH_RELEASED  0x00000001
/******************************************************/

        


#endif
