
#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"
#include "SYSTICK.h"
#include "LED.h"
#include "SCHED.h"
#include "USART.h"

int main(void)
{    
    RCC_EN_DIS_Peripheral(RCC_USART1_APB2,RCC_Enable_Peripheral);
    RCC_EN_DIS_Peripheral(RCC_GPIOA_AHB1,RCC_Enable_Peripheral);
    NVIC_EnableIRQ(NVIC_USART1);
   
    GPIO_pin_Confguration_V2 USART_TX_PIN;
    USART_TX_PIN.GPIO_PORT = GPIO_PORTA_v2;
    USART_TX_PIN.GPIO_PIN = GPIO_PIN9;
    USART_TX_PIN.GPIO_AF_PER = GPIO_AF7_USART1_2;
    USART_TX_PIN.GPIO_MODE  = GPIO_AF_PUSHPULL_NOPUPD_V2;
    USART_TX_PIN.GPIO_Speed = GPIO_HIGH_SPEED;
    USART_CFG_t USART_TX_CONFIG;
    USART_TX_CONFIG.USART_Number = USART1;
    USART_TX_CONFIG.USART_Sampling_rate = USART_OVERSAPMLING_16;
    USART_TX_CONFIG.USART_Break_Detection_Length = USART_NO_BD;
    USART_TX_CONFIG.USART_Device_mode = USART_FullDuplex_mode_;
    USART_TX_CONFIG.USART_mode_cfg    = USART_Asynchronous_mode;
    USART_TX_CONFIG.USART_BaudRate = 9600;
    USART_TX_CONFIG.USART_wordlength = USART_WORD_LENGTH_8;
    USART_TX_CONFIG.USART_StopBitsNum = USART_StopBits_1;
    GPIO_InitPin_v2(&USART_TX_PIN);
    USART_Init(&USART_TX_CONFIG);
    USART_Request_t USART_TxRequest;
    uint8_t NAME[4] = "nOUR";
    USART_TxRequest.USART_Data = NAME;
    USART_TxRequest.USART_DataArraySize = 4;
    USART_TxRequest.USART_ID = USART1_ID;
    USART_TxRequest.USART_Number = USART1;
    
   

   



    //USART_TxByte_Async();
    while (1)
    {
         USART_TxByte_Async(USART_TxRequest);
    }
 

    return 0;
}
