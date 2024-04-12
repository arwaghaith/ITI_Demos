#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include"LIB/Error_Status.h"
#include"LIB/Std_Types.h"
#include"LIB/Bit_Mask.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define READY                                      0
#define BUSY                                       1
#define     BAUD_RATE                              9600
#define     SYS_FREQUENCY                          16000000
//#define     SYS_FREQUENCY                        25000000UL

#define USART_1_BaseAddress                    ((volatile USART_t*)0x40011000)
#define USART_2_BaseAddress                    ((volatile USART_t*)0x40004400)
#define USART_6_BaseAddress                    ((volatile USART_t*)0x40011400)




typedef void (*CBF)(void);
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef struct 
{
   struct{
			u32 PE:  1;   //Parity error
			u32 FE:  1;   //Framing error
			u32 NF:  1;  //Noise detected flag
			u32 ORE: 1;  //Overrun error
			u32 IDLE:1;  //IDLE line detected
			u32 RXNE:1;  //Read data register not empty
			u32 TC:  1;  //Transmission complete
			u32 TXE: 1;  //Transmit data register empty
			u32 LBD: 1;  //LIN break detection flag
			u32 CTS: 1;  //CTS flag
			u32 :22;
		}USART_SR;

   struct{
			u32 DATA:9;
			u32:23;
		}USART_DR;

   struct{
			u32 DIV_FRACTION:4;
			u32 DIV_MANTISSA:12;
			u32 :16;
		}USART_BRR;

  struct{
			u32 SBK	   :1;  //Send break
			u32 RWU    :1;  //Receiver wakeup
			u32 RE     :1;  //Receiver enable
			u32 TE     :1;  //Transmitter enable
			u32 IDLEIE :1;  //IDLE interrupt enable
			u32 RXNEIE :1;  //RXNE interrupt enable "Read data register not empty"
			u32 TCIE   :1;  //Transmission complete interrupt enable
			u32 TXEIE  :1;  //TXE interrupt enable "Transmit data register empty"
			u32 PEIE   :1;  //PE interrupt enable
			u32 PS     :1;  //Parity selection
			u32 PCE    :1;  //Parity control enable
			u32 WAKE   :1;  //Wakeup method
			u32 M      :1;  //Word length
			u32 UE     :1;  //USART enable
			u32        :1;
			u32 OVER8  :1;  //Oversampling mode
			u32        :16;
		}USART_CR1;

  struct{
            /*(CPOL, CPHA, LBCL) should not be written while the transmitter is enabled*/
			u32 ADD   :4; //Address of the USART node
			u32       :1;
			u32 LBDL  :1; //lin break detection length
			u32 LBDIE :1; //LIN break detection interrupt enable
			u32       :1;
			u32 LBCL  :1; //Last bit clock pulse
			u32 CPHA  :1; //Clock phase
			u32 CPOL  :1; //Clock polarity
			u32 CLKEN :1; //Clock enable 
			u32 STOP  :2; //STOP bits
			u32 LINEN :1; //LIN mode enable
			u32       :17;
		}USART_CR2;

   struct{
			u32 EIE   :1; //Error interrupt enable
			u32 IREN  :1; //IrDA mode enable
			u32 IRLP  :1; //IrDA low-power
			u32 HDSEL :1; //Half-duplex selection
			u32 NACK  :1; //Smartcard NACK enable
			u32 SCEN  :1; //Smartcard mode enable
			u32 DMAR  :1; //DMA enable receiver
			u32 DMAT  :1; //DMA enable transmitter
			u32 RTSE  :1; //Request To Send enable
			u32 CTSE  :1; //clear to send enable
			u32 CTSIE :1; //CTS interrupt enable
			u32 ONEBIT:1; //One sample bit method enable
			u32       :20;
		}USART_CR3;
    
  
}USART_t;


#define USART_1    ((volatile USART_t*) USART_1_BaseAddress)
#define USART_2    ((volatile USART_t*) USART_2_BaseAddress)
#define USART_6    ((volatile USART_t*) USART_6_BaseAddress)



typedef enum {
    USART_Channel_1,
    USART_Channel_2,
    USART_Channel_6
} USART_Channel;


typedef struct
{
   USART_Channel Channel;
    u32 OVER8;
    u32 UE;               // USART enable
    u32 M;                // Word length
    u32 PCE;
    u32 TCIE;             // Transmission complete interrupt enable
    u32 TXEIE;
    u32 RE;               // Receiver enable
    u32 TE;               // Transceiver enable
    u32 BaudRate;
} USART_Config;


typedef struct 
{
	u16 *data;
	u32 size;
	u16 position;
}Buffer_t;


typedef struct 
{
	Buffer_t TX_Buffer;
	USART_Channel Channel;
	u32 state;
	CBF TX_callBack;
    
}Uart_TXRequest_t;





typedef struct 
{
  	Buffer_t RX_Buffer;
	USART_Channel Channel;
	u32 state;
	CBF RX_callBack;

}Uart_RXRequest_t;

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/


E_ErrorStatus_t  USART_Init(const USART_Config * Copy_addCFG);

E_ErrorStatus_t USART_SendByteSynchronous(USART_Channel Copy_enuChannel, u8 Copy_u8Data);

E_ErrorStatus_t USART_GetByteSynchronous(USART_Channel Copy_enuChannel, u8 Copy_u8Data);

/*Asynch function*/
E_ErrorStatus_t  USART_ReceiveBuffer( Uart_RXRequest_t * Copy_addRequest);

/*Asynch function*/
E_ErrorStatus_t USART_SendBufferZeroCopy(Uart_TXRequest_t * Copy_addRequest);

//E_ErrorStatus_t USART_RegisterCallBackFunction(USART_Channel Channel, USART_Mode Mode, CallBack CallBackFunction);

#endif // MCAL_UART_UART_H_