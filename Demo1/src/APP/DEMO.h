#ifndef APP__DEMO_H_
#define APP__DEMO_H_


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "LIB/STD_TYPES.h"
#include"LIB/Error_Status.h"
#include"HAL/LCD/LCD.h"
#include"HAL/HSWITCH/HSWITCH.h"
#include"MCAL/UART/UART.h"
#include"MCAL/RCC/RCC.h"
#include"MCAL/GPIO/GPIO.h"
#include"MCAL/NVIC/NVIC.h"

#define CHECKSUM   10

#define  CLOCK     1
#define  STOPWATCH 0
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
    uint16_t year;

 }Date_t;

  typedef struct 


{

    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t milliseconds;

}stopwatch_time;
typedef enum
{
    SWstate_Initial,
    SWstate_Running,
    SWstate_Paused

}StopWatch_State_t;

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

void Clock(void);
void Display (void);
void ReadSwitch(void);
#endif // APP__DEMO_H_