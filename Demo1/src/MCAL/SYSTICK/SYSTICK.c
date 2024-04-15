/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : SYSTICK   	       */
/*	Layer	  : MCAL               */
/*	Version   : 1.0                */
/*	Date	  : March 9 , 2024     */
/*	Last Edit : N/A                */
/***********************************/



/*************************************************************************************/
/********************          SYSTICK   DRIVER        *******************************/
/*************************************************************************************/

/*************************************************************************************/
/********************      SYSTICK Includes Region       *****************************/
/*************************************************************************************/
#include "SYSTICK.h"
/*************************************************************************************/
/********************      SYSTICK Defines  Region         ***************************/
/*************************************************************************************/
#define SYSTICK_type            volatile SYSTICK_reg_t * const 
#define NULL                    (void*)0
#define SYSTICK_BASEADD         0xE000E010
 
#define SYSTICK_MIN_LOAD_VAL    0x00000001UL
#define SYSTICK_MAX_LOAD_VAL    0x00FFFFFFUL

#define SYSTICK_Min_LoadValue   (uint32_t)(1UL)
#define SYSTICK_Max_LoadValue   (uint32_t)(16777215UL)


#define SYSTICK_MAX_RELOAD_MS    645.2775f 


#define SYSTICK_AHB_8_CLKSRC     0X00000000 
#define SYSTICK_Proc_AHB_CLKSRC  0X00000004 


#define SYSTICK_MASK_ENABLE      0X00000001 
#define SYSTICK_MASK_DISABLE     0X00000000

#define SYSTICK_MASK_TICKINT     0X00000002


#define SYSTICK_CHECK_CLK(CLK)  ((CLK==SYSTICK_AHB_8_CLK) || (CLK==SYSTICK_Processor_AHB_CLK))
#define SYSTICK_CHECK_MODE(MODE)  ((MODE==SYSTICK_SINGLE_SHOT) || (MODE==SYSTICK_MULTI_SHOT))
#define SYSTICK_CHECK_INT_MODE(INT)  ((INT==SYSTICK_INT_ENABLE) || (INT==SYSTICK_INT_DISABLE))
#define SYSTICK_CHECK_RELOAD(VAL)  ((VAL >= SYSTICK_Min_LoadValue) && (VAL <= SYSTICK_Max_LoadValue))

/******************************************************************************************/
/********************             SYSTICK  Datatypes        *******************************/
/******************************************************************************************/

typedef unsigned int uint32_t;
typedef unsigned int long uint64_t;
typedef unsigned char uint8_t;
typedef volatile unsigned int vuint32_t;

typedef void (*SYSTICK_Callback)(void);
static SYSTICK_Callback SYSTICK_CallBack = NULL;

typedef struct
{
    vuint32_t STK_CTRL;
    vuint32_t STK_LOAD;
    vuint32_t STK_VAL;
    vuint32_t STK_CALIB;

}SYSTICK_reg_t;

static SYSTICK_type SYSTICK_Ptr = (SYSTICK_type)SYSTICK_BASEADD;


typedef enum
{
	SYSTICK_CLEAR,
	SYSTICK_SET,
	SYSTICK_TOGGLE

}SYSTICK_REG_OPER;

static SYSTICK_CLKSRC_t SYSTICK_SystemClock_Global;

/*****************************************************************************************************************************************************/
/*********************************************         Static Functions Prototypes Region        *****************************************************/
/*****************************************************************************************************************************************************/
static uint32_t SYSTICK_EDIT_REG_MASK    (uint32_t SYSTICK_REG_EDIT,uint32_t STK_MASK, SYSTICK_REG_OPER OPERA);
//static uint32_t SYSTICK_EDIT_Bit_Reg     (uint32_t SYSTICK_REG_EDIT,uint32_t BIT_NUM,SYSTICK_REG_OPER OPERA);
/*static uint32_t SYSTICK_CONTROL_INTERRUPT(SYSTICK_INT_MODE SYSTICK_INT_INPUT);*/
/******************************************************************************************************************************************************/


/*********************************************************************************************************/
/***********************        SYSTICK Functions implmentation Region        ****************************/
/*********************************************************************************************************/

SYSTICK_ErrorStatus SYSTICK_SELECT_CLKSRC(SYSTICK_CLKSRC_t SYSTICK_SRC)
{
    SYSTICK_ErrorStatus SYSTICK_Local_status = SYSTICK_NOK;

    if(!SYSTICK_CHECK_CLK(SYSTICK_SRC) )
    {
        SYSTICK_Local_status = SYSTICK_ERROR;
    }
    else if(SYSTICK_SRC == SYSTICK_AHB_8_CLK)
    {
       SYSTICK_Ptr->STK_CTRL      = SYSTICK_EDIT_REG_MASK(SYSTICK_Ptr->STK_CTRL,SYSTICK_AHB_8_CLKSRC,SYSTICK_SET);
	   SYSTICK_Local_status       = SYSTICK_OK;
       SYSTICK_SystemClock_Global = SYSTICK_AHB_8_CLK;
    }
    else
    {
		SYSTICK_Ptr->STK_CTRL      = SYSTICK_EDIT_REG_MASK(SYSTICK_Ptr->STK_CTRL,SYSTICK_Proc_AHB_CLKSRC,SYSTICK_SET);
		SYSTICK_Local_status       = SYSTICK_OK;
        SYSTICK_SystemClock_Global = SYSTICK_Processor_AHB_CLK;
    }

	return SYSTICK_Local_status ;

}

SYSTICK_ErrorStatus SYSTICK_START(void)
{
    SYSTICK_ErrorStatus SYSTICK_Local_status = SYSTICK_NOK;
    uint32_t systick_local_mask;
 /*    if(SYTK_CHECK_INT_MODE(STK_INT_MODE_INPUT)) 
    {
       if(STK_INT_ENABLE)
        {
            */
           systick_local_mask = SYSTICK_MASK_TICKINT;
 /*       }
        else
        {
           systick_local_mask = SYSTICK_MASK_DISABLE;
        }
*/
        systick_local_mask |= SYSTICK_MASK_ENABLE;
        /* Now you start your timer whatever you enabled int or not */
        SYSTICK_Ptr->STK_CTRL   = SYSTICK_EDIT_REG_MASK(SYSTICK_Ptr->STK_CTRL,systick_local_mask,SYSTICK_SET);
        SYSTICK_Local_status    = SYSTICK_OK;
    
  /*    else 
    {
        SYTK_Local_status = SYTK_ERROR;
    }
*/
    return SYSTICK_Local_status;
}
void SYSTICK_DISABLE_INT(void)
{
     SYSTICK_Ptr->STK_CTRL  = SYSTICK_EDIT_REG_MASK(SYSTICK_Ptr->STK_CTRL,SYSTICK_MASK_TICKINT,SYSTICK_CLEAR);

}
SYSTICK_ErrorStatus SYTK_STOP(void)
{
	SYSTICK_ErrorStatus SYSTICK_Local_status = SYSTICK_NOK;

	SYSTICK_Ptr->STK_CTRL = SYSTICK_EDIT_REG_MASK(SYSTICK_Ptr->STK_CTRL,SYSTICK_MASK_DISABLE,SYSTICK_CLEAR);
	SYSTICK_Local_status  = SYSTICK_OK;

	return SYSTICK_Local_status;


}

SYSTICK_ErrorStatus SYSTICK_Get_Timer(uint32_t *SYSTICK_CRRENT_VAL)
{
	SYSTICK_ErrorStatus SYSTICK_Local_status = SYSTICK_NOK;
    if(!(SYSTICK_CRRENT_VAL == NULL ))
	{
        *SYSTICK_CRRENT_VAL  = SYSTICK_Ptr->STK_VAL;
        SYSTICK_Local_status = SYSTICK_OK;

	}
	else
	{
		SYSTICK_Local_status = SYSTICK_NULL_PTR;
	}
    return SYSTICK_Local_status;

}

SYSTICK_ErrorStatus SYSTICK_SetFrequencyHZ(uint32_t SYSTICK_Frequency_hz)
{
    SYSTICK_ErrorStatus SYSTICK_Local_status = SYSTICK_NOK;

    uint32_t reload_value = (SYSTICK_SystemClock_Global / SYSTICK_Frequency_hz) - 1;

    if(SYSTICK_CHECK_RELOAD(reload_value))
    {
        SYSTICK_Ptr->STK_LOAD = SYSTICK_EDIT_REG_MASK(SYSTICK_Ptr->STK_LOAD,reload_value,SYSTICK_SET);
        SYSTICK_Local_status = SYSTICK_OK;
    }
    else
    {
        SYSTICK_Local_status =SYSTICK_ERROR;
    }
    return SYSTICK_Local_status;

}

SYSTICK_ErrorStatus SYSTICK_SetTimeMS(uint32_t SYSTICK_TIME_MS)
{
    SYSTICK_ErrorStatus SYSTICK_Local_status = SYSTICK_NOK;

    uint32_t reload_value = (SYSTICK_TIME_MS*(SYSTICK_SystemClock_Global/1000))-1;

    if(SYSTICK_CHECK_RELOAD(reload_value))
    {
        SYSTICK_Ptr->STK_LOAD = SYSTICK_EDIT_REG_MASK(SYSTICK_Ptr->STK_LOAD,reload_value,SYSTICK_SET);
        SYSTICK_Local_status = SYSTICK_OK;
    }
    else
    {
        SYSTICK_Local_status = SYSTICK_ERROR;
    }
    return SYSTICK_Local_status;

}

SYSTICK_ErrorStatus SysTick_Handler(SYSTICK_MODE_t SYSTICK_INPUT_MODE)
{
   SYSTICK_ErrorStatus SYSTICK_Local_status = SYSTICK_NOK;
   
   if((!SYSTICK_CHECK_MODE(SYSTICK_INPUT_MODE)) &&  (SYSTICK_CallBack == NULL))
   {
      SYSTICK_Local_status = SYSTICK_ERROR;
   }
   else
   {
        if(SYSTICK_INPUT_MODE == SYSTICK_SINGLE_SHOT)
        {
            SYSTICK_CallBack();
            SYSTICK_DISABLE_INT();
        }
        else if(SYSTICK_INPUT_MODE == SYSTICK_MULTI_SHOT)
        {
            SYSTICK_CallBack();
        }
   }
   return SYSTICK_Local_status ;

}
SYSTICK_ErrorStatus SYSTICK_SetCallBack(SYSTICK_Callback Input_callback)
{
    SYSTICK_ErrorStatus SYSTICK_Local_status = SYSTICK_NOK;
   
   if( (Input_callback == NULL))
   {
      SYSTICK_Local_status = SYSTICK_ERROR;
   }
   else
   {
    SYSTICK_CallBack = Input_callback ;
   }
   
    return SYSTICK_Local_status;
}
/*********************************************************************************************************/
/***********************        SYSTICK Static Functions implmentation Region    *************************/
/*********************************************************************************************************/


/************************************** SYSTICK_EDIT_REG_MASK **********************************/

/* 
   
   * Functionality    : Apply mask on input register
   * Input Parameters : 1- Register you want to EDIT 
   *                    2- MASK 
   *                    3- Select Operation you want to apply.
   *                       (options : CLEAR , SET , TOGGLE) 	
   
   * NOTE             :   
 
 */
static uint32_t SYSTICK_EDIT_REG_MASK(uint32_t SYSTICK_REG_EDIT,uint32_t SYSTICK_MASK, SYSTICK_REG_OPER OPERA)
{
	uint32_t SYSTICK_Local_Var =0;
	switch (OPERA)
	{
	
		case SYSTICK_CLEAR :
			{
				SYSTICK_Local_Var  = SYSTICK_REG_EDIT ;
				SYSTICK_Local_Var &= ~SYSTICK_MASK;
				
			}
			break;
		case SYSTICK_SET :
			{
				SYSTICK_Local_Var  = SYSTICK_REG_EDIT ;
				SYSTICK_Local_Var |= SYSTICK_MASK; 
			}break;

		default:
			break;
	}
	return SYSTICK_Local_Var;
}
/************************************** SYSTICK_CONTROL_INTERRUPT **********************************/

/* 
   
   * Functionality    : Enable exception request once reach zero
                        Enable SYSTICK_INT

   * Input Parameters : 1- Register you want to EDIT 
   *                    2- MASK 
   *                    3- Select Operation you want to apply.
   *                       (options : CLEAR , SET , TOGGLE) 	
   
   * NOTE             :   
 
 */
/*
static uint32_t SYSTICK_CONTROL_INTERRUPT(SYSTICK_INT_MODE SYSTICK_INT_INPUT)
{




}
*/