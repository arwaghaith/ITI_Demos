#include "../HAL/LCD/LCD.h"
#include "../LIB/STD_TYPES.h"
#include "../HAL/HSWITCH/HSWITCH.h"
#include  "DEMO.h"
extern uint8_t DISPLAY_MODE;


stopwatch_time G_stopwatch_current_time=

{
0,0,0,0
};
volatile static uint16_t readSwitches_Buffer=1;

uint8_t start_flag=0;
uint8_t stop_flag=1;
uint8_t pause_flag=0;
uint8_t continue_flag=0;







void stopwatch()


{






    #if DISPLAY_MODE== STOPWATCH


    if(readSwitches_Buffer &(1<<START_STOP))
    {
    start_flag^=1;
      stop_flag^=1;;
       
    }

    else if(readSwitches_Buffer &(1<<PAUSE_CONT))

    {
        pause_flag!=pause_flag;
        continue_flag!=continue_flag;


    }

    else if(readSwitches_Buffer &(1<<MODE))
    



    {

        G_stopwatch_current_time.hours=0;
        G_stopwatch_current_time.minutes=0;
        G_stopwatch_current_time.seconds=0;
        G_stopwatch_current_time.milliseconds=0;
        start_flag=0;
        stop_flag=0;
        pause_flag=0;
        continue_flag=0;

        DISPLAY_MODE!=DISPLAY_MODE;
        return;
    }
    





    if(start_flag==1  ||continue_flag==1)
    {
        G_stopwatch_current_time.milliseconds+=100;
    }

    else if (stop_flag ==1)
    {
        G_stopwatch_current_time.milliseconds=0;
        G_stopwatch_current_time.seconds=0;
        G_stopwatch_current_time.minutes=0;
        G_stopwatch_current_time.hours=0;
        
    }

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

   

    

  

#endif



}