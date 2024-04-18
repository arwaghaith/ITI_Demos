/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : SYSTICK   	        */
/*	Layer	     : MCAL               */
/*	Version    : 1.0                */
/*	Date	     : March 9 , 2024     */
/*	Last Edit  : N/A                */
/***********************************/


#ifndef SYSTICK_H_
#define SYSTICK_H_

/****************************************************************************************/
/**********************      SYSTICK  DRIVER          ***********************************/
/****************************************************************************************/


/*************************************************************************************/
/********************         SYSTICK   datatypes      *******************************/
/*************************************************************************************/

typedef unsigned int uint32_t;
typedef enum 
{
   SYSTICK_NOK,
   SYSTICK_OK,
   SYSTICK_NULL_PTR,
   SYSTICK_ERROR

}SYSTICK_ErrorStatus;


typedef enum 
{
   SYSTICK_AHB_8_CLK = 3250000,
   SYSTICK_Processor_AHB_CLK = 26000000

}SYSTICK_CLKSRC_t;

typedef enum 
{
   SYSTICK_SINGLE_SHOT,
   SYSTICK_MULTI_SHOT 

} SYSTICK_MODE_t;

typedef enum
{
   SYSTICK_INT_DISABLE,
	SYSTICK_INT_ENABLE

}SYSTICK_INT_MODE;

typedef void (*SYSTICK_Callback)(void);

/**************************************************************************************/
/********************             SYSTICK  APIs         *******************************/
/**************************************************************************************/
/* Clock source selection
Selects the clock source.*/
/**************************** SYSTICK_START **************************/
/* 
   * Functionality    :  responsible for starting the SysTick timer.


   * Input Parameters : void
   
 
 *****************************************************************/
SYSTICK_ErrorStatus SYSTICK_START(void);
/*********************** SYSTICK_SELECT_CLKSRC **********************/
/* 
   * Functionality    :Select the clock source required for 
                       systick peripheral.
   -------------------------------------------------------------

   * Input Parameters : Systick  Clock source selection.
   -------------------                  
                  1 - SYSTICK_AHB_8_CLK.        -> "   AHB/8   "
                  2 - SYSTICK_Processor_AHB_CLK.-> " Processor "
                                                    ck src (AHB).
   --------------------------------------------------------------
   * Input Parameter Validation:
   ---------------------------
   It takes an input parameter SYSTICK_SRC of type SYSTICK_CLKSRC_t,
   which presumably specifies the desired clock source for the 
   SysTick timer.
   It checks if the specified clock source is valid by calling
   SYSTICK_CHECK_CLK(SYSTICK_SRC). If the specified clock source 
   is not valid, it sets SYSTICK_Local_status to SYSTICK_ERROR.
   ---------------------------------------------------------------
   * Return Status:
   -----------------
   It returns the status of the operation using SYSTICK_Local_status. 
   If the operation is successful, it returns SYSTICK_OK. Otherwise,
   it returns SYSTICK_ERROR.

 ********************************************************************/
SYSTICK_ErrorStatus SYSTICK_SELECT_CLKSRC(SYSTICK_CLKSRC_t SYSTICK_SRC);
/**************************** SYSTICK_STOP **************************/
/* 
   * Functionality    : STOP SYSTICK Timer .

   * Input Parameters : void
   
   * NOTE             : Disabling the SysTick timer effectively
                        freezes its countdown, and when you 
                        re-enable it, it starts counting from
                        the initial or reload value set in the
                        STK_LOAD register , thus to puase and 
                        continue you to save the current value 
                        and reload to STK_LOAD register manually
 
 *****************************************************************/
SYSTICK_ErrorStatus SYSTICK_STOP(void);
/******************** SYTK_SetTimeMS **************************/
/* 
   
   * Functionality    : 

   * Input Parameters : 
   
   * NOTE             :  
 
 **************************************************************/
SYSTICK_ErrorStatus SYSTICK_SetTimeMS(uint32_t SYSTICK_TIME_MS);
/******************** SYTK_SetFrequencyHZ **************************/
/* 
   
   * Functionality    : 

   * Input Parameters : 
   
   * NOTE             :  
 
 **************************************************************/
SYSTICK_ErrorStatus SYSTICK_SetFrequencyHZ(uint32_t SYSTICK_Frequency_hz);
/******************** SysTick_Handler **************************/
/* 
   
   * Functionality    :  Hnadler function automatically ex

   * Input Parameters :  void 
   
   * NOTE             :   
 
 **************************************************************/
void SysTick_Handler(void);
/******************** SYSTICK_SetCallBack **************************/
/* 
   
   * Functionality    : GET Current value in STK_VAL reg
                        which reprsent value which is decreamenting
                        each clock cycle Which is loaded from 
                        STK_LOAD reg.

   * Input Parameters : 1- You have to create variable and pass
                           its 	address to return value of STK_VAL
   
   * NOTE             :  Writting this register has no effect 
                         trying to write on this register clears
                         CFLAG -> 0 
 
 **************************************************************/
SYSTICK_ErrorStatus SYSTICK_SetCallBack(SYSTICK_Callback Input_callback);
/******************** SYSTICK_DISABLE_INT **************************/
/* 
  * Functionality    :  Is a function used to disable interrupts 
                        for the SysTick timer, which can be useful
                        in scenarios where interrupt-driven operation 
                        is not required or desired.

   * Input Parameters : 1- 
   
   * NOTE             : 
 
 **************************************************************/
void SYSTICK_DISABLE_INT(void);
/******************** SYSTICK_Get_Timer **************************/
/* 
   * Functionality    : GET Current value in STK_VAL reg
                        which reprsent value which is decreamenting
                        each clock cycle Which is loaded from 
                        STK_LOAD reg.

   * Input Parameters : 1- You have to create variable and pass
                           its 	address to return value of STK_VAL
   
   * NOTE             :  Writting this register has no effect 
                         trying to write on this register clears
                         CFLAG -> 0 
 
/ **************************************************************/
SYSTICK_ErrorStatus SYSTICK_Get_Timer(uint32_t *SYSTICK_CRRENT_VAL);

#endif