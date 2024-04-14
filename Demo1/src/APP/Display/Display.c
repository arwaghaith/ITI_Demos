

/************************************************Includes************************************************/
#include "Display.h"
#include "LCD.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
/********************************************************************************************************/



/************************************************Types***************************************************/
/********************************************************************************************************/



/************************************************Variables***********************************************/
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/

extern volatile Time_t Clock;
extern volatile Date_t Date;
extern volatile Time_t StopWatch; 
volatile DispalyMode_t DisplayMode = Clock_Mode;

/*This Runnable should come every: 4*Number of requstes made to the LCD (at least!!!!!!)*/
 /*Comes every 85ms تقريباً*/
void Display_Num(uint32_t num)
{
	uint32_t temp =  num;
	uint32_t NumOfDigits = 1, Digit = 0;
	char ToDisplay = 0;
	while (temp >= 10) {
		temp /= 10;
		NumOfDigits *= 10;
	}
	while(NumOfDigits)
	{
		Digit = num / NumOfDigits;
		ToDisplay = Digit+48;
		LCD_WriteDataAsynch(&ToDisplay,0);
		num = num%NumOfDigits;
		NumOfDigits /= 10;
	}
	
}

void Display_Runnable(void)
{
    LCD_ClearScreanAsynch(0);
    if(DisplayMode == Clock_Mode)
    {
        LCD_SetcursorAsynch(0,0,0);
        LCD_WriteStringAsynch("Date:",5,0);
        Display_Num(Date.Days);
        LCD_WriteStringAsynch(":",1,0);
        Display_Num(Date.Months);
        LCD_WriteStringAsynch(":",1,0);
        Display_Num(Date.Years);    
        
        LCD_SetcursorAsynch(0,1,0);
        LCD_WriteStringAsynch("Time:",5,0);
        Display_Num(Clock.Hours);
        LCD_WriteStringAsynch(":",1,0);
        Display_Num(Clock.Min);
        LCD_WriteStringAsynch(":",1,0);
        Display_Num(Clock.Sec);
    }
    else if(DisplayMode == StopWatch_Mode)
    {
        LCD_SetcursorAsynch(0,0,0);
        LCD_WriteStringAsynch("StopWatch",9,0);

        LCD_SetcursorAsynch(0,1,0);
        Display_Num(Clock.Hours);
        LCD_WriteStringAsynch(":",1,0);
        Display_Num(Clock.Min);
        LCD_WriteStringAsynch(":",1,0);
        Display_Num(Clock.Sec);
        LCD_WriteStringAsynch(":",1,0);
        Display_Num(Clock._100ms);
    }
}
/********************************************************************************************************/


