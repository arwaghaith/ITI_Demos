#ifndef UART_H
#define UART_H

#include "UART_private.h"
#include "../../LIB/STD_TYPES.h"

#define BUFFER_SIZE  2

#define BUSY 0
#define READY 1

/*******************************************************************************************************************/
/************************************************        CFG        ************************************************/




typedef void(*TXCB)(void);
typedef void(*RXCB)(void);
#define MAX_SIZE  3





typedef enum{

    USART_NOK,
    USART_OK
}USART_enu_STATE;


typedef struct
{
    uint16_t *data;
    uint32_t length;
    uint32_t pos;
    
}Buffer_t;

typedef struct 
{

    Buffer_t Buffer;
    uint32_t state;
    TXCB TX_CB;

}TX_t;

typedef struct 

{

    Buffer_t Buffer;
    uint32_t state;
    RXCB RX_CB;
}RX_t;







USART_enu_STATE UART_INIT(USART_CFG*CFG);

USART_enu_STATE UART_SendBuffer_Async(uint8_t USART_channel,uint16_t*Buffer,uint16_t length,TXCB UART_CB);
USART_enu_STATE UART_SendBuffer(uint8_t USART_channel,uint8_t Buffer,uint16_t length,TXCB UART_CB);



USART_enu_STATE UART_RXBufferAsync(uint8_t USART_channel,uint8_t*buffer,uint16_t length,RXCB UART_CB );
USART_enu_STATE UART_RecBuffer(uint8_t USART_channel,uint16_t*buffer,uint16_t length,RXCB UART_CB );




#endif