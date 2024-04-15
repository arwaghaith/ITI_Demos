/**
* 
* @file    : Display Module Source File (App)
* @author  : Alaa Ghita
* @date    : April 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
#include "Display.h"
#include "LCD.h"
#include "Clock.h"
#include "StopWatch.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
/********************************************************************************************************/



/************************************************Types***************************************************/
/********************************************************************************************************/



/************************************************Variables***********************************************/
extern volatile Time_t Clock;
extern volatile Date_t Date;
extern volatile Time_t StopWatch;
extern volatile EditState_t Edit_State = EditState_Done;
extern volatile EditControl_t Edit_Signal = EditControl_NoSignal;
extern volatile uint8_t Edit_Position = 1; 
volatile DispalyMode_t DisplayMode = Clock_Mode;
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
void Display_Init(void)
{
    LCD_InitAsynch();
    LCD_HideCursorAsynch(NULL);
}

void Display_Num(uint32_t num)
{
	uint32_t temp =  num;
	uint32_t NumOfDigits = 1, Digit = 0;
	while (temp >= 10) {
		temp /= 10;
		NumOfDigits *= 10;
	}
	while(NumOfDigits)
	{
		Digit = num / NumOfDigits;
		LCD_WriteDataAsynch(Digit+48,NULL);
		num = num%NumOfDigits;
		NumOfDigits /= 10;
	}
	
}

/*This Runnable should come every: 4*Number of requstes made to the LCD (at least!!!!!!)*/
 /*Comes every 85ms تقريباً*/
void Display_Runnable(void)
{
    LCD_ClearScreanAsynch(NULL);
    if(DisplayMode == Clock_Mode)
    {
        LCD_SetcursorAsynch(0,0,NULL);
        LCD_WriteStringAsynch("Date:",5,NULL);
        Display_Num(Date.Days);
        LCD_WriteDataAsynch(":",NULL);
        Display_Num(Date.Months);
        LCD_WriteDataAsynch(":",NULL);
        Display_Num(Date.Years);    
        
        LCD_SetcursorAsynch(1,0,NULL);
        LCD_WriteStringAsynch("Time:",5,NULL);
        Display_Num(Clock.Hours);
        LCD_WriteDataAsynch(":",NULL);
        Display_Num(Clock.Min);
        LCD_WriteDataAsynch(":",NULL);
        Display_Num(Clock.Sec);

        if(Edit_State == EditState_Editing)
        {
            switch(Edit_Position)
            {
                case 1:
                    LCD_SetcursorAsynch(0,6,NULL);
                    LCD_DisplayCursorAsynch(NULL);
                    break;
                case 2:
                    LCD_SetCursorAsynch(0,9,NULL);
                    LCD_DisplayCursorAsynch(NULL);
                    break;
                case 3:
                    LCD_SetcursorAsynch(0,14,NULL);
                    LCD_DisplayCursorAsynch(NULL);
                    break;
                case 4:
                    LCD_SetcursorAsynch(1,6,NULL);
                    LCD_DisplayCursorAsynch(NULL);
                    break;
                case 5:
                    LCD_SetcursorAsynch(1,9,NULL);
                    LCD_DisplayCursorAsynch(NULL);
                    break;
                case 6:
                    LCD_SetcursorAsynch(1,12,NULL);
                    LCD_DisplayCursorAsynch(NULL);
                    break;
                default:
                    break;
            }
        }
        else
        {
            LCD_HideCursorAsynch(NULL);
        }
    }
    else if(DisplayMode == StopWatch_Mode)
    {
        LCD_SetcursorAsynch(0,0,NULL);
        LCD_WriteStringAsynch("StopWatch",9,NULL);

        LCD_SetcursorAsynch(1,0,NULL);
        Display_Num(Clock.Hours);
        LCD_WriteDataAsynch(":",NULL);    
        Display_Num(Clock.Min);
        LCD_WriteDataAsynch(":",NULL);
        Display_Num(Clock.Sec);
        LCD_WriteDataAsynch(":",NULL);
        Display_Num(Clock._100ms);
    }

}

/*
__________________
|Date:00/00/0000 |
|Time:00:00:00   |
|_______________|
*/
/********************************************************************************************************/


