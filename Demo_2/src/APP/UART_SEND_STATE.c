


#include "../LIB/STD_TYPES.h"
#include "../MCAL/RCC/RCC.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/NVIC/NVIC.h"
#include "../HAL/LED/LEDCfg.h"
#include "../HAL/LED/LED.h"
#include "../HAL/HSWITCH/HSWITCH.h"
#include "../MCAL/STK/STK.h"
#include "../SERVICE/Sched/Sched.h"
#include "../MCAL/UART/UART.h"


void UART_CB()

{
    static uint8_t flag_yellow=0;

    if(flag_yellow==0)
    {
        LED_SetState(LED_YELLOW,LED_ON);
        flag_yellow=1;
    }
    else
    {
        LED_SetState(LED_YELLOW,LED_OFF);
        flag_yellow=0;
    }



}






void UART_SEND_STATE(void)

{
    USART_enu_STATE  UART_loc_State= USART_NOK;
    uint8_t*Buff="ABCD";

    UART_loc_State = UART_SendBuffer_Async(USART1_CH, Buff, 4, UART_CB);


}