#include "../LIB/STD_TYPES.h"
#include "../MCAL/RCC/RCC.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/NVIC/NVIC.h"
#include "../HAL/LED/LED.h"
#include "../HAL/HSWITCH/HSWITCH.h"

uint8_t green_switch_flag=0;
uint8_t red_switch_flag=0;
void LED_SWITCH_INIT()

{

LED_Init();
Switch_Init();

}


void LED_SWITCH_Task()
{
    volatile uint32_t RED_State_ON=SWITCH_RELEASED;
    volatile uint32_t RED_State_OFF=SWITCH_RELEASED;
    volatile uint32_t GREEN_State_ON=SWITCH_RELEASED;
    volatile uint32_t GREEN_State_OFF=SWITCH_RELEASED;

    Switch_GetState(SWITCH_RED_LED_ON,&RED_State_ON);
    Switch_GetState(SWITCH_RED_LED_OFF,&RED_State_OFF);
    Switch_GetState(SWITCH_GREEN_LED_ON,&GREEN_State_ON);
    Switch_GetState(SWITCH_GREEN_LED_OFF,&GREEN_State_OFF);
    if(RED_State_ON==SWITCH_PRESSED)
    {

        LED_SetState(LED_RED,LED_ON);

        red_switch_flag=1;
    }
    else if(RED_State_OFF==SWITCH_PRESSED)
    {
        LED_SetState(LED_RED,LED_OFF);

        red_switch_flag=0;
    }


    else if(GREEN_State_ON==SWITCH_PRESSED)
    {
        LED_SetState(LED_GREEN,LED_ON);

        green_switch_flag=1;
    }
    else if(GREEN_State_OFF==SWITCH_PRESSED)
    {
        LED_SetState(LED_GREEN,LED_OFF);
        green_switch_flag=0;
    }
    else
    {
        /*Do nothing*/
    }
    







}