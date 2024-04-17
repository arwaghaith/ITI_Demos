#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"
#include "SYSTICK.h"
#include "SCHED.h"
#include "USART.h"

int main(void)
{    
    RCC_APB2EnablePeri(PERI_APB2_USART1);
    RCC_AHB1EnablePeri(PERI_AHB1_GPIOA);
    NVIC_EnableIRQ(NVIC_USART1);
   
    GPIO_PinCfg_t USART_TX_PIN;
    USART_TX_PIN.GPIO_PORT = GPIO_PORT_A;
    USART_TX_PIN.GPIO_PIN = GPIO_PIN_9;
    USART_TX_PIN.GPIO_AF = GPIO_AF_7;
    USART_TX_PIN.GPIO_MODE  = GPIO_MODE_AF_PP;
    USART_TX_PIN.GPIO_PUPD  = GPIO_PUPD_NONE;
    USART_TX_PIN.GPIO_OSPEED = GPIO_OSPEED_HIGH;
    USART_CFG_t USART_TX_CONFIG;
    USART_TX_CONFIG.USART_Number = USART1;
    USART_TX_CONFIG.USART_Sampling_rate = USART_OVERSAPMLING_16;
    USART_TX_CONFIG.USART_Break_Detection_Length = USART_NO_BD;
    USART_TX_CONFIG.USART_Device_mode = USART_Transmitter_mode;
    USART_TX_CONFIG.USART_mode_cfg    = USART_Asynchronous_mode;
    USART_TX_CONFIG.USART_BaudRate = 115200;
    USART_TX_CONFIG.USART_wordlength = USART_WORD_LENGTH_9;
    USART_TX_CONFIG.USART_StopBitsNum = USART_StopBits_2;
    GPIO_InitPin(&USART_TX_PIN);
    USART_Init(&USART_TX_CONFIG);
    USART_Request_t USART_TxRequest;
    char NAME = 0b01110011;
    USART_TxRequest.USART_Data = &NAME;
    USART_TxRequest.USART_DataArraySize = 1;
    USART_TxRequest.USART_ID = USART1_ID;
    USART_TxRequest.USART_Number = USART1;
    
   

   



    //USART_TxByte_Async();
    while (1)
    {
         USART_TxByte_Async(USART_TxRequest);
    }
 

    return 0;
}