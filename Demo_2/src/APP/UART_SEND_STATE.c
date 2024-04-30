


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

#define RECIEVE_STATE  2
#define SEND_STATE     1
#define IDLE_STATE     0


uint32_t SERVER_STATE=RECIEVE_STATE;

uint8_t sent_buff=CHECKSUM;
uint8_t buffer[1];

volatile uint32_t led_res=LED_OFF;
volatile uint32_t switch_res=SWITCH_RELEASED;

/*
 0- Switch_ErrorStatus Switch_GetState(Switch_ChannelType Channel, uint32_t *State);

 1-  LED_Error_Status LED_getState(LED_NAME led,uint32_t *state);



 the frame has 8 bits
 the last 4  bits is a checksum
 the 0 bit is for a function id 
the 1 bit is for SWITCH NO OR LED NO.
the 2 bit is for SWITCH NO OR LED NO.
the 3 bit is for getting the state

*/
void UART_RCB()

{




    

    // Perform deserialization logic here using the received_data
    uint8_t func_id=buffer[0]&1;
    uint8_t switch_or_led=3&(buffer[0]>>1);
    uint32_t State;

     switch(func_id)

     {

        case 0:
        Switch_GetState(switch_or_led, &State);
        switch_res=State;
        break;
        case 1:
        LED_getState(switch_or_led, &State);
        led_res=State;

        break;
        }




SERVER_STATE=SEND_STATE;
}

void UART_SCB()

{


    sent_buff=CHECKSUM;

    switch((buffer[0])&1)
    {
        case 0:
        sent_buff|=switch_res;
        break;

        case 1:
        sent_buff|=led_res;

        break;
    }

   
    
    


SERVER_STATE=RECIEVE_STATE;
}




void UART_SEND_STATE(void)

{

    
    // USART_enu_STATE  UART_loc_State= USART_NOK;
    // uint32_t RED_STATE=GPIO_LOW;
    // uint32_t GREEN_STATE=GPIO_LOW;
    // GPIO_GET_PIN_VALUE( GPIO_PORTA, GPIO_PIN0,&GREEN_STATE);
    // GPIO_GET_PIN_VALUE( GPIO_PORTA, GPIO_PIN1,&RED_STATE);
    // volatile uint8_t Buff=CHECKSUM|(green_switch_flag)|(red_switch_flag<<1)|(GREEN_STATE<<2)|(RED_STATE<<3);


    // UART_loc_State = UART_SendBuffer_Async(USART1_CH, &Buff, 1, UART_CB);

    switch(SERVER_STATE)
    {
        case RECIEVE_STATE:
        {
            UART_RXBufferAsync(USART1_CH,buffer,1,UART_RCB );
            break;
        }
        case SEND_STATE:
        {
            UART_SendBuffer_Async(USART1_CH, &sent_buff, 1, UART_SCB);
            SERVER_STATE=RECIEVE_STATE;
            break;
        }
        case IDLE_STATE:
        {
            break;
        }
    }






}