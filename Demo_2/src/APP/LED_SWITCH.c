#include "../LIB/STD_TYPES.h"
#include "../MCAL/RCC/RCC.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/NVIC/NVIC.h"
#include "../HAL/LED/LED.h"
#include "../HAL/HSWITCH/HSWITCH.h"


void LED_SWITCH_INIT()

{

LED_Init();
Switch_Init();

}


void LED_SWITCH_Task()
{

    
    if(SWITCH_RED_LED_ON==SWITCH_PRESSED)
    {

        LED_SetState(LED_RED,LED_ON);
    }
    else if(SWITCH_RED_LED_OFF==SWITCH_PRESSED)
    {
        LED_SetState(LED_RED,LED_OFF);
    }


    else if(SWITCH_GREEN_LED_ON==SWITCH_PRESSED)
    {
        LED_SetState(LED_GREEN,LED_ON);
    }
    else if(SWITCH_GREEN_LED_OFF==SWITCH_PRESSED)
    {
        LED_SetState(LED_GREEN,LED_OFF);
    }
    else
    {
        /*Do nothing*/
    }
    







}