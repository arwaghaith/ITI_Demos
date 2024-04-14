/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : NVIC   		       */
/*	Layer	  : MCAL               */
/*	Version   : 1.0                */
/*	Date	  : March 3 , 2024     */
/*	Last Edit : N/A                */
/***********************************/


#ifndef NVIC_H_
#define NVIC_H_

/******************************************************************************************************************************************/
/**************************************************           NVIC  DRIVER          *******************************************************/
/******************************************************************************************************************************************/
#include "NVIC_IRQn.h"

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;


typedef enum 
{
    NVIC_IRQNUM_OK,
    NVIC_IRQNUM_NOK,
    NVIC_NULL_PTR,
    NVIC_ERROR,
    NVIC_ERROR_VAL,
    NVIC_NOK,
    NVIC_OK

}NVIC_ErrorStatus;


typedef enum
{
  NVIC_GP_0_bits,
  NVIC_GP_1_bits,
  NVIC_GP_2_bits,
  NVIC_GP_3_bits,
  NVIC_GP_4_bits,
  NVIC_GP_5_bits,
  NVIC_GP_6_bits,
  NVIC_GP_7_bits

}NVIC_Num_GP_Level;



/******************** NVIC_EnableIRQ ********************/
/* Functionality    :  Setting this bit in NVIC_ISERx
                       allows the associated interrupt 
                       to be serviced by the CPU when 
                       it occurs     
   Input Parameters : 1- type of Interrupt request to
                         be enabled to allow CPU service
                         this interrupt	(IRQn_Type)	  
   Function Test     :  DONE                            */
/********************************************************/
NVIC_ErrorStatus NVIC_EnableIRQ(NVIC_IRQn_Type NVIC_IRQn);
/******************** NVIC_DisableIRQ ********************/
/* Functionality    :  clearing this bit in NVIC_ISERx
                       prevents the associated interrupt 
                       to be serviced by the CPU when 
                       it occurs     
   Input Parameters : 1- type of Interrupt request to
                         be disabled.  (IRQn_Type).

   Function Test    :  DONE
                                                        */
/********************************************************/
NVIC_ErrorStatus NVIC_DisableIRQ(NVIC_IRQn_Type NVIC_IRQn);
/***************** NVIC_ClearPendingIRQ *****************/
/* Functionality    :   Setting a bit in NVIC_ICPRx will 
                        Removes the pending state of an 
                        interrup.

   Input Parameters : 1- type of Interrupt request to 
                         disable its pending. 
                         (IRQn_Type).

   Function Test    :  DONE
                                                        */
/********************************************************/
NVIC_ErrorStatus NVIC_ClearPendingIRQ(NVIC_IRQn_Type IRQn);
/***************** NVIC_SetPendingIRQ *********************/
/* Functionality    :   Setting a bit in NVIC_ISPRx will 
                        mark the corresponding interrupt 
                        as pending. When an interrupt is
                        pending, the processor will check 
                        its priority and, if appropriate, 
                        service the interrupt during the 
                        next available interrupt 
                        service routine (ISR) execution.

   Input Parameters : 1- type of Interrupt request to 
                         enable its pending. 
                        (IRQn_Type)                    

   Function Test    :  DONE
                                                        */
/********************************************************/
NVIC_ErrorStatus NVIC_SetPendingIRQ(NVIC_IRQn_Type IRQn);
/******************* NVIC_GetPendingIRQ *********************/
/* Functionality    :   Read bit in NVIC_ICPRx or use 
                        NVIC_ISPRx , when read 1 means the 
                        corrsponding IRQn is pending.

   Input Parameters : 1- type of Interrupt request to 
                         read its pending state. 
                        (IRQn_Type) 
                     2 - create a uint8_t variable to return 
                         state in if 1 -> pending 
                                     0 -> not pending 

   Function Test    :  DONE
                                                          */
/***********************************************************/
NVIC_ErrorStatus NVIC_GetPendingIRQ(NVIC_IRQn_Type NVIC_IRQn,uint32_t *NVIC_Pending_bit);
/******************* NVIC_GetActiveIRQ *********************/
/* Functionality    :   Read bit in NVIC_IABR corresponding
                        interrupt Request ID. 
                        If 1 -> active and pending.
                        If 0 -> not active.

   Input Parameters : 1- Type of Interrupt request to 
                         read its pending state. 
                         (IRQn_Type).

                      2- NVIC_Active_bit -> Address of 
                         variable will return bit reading.

   Function Test    :  DONE
                                                         */
/***********************************************************/
NVIC_ErrorStatus NVIC_GetActiveIRQ(NVIC_IRQn_Type NVIC_IRQn,uint32_t *NVIC_Active_bit);
/******************** NVIC_SetPriority ********************/
/* Functionality    :   Setting a byte for priority value
                        in corresponding NVIC_IPRx Register. 

   Input Parameters : 1- type of Interrupt request to 
                         enable its pending. 
                         (IRQn_Type).
                         
                      2- NVIC_Priority Value 
    Function Test    :  DONE.

   Function Test    :  DONE
                                                          */
/**********************************************************/
NVIC_ErrorStatus NVIC_SetPriority(NVIC_IRQn_Type NVIC_IRQn, uint8_t NVIC_Priority);
/******************** NVIC_GetPriority *********************/
/* Functionality    :   Reading a byte in NVIC_IPRx which 
                        indicates the priority value.

   Input Parameters : 1- Type of Interrupt request to 
                         read its pending state. 
                         (IRQn_Type).
                     2- NVIC_pirority_val -> Address of 
                        variable will return Priority value
                        reading.  
   Function Test    :  DONE        
 
   Function Test    :  DONE
                                                            */
/************************************************************/
NVIC_ErrorStatus NVIC_GetPriority(NVIC_IRQn_Type NVIC_IRQn,uint8_t *NVIC_pirority_val);
/******************** NVIC_TriggerSWInterrupt *********************/
/* Functionality    :   Bits [8:0]  Software generated interrupt ID
                        Write to the STIR to generate a Software 
                        Generated Interrupt (SGI). 
                        
   Input Parameters : 1- type of Interrupt request. 
                         (IRQn_Type) 
                        which indicates value to be written is 
                        the Interrupt ID of the required SGI,
                        in the range 0-239.
                        For example, a value of 0x03 specifies 
                        interrupt IRQ3.


   Function Test    :  DONE
                                                               */
/***************************************************************/
NVIC_ErrorStatus NVIC_TriggerSWInterrupt(NVIC_IRQn_Type NVIC_IRQn);
/******************** NVIC_SetPriorityGroup *********************/
/* Functionality    :   Determines the split of group priority.
                               in STM32 Cortex®-M4 
                        The processor implements only bits[7:4]
                        of each field, bits[3:0] read as zero and
                        ignore writes.
                         ---------------------------------
                         | 7   6   5   4 | 3   2   1   0 |
                         |---------------|---------------|
                         |   |   |   |   | x | x | x | x |
                         ----------------|----------------
                        0b0xx 0bxxxx  [7:4] None  16  None
                        0b100 0bxxx.y [7:5] [4]   8    2
                        0b101 0bxx.yy [7:6] [5:4] 4    4
                        0b110 0bx.yyy [7]   [6:4] 2    8
                        0b111 0b.yyyy None  [7:4] None 16

   Input Parameters : 1- type of Interrupt request to 
                         enable its pending. 
                         (IRQn_Type) 	                     */
/************************************************************/
NVIC_ErrorStatus NVIC_SetPriorityGroup(NVIC_Num_GP_Level NVIC_GroupPriorityBits_Num);
/******************** NVIC_GetPriorityGroup *********************/
/* Functionality    :   Setting a bit in NVIC_ISPRx will 
                        mark the corresponding interrupt 
                        as pending. When an interrupt is
                        pending, the processor will check 
                        its priority and, if appropriate, 
                        service the interrupt during the 
                        next available interrupt 
                        service routine (ISR) execution.

   Input Parameters : 1- type of Interrupt request to 
                         enable its pending. 
                         (IRQn_Type) 	                       */
/**************************************************************/
NVIC_ErrorStatus NVIC_GetPriorityGroup(NVIC_Num_GP_Level* NVIC_GroupPriorityBits_Num);
/******************** NVIC_EncodePriority *********************/
/* Functionality    :   This function take NVIC_PreemptPriority
                        value and NVIC_SubPriority and based on 
                        number of bits of the SUBGROUP priority
                        it calculate priority value to be set 
                        directly to  NVIC_IPRx using 
                        " NVIC_SetPriority " function.          

   Input Parameters : 1- NVIC_PreemptPriority value
                      2- NVIC_SubPriority     value          
                      3- Address of variable in which return
                         prioity value   NVIC_Priority_Val    */
/**************************************************************/
NVIC_ErrorStatus NVIC_EncodePriority(uint8_t NVIC_PreemptPriority, uint8_t NVIC_SubPriority,uint8_t *NVIC_Priority_Val);
/******************** NVIC_DecodePriority *********************/
/* Functionality    :   
 
   Input Parameters : 1-  	                             */
/********************************************************/
NVIC_ErrorStatus NVIC_DecodePriority(uint8_t NVIC_GroupPriority, uint8_t NVIC_SubPriority, uint8_t NVIC_32PriGroup, uint8_t* NVIC_PriorityValue);


#endif