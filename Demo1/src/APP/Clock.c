#include"DEMO.h"
#include "../HAL/HSWITCH/HSWITCH.h"





#define start_Edit_pos_inLCD     4 
#define hr_pos                   5
#define min_pos                  8
#define sec_pos                  11
#define day_pos                  5
#define month_pos                8
#define year_pos                 11

#define first_line               0
#define Sec_line                 1


#define pressed                   0
#define NotPressed                1



uint8_t arr[9]= {1,1,0,1,0,1,0,1,};

Clk_t current_time = {0, 0, 0};
Date_t current_date = {11, 4, 2024};

uint8_t isLeapYear(uint16_t year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}


uint8_t daysInMonth(uint8_t month, uint16_t year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;  // Error case
    }
}

static void updateDate() {
    // Increment day and check for month 
    current_date.day++;
    if (current_date.day > (daysInMonth(current_date.month, current_date.year))) {
        current_date.day = 1;
        if (current_date.month > 12) {
            current_date.month = 1;
            current_date.year++;
        }
    }
}

void Clock(void) {

    uint8_t current_X = 0; // rows
    uint8_t Current_Y = start_Edit_pos_inLCD  ; // cols  start 4 :

    uint8_t current_edit_position = hr_pos ; 


if (arr[MODE] == 1) { //default mode 


      current_time.seconds++;
    if (current_time.seconds == 60) {
        current_time.seconds = 0;
        current_time.minutes++;
    }
    if (current_time.minutes == 60) {
        current_time.minutes = 0;
        current_time.hours++;
    }
    if (current_time.hours == 24) 
    {
        current_time.hours = 0;
        current_date.day++;
        int daysInCurrMonth = daysInMonth(current_date.month, current_date.year);
        // Check if the current day exceeds the maximum days in the current month
        if (current_date.day >= daysInCurrMonth) 
        {
            // Move to the next month
            current_date.day = 1;
            current_date.month++;

            // If the month exceeds 12, reset to 1 and increment the year
            if (current_date.month > 12) 
            {
                current_date.month = 1;
                current_date.year++;
            }
         
        }
    
    }

        
     if (arr[EDIT] == 0)
      { //edit mode 
           LCD_SET_CURSOR_POS_ASYNC(1, Current_Y); // sec row "the clock"  hours / min / sec 
           
           if(arr[RIGHT] ==0){
             LCD_SET_CURSOR_POS_ASYNC(1, Current_Y+1); 
             //current_edit_position++;
           }
           if(arr[LEFT] ==0)
           {
              LCD_SET_CURSOR_POS_ASYNC(1, Current_Y-1);
              current_edit_position--;
           }
            if (arr[UP] == 0) { // UP button pressed
                if (current_edit_position ==  hr_pos) { // Editing hours
                    current_time.hours = (current_time.hours + 1) % 24; // Increment hours, looping from 23 to 0
                    if(current_time.hours ==0 )
                    {
                        updateDate();
                    }
                } else if (current_edit_position ==min_pos) { // Editing minutes
                    current_time.minutes = (current_time.minutes + 1) % 60; // Increment minutes, looping from 59 to 0
                } else if (current_edit_position == sec_pos) { // Editing seconds
                    current_time.seconds = (current_time.seconds + 1) % 60; // Increment seconds, looping from 59 to 0
                }
            } else if (arr[DOWN] == 0) { // DOWN button pressed
                if (current_edit_position ==  hr_pos) { // Editing hours
                    current_time.hours = (current_time.hours - 1 + 24) % 24; // Decrement hours, looping from 0 to 23
                    if(current_time.hours == 0){updateDate();}
                } else if (current_edit_position == min_pos) { // Editing minutes
                    current_time.minutes = (current_time.minutes - 1 + 60) % 60; // Decrement minutes, looping from 0 to 59
                } else if (current_edit_position == sec_pos) { // Editing seconds
                    current_time.seconds = (current_time.seconds - 1 + 60) % 60; // Decrement seconds, looping from 0 to 59
                }
            }
        }

     
}

else 
    {
        return;
    }


}


