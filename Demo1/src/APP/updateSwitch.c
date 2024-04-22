
#include "../HAL/LCD/LCD.h"
#include "../LIB/STD_TYPES.h"
#include "../HAL/HSWITCH/HSWITCH.h"
#include "../MCAL/UART/UART.h"
#include"../LIB/Error_Status.h"
#include "Demo.h"



uint8_t updateSwitches_Buffer=0;


void updateSwitch()

{
  

    uint8_t loc_Switch_counter=0;
    static uint8_t loc_visit_counter=0;
    Switch_ErrorStatus loc_Switch_Status =SWITCH_NOK;
    uint32_t switchState=SWITCH_RELEASED;
    E_ErrorStatus_t  loc_UART_ERROR_Status;

    Uart_TXRequest_t  loc_UART_TX_REQ;

    

    if(loc_visit_counter==0)
    {

    

    for(loc_Switch_counter=0;loc_Switch_counter<Switch_NUM;loc_Switch_counter++)

    {

        loc_Switch_Status=Switch_GetState(loc_Switch_counter, &switchState);
        

        if(/*loc_Switch_Status==SWITCH_OK  && */ switchState==SWITCH_PRESSED)
        {
            updateSwitches_Buffer=CHECKSUM;

            updateSwitches_Buffer+=loc_Switch_counter+1;
            loc_Switch_counter=Switch_NUM;

        }
       else{
        updateSwitches_Buffer=0;
       }




    }

// 	uint32_t size;
// 	uint16_t position;
// }Buffer_t;
// Buffer_t TX_Buffer;
// 	USART_Channel Channel;
// 	uint32_t state;
// 	CBF TX_callBack;
    


     
  


if(updateSwitches_Buffer)
USART_SendByteAsynchronous(USART_Channel_2, updateSwitches_Buffer);

    loc_visit_counter++;

    }


    else
    {

        updateSwitches_Buffer=0;

        loc_visit_counter=0;



    }



    
}
































































