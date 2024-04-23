#ifndef LED_CFG_H
#define LED_CFG_H


#include "../../LIB/STD_TYPES.h"
#define LEDs_NUM 4
#define LED_OFF 0
#define LED_ON 1

typedef enum
{
   
    LED_RED,
    LED_BLUE,
    LED_yellow,
}LED_NAME;

typedef struct
{

    
    uint32_t port;
    uint32_t pin;
    uint32_t connection;
    uint32_t LED_STATE;
}LED_t;

/************************************************************************************************************************************/
/**************************************************     LED  connection *************************************************************/

#define LED_FORWARD 0
#define LED_REVERSE 1
/************************************************************************************************************************************/
/**************************************************     LED  state     *************************************************************/





#endif
