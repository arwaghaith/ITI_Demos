


#include "../LIB/STD_TYPES.h"
#include "../MCAL/RCC/RCC.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/NVIC/NVIC.h"
#include "../HAL/LED/LED.h"
#include "../HAL/HSWITCH/HSWITCH.h"
#include "../MCAL/STK/STK.h"
#include "../SERVICE/SCHED/Sched.h"
#include "../MCAL/UART/UART.h"

#define CHECKSUM 32

extern green_switch_flag;
extern red_switch_flag;


void UART_CB()

{
   
    
    



}






void UART_SEND_STATE(void)

{

    
    USART_enu_STATE  UART_loc_State= USART_NOK;
    uint32_t RED_STATE=GPIO_LOW;
    uint32_t GREEN_STATE=GPIO_LOW;
    GPIO_GET_PIN_VALUE( GPIO_PORTA, GPIO_PIN0,&GREEN_STATE);
    GPIO_GET_PIN_VALUE( GPIO_PORTA, GPIO_PIN1,&RED_STATE);
    volatile uint8_t Buff=CHECKSUM|(green_switch_flag)|(red_switch_flag<<1)|(GREEN_STATE<<2)|(RED_STATE<<3);


    UART_loc_State = UART_SendBuffer_Async(USART1_CH, &Buff, 1, UART_CB);


}