#include "../HAL/LCD/LCD.h"
#include "../LIB/STD_TYPES.h"
#include "../HAL/HSWITCH/HSWITCH.h"

extern uint8_t MODE;
 typedef struct 


{

    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t milliseconds;

}stopwatch_time;

G_stopwatch_time=

{

    0,0,0,0
};
uint16_t readSwitches_Buffer=0;

uint8_t start_flag=0;
uint8_t stop_flag=0;
uint8_t pause_flag=0;
uint8_t continue_flag=0;







void stopwatch()


{




    #if MODE== STOPWATCH

    if(readSwitches_Buffer &(1<<START_STOP))
    {
      start_flag!=start_flag;
      stop_flag!=stop_flag;

       
    }

    else if(readSwitches_Buffer &(1<<PAUSE_CONT))

    {
        pause_flag!=pause_flag;
        continue_flag!=continue_flag;


    }

    else if(readSwitches_Buffer &(1<<MODE))
    



    {

        G_stopwatch_time.hours=0;
        G_stopwatch_time.minutes=0;
        G_stopwatch_time.seconds=0;
        G_stopwatch_time.milliseconds=0;
        start_flag=0;
        stop_flag=0;
        pause_flag=0;
        continue_flag=0;

        MODE!=MODE;
        return;
    }
    





    if(start_flag==1  ||continue_flag==1)
    {
        G_stopwatch_time.milliseconds++;
    }

    if(G_stopwatch_time.milliseconds==1000)
    {
        G_stopwatch_time.milliseconds=0;
        G_stopwatch_time.seconds++;
    }

    if(G_stopwatch_time.seconds==60)
    {
        G_stopwatch_time.seconds=0;
        G_stopwatch_time.minutes++;
    }

    if(G_stopwatch_time.minutes==60)
    {
        G_stopwatch_time.minutes=0;
        G_stopwatch_time.hours++;
    }

   

    

    #endif



}