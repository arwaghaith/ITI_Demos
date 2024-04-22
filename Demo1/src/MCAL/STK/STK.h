#ifndef STK_H
#define STK_H



#include "../../LIB/STD_TYPES.h"
#include "STK_private.h"



#define STK_LOAD_MAX_VAL 0x00FFFFFF

#define SYS_CLK 16000000
#define AHB_PRESCALER 8
#define MS_TO_US 1000


#define ISEXPIRED 1
#define NOTEXPIRED 0

typedef enum
{
    STK_NOK,
    STK_OK

}STK_status;

typedef enum
{
    STK_AHB_DIVIDED_BY_8=0,
    STK_AHB=4
}STK_CLK;

typedef enum
{
    STK_SINGLE_INTERVAL,
    STK_PERIOD_INTERVAL
}STK_MODE;

#define  STK_ENABLE  0x00000001
#define  STK_DISABLE 0x00000000


/**************************************************  STK INTERFACE ***********************************/

/*
@fn                  - STK_Init
@brief               - Initialize the SysTick Timer
@param [in]          - STK_CLK Copy_CLK
@param [in]          - STK_MODE Copy_Mode
@param [in]          - uint32_t Copy_Load
@param [in]          - void (*Copy_Ptr)(void)
@return              - STK_status

*/
/************************************************** ***************************************************/
STK_status STK_Init(STK_CLK Copy_CLK, STK_MODE Copy_Mode,uint32_t Copy_Load, void (*Copy_Ptr)(void));

/*
@fn                  - STK_SetTime
@brief               - Set the time of the SysTick Timer
@param [in]          - uint32_t Copy_Time
@return              - STK_status
*/
/***************************************************************************************************/
STK_status STK_SetTimeMS(uint32_t Copy_Time);

/*
@fn                  - STK_SetCLK
@brief               - Set the clock of the SysTick Timer
@param [in]          - STK_CLK Copy_CLK
@return              - STK_status
*/
STK_status STK_SetCLK(STK_CLK Copy_CLK);


/*
@fn                  - STK_SetMode
@brief               - Set the mode of the SysTick Timer
@param [in]          - STK_MODE Copy_Mode
@return              - STK_status
*/
STK_status STK_SetMode(STK_MODE Copy_Mode);

/*

@fn                  - STK_SetLoad
@brief               - Set the load of the SysTick Timer
@param [in]          - uint32_t Copy_Load
@return              - STK_status
*/
STK_status STK_SetLoad(uint32_t Copy_Load);

/*
@fn                  - STK_SetCallBack
@brief               - Set the callback function of the SysTick Timer
@param [in]          - void (*Copy_Ptr)(void)
@return              - STK_status
*/
STK_status STK_SetCallBack(void (*Copy_Ptr)(void));

/*

@fn                  - STK_Start
@brief               - Start the SysTick Timer
@param [in]          - void
@return              - STK_status
*/
STK_status STK_Start(void);

/*

@fn                  - STK_Stop
@brief               - Stop the SysTick Timer
@param [in]          - void
@return              - STK_status
*/
STK_status STK_Stop(void);


/*
@fn                  - STK_GetElapsedTime
@brief               - Get the elapsed time of the SysTick Timer
@param [in]          - uint32_t *Copy_Time
@return              - STK_status
*/
STK_status STK_IsEXPired(uint32_t *Copy_Flag);

/*

@fn                  - STK_GetElapsedTime
@brief               - Get the elapsed time of the SysTick Timer
@param [in]          - uint32_t *Copy_Time
@return              - STK_status
*/

#endif /* STK_H */
