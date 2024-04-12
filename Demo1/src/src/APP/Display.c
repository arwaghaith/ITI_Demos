#include "../HAL/LCD/LCD.h"
#include "../LIB/STD_TYPES.h"


#define  CLOCK     0
#define  STOPWATCH 1


uint8_t MODE=CLOCK;


uint8_t stopWtach_arr[]=

{



};




void Display()


{

    switch(MODE)

    {





        case CLOCK:

        {

             uint8_t str[16];
             str[0]='D';
             str[1]='a';
             str[2]='t';
             str[3]='e';
             str[4]=':';
             str[5]=vu



           LCD_Write_String_POS_ASYNC(, 16, 1, 0)



    }

    









}