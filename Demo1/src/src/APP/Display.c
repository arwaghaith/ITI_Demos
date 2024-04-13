#include "../HAL/LCD/LCD.h"
#include "../LIB/STD_TYPES.h"
#include "DEMO.h"


#define  CLOCK     0
#define  STOPWATCH 1


uint8_t DISPLAY_MODE=STOPWATCH;
extern Clk_t current_time;
extern Date_t current_date;
extern stopwatch_time G_stopwatch_current_time;





void Display()


{


static uint8_t loc_visit_counter=0;

   
    #if DISPLAY_MODE==CLOCK
     static uint8_t date[16];
     static uint8_t time[16];
     // 1- print the date
     if (loc_visit_counter==0)
     {
     date[0]='D';
     date[1]='a';
     date[2]='t';
     date[3]='e';
     date[4]=':';
     date[5]=current_date.day/10+'0';
     date[6]=current_date.day%10+'0';
     date[7]='/';
     date[8]=current_date.month/10+'0';
     date[9]=current_date.month%10+'0';
     date[10]='/';
     date[11]=current_date.year/1000+'0';
     date[12]=(current_date.year/100)%10+'0';
     date[13]=(current_date.year/10)%10+'0';
     date[14]=current_date.year%10+'0';
     date[15]='\0';


     //2- printing the time
     time[0]='T';
     time[1]='i';
     time[2]='m';
     time[3]='e';
     time[4]=':';
     time[5]=current_time.hours/10+'0';
     time[6]=current_time.hours%10+'0';
     time[7]=':';
     time[8]=current_time.minutes/10+'0';
     time[9]=current_time.minutes%10+'0';
     time[10]=':';
     time[11]=current_time.seconds/10+'0';
     time[12]=current_time.seconds%10+'0';
     time[13]='\0';



     

    clearScreenAsync();
     

    loc_visit_counter++;
     }

    else if (loc_visit_counter==1)
    {

            clearScreenAsync();

          loc_visit_counter++;

    }
    else if (loc_visit_counter==2  || loc_visit_counter==3)
    {
        




    LCD_Write_String_POS_ASYNC(date, 16, 1, 0);
    loc_visit_counter++;

    }

    else if (loc_visit_counter==4 || loc_visit_counter==5)
    {
        
    LCD_Write_String_POS_ASYNC(time, 16, 2, 0);
    loc_visit_counter++;
    }

    else 
                    loc_visit_counter=0;
       // Add a closing brace here

      #elif DISPLAY_MODE==STOPWATCH // Replace #else if with #elif

    uint8_t STOPWATCH="StopWatch";
    uint8_t time[16];
    // 1- print the Time
    time[0]= G_stopwatch_current_time.hours%10;
    time[1]= G_stopwatch_current_time.hours/10;
    time[2]=':';
    time[3]= G_stopwatch_current_time.minutes%10;
    time[4]= G_stopwatch_current_time.minutes/10;
    time[5]=':';
    time[6]= G_stopwatch_current_time.seconds%10;
    time[7]= G_stopwatch_current_time.seconds/10;
    time[8]=':';
    time[9]= G_stopwatch_current_time.milliseconds%10;
    time[10]= G_stopwatch_current_time.milliseconds/10;
    time[11]='\0';

     clearScreenAsync();
     

    loc_visit_counter++;
     }

    else if (loc_visit_counter==1)
    {

            clearScreenAsync();

          loc_visit_counter++;

    }
    else if (loc_visit_counter==2  || loc_visit_counter==3)
    {
        




    LCD_Write_String_POS_ASYNC(STOPWATCH, 16, 1, 0);
    loc_visit_counter++;

    }

    else if (loc_visit_counter==4 || loc_visit_counter==5)
    {
        
    LCD_Write_String_POS_ASYNC(time, 16, 2, 0);
    loc_visit_counter++;
    }

    else 
    {
          loc_visit_counter=0;

    }

    


    
       


    #endif
}


    









