#include "../HAL/LCD/LCD.h"
#include "../LIB/STD_TYPES.h"
#include "../HAL/HSWITCH/HSWITCH.h"
#include "../MCAL/UART/UART.h"


uint16_t updateSwitches_Buffer=0;


void updateSwitch()

{

    uint8_t loc_Switch_counter=0;
    Switch_ErrorStatus loc_Switch_Status =SWITCH_NOK;
    uint32_t switchState=SWITCH_RELEASED;

    Uart_TXRequest_t  loc_UART_TX_REQ;

    

    for(loc_Switch_counter=0;loc_Switch_counter<Switch_NUM;loc_Switch_counter++)

    {

        loc_Switch_Status=Switch_GetState(loc_Switch_counter, &switchState);

        if(loc_Switch_Status==SWITCH_OK  &&  switchState==SWITCH_PRESSED)
        {

            updateSwitches_Buffer|=(1<<loc_Switch_counter);

        }




    }

    loc_UART_TX_REQ=

    {



        {

            updateSwitches_Buffer,
            9,
            0

        },
        USART_1,
        UART_TX_BUFFER_READY,

        NULL


    }

    USART_SendBufferZeroCopy(&loc_UART_TX_REQ);









    
}
