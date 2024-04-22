

#include "STK_private.h"
#include  "STK.h"
#include "../../LIB/STD_TYPES.h"


volatile static STK_t * const STK = (STK_t *)STK_BASE_ADDRESS;
volatile static STK_MODE MODE = STK_SINGLE_INTERVAL;
typedef void (*STK_CallBack_t)(void);

static STK_CallBack_t STK_CallBack = NULL;

STK_status STK_Init(STK_CLK Copy_CLK, STK_MODE Copy_Mode,uint32_t Copy_Load, void (*Copy_Ptr)(void))

{
    volatile STK_status Local_Status = STK_OK;

    volatile uint32_t Local_CTRL =STK->CTRL;
    if (Copy_Load <= STK_LOAD_MAX_VAL)
    {
        Local_CTRL &= ~STK_CLK_MASK;
        Local_CTRL |= Copy_CLK;
        Local_CTRL|=STK_INTERRUPT_ENABLE;
        STK->CTRL=Local_CTRL;
       
        STK->LOAD = Copy_Load;
        STK_CallBack = Copy_Ptr;

        MODE = Copy_Mode;
    }
    else
    {
        Local_Status = STK_NOK;
    }

    return Local_Status;
}


STK_status STK_Start(void)
{
    STK_status Local_Status = STK_OK;
            STK->CTRL |=STK_ENABLE;


   
    return Local_Status;
}
  


STK_status STK_Stop(void)
{
    STK_status Local_Status = STK_OK;
    STK->CTRL &= ~STK_INTERRUPT_ENABLE;


    return Local_Status;
}

STK_status STK_SetCallBack(void (*Copy_Ptr)(void))
{
    STK_status Local_Status = STK_OK;
    STK_CallBack = Copy_Ptr;
    return Local_Status;
}

STK_status STK_SetTimeMS(uint32_t Copy_Time)
{
    STK_status Local_Status = STK_OK;
    if (Copy_Time <= STK_LOAD_MAX_VAL)
    {
        STK->LOAD = ((Copy_Time*SYS_CLK)/MS_TO_US/AHB_PRESCALER);
    }
    else
    {
        Local_Status = STK_NOK;
    }
    return Local_Status;
}

STK_status STK_SetCLK(STK_CLK Copy_CLK)

{
    STK_status Local_Status = STK_OK;
    STK->CTRL &= ~STK_CLK_MASK;
    STK->CTRL |= Copy_CLK;
    return Local_Status;
}

STK_status STK_SetMode(STK_MODE Copy_Mode)
{
    STK_status Local_Status = STK_OK;
    if(Copy_Mode == STK_SINGLE_INTERVAL||Copy_Mode == STK_PERIOD_INTERVAL)
    {
        MODE = Copy_Mode;

    }
    else
    {
        Local_Status = STK_NOK;
    }
    return Local_Status;        
 
}

void SysTick_Handler(void)

{

    STK->CTRL &= 0xFFFEFFFF;

    if (STK_CallBack != NULL)
    {
        STK_CallBack();
    }
    if (MODE == STK_SINGLE_INTERVAL)
    {
        STK_Stop();
    }
}

STK_status STK_IsEXPired(uint32_t *Copy_Flag)
{
    STK_status Local_Status = STK_NOK;
    if ((STK->CTRL & STK_COUNTER_FLAG_MASK) == STK_COUNTER_FLAG_MASK)
    {
        Local_Status = STK_OK;
        *Copy_Flag = NOTEXPIRED;
    }
    else
    {
        *Copy_Flag = ISEXPIRED;
    }
    return Local_Status;
}
