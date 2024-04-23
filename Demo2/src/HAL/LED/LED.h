#ifndef LED_H
#define LED_H

#include "../../LIB/STD_TYPES.h"
#include "LEDcfg.h"

typedef enum
{
    LED_NOK,
    LED_OK,
}LED_Error_Status;




/* 
   This function is used to initialize the LEDs used
    * Inputs: void
    * Outputs: Error_Status
*/


LED_Error_Status LED_Init(void);

/* 
   This function is used to set the state of the LED
    * Inputs: LED_t led,uint32_t state
    * Outputs: Error_Status
*/
LED_Error_Status LED_SetState(LED_NAME led,uint32_t state);

/* 
   This function is used to get the state of the LED
    * Inputs: LED_t led,uint32_t *state
    * Outputs: Error_Status
*/
LED_Error_Status LED_getState(LED_NAME led,uint32_t *state);


void Toggle_LED(LED_NAME led);

#endif
