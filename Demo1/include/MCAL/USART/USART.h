/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		  : USART     	       */
/*	Layer	  : MCAL               */
/*	Version   : 1.0                */
/*	Date	  : March 25 , 2024    */
/*	Last Edit : N/A                */
/***********************************/



/************************************************************************************/
/**************************      USART   DRIVER         *****************************/
/************************************************************************************/
#include"NVIC_IRQn.h"

/*UART_NUMBER*/

#define USART1  (void*)0x40011000
#define USART2  (void*)0x40014400
#define USART6  (void*)0x40011400

#define USART_NUM  3U

#define CLKEN   11U
#define CPOL    10U
#define CPHA    9U
#define STOP    12U
#define TE      3U
#define RE      2U
#define OVER8   15U
#define PS_PCE  9U
#define UE      13U
#define M       12U
#define LINEN   14U
#define CTSE    9U
#define RTSE    8U
#define LBDL    5U
#define RXNEIE  5U
#define IDLEIE  4U
#define TCIE    6U
#define TXEIE   7U
#define PEEIE   8U
#define TXE     7U
#define TC      6U
#define SCEN    5U
#define RE      2U
#define RXNE    5U



typedef unsigned int uint32_t;
typedef enum
{
    USART_Asynchronous_mode,
    USART_Synchronous_mode,
    USART_LIN_mode,
    USART_HardwareFlowControl_mode,
    USART_Multiprocessor_mode,
    USART_SmartCard_mode,
    USART_HalfDuplex_mode,
    USART_MultiBufferCommunication_mode,
    USART_IrDA_mode,
    USART_FullDuplex_mode


}USART_Confguration_mode;

typedef enum
{
    USART1_ID,
    USART2_ID,
    USART6_ID

}USART_ID_t;

typedef enum
{
    /*0: (1 Start bit, 8 Data bits, n Stop bit)*/
    USART_WORD_LENGTH_8 = (0<<M),
    /*1: (1 Start bit, 9 Data bits, n Stop bit)*/
    USART_WORD_LENGTH_9 = (1<<M)

 }USART_wordlength_t;

 typedef enum
{
    USART_DISABLE = (0<<UE),
    USART_ENABLE  = (1<<UE)

 }USART_EN_DIS_t;


typedef enum
{ 
    USART_StopBits_1   = (0<<STOP),
    USART_StopBits_0_5 = (1<<STOP),
    USART_StopBits_2   = (2<<STOP),
    USART_StopBits_1_5 = (3<<STOP),

 }USART_StopBitsNum_t;

 typedef enum
{
    USART_Parity_Enable_even = (2<<PS_PCE),
    USART_Parity_Enable_odd  = (3<<PS_PCE),
    USART_Parity_Disable     = (0<<PS_PCE)

 }USART_ParityControl_mode_t;

 
 typedef enum
{
    USART_CK_Disabled   = (0<<CLKEN),
    USART_CK_Enabled    = (1<<CLKEN)

 }USART_Clock_Enable_t;

 typedef enum
{
    USART_first_clock_transition    = (0<<CPHA),
    USART_Second_clock_transition   = (1<<CPHA)

 }USART_Clock_phase_t;

  typedef enum
{
    USART_Steady_LowValue_CK    = (0<<CPOL),
    USART_Steady_HighValue_CK   = (1<<CPOL)

 }USART_ClockPolarity_t;

typedef enum
{
    /*Note: Oversampling by 8 is not available in the Smartcard, IrDA and LIN modes: when 
    SCEN=1,IREN=1 or LINEN=1 then OVER8 is forced to ‘0 by hardware.*/
    USART_OVERSAPMLING_16   = (0<<OVER8),
    USART_OVERSAPMLING_8    = (1<<OVER8)

}USART_OVERSAPMLING_t;


typedef enum
{
    USART_NO_BD      = 0,
    USART_LBDL_10    = (0<<LBDL),
    USART_LBDL_11    = (1<<LBDL)

}USART_LIN_BDL_t;


typedef enum
{
    USART_Receiver_mode    = (1<<RE),
    USART_Transmitter_mode = (1<<TE),
    USART_FullDuplex_mode_  = (3<<RE)

}USART_Device_mode_t;

typedef void ( * USART_CallBackFunc)(void) ;

typedef unsigned char uint8_t;

typedef enum 
{
    USART_OK,
    USART_ERROR,
    USART_INIT_OK,
    USART_INIT_ERROR,
    USART_INT_Enabled,
    USART_INT_Disabled,
    USART_ByteSent,
    USART_TIMEOUT,
    USART_ByteDropped,
    USART_ByteReceived,
    USART_NULL_PTR,
    USART_Busy


}USART_ErrorStatus_t;

typedef struct 
{
    USART_Confguration_mode    USART_mode_cfg;
    uint32_t                   USART_BaudRate;
    USART_OVERSAPMLING_t       USART_Sampling_rate;
    USART_wordlength_t         USART_wordlength;
    USART_StopBitsNum_t        USART_StopBitsNum;
    USART_ParityControl_mode_t USART_Parity_mode;
    USART_Device_mode_t        USART_Device_mode;
    void*                      USART_Number;
    USART_ClockPolarity_t      USART_ClockPolarity;
    USART_Clock_phase_t        USART_ClockPhase;
    USART_LIN_BDL_t            USART_Break_Detection_Length;
    

}USART_CFG_t;

/*

  USART_Data          :  User create array of char "Byte" and assign to 
                         USART Request.

  USART_DataArraySize : Array size.

  USART_Number        : USART1 - USART2 - USART6.
  USART_ID            : USART1_ID - USART2_ID - USART6_ID.
   
  USART_Tx_CBFunc     : Create CB function.

*/
typedef struct
{
	uint8_t*            USART_Data;
	uint32_t            USART_DataArraySize;
	void*               USART_Number;
	USART_ID_t          USART_ID;
    USART_CallBackFunc  USART_CBFunc;
	
}USART_Request_t;

/*****************************  USART_Init  ***************************
 * 
 * Functionality  : 1 - Enable the clock for the USART peripheral in 
 *                      the RCC.
 *                  2 - Configure the GPIO pins that are connected to the 
 *                      USART peripheral for alternate function mode.
 *                  3 - Calculate the baud rate divisor and configure
 *                      the USART_BRR register accordingly
 *                  4 -  Set word length, parity control, stop bits,
 *                       Sampling rate and enable transmitter and 
 *                       receiver.
 *                  5 - Set the UE.
 *                  6 - Set device mode -> set TE (Transmitter Enable) 
 *                      and/or RE (Receiver Enable) .
 *                  7 - Write the data to send in the USART_DR 
 *                      register (this clears the TXE bit).
 *                      Repeat this for each data to be transmitted 
 *                      in case of single buffer.
 *                  8 - After writing the last data into the USART_DR 
 *                      register, wait until TC=1. This indicates 
 *                      that the transmission of the last frame is complete.
 *                      This is required for instance when 
 *                      the USART is disabled or enters the Halt mode to avoid
 *                      corrupting the last transmission.
 * 
 * Input Prameter :   User create struct of type " USART_CFG_t "
 *                    start fill parameters of :
 *                    
 *                   1- Mode : (USART_Asynchronous_mode,
                                USART_Synchronous_mode,
                                USART_LIN_mode,
                                USART_HardwareFlowControl_mode,
                                USART_Multiprocessor_mode,
                                USART_SmartCard_mode,
                                USART_HalfDuplex_mode,
                                USART_MultiBufferCommunication_mode,
                                USART_IrDA_mode).

                    2 - USART_BaudRate -> Baudrate Value.

                    3 - USART_Sampling_rate -> (USART_OVERSAPMLING_16 ,USART_OVERSAPMLING_8)
 * 
**********************************************************************************/
USART_ErrorStatus_t USART_Init(USART_CFG_t * USART_Cfg);
/******************************  USART_ENABLE_TXE_INT  ***************************
 * 
 *  Functionality  : This function enables Interrupt generation by Microcontroller,
 *                   when transmit data register is ready to accept new data for 
 *                   transmission.
 *               
 * Input Parmeters : USART ID number to enable its TXE Interrupt.
 * Return          : Error Status about this function.
 * 
**********************************************************************************/
USART_ErrorStatus_t USART_ENABLE_TXE_INT(void* USART_Number);
/******************************  USART_DISABLE_TXE_INT  ***************************
 * 
 *  Functionality  : This function disabes Interrupt generation by Microcontroller,
 *                   when transmit data register is ready to accept new data for 
 *                   transmission.
 *               
 * Input Parmeters : USART ID number to enable its TXE Interrupt.
 * Return          : Error Status about this function.
 * 
**********************************************************************************/
USART_ErrorStatus_t USART_DISABLE_TXE_INT(void* USART_Number);
/******************************  USART_GetTXE  ***************************
 * 
 *  Functionality  : This function Gets the state of TX bit flag in SR register
 *                   to check if the data in transmit data registe is transmitted
 *                   and ready for new data transmission. 
 *               
 * Input Parmeters : USART ID number.
 * Return          : bit value 1 / 0.
 * 
**********************************************************************************/
uint8_t  USART_GetTXE(void* USART_Number);
/******************************  USART_GetTC  ************************************
 * 
 *  Functionality  : This function Gets the state of TC bit flag in SR register
 *                   to check if the whole frame is transmitted or not in both
 *                   Data Register and shift register. 
 *               
 * Input Parmeters : USART ID number.
 * Return          : bit value 1 / 0.
 * 
**********************************************************************************/
uint8_t  USART_GetTC(void* USART_Number);
/******************************  USART_GetRXNE  ************************************
 * 
 *  Functionality  : This function Gets the state of RXNE bit flag in SR register
 *                   to check if there is data from RDR from shift register is 
 *                   transfere to rececive data register and ready to read it . 
 *               
 * Input Parmeters : USART ID number.
 * 
 * Return          : bit value 1 / 0.
 * 
**********************************************************************************/
uint8_t  USART_GetRXNE(void* USART_Number);
/********************************  USART_ENABLE_TC_INT  ******************************
 *
 *   Functionality  : This function enables Interrupt generation by Microcontroller,
 *                    when all data in the transmit shift register and the shift register
 *                    itself have completed.
 *                    This flag indicates that the transmission of all data in the 
 *                    transmit shift register and the shift register
 *                    itself have completed.
 * 
 *  Input Parmeters : USART ID number to enable its TXE Interrupt.
 * 
 *  Return          : Error Status about this function.
 * 
 *  Note            : The TC (Transmission Complete) flag in the USART_SR register 
 *                    indicates that the entire frame, including the start bit, 
 *                    data bits, parity bit (if enabled), and stop bit(s), has 
 *                    been successfully transmitted.
 * 
**********************************************************************************/
USART_ErrorStatus_t USART_ENABLE_TC_INT(void* USART_Number);
/******************************  USART_DISABLE_TC_INT  ***************************
 * 
 *  Functionality  : This function disables Interrupt generation by Microcontroller,
 *                   when transmit when Frame transmission is completed.
 *               
 * Input Parmeters : USART ID number to enable its TXE Interrupt.
 * 
 * Return          : Error Status about this function.
 * 
**********************************************************************************/
USART_ErrorStatus_t USART_DISABLE_TC_INT(void* USART_Number);
/******************************  USART_ENABLE_RXEIE_INT  ***************************
 * 
 *  Functionality  : This function enables Interrupt generation by Microcontroller,
 *                   whenever the receive data register becomes not empty new data
 *                   is available for reading
 *               
 * Input Parmeters : USART ID number to enable its RXE Interrupt.
 * 
 * Return          : Error Status about this function.
 * 
**********************************************************************************/
USART_ErrorStatus_t USART_ENABLE_RXEIE_INT(void* USART_Number);
/***************************  USART_DISABLE_RXEIE_INT  ***************************
 * 
 *  Functionality  : This function disables the USART from generating interrupts 
 *                   for incoming data.
 *               
 * Input Parmeters : USART ID number to disable its RXE Interrupt.
 * 
 * Return          : Error Status about this function.
 * 
**********************************************************************************/
USART_ErrorStatus_t USART_DISABLE_RXEIE_INT(void* USART_Number);
/******************************  USART_TxByte_Sync  *******************************
 * 
 *  Functionality  : This function sends a Byte .
 *               
 * Input Parmeters : USART ID number to enable its TXE Interrupt.
 * Return          : Error Status about this function.
 * 
**********************************************************************************/
USART_ErrorStatus_t USART_TxByte_Sync(void* USART_Number ,uint8_t USART_Byte);
/******************************  USART_TxByte_Async  ***************************
 * 
 *  Functionality  : This function assign the input struct createed by user and 
 *                   start copy the required data to the transmisssion buffer
 *                   Request based on USART Id required and then transmit first 
 *                   Byte to initiate the transmission process by triggring first 
 *                   INT .s
 *               
 * Input Parmeters : USART_Request_t
 *                   user create struct of this data type and create an array of 
 *                   bytes as buffer want to transfer , besides the size of 
 *                   this array, then user must assign USART number on which 
 *                   want to transfer this data ,  finally the callback function 
 *                   required to be executed once this buffer is transferred
 *                   successfully.
 * 
 * Return          : Error Status about this function.
 * 
**********************************************************************************/
USART_ErrorStatus_t USART_TxByte_Async(USART_Request_t USART_TxRequest);
/******************************  USART_RxByte_Sync  ******************************
 * 
 *  Functionality  : This function disabes Interrupt generation by Microcontroller,
 *                   when transmit data register is ready to accept new data for 
 *                   transmission.
 *               
 * Input Parmeters : USART ID number to enable its TXE Interrupt.
 * Return          : Error Status about this function.
 * 
**********************************************************************************/
USART_ErrorStatus_t USART_RxByte_Sync(void* USART_Number ,uint8_t * USART_Byte);
/******************************  USART_RxByte_Async  ******************************
 * 
 *  Functionality  : This function disabes Interrupt generation by Microcontroller,
 *                   when transmit data register is ready to accept new data for 
 *                   transmission.
 *               
 * Input Parmeters : USART ID number to enable its TXE Interrupt.
 * 
 * Return          : Error Status about this function.
 * 
**********************************************************************************/
USART_ErrorStatus_t USART_RxByte_Async(USART_Request_t USART_RxRequest);
/******************************  USART1_IRQHandler  ******************************
 * 
 *  Functionality  : This function Handles Asyncrounus Byte transmission based on 
 *                   USART Id number it handles both trasmission nd received bytes 
 *                   1st it checks on the idx of buffer if still didn't finish 
 *                   it continue sending or receiving bytes and increamenting bytes
 *                   till finish the request buffer nd then execute its assigned 
 *                   Call back function.
 *               
 * Input Parmeters : void.
 * 
 * Return          : void.
 * 
**********************************************************************************/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART6_IRQHandler(void);

/*When CPOL=0, the clock starts from 0 or low level and then it toggles. 
Here the idle state is 0, which is at the end of the clock cycle.

Idle state means when there is no communication between master and slave
 the clock line or serial clock pin will be at 0 or low level. When CPOL=1, 
 the clock starts from a high level or 1. So, there is a transition from high to 
 low state. Here the idle state is 1. That means when there is no communication between
  the master and slave, the status of the serial clock pin is high.
 Depending on the application requirements, one can select either CPOL=0 or CPOL=1. 
 By default, the clock polarity is 0. 
 
 
 It decides the clock phase. CPHA controls at which clock edge that is the 1st or 2nd edge 
 of SCLK, the slave should sample the data. The combination of CPOL (clock polarity) and CPHA 
 (clock phase) bits selects the data capture clock edge.*/






