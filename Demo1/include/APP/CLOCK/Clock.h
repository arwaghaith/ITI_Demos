/**
* 
* @file    : Clock Module Header File (App)
* @author  : Alaa Ghita
* @date    : April 2024
* @version : 0.1v
* 
*/

#ifndef	 _CLOCK_H_
#define	 _CLOCK_H_

/************************************************Includes************************************************/
 #include "Typedefs.h"
 #include "ErrorStatus.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
/********************************************************************************************************/



/************************************************Types***************************************************/
typedef struct
{
	uint32_t Hours;
    uint32_t Min;
    uint32_t Sec;
    uint32_t _100ms;
}Time_t;

typedef struct
{
    uint32_t Days;
    uint32_t Months;
    uint32_t Years;
}Date_t;

typedef enum 
{
    EditState_Editing,
    EditState_Done,   /*When an OK signal comes to the MC the Edit_State will be updated to be EditState_Done*/
}EditState_t;

/*typedef enum
{
    EditControl_NoSignal,
    EditControl_IncreaseSignal,    */     /*When the Up arrow is pressed*/
    //EditControl_DecreaseSignal,         /*When the Down arrow is pressed*/
    /*EditControl_RightSignal,
    EditControl_LeftSignal
}EditControl_t;*/
/********************************************************************************************************/



/************************************************APIs****************************************************/
/********************************************************************************************************/




#endif /*_CLOCK_H_*/
