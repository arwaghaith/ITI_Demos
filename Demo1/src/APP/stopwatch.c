
#include "../HAL/LCD/LCD.h"
#include "../LIB/STD_TYPES.h"
#include "../HAL/HSWITCH/HSWITCH.h"
#include  "DEMO.h"

extern volatile uint8_t DISPLAY_MODE ;
volatile StopWatch_State_t SW_State = SWstate_Running;


volatile stopwatch_time G_stopwatch_current_time=

{
0,0,0,0

};
extern volatile uint8_t buttonConditions;
void stopwatch()


{


volatile static StopWatch_State_t SW_State = SWstate_Running;


        switch(SW_State)
        {
            case(SWstate_Initial):
            
        G_stopwatch_current_time.milliseconds=0;
        G_stopwatch_current_time.seconds=0;
        G_stopwatch_current_time.minutes=0;
        G_stopwatch_current_time.hours=0;
        
                


                if( DISPLAY_MODE==STOPWATCH)
                {
                if ((buttonConditions &(1<<START_STOP) ))
                {
                    SW_State      = SWstate_Running  ;
                    buttonConditions=0;
                }
                }
                

             break;

            case(SWstate_Running):
            
                       G_stopwatch_current_time.milliseconds+=100;

               if(G_stopwatch_current_time.milliseconds==1000)
    {
        G_stopwatch_current_time.milliseconds=0;
        G_stopwatch_current_time.seconds++;
    }

    if(G_stopwatch_current_time.seconds==60)
    {
        G_stopwatch_current_time.seconds=0;
        G_stopwatch_current_time.minutes++;
    }

    if(G_stopwatch_current_time.minutes==60)
    {
        G_stopwatch_current_time.minutes=0;
        G_stopwatch_current_time.hours++;
    }

                if( DISPLAY_MODE==STOPWATCH)
                {
                if(buttonConditions &(1<<START_STOP)) 
                {
                    SW_State      = SWstate_Initial;
                                        buttonConditions=0;

                }
                
                else if ( buttonConditions &(1<<PAUSE_CONT)  ) 
                {
                    SW_State      = SWstate_Paused;
                                        buttonConditions=0;

                }
                }
  

             break;
            case(SWstate_Paused):
            
               
              if( DISPLAY_MODE==STOPWATCH)
                {
                if (buttonConditions &(1<<PAUSE_CONT) )
                {
                    SW_State      = SWstate_Running;
                                        buttonConditions=0;

                }
                else if(buttonConditions &(1<<START_STOP)) 
                {
                    SW_State      = SWstate_Initial;
                                        buttonConditions=0;

                }
                }

            break;
            default:
                /*Do Nothing*/
                break;

        }
}