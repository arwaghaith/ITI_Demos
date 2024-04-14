/**
* 
* @file    : Clock Module Source File (App)
* @author  : Alaa Ghita & Nour Abdelaziz
* @date    : April 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
 #include "Clock.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
/********************************************************************************************************/



/************************************************Types***************************************************/
/********************************************************************************************************/



/************************************************Variables***********************************************/
volatile Time_t Clock;
volatile Date_t Date = {17, 4, 2024};
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
/*Should come every 500ms*/
void Clock_Runnable(void)
{
    static uint32_t counter;
    counter++;
    if(counter % 2 == 0)
    {
        Clock.Sec++;
        if(Clock.Sec == 60)
        {
            Clock.Min++;
            Clock.Sec = 0;
        }
        if(Clock.Min == 60)
        {
            Clock.Hours++;
            Clock.Min = 0;
        }
        if(Clock.Hours == 24)
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
    }
}

/********************************************************************************************************/


