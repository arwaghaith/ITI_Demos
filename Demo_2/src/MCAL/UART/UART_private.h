#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

#include "../../LIB/STD_TYPES.h"

#define USART6_BASE  0X40011400
#define USART1_BASE  0x40011000
#define USART2_BASE  0x40004400





typedef struct {

    volatile uint32_t SR;   /* status register */
    volatile uint32_t DR;   /* data register */
    volatile uint32_t BRR;  /* baud rate register */
    volatile uint32_t CR1;  /* control register 1 */
    volatile uint32_t CR2;  /* control register 2 */
    volatile uint32_t CR3;  /* control register 3 */
    volatile uint32_t GTPR; /* guard time and prescaler register */

}USART_t;

#define USART1   (USART_t *) USART1_BASE
#define USART2   (USART_t *) USART2_BASE
#define USART6   (USART_t *) USART6_BASE



/******************************************************************************************************************/
/************************************************        MASKS      ***********************************************/

#define OVERSAMPLING_MASK    0XFFFF7FFF
#define USART_EN_MASK        0XFFFFDFFF
#define WORD_LENGTH_MASK     0XFFFFEFFF
#define WAKEUP_MASK          0XFFFFF7FF
#define PARITY_CTRL_EN_MASK  0XFFFFFBFF
#define PARITY_SELEC_METHOD  0XFFFFFDFF
#define STOP_BITS_MASK       0XFFFFCFFF
#define CLK_EN_MASK          0XFFFFF700
#define CLK_POL_MASK         0XFFFFFBFF
#define CLK_PH_MASK          0XFFFFFDFF
#define TE_INTERRUPT_MASK    0XFFFFFF7F
#define RE_INTERRUPT_MASK    0XFFFFFFBF
#define Baud_Rate_Mask       0XFFFF0000
#define TEXIE_MASK           0XFFFFFF7F
#define RXNEIE_MASK          0XFFFFFFBF
#define RE_MASK              0xFFFFFFFB
#define TE_MASK              0XFFFFFFF7

/******************************************************************************************************************/

#define TXE_FLAG            0X00000080      
#define RXNE_FLAG           0X00000020
/************************************************        CONF_OPTIONS *********************************************/

/******************************************************************************************************************/

#define USART1_CH            0
#define USART2_CH            1
#define USART6_CH            2

/******************************************************************************************************************/

#define OVERSAMPLING_16      0X00000000
#define OVERSAMPLING_8       0X00008000
/******************************************************************************************************************/

#define USART_DISABLE        0X00000000
#define USART_ENABLE         0X00002000
/******************************************************************************************************************/

#define WORD_LENGTH_8        0X00000000
#define WORD_LENGTH_9        0X00001000
/******************************************************************************************************************/

#define WAKEUP_IDLE_LINE     0X00000000
#define WAKEUP_ADDRESS       0X00000400
/******************************************************************************************************************/

#define PARITY_CTRL_DISABLE  0X00000000
#define PARITY_CTRL_ENABLE   0X00000200
/******************************************************************************************************************/

#define PARITY_EVEN          0X00000000
#define PARITY_ODD           0X00000100
/******************************************************************************************************************/
#define STOP_BITS_1          0X00000000
#define STOP_BITS_0_5        0X00001000
#define STOP_BITS_2          0X00002000
#define STOP_BITS_1_5        0X00003000
/******************************************************************************************************************/

#define CLK_DISABLE          0X00000000
#define CLK_ENABLE           0X00000800
/******************************************************************************************************************/

#define CLK_POL_LOW          0X00000000
#define CLK_POL_HIGH         0X00000400
/******************************************************************************************************************/
#define CLK_PHASE_FIRST      0X00000000
#define CLK_PHASE_SECOND     0X00000200
/******************************************************************************************************************/
#define TE_INTERRUPT         0X00000080
#define RE_INTERRUPT         0X00000040
/******************************************************************************************************************/
#define TEXIE                0X00000080
#define RXNEIE               0X00000020
/******************************************************************************************************************/
#define RE                  0X00000004
#define TE                  0X00000008
/******************************************************************************************************************/

typedef struct 
{


    uint8_t channel;
    uint32_t OVERSAMPLING;
    uint32_t USART_EN;
    uint32_t Word_length;
    uint32_t Wakeup_method;
    uint32_t Parity_control;
    uint32_t Parity_selection;
    uf32_t BaudRate;
    uint32_t Stop_Bits;
    uint32_t CLK_EN;
    uint32_t CLK_PH;
    uint32_t CLK_POL;


  
} USART_CFG;



#endif 