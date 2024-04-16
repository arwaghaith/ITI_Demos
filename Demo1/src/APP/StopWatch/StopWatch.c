/**
* 
* @file    : StopWatch Module Source File (App)
* @author  : Alaa Ghita
* @date    : April 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
<<<<<<< HEAD
#include "StopWatch.h"
#include "Typedefs.h"
#include "DEMO1_Data_cfg.h"
=======
#include "STOPWATCH/StopWatch.h"
>>>>>>> f23f54b52c6a2d91877f8d933b7f13ed4e02bf8f

/********************************************************************************************************/



/************************************************Defines*************************************************/
/********************************************************************************************************/



/************************************************Types***************************************************/
/********************************************************************************************************/



/************************************************Variables***********************************************/
volatile Time_t StopWatch;
volatile StopWatch_Control_t SWcontrol = SWcontrol_StopSignal;
extern uint8_t  Received_SW_Pressed_ID;
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
//static uint32_t counter = 0;
    //counter ++;
    //if(counter % 2 == 0)
    //{
/*This runnable comes every 100ms*/
void StopWatch_Runnable(void)
{
        static StopWatch_State_t SW_State = SWstate_Initial;
        static StopWatch_State_t SW_PREV_STATE    = SWstate_Initial;


        switch(SW_State)
        {
            case(SWstate_Initial):
            {
                StopWatch.Hours = 0;
                StopWatch.Min = 0;
                StopWatch.Sec = 0;
                StopWatch._100ms = 0;
                
                if ((Received_SW_Pressed_ID == SW_Start_Stop ))
                {
                    SW_PREV_STATE = SWstate_Initial ;
                    SW_State      = SWstate_Running  ;
                }
                

            } break;

            case(SWstate_Running):
            {
                SW_FLAG = 2;
                StopWatch._100ms++;
                if(StopWatch._100ms >= 10)
                {
                    StopWatch.Sec++;
                    StopWatch._100ms = 0;
                }
                if(StopWatch.Sec >= 60)
                {
                    StopWatch.Min++;
                    StopWatch.Sec = 0;
                }
                if(StopWatch.Min >= 60)
                {
                    StopWatch.Hours++;
                    StopWatch.Min = 0;
                }
                if(StopWatch.Hours >= 24)
                {
                    StopWatch._100ms = 0;
                    StopWatch.Sec = 0;
                    StopWatch.Min = 0;
                    StopWatch.Hours = 0;
                }
                if( Received_SW_Pressed_ID == SW_Start_Stop ) 
                {
                    SW_PREV_STATE = SWstate_Running ;
                    SW_State      = SWstate_Initial;
                }
                else if ( Received_SW_Pressed_ID == SW_Pause_Continue  ) 
                {
                    SW_PREV_STATE = SWstate_Running ;
                    SW_State      = SWstate_Paused;
                }
  

            } break;
            case(SWstate_Paused):
            {
               

                if(Received_SW_Pressed_ID == SW_Pause_Continue  )
                {
                    SW_PREV_STATE = SWstate_Paused ;
                    SW_State      = SWstate_Running;
                }
                else if (Received_SW_Pressed_ID == SW_Start_Stop  )
                {
                    SW_PREV_STATE = SWstate_Paused ;
                    SW_State      = SWstate_Initial;
                }

            } break;
            default:
                /*Do Nothing*/
                break;
        }
    //}
}
/********************************************************************************************************/