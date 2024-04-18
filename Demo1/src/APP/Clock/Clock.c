/**
* 
* @file    : Clock Module Source File (App)
* @author  : Alaa Ghita
* @date    : April 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
 #include "CLOCK/Clock.h"
 #include "HSwitch_cfg.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
/********************************************************************************************************/



/************************************************Types***************************************************/
/********************************************************************************************************/



/************************************************Variables***********************************************/
volatile Time_t Clock;
volatile Date_t Date = {17, 4, 2024};
volatile EditState_t Edit_State = EditState_Done;
//volatile EditControl_t Edit_Signal = EditControl_NoSignal;
volatile uint8_t Edit_Position = 1;
extern uint8_t Received_SW_Pressed_ID;
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
/*Should come every 500ms*/
/*NOTE: This Runnable should come when receiving a new signal from the uart to be able to serve that signal before it's changed by another signal*/
/*I think maybe 1 sec will be enough*/
void Clock_Runnable(void)
{
    //static uint32_t counter;
    //counter++;
    //if(counter % 2 == 0)
    //{
        /*Clock Editing Code*/
        switch(Received_SW_Pressed_ID)
        {
            case(SW_Edit):
                Edit_State = EditState_Editing;
                break;
            case(SW_OK):
                Edit_State = EditState_Done;
                break;
            default:
                break;
        }

        if(Edit_State == EditState_Editing)
        {
            switch(Received_SW_Pressed_ID)
            {
                case(SW_Up):
                    switch(Edit_Position)
                    {
                        case 1:
                            Date.Days++;
                            break;
                        case 2:
                            Date.Months++;
                            break;
                        case 3:
                            Date.Years++;
                            break;
                        case 4:
                            Clock.Hours++;
                            break;
                        case 5:
                            Clock.Min++;
                            break;
                        case 6:
                            Clock.Sec++;
                            break;
                        default:
                            break;
                    }
                    break;
                case(SW_Down):
                    switch(Edit_Position)
                    {
                        case 1:
                            if(Date.Days == 1)
                            {
                                Date.Days = 31;
                                Date.Months--;
                            }
                            else
                            {
                                Date.Days--;
                            }
                            break;
                        case 2:
                            if(Date.Months == 1)
                            {
                                Date.Months = 12;
                                Date.Years--;
                            }
                            else
                            {
                                Date.Months--;
                            }
                            break;
                        case 3:
                            if(Date.Years == 0)
                            {
                                Date.Years = 9999;
                            }
                            else
                            {
                                Date.Years--;
                            }
                            break;
                        case 4:
                            if(Clock.Hours == 0)
                            {
                                Clock.Hours = 23;
                                Date.Days--;
                            }
                            else
                            {
                                Clock.Hours--;
                            }
                            break;
                        case 5:
                            if(Clock.Min == 0)
                            {
                                Clock.Min = 59;
                                Clock.Hours--;
                            }
                            else
                            {
                                Clock.Min--;
                            }
                            break;
                        case 6:
                            if(Clock.Sec == 0)
                            {
                                Clock.Sec = 59;
                                Clock.Min--;
                            }
                            else
                            {
                                Clock.Sec--;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case(SW_Right):
                    if(Edit_Position < 6)
                    {
                        Edit_Position++;
                    }
                    else
                    {
                        Edit_Position = 1;    
                    }
                    break;
                case(SW_Left):
                    if(Edit_Position > 1)
                    {
                        Edit_Position--;
                    }
                    else
                    {
                        Edit_Position = 6;    
                    }
                    break;
                default:
                    break;
            }
        }
        else
        {
            //Edit_Signal = EditControl_NoSignal;
            Edit_Position = 1;
        }

        /*Clock Running Code*/
        Clock.Sec++;
        if(Clock.Sec >= 60)
        {
            Clock.Min++;
            Clock.Sec = 0;
        }
        if(Clock.Min >= 60)
        {
            Clock.Hours++;
            Clock.Min = 0;
        }
        if(Clock.Hours >= 24)
        {
            Date.Days++;
            Clock.Sec = 0;
            Clock.Min = 0;
            Clock.Hours = 0;
        }
        if(Date.Days >= 29)
        {
            if((Date.Months==4) || (Date.Months==6)
             ||(Date.Months==9) || (Date.Months==11))
            {
                if(Date.Days > 30)
                {
                    Date.Days = 1;
                    Date.Months++;
                }
            }
            else if((Date.Months==1) || (Date.Months==3)
                  ||(Date.Months==5) || (Date.Months==7)
                  ||(Date.Months==8) || (Date.Months==10)
                  ||(Date.Months==12))
            {
                if(Date.Days > 31)
                {
                    Date.Days = 1;
                    Date.Months++;
                }
            }
            else /*(Date.Months=2)*/
            {
                if((Date.Years%4)!=0)
                {
                    Date.Days = 1;
                    Date.Months++;
                }
                else
                {
                    if(Date.Days > 29)
                    {
                        Date.Days = 1;
                        Date.Months++;
                    }
                }
            }
        } 
        if(Date.Months > 12)
        {
            Date.Years++;
            Date.Months = 1;
        }
    //}
}

/*
------------------
|Date:00/00/0000 |
------------------
|Time:00:00:00   |
------------------
*/
/********************************************************************************************************/


