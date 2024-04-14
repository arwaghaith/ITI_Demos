

/************************************************Includes************************************************/
#include "StopWatch.h"

/********************************************************************************************************/



/************************************************Defines*************************************************/
/********************************************************************************************************/



/************************************************Types***************************************************/
/********************************************************************************************************/



/************************************************Variables***********************************************/
volatile Time_t StopWatch;
volatile StopWatch_Control_t SWcontrol = SWcontrol_StopSignal;
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/

/*This runnable comes every 50ms*/
void StopWatch_Runnable(void)
{
    static StopWatch_State_t SW_State = SWstate_Initial;
    static uint32_t counter = 0;
    counter ++;
    if(counter % 2 == 0)
    {
        switch(SW_State)
        {
            case(SWstate_Initial):
                StopWatch.Hours = 0;
                StopWatch.Min = 0;
                StopWatch.Sec = 0;
                StopWatch._100ms = 0;
                if(SWcontrol == SWcontrol_StartSignal)
                {
                    SW_State = SWstate_Running;
                }
                break;
            case(SWstate_Running):
                StopWatch._100ms++;
                if(StopWatch._100ms == 10)
                {
                    StopWatch.Sec++;
                    StopWatch._100ms = 0;
                }
                if(StopWatch.Sec == 60)
                {
                    StopWatch.Min++;
                    StopWatch.Sec = 0;
                }
                if(StopWatch.Min == 60)
                {
                    StopWatch.Hours++;
                    StopWatch.Min = 0;
                }
                if(StopWatch.Hours == 24)
                {
                    StopWatch._100ms = 0;
                    StopWatch.Sec = 0;
                    StopWatch.Min = 0;
                    StopWatch.Hours = 0;
                }
                if(SWcontrol == SWcontrol_PauseSignal)
                {
                    SW_State = SWstate_Paused;
                }
                else if(SWcontrol == SWcontrol_StopSignal)
                {
                    SW_State = SWstate_Initial;
                }
                break;
            case(SWstate_Paused):
                /*Do Nothing*/
                if(SWcontrol == SWcontrol_ContinueSignal)
                {
                    SW_State = SWstate_Running;
                }
                else if(SWcontrol == SWcontrol_StopSignal)
                {
                    SW_State = SWstate_Initial;
                }
                break;
            default:
                /*Do Nothing*/
                break;
        }
    }
}
/********************************************************************************************************/


