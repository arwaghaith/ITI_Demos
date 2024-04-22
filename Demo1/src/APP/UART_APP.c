#include"DEMO.h"



void UART_init()
{




















 GPIO_PIN_t GPIOA5=
 {
GPIO_PORTA, GPIO_PIN5, GPIO_MODE_OUTPUT, GPIO_SPEED_HIGH, GPIO_OUTPUT_TYPE_PUSH_PULL, GPIO_LOW
 };
 GPIO_PIN_t GPIOA7=
 {
GPIO_PORTA, GPIO_PIN7, GPIO_MODE_OUTPUT, GPIO_SPEED_HIGH, GPIO_OUTPUT_TYPE_PUSH_PULL, GPIO_LOW
 };
 GPIO_Init(&GPIOA5);
 GPIO_Init(&GPIOA7);











uint8_t volatile data_recieved=0;

USART_SendByteAsynchronous(USART_Channel_2, 'a');
USART_GetByteASynchronous(USART_Channel_2, &data_recieved);
if(data_recieved == 'y')
{
   GPIO_SET_PIN_VALUE(GPIO_PORTA , GPIO_PIN7 ,GPIO_HIGH);
}
}