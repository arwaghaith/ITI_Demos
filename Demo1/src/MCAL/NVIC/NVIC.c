/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include"NVIC.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define   NVIC_Core_peripheral_base   0xE000E100
#define   NVIC_Core_peripheral   ((volatile NVIC_t* const)NVIC_Core_peripheral_base)
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct
{
	uint32_t ISER[32];
	uint32_t ICER[32];
	uint32_t ISPR[32];
	uint32_t ICPR[32];
    uint32_t IABR[32];
	uint32_t reserved[32];
    uint8_t IPR[60];          /**< Interrupt Priority Registers (0-59) - Byte Accessible */
    uint32_t RESERVED5[644];    /**< Reserved space */
    uint32_t STIR;              /**< Software Trigger Interrupt Register */
}NVIC_t;


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
#define GROUP_16_SUB_0        0x05FA0000
#define GROUP_8_SUB_2         0x05FA0400
#define GROUP_4_SUB_4         0x05FA0500
#define GROUP_2_SUB_8         0x05FA0600
#define GROUP_0_SUB_16        0x05FA0700

#define GROUP_SUB_PRIORITY  GROUP_4_SUB_4


/********************************************************************************************************/
/******************************************* Static Functions *******************************************/
/********************************************************************************************************/
/*static  GetPriorityAndGroupConfig(uint8_t local_u8Group  ,uint8_t  local_u8SubGroup ){
		u8 localconfigReturnValue = 0 ;
		#if  GROUP_SUB_PRIORITY  == GROUP_16_SUB_0
		localconfigReturnValue = local_u8Group ;
		#elif GROUP_SUB_PRIORITY == GROUP_8_SUB_2
		localconfigReturnValue = ((local_u8Group<<1) | (local_u8SubGroup<<0) );
		#elif GROUP_SUB_PRIORITY == GROUP_4_SUB_4
		localconfigReturnValue = ((local_u8Group<<2) | (local_u8SubGroup<<0) );
		#elif GROUP_SUB_PRIORITY == GROUP_2_SUB_8
		localconfigReturnValue = ((local_u8Group<<3) | (local_u8SubGroup<<0) );
		#else GROUP_SUB_PRIORITY == GROUP_0_SUB_16
		localconfigReturnValue =  local_u8SubGroup ;
		#endif
		return (localconfigReturnValue<<4);
}*/


/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

/* Enables the given interrupt */
E_ErrorStatus_t NVIC_EnableInterrupt(uint8_t NVIC_InterruptID)
{
    E_ErrorStatus_t NVIC_E_ErrorStatus_t = E_NOK;
    if (NVIC_InterruptID >= 240) {
        return NVIC_E_ErrorStatus_t;
    }
    else
    { 
        NVIC_ClearPending(NVIC_InterruptID);
        NVIC_Core_peripheral->ISER[NVIC_InterruptID / 32] |= (1UL << (NVIC_InterruptID % 32));
        NVIC_E_ErrorStatus_t = E_OK;
    }
    return NVIC_E_ErrorStatus_t;
}




/*Disables the given interrupt*/
E_ErrorStatus_t NVIC_DisableInterrupt(uint8_t NVIC_InterruptID)
{

    E_ErrorStatus_t NVIC_E_ErrorStatus_t = E_NOK;
    if(NVIC_InterruptID <0 || NVIC_InterruptID > 240){
        return NVIC_E_ErrorStatus_t;
    }
    else
    {
        NVIC_Core_peripheral->ICER[NVIC_InterruptID/32] = (1UL <<(NVIC_InterruptID % 32 )) ;
         NVIC_E_ErrorStatus_t = E_OK;

    }

    return  NVIC_E_ErrorStatus_t;

}




/*Sets the pending state for the given interrupt*/
E_ErrorStatus_t NVIC_SetPending(uint8_t NVIC_InterruptID)
{
    E_ErrorStatus_t NVIC_E_ErrorStatus_t = E_NOK;
    if(NVIC_InterruptID <0 || NVIC_InterruptID > 240){
        return NVIC_E_ErrorStatus_t;
    }
    else
    {
        NVIC_Core_peripheral->ISPR[NVIC_InterruptID/32] = (1UL <<(NVIC_InterruptID % 32 )) ;
         NVIC_E_ErrorStatus_t = E_OK;

    }

    return  NVIC_E_ErrorStatus_t;

}





/*Clears the pending state for the given interrupt*/
E_ErrorStatus_t NVIC_ClearPending(uint8_t NVIC_InterruptID)
{
     E_ErrorStatus_t NVIC_E_ErrorStatus_t = E_NOK;
    if(NVIC_InterruptID <0 || NVIC_InterruptID > 240){
        return NVIC_E_ErrorStatus_t;
    }
    else
    {
        NVIC_Core_peripheral-> ICPR[NVIC_InterruptID/32] = (1UL <<(NVIC_InterruptID % 32 )) ;
         NVIC_E_ErrorStatus_t = E_OK;

    }

    return  NVIC_E_ErrorStatus_t;
}





/* Returns wether the given interrupt is pending or not*/
E_ErrorStatus_t NVIC_GetPending(uint8_t NVIC_InterruptID, uint8_t *Add_ReturnPending)
{
    
    E_ErrorStatus_t NVIC_E_ErrorStatus_t = E_NOK;
    if(NVIC_InterruptID <0 || NVIC_InterruptID > 240){
        return NVIC_E_ErrorStatus_t;
    }
    else
    {
       *Add_ReturnPending = (NVIC_Core_peripheral-> ISPR[NVIC_InterruptID/32])&(1 << (NVIC_InterruptID % 32 ));
        NVIC_E_ErrorStatus_t = E_OK;
    }

    return  NVIC_E_ErrorStatus_t;
}





/*Returns wether the given interrupt is active or not*/
E_ErrorStatus_t NVIC_GetActive(uint8_t NVIC_InterruptID, uint8_t* Add_ReturnActive)
{    
    E_ErrorStatus_t NVIC_E_ErrorStatus_t = E_NOK;
    if(NVIC_InterruptID <0 || NVIC_InterruptID > 240){
        return NVIC_E_ErrorStatus_t;
    }
    else if (*Add_ReturnActive == NULL){
        NVIC_E_ErrorStatus_t =  E_NULL_PTR; 
        return NVIC_E_ErrorStatus_t;
    }
    else
    {
       *Add_ReturnActive = (NVIC_Core_peripheral-> IABR[NVIC_InterruptID/32])&(1 << (NVIC_InterruptID % 32 ));
        NVIC_E_ErrorStatus_t = E_OK;
    }

    return  NVIC_E_ErrorStatus_t;

}




/*Gets the priority for the given interrupt*/
E_ErrorStatus_t NVIC_GetPeriority(uint8_t NVIC_InterruptID, uint8_t *NVIC_Periority)
{
    
    E_ErrorStatus_t NVIC_E_ErrorStatus_t = E_NOK;
    if(NVIC_InterruptID <0 || NVIC_InterruptID > 240){
        return NVIC_E_ErrorStatus_t;
    }

    else
    {
       
       *NVIC_Periority = ( NVIC_Core_peripheral->IPR[(uint8_t)(((float)NVIC_InterruptID / 240.00f) * 60)]) >> ((NVIC_InterruptID % 4) );
        NVIC_E_ErrorStatus_t = E_OK;
    }

    return  NVIC_E_ErrorStatus_t;
}



/*Sets the priority for the given interrupt*/
E_ErrorStatus_t NVIC_SetPeriority(uint8_t NVIC_InterruptID, uint8_t NVIC_Periority)
{
    E_ErrorStatus_t NVIC_E_ErrorStatus_t = E_NOK;
    if(NVIC_InterruptID <0 || NVIC_InterruptID > 240){
        return NVIC_E_ErrorStatus_t;
    }
   
    else
    {
       
          NVIC_Core_peripheral->IPR[(uint8_t)(((float)NVIC_InterruptID / 240.00f) * 60)] &= ~(0xFF << (NVIC_InterruptID % 4));
          NVIC_Core_peripheral->IPR[(uint8_t)(((float)NVIC_InterruptID / 240.00f) * 60)] |= (NVIC_Periority << (NVIC_InterruptID % 4));

        NVIC_E_ErrorStatus_t = E_OK;
    }

    return  NVIC_E_ErrorStatus_t;

}




