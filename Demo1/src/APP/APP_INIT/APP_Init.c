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
#include "Display.h"


void APP_Init(void)
{
    RCC_AHB1EnablePeri(PERI_AHB1_GPIOA);
    RCC_AHB1EnablePeri(PERI_AHB1_GPIOB);
    RCC_APB2EnablePeri(PERI_APB2_USART1);

    NVIC_EnableIRQ(NVIC_USART1);

    GPIO_PinCfg_t USART_TX_PIN;
    USART_TX_PIN.GPIO_PORT = GPIO_PORT_A;
    USART_TX_PIN.GPIO_PIN = GPIO_PIN_9;
    USART_TX_PIN.GPIO_AF = GPIO_AF_7;
    USART_TX_PIN.GPIO_MODE  = GPIO_MODE_AF_PP;
    USART_TX_PIN.GPIO_PUPD = GPIO_PUPD_NONE;
    USART_TX_PIN.GPIO_OSPEED = GPIO_OSPEED_HIGH;

    GPIO_PinCfg_t USART_RX_PIN;
    USART_RX_PIN.GPIO_PORT = GPIO_PORT_A;
    USART_RX_PIN.GPIO_PIN = GPIO_PIN_10;
    USART_RX_PIN.GPIO_AF = GPIO_AF_7;
    USART_RX_PIN.GPIO_MODE  = GPIO_MODE_AF_PP;
    USART_RX_PIN.GPIO_PUPD = GPIO_PUPD_NONE;
    USART_RX_PIN.GPIO_OSPEED = GPIO_OSPEED_HIGH;

    //GPIO_InitPin(&USART_TX_PIN);
    //GPIO_InitPin(&USART_RX_PIN);

   /* USART_CFG_t APP_USART_Init;
    APP_USART_Init.USART_Number        = USART1;
    APP_USART_Init.USART_BaudRate      = 9600;
    APP_USART_Init.USART_Device_mode   = USART_FullDuplex_mode_;
    APP_USART_Init.USART_Sampling_rate = USART_OVERSAPMLING_16;
    APP_USART_Init.USART_mode_cfg      = USART_Asynchronous_mode;
    APP_USART_Init.USART_Parity_mode   = USART_Parity_Disable;
    APP_USART_Init.USART_wordlength    = USART_WORD_LENGTH_8;
    APP_USART_Init.USART_StopBitsNum   = USART_StopBits_0_5;
    USART_Init(&APP_USART_Init);*/
    
    Display_Init();
   // APP_RX_MSG_Init();
    //APP_TX_MSG_Init();
   // HSwitch_init();

}


