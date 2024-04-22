#ifndef MCAL_NVIC_NVIC_H_
#define MCAL_NVIC_NVIC_H_




/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/


#include"interrupts.h"
#include "LIB/STD_TYPES.h"
#include"LIB/Error_Status.h"



/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

/*Enables the given interrupt*/
E_ErrorStatus_t NVIC_EnableInterrupt(uint8_t NVIC_InterruptID);


/*Disables the given interrupt*/
E_ErrorStatus_t NVIC_DisableInterrupt(uint8_t NVIC_InterruptID);


/*Sets the pending state for the given interrupt*/
E_ErrorStatus_t NVIC_SetPending(uint8_t NVIC_InterruptID);


/*Clears the pending state for the given interrupt*/
E_ErrorStatus_t NVIC_ClearPending(uint8_t NVIC_InterruptID);


/* Returns wether the given interrupt is pending or not*/
E_ErrorStatus_t NVIC_GetPending(uint8_t NVIC_InterruptID, uint8_t *Add_ReturnPending);


/*Returns wether the given interrupt is active or not*/
E_ErrorStatus_t NVIC_GetActive(uint8_t NVIC_InterruptID, uint8_t* Add_ReturnActive);


/*Sets the priority for the given interrupt*/
E_ErrorStatus_t NVIC_SetPeriority(uint8_t NVIC_InterruptID, uint8_t NVIC_Periority);


/*Gets the priority for the given interrupt*/
E_ErrorStatus_t NVIC_GetPeriority(uint8_t NVIC_InterruptID, uint8_t *NVIC_Periority);



#endif // MCAL_NVIC_NVIC_H_