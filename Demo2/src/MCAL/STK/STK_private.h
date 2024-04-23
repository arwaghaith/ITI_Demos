#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H



#include "../../LIB/STD_TYPES.h"

/************************************************************************************************/

#define STK_BASE_ADDRESS  ((volatile uint32_t *)0xE000E010)

/******************************************** MASKS *********************************************/

#define  STK_CLK_MASK 0x00000004
#define  STK_TICKINT_MASK 0x00000002

#define STK_CLK_SHIFT 2

#define STK_INTERRUPT_ENABLE 0x00000002
#define STK_COUNTER_FLAG_MASK 0x00010000



typedef struct
{
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;

}STK_t;



#endif // STK_PRIVATE_H