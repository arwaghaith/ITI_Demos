




#include "../../LIB/STD_TYPES.h"
#include "HSWITCH_cfg.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "HSWITCH.h"
/*               Switch Functions                */
/*               Switch_Init                */
/*Description: This Function is used to initialize the switch
 * Input: void
 * Output: ErrorStatus
 */

extern Switch_t Switches[Switch_NUM];
Switch_ErrorStatus Switch_Init(void)

{
    Switch_ErrorStatus local_Error_status = SWITCH_NOK;
    GPIO_PIN_t Switch_PIN;
    for(uint32_t i=0;i<Switch_NUM;i++)
    {
        Switch_PIN.port=Switches[i].Switch_Port;
        Switch_PIN.pin=Switches[i].Switch_Pin;
        Switch_PIN.mode=GPIO_MODE_INPUT;
        Switch_PIN.speed=GPIO_SPEED_HIGH;
        Switch_PIN.pull=Switches[i].Switch_Mode+SWITCH_PULL_OFFSET;
        Switch_PIN.value=Switches[i].Switch_State^Switches[i].Switch_State;

        local_Error_status=GPIO_Init(&Switch_PIN);

    }

    return local_Error_status;
}

        

/*               Switch_SetState                */
/*Description: This Function is used to set the state of the switch
 * Input: Channel, State
 * Output: ErrorStatus
 */



/*               Switch_GetState                */
/*Description: This Function is used to get the state of the switch
 * Input: Channel, State
 * Output: ErrorStatus
 */




void Switch_GetInstant(void)

{


   uint8_t idx=0;
   volatile  uint32_t State;

   for(idx=0;idx<Switch_NUM;idx++)
   {
       

   GPIO_GET_PIN_VALUE(Switches[idx].Switch_Port,Switches[idx].Switch_Pin,&State);
    Switches[idx].current= State;
   


   if(Switches[idx].current==Switches[idx].previous)
   {
    
    Switches[idx].counter_debounce++;
   }
   else
   {
       
    Switches[idx].counter_debounce=0;
   }

    if(Switches[idx].counter_debounce==(SWITCH_STABLE_STATE))
    {
        Switches[idx].Switch_State=Switches[idx].current;
     
     Switches[idx].counter_debounce=0;
    }

    Switches[idx].previous=Switches[idx].current;




}
}


Switch_ErrorStatus Switch_GetState(Switch_ChannelType Channel, uint32_t *State)
{

    *State=Switches[Channel].Switch_State;
}


