// #include "../HAL/LCD/LCD.h"
// #include "../LIB/STD_TYPES.h"
// #include "../HAL/HSWITCH/HSWITCH.h"
// #include "../MCAL/UART/UART.h"
// #include"../LIB/Error_Status.h"




// uint16_t updateSwitches_Buffer=0;


// void updateSwitch_test()

// {

//     uint8_t loc_Switch_counter=0;
//     static uint8_t loc_visit_counter=0;
//     Switch_ErrorStatus loc_Switch_Status =SWITCH_NOK;
//     uint32_t switchState=SWITCH_RELEASED;
//     E_ErrorStatus_t  loc_UART_ERROR_Status;

//     Uart_TXRequest_t  loc_UART_TX_REQ;

    

//     if(loc_visit_counter==0)
//     {

    

//     for(loc_Switch_counter=0;loc_Switch_counter<Switch_NUM;loc_Switch_counter++)

//     {

//         loc_Switch_Status=Switch_GetState(loc_Switch_counter, &switchState);
        

//         if(loc_Switch_Status==SWITCH_OK  &&  switchState==SWITCH_PRESSED)
//         {

//             updateSwitches_Buffer|=(1<<loc_Switch_counter);

//         }




//     }

// // 	uint32_t size;
// // 	uint16_t position;
// // }Buffer_t;
// // Buffer_t TX_Buffer;
// // 	USART_Channel Channel;
// // 	uint32_t state;
// // 	CBF TX_callBack;
    


//         loc_UART_TX_REQ.TX_Buffer.data=&updateSwitches_Buffer;
//         loc_UART_TX_REQ.TX_Buffer.size=sizeof(updateSwitches_Buffer);
//         loc_UART_TX_REQ.TX_Buffer.position=0;
//         loc_UART_TX_REQ.Channel=USART_Channel_1;
//         loc_UART_TX_REQ.state=0;
//         loc_UART_TX_REQ.TX_callBack=NULL;
  




   
//     loc_visit_counter++;

//     loc_UART_ERROR_Status=USART_SendBufferZeroCopy(&loc_UART_TX_REQ);
//     }


//     else
//     {

//         updateSwitches_Buffer=0;

//         loc_visit_counter=0;



//     }









    
// }
