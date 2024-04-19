/***********************************/
/*	Author 	  : Nour Abd-elaziz    */
/*	Swc		     : APP_READSWITCH    */
/*	Layer	     : APP               */
/*	Version    : 1.0               */
/*	Date	     : April 14 , 2024   */
/*	Last Edit  : N/A               */
/***********************************/


                /**************************************************/
                /**            APP_INIT driver             **/
                /**************************************************/
                
#include "APP_READSWITCH.h"
#include "USART.h"
#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"


void APP_Init(void)
{
    RCC_EN_DIS_Peripheral(RCC_GPIOA_AHB1,RCC_Enable_Peripheral);
    RCC_EN_DIS_Peripheral(RCC_GPIOB_AHB1,RCC_Enable_Peripheral);
    RCC_EN_DIS_Peripheral(RCC_USART1_APB2,RCC_Enable_Peripheral);
    NVIC_EnableIRQ(NVIC_USART1);
    GPIO_pin_Confguration_V2 USART_TX_PIN;
    USART_TX_PIN.GPIO_PORT = GPIO_PORTA_v2;
    USART_TX_PIN.GPIO_PIN = GPIO_PIN9;
    USART_TX_PIN.GPIO_AF_PER = GPIO_AF7_USART1_2;
    USART_TX_PIN.GPIO_MODE  = GPIO_AF_PUSHPULL_NOPUPD_V2;
    USART_TX_PIN.GPIO_Speed = GPIO_HIGH_SPEED;

    GPIO_pin_Confguration_V2 USART_RX_PIN;//NEED TO CHECK RX PIN PORT
    USART_TX_PIN.GPIO_PORT = GPIO_PORTA_v2;
    USART_TX_PIN.GPIO_PIN = GPIO_PIN10;
    USART_TX_PIN.GPIO_AF_PER = GPIO_AF7_USART1_2;
    USART_TX_PIN.GPIO_MODE  = GPIO_AF_PUSHPULL_NOPUPD_V2;
    USART_TX_PIN.GPIO_Speed = GPIO_HIGH_SPEED;

    //SEND TO CONFIGURE PIN 
    USART_CFG_t APP_USART_Init;
    APP_USART_Init.USART_Number        = USART1;
    APP_USART_Init.USART_BaudRate      = 9600;
    APP_USART_Init.USART_Device_mode   = USART_FullDuplex_mode_;
    APP_USART_Init.USART_Sampling_rate = USART_OVERSAPMLING_16;
    APP_USART_Init.USART_mode_cfg      = USART_Asynchronous_mode;
    APP_USART_Init.USART_Parity_mode   = USART_Parity_Disable;
    APP_USART_Init.USART_wordlength    = USART_WORD_LENGTH_8;
    APP_USART_Init.USART_StopBitsNum   = USART_StopBits_0_5;
    USART_Init(&APP_USART_Init);
    APP_RX_MSG_Init();
    APP_TX_MSG_Init();
    HSwitch_init();

}


