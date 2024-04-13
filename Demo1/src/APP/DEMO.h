#ifndef APP__DEMO_H_
#define APP__DEMO_H_


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include"../LIB/STD_TYPES.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
 typedef struct
 {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;

 }Clk_t;
 
 
  typedef struct
 {
    uint8_t day;
    uint8_t month;
    uint8_t year;

 }Date_t;

  typedef struct 


{

    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t milliseconds;

}stopwatch_time;


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

void Clock(void);
void Display (void);
void ReadSwitch(void);
#endif // APP__DEMO_H_