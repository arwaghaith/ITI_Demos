/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : USART     	       */
/*	Layer	  : MCAL               */
/*	Version   : 1.0                */
/*	Date	  : March 25 , 2024    */
/*	Last Edit : N/A                */
/***********************************/



/*************************************************************************************************/
/**********************************      USART   DRIVER        ***********************************/
/*************************************************************************************************/

#include "USART.h"
#include "GPIO.h"
#include "RCC.h"


#define USART_CLK_Frequency      16000000UL
#define USART_DIV_MANTISSA_POS   4U
#define USART_Init_BufferIdx     0
#define NULL (void*)0
/*****************************************************/
/****************   USART   Masks     ****************/
/*****************************************************/

/* Clear -> TE RE  PCE PS  UE M */
#define USART_CFG_MASK   0X0000360C
#define USART_STOP_MASK  0X00003000

#define USART_TXEIE_MASK      (uint32_t)(1<<TXEIE)
#define USART_TXE_MASK        (uint32_t)(1<<TXE)
#define USART_TCIE_MASK       (uint32_t)(1<<TCIE)
#define USART_IDLEIE_MASK     (uint32_t)(1<<IDLEIE)
#define USART_CLKEN_MASK      (uint32_t)(1<<CLKEN)
#define USART_LIN_MASK        (uint32_t)(1<<LINEN)
#define USART_CTSE_MASK       (uint32_t)(1<<CTSE)
#define USART_RTSE_MASK       (uint32_t)(1<<RTSE)
#define USART_DISABLE_Tx_MASK (uint32_t)(0<<TE)
#define USART_SmartCard       (uint32_t)(1<<SCEN)
#define USART_TE_MASK         (uint32_t)(1<<TE)
#define USART_RE_MASK         (uint32_t)(1<<RE)
#define USART_RXNEIE_MASK     (uint32_t)(1<<RXNEIE)
#define USART_UE_MASK         (uint32_t)(1<<UE)


/*****************************************************/
/**************   USART  Macro Checks ****************/
/*****************************************************/

#define USART_CHECK_Number(USART_Num) ((USART_Num==USART1) || (USART_Num==USART2) || (USART_Num==USART6))

/*****************************************************/
/**************   USART  Typedefs    *****************/
/*****************************************************/


typedef struct
{
    uint32_t USART_SR;
    uint32_t USART_DR;
    uint32_t USART_BRR;
    uint32_t USART_CR1;
    uint32_t USART_CR2;
    uint32_t USART_CR3;
    uint32_t USART_GTPR;

}USART_Registers_t;


typedef enum
{
	USART_CLEAR,
	USART_SET,
	USART_TOGGLE

}USART_REG_OPER;

typedef enum
{
	USART_TxRequest_Ready,
	USART_TxRequest_busy,
	USART_RxRequest_busy,
	USART_RxRequest_Ready

}USART_TxRequest_State_t;


typedef struct 
{
	uint8_t *  USART_ByteBufferPtr;
	uint32_t   USART_BufferSize;
	uint32_t   USART_BufferCurrentIdx;

}USART_Buffer_t;

typedef struct
{
	USART_Buffer_t          USART_Buffer;
	USART_TxRequest_State_t USART_RequestState;
    USART_CallBackFunc      USART_TxRx_CBFunc;
	
}USART_TxRxRequest_t;
/*
typedef struct 
{
	USART_TxRxRequest_t  USART_TxRequests;
	USART_TxRxRequest_t  USART_RxRequests;

}USART_Requests_t;
*/


static volatile USART_Registers_t * USART_Reg_ptr = NULL;

/*Array of transmission Reqests for each USART avaliable in system*/
USART_TxRxRequest_t USART_TxRequests[USART_NUM]={0};
USART_TxRxRequest_t USART_RxRequests[USART_NUM]={0};

/*****************************************************************************************************************************************************/
/*********************************************         Static Functions Prototypes Region        *****************************************************/
/*****************************************************************************************************************************************************/
static uint32_t USART_EDIT_REG_MASK    (uint32_t USART_REG_EDIT,uint32_t USART_MASK, USART_REG_OPER OPERA);
//static uint32_t USART_EDIT_Bit_Reg     (uint32_t SYSTICK_REG_EDIT,uint32_t BIT_NUM,USART_REG_OPER OPERA);
/******************************************************************************************************************************************************/


USART_ErrorStatus_t USART_Init(USART_CFG_t * USART_Cfg)
{
    uint32_t USART_local_mask   = 0x00000000,USART_local_mask2 = 0x00000000;
	float USARTDIV,DIV_FRACTION = 0.0;
	int DIV_Mantissa;

    USART_ErrorStatus_t USART_Local_error = USART_INIT_OK;

    if(!USART_Cfg)
    {
        USART_Local_error = USART_INIT_ERROR;
    }
    else
    {
        USART_Reg_ptr = (USART_Registers_t*)USART_Cfg->USART_Number;

        USART_local_mask         = USART_Cfg->USART_Sampling_rate | USART_Cfg->USART_Parity_mode | USART_Cfg->USART_Device_mode | USART_Cfg->USART_wordlength;
        USART_Reg_ptr->USART_CR1 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_CFG_MASK,USART_CLEAR);
        USART_Reg_ptr->USART_CR1 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_local_mask,USART_SET);
		USART_Reg_ptr->USART_CR2 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR2,USART_STOP_MASK,USART_CLEAR);
		USART_Reg_ptr->USART_CR2 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR2,USART_Cfg->USART_StopBitsNum,USART_SET);
        /*Enable USART*/
		USART_Reg_ptr->USART_CR1 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_UE_MASK,USART_SET);
        

		/*
		Baud Rate Calculations :
		
		Tx/Rx ×baudrate  =           fCK                                              fCK
		                    ------------------         --------->  USARTDIV =    ----------------
					      (8×(2-OVER8) × USARTDIV)                            (8×(2-OVER8 ) ×baudrate)

        */

		USARTDIV     =  ((float) USART_CLK_Frequency )/(float)(8*(2-((USART_Reg_ptr->USART_CR1)>>OVER8 &1))*USART_Cfg->USART_BaudRate);
		DIV_FRACTION =  (float)(((int)(USARTDIV*1000))%1000)/1000.0;
		DIV_Mantissa =  USARTDIV - DIV_FRACTION;
        
		if(USART_Cfg->USART_Sampling_rate == USART_OVERSAPMLING_16)
		{
			 DIV_FRACTION *=16;
			
			if(((int)(DIV_FRACTION*10))%10 >5)
			{
				DIV_FRACTION += 1;
				DIV_FRACTION =(int)(DIV_FRACTION);
			}
			else
			{
				DIV_FRACTION =(int)(DIV_FRACTION);
			}

			if(DIV_FRACTION > 15)
			{
				DIV_Mantissa++; 
				DIV_FRACTION = 0;
			}
	

		}
		else if(USART_Cfg->USART_Sampling_rate == USART_OVERSAPMLING_8)
		{
			 DIV_FRACTION *=8;
			
			if(((int)(DIV_FRACTION*10))%10 >5)
			{
				DIV_FRACTION += 1;
				DIV_FRACTION =(int)(DIV_FRACTION);
			}
			else
			{
				DIV_FRACTION =(int)(DIV_FRACTION);
			}
			
			if(DIV_FRACTION > 7)
			{
				DIV_Mantissa++; 
				DIV_FRACTION = 0;
			}


		}
		USART_local_mask         = (0x068<<USART_DIV_MANTISSA_POS) | (int) (0x3);
		USART_Reg_ptr->USART_BRR = USART_local_mask ;




		switch (USART_Cfg->USART_mode_cfg)
		{
			case USART_Asynchronous_mode :
			{

			} break;

				
			case USART_Synchronous_mode :
			{
				/*
				   Enables the USART Clock 
				                     Clock polarity
									 Clock phase  
                */
                /*TE must be disabled while cfg CPOL & CPHA*/
				USART_local_mask2 = (USART_DISABLE_Tx_MASK & USART_Reg_ptr->USART_CR1);

				USART_Reg_ptr->USART_CR1 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_DISABLE_Tx_MASK,USART_CLEAR);
				USART_local_mask = USART_CLKEN_MASK | USART_Cfg->USART_ClockPolarity | USART_Cfg->USART_ClockPhase;
				USART_Reg_ptr->USART_CR2 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR2,USART_local_mask,USART_CLEAR);
				USART_Reg_ptr->USART_CR2 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR2,USART_local_mask,USART_SET);

				/*Return prvious cfg saved for TE*/
				USART_Reg_ptr->USART_CR1 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_local_mask2,USART_SET);

			} break;

			case  USART_HardwareFlowControl_mode :
			{

				/*
				GPIO pins for RTS (Request to Send) and CTS (Clear to Send) signals.
				Configure the GPIO pins as alternate function output (for RTS) and input (for CTS) pins.
				Set the GPIO alternate function mode and select the USART peripheral.
				*/
			    /* Set RTS and CTS bits in USART_CR3 to enable hardware flow control*/
				USART_local_mask = USART_CTSE_MASK | USART_RTSE_MASK ;
				USART_Reg_ptr->USART_CR3 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR3,USART_local_mask,USART_CLEAR);
				USART_Reg_ptr->USART_CR3 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR3,USART_local_mask,USART_SET);




			} break;
			
			
			case USART_LIN_mode :
			{
				/*Enabe LIN Mode*/
				USART_Reg_ptr->USART_CR2 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR2,USART_LIN_MASK,USART_SET);

				/*Set LIN Break Detection Length configuration*/
				USART_local_mask         = USART_Cfg->USART_Break_Detection_Length ;
				USART_Reg_ptr->USART_CR2 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR2,USART_local_mask,USART_SET);


			} break;
		

			case USART_FullDuplex_mode :
			{

			} break;

			case USART_HalfDuplex_mode :
			{

			} break;

			
			case USART_SmartCard_mode :
			{
				USART_Reg_ptr->USART_CR3 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR3,USART_SmartCard,USART_SET);

			} break;

			case USART_IrDA_mode :
			{

			} break;
		
			default:
			{

			} break;
		}

		

    }
     
	return USART_Local_error;
}
USART_ErrorStatus_t USART_ENABLE_TXE_INT(void* USART_Number)
{
	USART_ErrorStatus_t USART_Local_error = USART_INT_Enabled;
	USART_Reg_ptr =  (USART_Registers_t*) USART_Number;
	if (!USART_CHECK_Number(USART_Number))
	{
		USART_Local_error = USART_ERROR;
		
	}
	
	USART_Reg_ptr->USART_CR1 =USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1 , USART_TXEIE_MASK,USART_SET);

	return USART_Local_error;

}
USART_ErrorStatus_t USART_DISABLE_TXE_INT(void* USART_Number)
{
	USART_ErrorStatus_t USART_Local_error = USART_INT_Disabled;
	if (!USART_CHECK_Number(USART_Number))
	{
		USART_Local_error = USART_ERROR;
		
	}

	USART_Reg_ptr->USART_CR1 =USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1 , USART_TXEIE_MASK,USART_CLEAR);

	return USART_Local_error;

}
USART_ErrorStatus_t USART_ENABLE_TC_INT(void* USART_Number)
{

	USART_ErrorStatus_t USART_Local_error = USART_INT_Enabled;
	USART_Reg_ptr =  (USART_Registers_t*) USART_Number;
	if (!USART_CHECK_Number(USART_Number))
	{
		USART_Local_error = USART_ERROR;
		
	}
	else
	{
			USART_Reg_ptr->USART_CR1 =USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1 , USART_TCIE_MASK , USART_SET);
			USART_Local_error = USART_OK;

	}


	return USART_Local_error;


}
USART_ErrorStatus_t USART_DISABLE_TC_INT(void* USART_Number)
{
	
	USART_ErrorStatus_t USART_Local_error = USART_INT_Disabled;
	USART_Reg_ptr =  (USART_Registers_t*) USART_Number;
	if (!USART_CHECK_Number(USART_Number))
	{
		USART_Local_error = USART_ERROR;
		
	}
	else
	{
			USART_Reg_ptr->USART_CR1 =USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1 , USART_TCIE_MASK , USART_CLEAR);
            USART_Local_error = USART_OK;

	}


	return USART_Local_error;
}
USART_ErrorStatus_t USART_ENABLE_RXEIE_INT(void* USART_Number)
{
	USART_ErrorStatus_t USART_Local_error = USART_INT_Disabled;
	USART_Reg_ptr =  (USART_Registers_t*) USART_Number;
	if (!USART_CHECK_Number(USART_Number))
	{
		USART_Local_error = USART_ERROR;
		
	}
	else
	{
		USART_Reg_ptr->USART_CR1 =USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1 ,USART_RXNEIE_MASK,USART_SET);
		USART_Local_error = USART_OK;
	}
	



	return USART_Local_error;

}
USART_ErrorStatus_t USART_DISABLE_RXEIE_INT(void* USART_Number)
{
	USART_ErrorStatus_t USART_Local_error = USART_INT_Disabled;
	USART_Reg_ptr =  (USART_Registers_t*) USART_Number;
	if (!USART_CHECK_Number(USART_Number))
	{
		USART_Local_error = USART_ERROR;
		
	}
	else
	{
		USART_Reg_ptr->USART_CR1 =USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1 ,USART_RXNEIE_MASK,USART_CLEAR);
		USART_Local_error = USART_OK;
	}


	return USART_Local_error;


}
uint8_t  USART_GetTXE(void* USART_Number)
{
	USART_Reg_ptr =  (USART_Registers_t*) USART_Number;

	return ((USART_Reg_ptr->USART_SR & USART_TXE_MASK)>>TXE);

}
uint8_t  USART_GetRXNE(void* USART_Number)
{
	USART_Reg_ptr =  (USART_Registers_t*) USART_Number;
	return ((USART_Reg_ptr->USART_SR & USART_TXE_MASK)>>RXNE);


}
uint8_t  USART_GetTC(void* USART_Number)
{
	USART_Reg_ptr =  (USART_Registers_t*) USART_Number;

	return ((USART_Reg_ptr->USART_SR & USART_TXE_MASK)>>TC);

}

USART_ErrorStatus_t USART_TxByte_Sync(void* USART_Number ,uint8_t USART_Byte)
{
    USART_ErrorStatus_t USART_Local_error = USART_ERROR;
    uint32_t timeout = 10000 ;
	USART_Reg_ptr =  (USART_Registers_t*) USART_Number;

	if (!USART_CHECK_Number(USART_Number))
		{
			USART_Local_error = USART_ERROR;
			
		}
    
	else
	{	
        USART_DISABLE_TXE_INT(USART_Number);
      
        if (USART_GetTXE(USART_Number))
		{
			 USART_Reg_ptr->USART_DR = USART_Byte;
			
			while( !USART_GetTXE(USART_Number) && timeout )
			{
				timeout--;
			}
			if(! timeout)
			{
				USART_Local_error = USART_TIMEOUT;
			}/* Data is transferred to the shift register*/
			else if( USART_GetTXE(USART_Number) )
			{
				USART_Local_error = USART_ByteSent;
			}
		}
		else
		{
			USART_Local_error = USART_ByteDropped;
		}
       
	}

   return USART_Local_error;

}

USART_ErrorStatus_t USART_TxByte_Async(USART_Request_t USART_TxRequest)
{
	USART_ErrorStatus_t USART_Local_error = USART_ERROR;
	USART_Reg_ptr =  (USART_Registers_t*) USART_TxRequest.USART_Number;
    
	if (!USART_CHECK_Number(USART_TxRequest.USART_Number))
		{
			USART_Local_error = USART_ERROR;
			
		}
	else if (!(USART_TxRequest.USART_CBFunc|| USART_TxRequest.USART_Data))
		{
			USART_Local_error = USART_NULL_PTR;
		}
	else if(USART_TxRequests[USART_TxRequest.USART_ID].USART_RequestState == USART_TxRequest_busy)
		{
			USART_Local_error = USART_Busy;
		}
	else
		{
			
			/*Assign USART based on Argument USART ID with its request buffer data size and state of this request */
			USART_TxRequests[USART_TxRequest.USART_ID].USART_RequestState                  = USART_TxRequest_busy ;
			USART_TxRequests[USART_TxRequest.USART_ID].USART_Buffer.USART_ByteBufferPtr    = USART_TxRequest.USART_Data;
			USART_TxRequests[USART_TxRequest.USART_ID].USART_Buffer.USART_BufferSize       = USART_TxRequest.USART_DataArraySize;
			USART_TxRequests[USART_TxRequest.USART_ID]. USART_TxRx_CBFunc                  = USART_TxRequest.USART_CBFunc;
			USART_TxRequests[USART_TxRequest.USART_ID].USART_Buffer.USART_BufferCurrentIdx = USART_Init_BufferIdx ;
			USART_Reg_ptr->USART_CR1= USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_TE_MASK,USART_SET);
            /*Sening 1st byte to trigger Tx interrupt*/
			USART_Reg_ptr->USART_DR = USART_TxRequests[USART_TxRequest.USART_ID].USART_Buffer.USART_ByteBufferPtr[0];
			USART_TxRequests[USART_TxRequest.USART_ID].USART_Buffer.USART_BufferCurrentIdx++;
			USART_ENABLE_TXE_INT(USART_TxRequest.USART_Number);

			USART_Local_error = USART_OK;
		}
    

   return USART_Local_error;

}

USART_ErrorStatus_t USART_RxByte_Sync(void* USART_Number ,uint8_t * USART_Byte)
{
	USART_ErrorStatus_t USART_Local_ErrorStatus =USART_ERROR ;
    uint32_t timeout = 10000 ;
	USART_Reg_ptr =  (USART_Registers_t*) USART_Number;


	if (!USART_CHECK_Number(USART_Number))
		{
			USART_Local_ErrorStatus = USART_ERROR;
			
		}
	else if (!USART_Byte )
	{
		USART_Local_ErrorStatus =USART_NULL_PTR;
	
	}
	else
		{
			while(!USART_GetRXNE(USART_Number) && timeout)
			{
				timeout--;
			}
			if(! timeout)
			{
				USART_Local_ErrorStatus = USART_TIMEOUT;
			}/* Data is transferred to the shift register*/
			else if( USART_GetRXNE(USART_Number) )
			{
				*USART_Byte = (uint8_t)((USART_Reg_ptr->USART_DR) & 0xFF);
				USART_Local_ErrorStatus = USART_ByteReceived;
			}
			
		}

   return USART_Local_ErrorStatus;
}

USART_ErrorStatus_t USART_RxByte_Async(USART_Request_t USART_RxRequest)
{
	
	USART_ErrorStatus_t USART_Local_error ;
	USART_Reg_ptr =  (USART_Registers_t*) USART_RxRequest.USART_Number;

	if (!USART_CHECK_Number(USART_RxRequest.USART_Number))
		{
			USART_Local_error = USART_ERROR;
			
		}
	else if (!(USART_RxRequest.USART_CBFunc|| USART_RxRequest.USART_Data))
		{
			USART_Local_error = USART_NULL_PTR;
		}
	else if(USART_TxRequests[USART_RxRequest.USART_ID].USART_RequestState == USART_TxRequest_busy)
		{
			USART_Local_error = USART_Busy;
		}
   else
		{
			
			/*Assign USART based on Argument USART ID with its request buffer data size and state of this request */
			USART_RxRequests[USART_RxRequest.USART_ID].USART_RequestState                  = USART_RxRequest_busy ;
			USART_RxRequests[USART_RxRequest.USART_ID].USART_Buffer.USART_ByteBufferPtr    = USART_RxRequest.USART_Data;
			USART_RxRequests[USART_RxRequest.USART_ID].USART_Buffer.USART_BufferSize       = USART_RxRequest.USART_DataArraySize;
			USART_RxRequests[USART_RxRequest.USART_ID].USART_Buffer.USART_BufferCurrentIdx = USART_Init_BufferIdx;

			USART_Reg_ptr->USART_CR1 =USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_RE_MASK,USART_SET);
			USART_ENABLE_RXEIE_INT(USART_RxRequest.USART_Number);

		    USART_Local_error = USART_OK;
			
		}




   return USART_Local_error;

}
void USART1_IRQHandler(void)
{
	USART_Reg_ptr =  (USART_Registers_t*)USART1;
	if(USART_GetTXE(USART1))
	{
		if(USART_TxRequests[USART1_ID].USART_Buffer.USART_BufferCurrentIdx < USART_TxRequests[USART1_ID].USART_Buffer.USART_BufferSize)
		{
			USART_Reg_ptr->USART_DR = USART_TxRequests[USART1_ID].USART_Buffer.USART_ByteBufferPtr[USART_TxRequests[USART1_ID].USART_Buffer.USART_BufferCurrentIdx];
			USART_TxRequests[USART1_ID].USART_Buffer.USART_BufferCurrentIdx++;

		}
		else if (USART_GetTC(USART1))
		{
			/* code */
		}
		
		{
			/*Finished and become ready for another tranfer request*/
			USART_TxRequests[USART1_ID].USART_RequestState = USART_TxRequest_Ready;
			USART_DISABLE_TXE_INT(USART1);
			USART_Reg_ptr->USART_CR1 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_TE_MASK,USART_CLEAR);
			/*Executing action required after transmission completed sucessfully*/
			USART_TxRequests[USART1_ID].USART_TxRx_CBFunc();
			
		}
	}
	if(USART_GetRXNE(USART1))
	{
		if(USART_RxRequests[USART1_ID].USART_Buffer.USART_BufferCurrentIdx < USART_RxRequests[USART1_ID].USART_Buffer.USART_BufferSize)
		{
			USART_RxRequests[USART1_ID].USART_Buffer.USART_ByteBufferPtr[USART_RxRequests[USART1_ID].USART_Buffer.USART_BufferCurrentIdx] = USART_Reg_ptr->USART_DR ;
			USART_RxRequests[USART1_ID].USART_Buffer.USART_BufferCurrentIdx++;

		}
		else
		{
			/*Finished and become ready for another tranfer request*/
			USART_RxRequests[USART1_ID].USART_RequestState = USART_RxRequest_Ready;
			USART_DISABLE_RXEIE_INT(USART1);
			USART_Reg_ptr->USART_CR1 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_RE_MASK,USART_CLEAR);
			/*Executing action required after transmission completed sucessfully*/
			USART_RxRequests[USART1_ID].USART_TxRx_CBFunc();
			
		}



	}


}
void USART2_IRQHandler(void)
{
	USART_Reg_ptr =  (USART_Registers_t*)USART2;
	if(USART_GetTXE(USART2))
	{
		if(USART_TxRequests[USART2_ID].USART_Buffer.USART_BufferCurrentIdx < USART_TxRequests[USART2_ID].USART_Buffer.USART_BufferSize)
		{
			USART_Reg_ptr->USART_DR = USART_TxRequests[USART2_ID].USART_Buffer.USART_ByteBufferPtr[USART_TxRequests[USART2_ID].USART_Buffer.USART_BufferCurrentIdx];
			USART_TxRequests[USART2_ID].USART_Buffer.USART_BufferCurrentIdx++;

		}
		else if (USART_GetTC(USART2))
		{
			/*Finished and become ready for another tranfer request*/
			USART_TxRequests[USART2_ID].USART_RequestState = USART_TxRequest_Ready;
			USART_DISABLE_TXE_INT(USART2);
			USART_Reg_ptr->USART_CR1 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_TE_MASK,USART_CLEAR);
			/*Executing action required after transmission completed sucessfully*/
			USART_TxRequests[USART2_ID].USART_TxRx_CBFunc();
			
		}
	}
	if(USART_GetRXNE(USART2))
		{
			if(USART_RxRequests[USART2_ID].USART_Buffer.USART_BufferCurrentIdx < USART_RxRequests[USART2_ID].USART_Buffer.USART_BufferSize)
			{
				USART_RxRequests[USART2_ID].USART_Buffer.USART_ByteBufferPtr[USART_RxRequests[USART2_ID].USART_Buffer.USART_BufferCurrentIdx] = USART_Reg_ptr->USART_DR ;
				USART_RxRequests[USART2_ID].USART_Buffer.USART_BufferCurrentIdx++;

			}
			else
			{
				/*Finished and become ready for another tranfer request*/
				USART_RxRequests[USART2_ID].USART_RequestState = USART_RxRequest_Ready;
				USART_DISABLE_RXEIE_INT(USART2);
				USART_Reg_ptr->USART_CR1 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_RE_MASK,USART_CLEAR);
				/*Executing action required after transmission completed sucessfully*/
				USART_RxRequests[USART2_ID].USART_TxRx_CBFunc();
				
			}



		}


}
void USART6_IRQHandler(void)
{
	USART_Reg_ptr =  (USART_Registers_t*)USART6;
	if(USART_GetTXE(USART6))
		{
			if(USART_TxRequests[USART6_ID].USART_Buffer.USART_BufferCurrentIdx < USART_TxRequests[USART6_ID].USART_Buffer.USART_BufferSize)
			{
				USART_Reg_ptr->USART_DR = USART_TxRequests[USART6_ID].USART_Buffer.USART_ByteBufferPtr[USART_TxRequests[USART6_ID].USART_Buffer.USART_BufferCurrentIdx];
				USART_TxRequests[USART6_ID].USART_Buffer.USART_BufferCurrentIdx++;

			}
			else if (USART_GetTC(USART6))
			{
				/*Finished and become ready for another tranfer request*/
				USART_TxRequests[USART6_ID].USART_RequestState = USART_TxRequest_Ready;
				USART_DISABLE_TXE_INT(USART6);
				USART_Reg_ptr->USART_CR1 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_TE_MASK,USART_CLEAR);
				/*Executing action required after transmission completed sucessfully*/
				USART_TxRequests[USART6_ID].USART_TxRx_CBFunc();
				
			}
		}
		if(USART_GetRXNE(USART6))
		{
			if(USART_RxRequests[USART6_ID].USART_Buffer.USART_BufferCurrentIdx < USART_RxRequests[USART6_ID].USART_Buffer.USART_BufferSize)
			{
				USART_RxRequests[USART6_ID].USART_Buffer.USART_ByteBufferPtr[USART_RxRequests[USART6_ID].USART_Buffer.USART_BufferCurrentIdx] = USART_Reg_ptr->USART_DR ;
				USART_RxRequests[USART6_ID].USART_Buffer.USART_BufferCurrentIdx++;

			}
			else
			{
				/*Finished and become ready for another tranfer request*/
				USART_RxRequests[USART6_ID].USART_RequestState = USART_RxRequest_Ready;
				USART_DISABLE_RXEIE_INT(USART6);
				USART_Reg_ptr->USART_CR1 = USART_EDIT_REG_MASK(USART_Reg_ptr->USART_CR1,USART_RE_MASK,USART_CLEAR);
				/*Executing action required after transmission completed sucessfully*/
				USART_RxRequests[USART6_ID].USART_TxRx_CBFunc();
				
			}



		}


}

/************************************** USART_EDIT_Bit_Reg **********************************/

/* 
   
   * Functionality    : EDIT bit in register
   * Input Parameters : 1- Register you want to EDIT 
   *                    2- Number of Bit you want to EDIT
   *                    3- Select Operation you want to apply.
   *                       (options : CLEAR , SET , TOGGLE) 	
   
   * NOTE             :   
 
 */
/*
static uint32_t USART_EDIT_Bit_Reg(uint32_t USART_REG_EDIT,uint32_t BIT_NUM,USART_REG_OPER OPERA)
{
	uint32_t USART_Local_Var =0;
	switch (OPERA)
	{
	
	case USART_CLEAR :
		{
			USART_Local_Var  = USART_REG_EDIT ;
			USART_Local_Var &= ~(1<<BIT_NUM);
			
		}
		break;
	case USART_SET :
		{
			USART_Local_Var  = USART_REG_EDIT ;
			USART_Local_Var |= (1<<BIT_NUM); 
		}break;

	default:
		break;
	}
	return USART_Local_Var;
}

*/
/************************************** USART_EDIT_REG_MASK **********************************/

/* 
   
   * Functionality    : Apply mask on input register
   * Input Parameters : 1- Register you want to EDIT 
   *                    2- MASK 
   *                    3- Select Operation you want to apply.
   *                       (options : CLEAR , SET , TOGGLE) 	
   
   * NOTE             :   
 
 */
static uint32_t USART_EDIT_REG_MASK(uint32_t USART_REG_EDIT,uint32_t USART_MASK, USART_REG_OPER OPERA)
{
	uint32_t USART_Local_Var =0;
	switch (OPERA)
	{
	
		case USART_CLEAR :
			{
				USART_Local_Var  = USART_REG_EDIT ;
				USART_Local_Var &= ~USART_MASK;
				
			}
			break;
		case USART_SET :
			{
				USART_Local_Var  = USART_REG_EDIT ;
				USART_Local_Var |= USART_MASK; 
			}break;

		default:
			break;
	}
	return USART_Local_Var;
}
