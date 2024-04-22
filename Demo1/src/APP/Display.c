

#include "../HAL/LCD/LCD.h"
#include "../LIB/STD_TYPES.h"
#include "DEMO.h"






extern Clk_t current_time;
extern Date_t current_date;
extern volatile stopwatch_time G_stopwatch_current_time;
extern volatile uint8_t buttonConditions;

volatile uint8_t DISPLAY_MODE;



void Display()


{
//will be externed from readswitch_app


static uint8_t loc_visit_counter=0;
static uint8_t row1[16];
static uint8_t row2[16];


   
    if (DISPLAY_MODE==CLOCK)
    {
    
     // 1- print the row1
     if (loc_visit_counter==0)
     {
     row1[0]='D';
     row1[1]='a';
     row1[2]='t';
     row1[3]='e';
     row1[4]=':';
     row1[5]=current_date.day/10+'0';
     row1[6]=current_date.day%10+'0';
     row1[7]='/';
     row1[8]=current_date.month/10+'0';
     row1[9]=current_date.month%10+'0';
     row1[10]='/';
     row1[11]=current_date.year/1000+'0';
     row1[12]=(current_date.year/100)%10+'0';
     row1[13]=(current_date.year/10)%10+'0';
     row1[14]=current_date.year%10+'0';
     row1[15]=' ';


     //2- printing the row2
     row2[0]='T';
     row2[1]='i';
     row2[2]='m';
     row2[3]='e';
     row2[4]=':';
     row2[5]=current_time.hours/10+'0';
     row2[6]=current_time.hours%10+'0';
     row2[7]=':';
     row2[8]=current_time.minutes/10+'0';
     row2[9]=current_time.minutes%10+'0';
     row2[10]=':';
     row2[11]=current_time.seconds/10+'0';
     row2[12]=current_time.seconds%10+'0';
     row2[13]=' ';
     row2[14]=' ';
     row2[15]=' ';



     

    clearScreenAsync();
     

    loc_visit_counter++;
     }

    else if (loc_visit_counter==1)
    {


        


    LCD_Write_String_POS_ASYNC(row1, 16, 1, 0);
    loc_visit_counter++;

    }

    else if (loc_visit_counter==2)
    {
        
    LCD_Write_String_POS_ASYNC(row2, 16, 2, 0);
    loc_visit_counter++;
    }

    else 

            { loc_visit_counter=0;

            }
    }
            
       // Add a closing brace here

 else if (DISPLAY_MODE==STOPWATCH)
 
  {
  
     // 1- print the row1
     if (loc_visit_counter==0)
     {
    row1[0]=' ';
        row1[1]=' ';
    row1[2]=' ';
    row1[3]='S';

     row1[4]='T';
     row1[5]='O';
     row1[6]='P';
     row1[3]='S';
     row1[4]='T';
     row1[5]='O';
     row1[6]='P';
     row1[7]='W';
     row1[8]='A';
     row1[9]='T';
     row1[10]='C';
     row1[11]='H';
     row1[12]=' ';
     row1[13]=' ';
     row1[14]=' ';
     row1[15]=' ';

   
   


     //2- printing the row2
          row2[0]=' ';
          row2[1]='S';

     row2[2]=G_stopwatch_current_time.hours/10+'0';
     row2[3]=G_stopwatch_current_time.hours%10+'0';
     row2[4]=':';
     row2[5]=G_stopwatch_current_time.minutes/10+'0';
     row2[6]=G_stopwatch_current_time.minutes%10+'0';
     row2[7]=':';
     row2[8]=G_stopwatch_current_time.seconds/10+'0';
     row2[9]=G_stopwatch_current_time.seconds%10+'0';
     row2[10]=':';
     row2[11]=G_stopwatch_current_time.milliseconds/100+'0';
     row2[12]=(G_stopwatch_current_time.milliseconds%100)/10+'0';
     row2[13]=G_stopwatch_current_time.milliseconds%10+'0';
   
     row2[14] = ' ';  // units place 
     row2[15] = ' ';

     

    clearScreenAsync();
     

    loc_visit_counter++;
     }

    else if (loc_visit_counter==1)
    {


        


    LCD_Write_String_POS_ASYNC(row1, 16, 1, 0);
    loc_visit_counter++;

    }

    else if (loc_visit_counter==2)
    {
        
    LCD_Write_String_POS_ASYNC(row2, 16, 2, 0);
    loc_visit_counter++;
    }

    else 

            { loc_visit_counter=0;

            }
    }


}
            
    



    








