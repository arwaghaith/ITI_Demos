/**
* 
* @file    : Display Module Source File (App)
* @author  : Alaa Ghita
* @date    : April 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
#include "DISPLAY/Display.h"
#include "LCD.h"
#include "CLOCK/Clock.h"
#include "STOPWATCH/StopWatch.h"
#include "HSwitch_cfg.h"
#include "HSwitch.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
/********************************************************************************************************/



/************************************************Types***************************************************/
typedef enum
{
	Display_Row1,
	Display_Row2
}DisplayState_t;
/********************************************************************************************************/



/************************************************Variables***********************************************/
extern volatile Time_t Clock;
extern volatile Date_t Date;
extern volatile Time_t StopWatch;
extern volatile EditState_t Edit_State;
extern uint8_t Received_SW_Pressed_ID;
extern volatile uint8_t Edit_Position;
volatile DispalyMode_t DisplayMode = Clock_Mode;
volatile DispalyMode_t Prev_DisplayMode;
static DisplayState_t Display_State = Display_Row1;
extern uint8_t Received_SW_Pressed_ID;
//static char * ClockString;
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
void Display_Init(void)
{
    LCD_InitAsynch();
    LCD_HideCursorAsynch(NULL);
}


 /*Comes every 85ms تقريباً*/
void Display_Runnable(void)
{

	enuHSwitchState_t var;
	HSwitch_GetStatus(SW_MODE,&var);
	if(var == enuHSwitch_Pressed)
	{
		DisplayMode = !DisplayMode;
	}
	/*if(Received_SW_Pressed_ID == SW_MODE)
	{
		DisplayMode = !DisplayMode;
	}*/

	if(DisplayMode != Prev_DisplayMode)
	{
    	LCD_ClearScreanAsynch(NULL);
	}

    if(DisplayMode == Clock_Mode)
    {
    	switch (Display_State)
    	{
    		case(Display_Row1):
    			LCD_SetCursorAsynch(ROW_1,COLUMN_1,NULL);
        		LCD_WriteStringAsynch("Date:",5,NULL);
        		LCD_WriteDataAsynch((Date.Days/10)+48,NULL);
        		LCD_WriteDataAsynch((Date.Days%10)+48,NULL);
        		LCD_WriteDataAsynch('/',NULL);
        		LCD_WriteDataAsynch((Date.Months/10)+48,NULL);
        		LCD_WriteDataAsynch((Date.Months%10)+48,NULL);
        		LCD_WriteDataAsynch('/',NULL);
        		LCD_WriteDataAsynch((Date.Years/1000)+48,NULL);
				LCD_WriteDataAsynch(((Date.Years%1000)/100)+48,NULL);
				LCD_WriteDataAsynch(((Date.Years%100)/10)+48,NULL);
        		LCD_WriteDataAsynch((Date.Years%10)+48,NULL);
        		Display_State = Display_Row2;
        		break;
    		case(Display_Row2):
				LCD_SetCursorAsynch(ROW_2,COLUMN_1,NULL);
    			LCD_WriteStringAsynch("Time:",5,NULL);
				LCD_WriteDataAsynch((Clock.Hours/10)+48,NULL);
		   		LCD_WriteDataAsynch((Clock.Hours%10)+48,NULL);
	 			LCD_WriteDataAsynch(':',NULL);
		    	LCD_WriteDataAsynch((Clock.Min/10)+48,NULL);
		    	LCD_WriteDataAsynch((Clock.Min%10)+48,NULL);
		    	LCD_WriteDataAsynch(':',NULL);
		    	LCD_WriteDataAsynch((Clock.Sec/10)+48,NULL);
		    	LCD_WriteDataAsynch((Clock.Sec%10)+48,NULL);
        		Display_State = Display_Row1;
        		break;
			if(Edit_State == EditState_Editing)
        {
            switch(Edit_Position)
            {
                case 1:
                    LCD_SetCursorAsynch(ROW_1,COLUMN_6,NULL);
					LCD_WriteDataAsynch(0xff,NULL);
					LCD_WriteDataAsynch(0xff,NULL);
                    break;
                case 2:
                    LCD_SetCursorAsynch(ROW_1,COLUMN_9,NULL);
                    LCD_WriteDataAsynch(0xff,NULL);
					LCD_WriteDataAsynch(0xff,NULL);
                    break;
                case 3:
                    LCD_SetCursorAsynch(ROW_1,COLUMN_14,NULL);
                    LCD_WriteDataAsynch(0xff,NULL);
					LCD_WriteDataAsynch(0xff,NULL);
                    break;
                case 4:
                    LCD_SetCursorAsynch(ROW_2,COLUMN_6,NULL);
                    LCD_WriteDataAsynch(0xff,NULL);
					LCD_WriteDataAsynch(0xff,NULL);
                    break;
                case 5:
                    LCD_SetCursorAsynch(1,COLUMN_9,NULL);
                    LCD_WriteDataAsynch(0xff,NULL);
					LCD_WriteDataAsynch(0xff,NULL);
                    break;
                case 6:
                    LCD_SetCursorAsynch(1,COLUMN_12,NULL);
                    LCD_WriteDataAsynch(0xff,NULL);
					LCD_WriteDataAsynch(0xff,NULL);
                    break;
                default:
                    break;
            }
    	}

        
        }
        /*else
        {
            LCD_HideCursorAsynch(NULL);
        }*/
    }
    else
    {
    	switch (Display_State)
    	{
    		case(Display_Row1):
        		LCD_SetCursorAsynch(ROW_1,COLUMN_1,NULL);
    			LCD_WriteStringAsynch("StopWatch",9,NULL);
    			Display_State = Display_Row2;
    			break;
    		case(Display_Row2):
        		LCD_SetCursorAsynch(ROW_2,COLUMN_1,NULL);
    			LCD_WriteDataAsynch((StopWatch.Hours/10)+48,NULL);
    			LCD_WriteDataAsynch((StopWatch.Hours%10)+48,NULL);
    			LCD_WriteDataAsynch(':',NULL);
    			LCD_WriteDataAsynch((StopWatch.Min/10)+48,NULL);
    			LCD_WriteDataAsynch((StopWatch.Min%10)+48,NULL);
    			LCD_WriteDataAsynch(':',NULL);
    			LCD_WriteDataAsynch((StopWatch.Sec/10)+48,NULL);
    			LCD_WriteDataAsynch((StopWatch.Sec%10)+48,NULL);
    			LCD_WriteDataAsynch(':',NULL);
    			LCD_WriteDataAsynch((StopWatch._100ms/10)+48,NULL);
    			LCD_WriteDataAsynch((StopWatch._100ms%10)+48,NULL);
    			Display_State = Display_Row1;
    			break;
			
    	}
    }
	Prev_DisplayMode = DisplayMode;
}

/*
------------------
|Date:00/00/0000 |
------------------
|Time:00:00:00   |
------------------
*/
/********************************************************************************************************/


