/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : NVIC   		       */
/*	Layer	  : MCAL               */
/*	Version   : 1.0                */
/*	Date	  : March 3 , 2024     */
/*	Last Edit : N/A                */
/***********************************/



/*********************************************************************************************************/
/******************************          NVIC  DRIVER         ********************************************/
/*********************************************************************************************************/
#include "SCB.h"
#include "NVIC.h"



/*********************************************************************************************************/
/***************************             Defines Region           ****************************************/
/*********************************************************************************************************/

#define NVIC_typedef             volatile NVIC_registers_t* const
#define NVIC_BASEADD		     0xE000E100
#define NULL		             (void*)0
#define NVIC_NONIMPLEMENTED_BITS 4

/*******************************************/
/**************  NVIC MASK *****************/
/*******************************************/
#define NVIC_MASK_PRI         0x000000FF
#define NVIC_MASK_PRIGROUP    0x00000700
#define NVIC_MASK_VECTKEY     0xFFFF0000

/*This key value for AIRCR Register to unlock write access*/
#define NVIC_VECTKEY                        (uint32_t)0xFA050000
#define NVIC_PRIGROUP_OFFSET                 8U
#define NVIC_SET_PRIGROUP(NUM_of_BITS)      (NUM_of_BITS<<8)
#define NVIC_GET_PRIGROUP(PRIGROUP)         ((PRIGROUP)>>8)
#define NVIC_SET_PRIORITY(NVIC_Priority)    ((NVIC_Priority<<((NVIC_IRQn%4)*8))<<NVIC_NONIMPLEMENTED_BITS)
#define NVIC_GET_PRIORITY(NVIC_IRQn)        (((NVIC_REG_Ptr->NVIC_IPRx[NVIC_IRQn/4]>>((NVIC_IRQn%4)*8))&NVIC_MASK_PRI)>>NVIC_NONIMPLEMENTED_BITS)

/*This can be changed based on system design */
/*
    *ARM take MSB for implementing pirority level
    *to avoid misorder the pirority levels, thus 
    *system become portable keeping the correct features ihbhjbjhvhgvhg

*/
#define NVIC_NON_IMPLEMENTED_BITs      4U

/*********************************************************************************************************/
/****************************************     Typedef Region      ****************************************/
/*********************************************************************************************************/

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef volatile unsigned int vuint32_t;

typedef struct 
{
    vuint32_t NVIC_ISERx[8];
    vuint32_t reserved[24];
    vuint32_t NVIC_ICERx[8];
    vuint32_t reserved1[24];
    vuint32_t NVIC_ISPRx[8];
    vuint32_t reserved2[24];
    vuint32_t NVIC_ICPRx[8];
    vuint32_t reserved3[24];
    vuint32_t NVIC_IABRx[8];
    vuint32_t reserved4[56];
    vuint32_t NVIC_IPRx[60];
    vuint32_t reserved5[644];
    vuint32_t NVIC_STIR;

}NVIC_registers_t;
typedef enum
{
	NVIC_CLEAR,
	NVIC_SET,
	NVIC_TOGGLE

}NVIC_REG_OPER;

static NVIC_typedef  NVIC_REG_Ptr = (NVIC_typedef)NVIC_BASEADD;

/*
   *by default SUBGROUP at least number of bits to be implemented 
   *is 1 bit -> bit number 4. 
*/
static uint8_t NVIC_SUBGROUP_BitNum = NVIC_NON_IMPLEMENTED_BITs;
/*****************************************************************************************************************************************************/
/*********************************************         Static Functions Prototypes Region        *****************************************************/
/*****************************************************************************************************************************************************/
static uint32_t NVIC_EDIT_REG_MASK    (uint32_t NVIC_REG_EDIT,uint32_t NVIC_MASK, NVIC_REG_OPER OPERA);
static uint32_t NVIC_EDIT_Bit_Reg     (uint32_t NVIC_REG_EDIT,uint32_t BIT_NUM,NVIC_REG_OPER OPERA);
/*************************************************************************************************************************************************/
/*********************************************             Function implementaion Region                  ****************************************/
/*************************************************************************************************************************************************/

NVIC_ErrorStatus NVIC_EnableIRQ(NVIC_IRQn_Type NVIC_IRQn)
{
    NVIC_ErrorStatus NVIC_State= NVIC_IRQNUM_NOK;
    uint32_t NVIC_local_REG_num ,NVIC_local_bit_num ;


    if(NVIC_IRQn >= 0 && NVIC_IRQn<=_NVIC_IRQn)
    {
         NVIC_local_REG_num =NVIC_IRQn/32;
         NVIC_local_bit_num =NVIC_IRQn%32;
         NVIC_REG_Ptr->NVIC_ISERx[NVIC_local_REG_num] =NVIC_EDIT_Bit_Reg(NVIC_REG_Ptr->NVIC_ISERx[NVIC_local_REG_num],NVIC_local_bit_num,NVIC_SET);
         NVIC_State =NVIC_IRQNUM_OK;
    }
    else
    {
        NVIC_State = NVIC_IRQNUM_NOK;
    }
    return NVIC_State;

}


NVIC_ErrorStatus NVIC_DisableIRQ(NVIC_IRQn_Type NVIC_IRQn)
{
   
    NVIC_ErrorStatus NVIC_State= NVIC_IRQNUM_NOK;
    uint32_t NVIC_local_var;

    if(NVIC_IRQn >= 0 && NVIC_IRQn<=_NVIC_IRQn)
    {
         /*divide to determine reg number*/
         NVIC_local_var  = NVIC_REG_Ptr->NVIC_ICERx[NVIC_IRQn/32];
         /*remainder to determine bit number*/
         NVIC_local_var |= (1<<(NVIC_IRQn%32));
         NVIC_REG_Ptr->NVIC_ICERx[NVIC_IRQn/32] =NVIC_local_var;
         NVIC_State =NVIC_IRQNUM_OK;
    }
    else
    {
        NVIC_State = NVIC_IRQNUM_NOK;
    }
    return NVIC_State;
}

NVIC_ErrorStatus NVIC_SetPendingIRQ(NVIC_IRQn_Type NVIC_IRQn)
{
     NVIC_ErrorStatus NVIC_State= NVIC_IRQNUM_NOK;
    uint32_t NVIC_local_var;

    if(NVIC_IRQn >= 0 && NVIC_IRQn<=_NVIC_IRQn)
    {
         NVIC_local_var  = NVIC_REG_Ptr->NVIC_ISPRx[NVIC_IRQn/32];/*divide to determine reg number*/
         NVIC_local_var |= (1<<(NVIC_IRQn%32));/*remainder to determine bit number*/
         NVIC_REG_Ptr->NVIC_ISPRx[NVIC_IRQn/32] =NVIC_local_var;
         NVIC_State =NVIC_IRQNUM_OK;
    }
    else
    {
        NVIC_State = NVIC_IRQNUM_NOK;
    }
    return NVIC_State;

}

NVIC_ErrorStatus NVIC_ClearPendingIRQ(NVIC_IRQn_Type NVIC_IRQn)
{

    NVIC_ErrorStatus NVIC_State= NVIC_IRQNUM_NOK;
    uint32_t NVIC_local_var;

    if(NVIC_IRQn >= 0 && NVIC_IRQn<=_NVIC_IRQn)
    {
         NVIC_local_var  = NVIC_REG_Ptr->NVIC_ICPRx[NVIC_IRQn/32];
         /*divide to determine reg number*/
         NVIC_local_var |= (1<<(NVIC_IRQn%32));
         /*remainder to determine bit number*/
         NVIC_REG_Ptr->NVIC_ICPRx[NVIC_IRQn/32] = NVIC_local_var;
         NVIC_State =NVIC_IRQNUM_OK;
    }
    else
    {
        NVIC_State = NVIC_IRQNUM_NOK;
    }
    return NVIC_State;

}

NVIC_ErrorStatus NVIC_GetPendingIRQ(NVIC_IRQn_Type NVIC_IRQn,uint32_t *NVIC_Pending_bit)
{
    NVIC_ErrorStatus NVIC_State= NVIC_IRQNUM_NOK;
    uint32_t NVIC_local_var;

    if(NVIC_IRQn >= 0 && NVIC_IRQn<=_NVIC_IRQn)
    {
         NVIC_local_var    = NVIC_REG_Ptr->NVIC_ICPRx[NVIC_IRQn/32];
         /*divide to determine reg number*/
         NVIC_local_var    = ((NVIC_local_var>>(NVIC_IRQn%32))&1);
         /*remainder to determine bit number*/
         *NVIC_Pending_bit = NVIC_local_var;
         NVIC_State        = NVIC_IRQNUM_OK;
    }
    else
    {
        NVIC_State = NVIC_IRQNUM_NOK;
    }
    return NVIC_State;

}

NVIC_ErrorStatus NVIC_GetActiveIRQ(NVIC_IRQn_Type NVIC_IRQn,uint32_t *NVIC_Active_bit)
{
    NVIC_ErrorStatus NVIC_State= NVIC_IRQNUM_NOK;
    uint32_t NVIC_local_var;

    if(NVIC_IRQn >= 0 && NVIC_IRQn<=_NVIC_IRQn)
    {
         NVIC_local_var   = NVIC_REG_Ptr->NVIC_IABRx[NVIC_IRQn/32];
         /*divide to determine reg number*/
         NVIC_local_var   = ((NVIC_local_var>>(NVIC_IRQn%32))&1);
         /*remainder to determine bit number*/
         *NVIC_Active_bit = NVIC_local_var;
         NVIC_State       = NVIC_IRQNUM_OK;
    }
    else
    {
        NVIC_State = NVIC_IRQNUM_NOK;
    }
    return NVIC_State;

}
NVIC_ErrorStatus NVIC_SetPriority(NVIC_IRQn_Type NVIC_IRQn, uint8_t NVIC_Priority)
{
    NVIC_ErrorStatus NVIC_State= NVIC_IRQNUM_NOK;
   // uint32_t NVIC_local_var;
    
    if((NVIC_IRQn >= 0 && NVIC_IRQn<=_NVIC_IRQn) && (NVIC_Priority>=0 && NVIC_Priority<=255))
    {
        //NVIC_local_var  =NVIC_REG_Ptr->NVIC_IPRx[NVIC_IRQn/4];  
        //NVIC_local_var &= ~(NVIC_MASK_PRI<<((NVIC_IRQn%4)*8));  
        //3NVIC_local_var |=  (NVIC_Priority<<((NVIC_IRQn%4)*8));
        NVIC_REG_Ptr->NVIC_IPRx[NVIC_IRQn/4] = NVIC_EDIT_REG_MASK(NVIC_REG_Ptr->NVIC_IPRx[NVIC_IRQn/4] ,NVIC_SET_PRIORITY(NVIC_Priority),NVIC_SET);
        NVIC_State      =NVIC_IRQNUM_OK;
    }
    else
    {
        NVIC_State = NVIC_IRQNUM_NOK;
    }
    return NVIC_State;

}
NVIC_ErrorStatus NVIC_GetPriority(NVIC_IRQn_Type NVIC_IRQn,uint8_t *NVIC_pirority_val)
{

    NVIC_ErrorStatus NVIC_State= NVIC_IRQNUM_NOK;

    if(NVIC_IRQn >= 0 && NVIC_IRQn<=_NVIC_IRQn)
    {
        *NVIC_pirority_val = NVIC_GET_PRIORITY(NVIC_IRQn);  
       
        NVIC_State =NVIC_IRQNUM_OK;
    }
    else
    {
        NVIC_State = NVIC_IRQNUM_NOK;
    }
    return NVIC_State;

}
NVIC_ErrorStatus NVIC_TriggerSWInterrupt(NVIC_IRQn_Type NVIC_IRQn)
{
    
    NVIC_ErrorStatus NVIC_State= NVIC_IRQNUM_NOK;

    if(NVIC_IRQn >= 0 && NVIC_IRQn<=_NVIC_IRQn)
    {
        NVIC_REG_Ptr->NVIC_STIR=NVIC_IRQn;
        NVIC_State =NVIC_IRQNUM_OK;
    }
    else
    {
        NVIC_State = NVIC_IRQNUM_NOK;
    }
    return NVIC_State;

}

NVIC_ErrorStatus NVIC_SetPriorityGroup(NVIC_Num_GP_Level NVIC_GroupingPriorityNum)
{
    NVIC_ErrorStatus NVIC_Status = NVIC_OK ; 
    uint32_t NVIC_local;
    if(!((NVIC_GroupingPriorityNum <= NVIC_GP_0_bits) && (NVIC_GroupingPriorityNum >= NVIC_GP_7_bits)))
    {
        NVIC_Status = NVIC_NOK;
    }
    else
    {
        NVIC_local = NVIC_MASK_PRIGROUP | NVIC_MASK_VECTKEY;
        SCB_REG_Ptr->SCB_AIRCR=NVIC_EDIT_REG_MASK(SCB_REG_Ptr->SCB_AIRCR,NVIC_local,NVIC_CLEAR);
        NVIC_local = NVIC_SET_PRIGROUP(NVIC_GroupingPriorityNum) | NVIC_VECTKEY;
        SCB_REG_Ptr->SCB_AIRCR=NVIC_EDIT_REG_MASK(SCB_REG_Ptr->SCB_AIRCR,NVIC_local,NVIC_SET);
    }
    if (NVIC_GroupingPriorityNum + 1 > NVIC_NON_IMPLEMENTED_BITs)
    {
        /*if it already more than number of non-implemented bits ,just assign num of bits taken by subpir*/
        NVIC_SUBGROUP_BitNum = NVIC_GroupingPriorityNum + 1 ;
    }
    else
    {
        /*keep at least 1 bit for subgroup priority offset from non-implemented bits */
        NVIC_SUBGROUP_BitNum = NVIC_NON_IMPLEMENTED_BITs+1 ;
    }
    

    return NVIC_Status;
}
NVIC_ErrorStatus NVIC_GetPriorityGroup(NVIC_Num_GP_Level* NVIC_GroupPriorityBits_Num)
{
    NVIC_ErrorStatus NVIC_Status = NVIC_NOK ;

    if(NVIC_GroupPriorityBits_Num == NULL)
    {
        NVIC_Status = NVIC_NULL_PTR ;
    }
    else
    {
        *NVIC_GroupPriorityBits_Num = NVIC_GET_PRIGROUP((SCB_REG_Ptr -> SCB_AIRCR) & NVIC_MASK_PRIGROUP);
        NVIC_Status = NVIC_OK ;
    }
    return NVIC_Status;
}
NVIC_ErrorStatus NVIC_EncodePriority(uint8_t NVIC_PreemptPriority, uint8_t NVIC_SubPriority,uint8_t *NVIC_Priority_Val)
{
    
    NVIC_ErrorStatus NVIC_Status = NVIC_OK ;

    uint8_t NVIC_Preemption_BitsNum  = 8 - NVIC_SUBGROUP_BitNum;
    uint8_t NVIC_loc_max_preept      = (1<<NVIC_Preemption_BitsNum)-1;
    uint8_t NVIC_loc_max_SubPriority = (1<<(NVIC_SUBGROUP_BitNum-NVIC_NON_IMPLEMENTED_BITs))-1;
    if((NVIC_PreemptPriority > NVIC_loc_max_preept) || (NVIC_SubPriority > NVIC_loc_max_SubPriority))
    {
        NVIC_Status = NVIC_ERROR_VAL;
    }
    else if(NVIC_Priority_Val == NULL)
    {
        NVIC_Status = NVIC_NULL_PTR ;
    }
    else
    {
        *NVIC_Priority_Val = (NVIC_PreemptPriority << (NVIC_Preemption_BitsNum)) | (NVIC_SubPriority << (NVIC_NON_IMPLEMENTED_BITs));
    }
    
  
    return NVIC_Status;

}
NVIC_ErrorStatus NVIC_DecodePriority(uint8_t NVIC_GroupPriority, uint8_t NVIC_SubPriority, uint8_t NVIC_32PriGroup, uint8_t* NVIC_PriorityValue);

/************************************** NVIC_EDIT_Bit_Reg **********************************/

/* 
   
   * Functionality    : EDIT bit in register
   * Input Parameters : 1- Register you want to EDIT 
   *                    2- Number of Bit you want to EDIT
   *                    3- Select Operation you want to apply.
   *                       (options : CLEAR , SET , TOGGLE) 	
   
   * NOTE             :   
 
 */
static uint32_t NVIC_EDIT_Bit_Reg(uint32_t NVIC_REG_EDIT,uint32_t BIT_NUM,NVIC_REG_OPER OPERA)
{
	uint32_t NVIC_Local_Var =0;
	switch (OPERA)
	{
	
	case NVIC_CLEAR :
		{
			NVIC_Local_Var  = NVIC_REG_EDIT ;
			NVIC_Local_Var &= ~(1<<BIT_NUM);
			
		}
		break;
	case NVIC_SET :
		{
			NVIC_Local_Var  = NVIC_REG_EDIT ;
			NVIC_Local_Var |= (1<<BIT_NUM); 
		}break;

	default:
		break;
	}
	return NVIC_Local_Var;
}


/************************************** NVIC_EDIT_REG_MASK **********************************/

/* 
   
   * Functionality    : Apply mask on input register
   * Input Parameters : 1- Register you want to EDIT 
   *                    2- MASK 
   *                    3- Select Operation you want to apply.
   *                       (options : CLEAR , SET , TOGGLE) 	
   
   * NOTE             :   
 
 */
static uint32_t NVIC_EDIT_REG_MASK(uint32_t NVIC_REG_EDIT,uint32_t NVIC_MASK, NVIC_REG_OPER OPERA)
{
	uint32_t NVIC_Local_Var =0;
	switch (OPERA)
	{
	
		case NVIC_CLEAR :
			{
				NVIC_Local_Var  = NVIC_REG_EDIT ;
				NVIC_Local_Var &= ~NVIC_MASK;
				
			}
			break;
		case NVIC_SET :
			{
				NVIC_Local_Var  = NVIC_REG_EDIT ;
				NVIC_Local_Var |= NVIC_MASK; 
			}break;

		default:
			break;
	}
	return NVIC_Local_Var;
}