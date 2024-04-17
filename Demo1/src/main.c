// // /*
// //  * This file is part of the �OS++ distribution.
// //  *   (https://github.com/micro-os-plus)
// //  * Copyright (c) 2014 Liviu Ionescu.
// //  *
// //  * Permission is hereby granted, free of charge, to any person
// //  * obtaining a copy of this software and associated documentation
// //  * files (the "Software"), to deal in the Software without
// //  * restriction, including without limitation the rights to use,
// //  * copy, modify, merge, publish, distribute, sublicense, and/or
// //  * sell copies of the Software, and to permit persons to whom
// //  * the Software is furnished to do so, subject to the following
// //  * conditions:
// //  *
// //  * The above copyright notice and this permission notice shall be
// //  * included in all copies or substantial portions of the Software.
// //  *
// //  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// //  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// //  * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// //  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// //  * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// //  * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// //  * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// //  * OTHER DEALINGS IN THE SOFTWARE.
// //  */

// // ----------------------------------------------------------------------------

// // #include "LIB/STD_TYPES.h"
// // #include "MCAL/RCC/RCC.h"
// // #include "MCAL/GPIO/GPIO.h"
// // #include "MCAL/NVIC/NVIC.h"

// // #include "HAL/HSWITCH/HSWITCH.h"
// // #include "MCAL/SysTick/SysTick.h"
// // #include  "SCHED/SCHED.h"
// // #include "HAL/LCD/LCD.h"
// // #include "MCAL/UART/UART.h"
// // /***********************************************************************************************/


// // ----------------------------------------------------------------------------

// // Standalone STM32F4 empty sample (trace via DEBUG).

// // Trace support is enabled by adding the TRACE macro definition.
// // By default the trace messages are forwarded to the DEBUG output,
// // but can be rerouted to any device or completely suppressed, by
// // changing the definitions required in system/src/diag/trace_impl.c
// // (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).


// // ----- main() ---------------------------------------------------------------

// // Sample pragmas to cope with warnings. Please note the related line at
// // the end of this function, used to pop the compiler diagnostics status.




// // extern void Toggle_LED_GREEN(void);
// // extern user_request_t LCD_user_requests;

// // int main()
// // {

// //   RCC_ControlClock(RCC_HSE,CLK_ON);
// //   RCC_SelectSysClk(RCC_HSE);
// //   RCC_ControlPeripheralClock(RCC_AHB1,GPIOBEN,CLK_ON);
// //   RCC_ControlPeripheralClock(RCC_AHB1,GPIOCEN,CLK_ON);
// //   RCC_ControlPeripheralClock(RCC_AHB1,GPIOAEN,CLK_ON);

// //   GPIO_PIN_t GPIO_TX=

// //   {

// //     GPIO_PORTA,
// //     GPIO_PIN9,
// //     GPIO_MODE_ALTERNATE,
// //     GPIO_SPEED_HIGH,
    
    
// //     AF7,
// //     0


// //   };
  
// //   GPIO_PIN_t GPIO_RX=

// //   {

// //     GPIO_PORTA,
// //     GPIO_PIN10,
// //     GPIO_MODE_ALTERNATE,
// //     GPIO_SPEED_HIGH,
    
    
// //     AF7,
// //     0


// //   };
  

// //   GPIO_Init(&GPIO_TX);
// //   GPIO_Init(&GPIO_RX);
// //    RCC_ControlPeripheralClock(RCC_APB2,USART1RST,CLK_ON);

// //   Switch_Init();
// //   LCD_INIT_PINS();
// // USART_Config Copy_addCFG=

// // {


// //     USART_Channel_1,
// //     0,
// //     1,
// //     0,
// //     0,
// //     0,
// //     0,
// //     1,
// //     9600
// // };

// //  USART_Init(&Copy_addCFG);
 



    
// //  Sched_Init();
// //  Sched_Start ();
 

// //   while(1)
// //   {

  

// //   }
// //   return 0;




// // }
//  /*
//  * This file is part of the �OS++ distribution.
//  *   (https://github.com/micro-os-plus)
//  * Copyright (c) 2014 Liviu Ionescu.
//  *
//  * Permission is hereby granted, free of charge, to any person
//  * obtaining a copy of this software and associated documentation
//  * files (the "Software"), to deal in the Software without
//  * restriction, including without limitation the rights to use,
//  * copy, modify, merge, publish, distribute, sublicense, and/or
//  * sell copies of the Software, and to permit persons to whom
//  * the Software is furnished to do so, subject to the following
//  * conditions:
//  *
//  * The above copyright notice and this permission notice shall be
//  * included in all copies or substantial portions of the Software.
//  *
//  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//  * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  * OTHER DEALINGS IN THE SOFTWARE.
//  */


// #include "LIB/STD_TYPES.h"
// #include "MCAL/RCC/RCC.h"
// #include "MCAL/GPIO/GPIO.h"
// #include "MCAL/NVIC/NVIC.h"

// #include "HAL/HSWITCH/HSWITCH.h"
// #include "MCAL/SysTick/SysTick.h"
// #include  "SCHED/SCHED.h"
// #include "HAL/LCD/LCD.h"
// #include "MCAL/UART/UART.h"
// /***********************************************************************************************/





// extern void Toggle_LED_GREEN(void);
// extern user_request_t LCD_user_requests;

// int main()
// {

//   RCC_ControlClock(RCC_HSE,CLK_ON);
//   RCC_SelectSysClk(RCC_HSE);
//   RCC_ControlPeripheralClock(RCC_AHB1,GPIOBEN,CLK_ON);
//   RCC_ControlPeripheralClock(RCC_AHB1,GPIOCEN,CLK_ON);
//   RCC_ControlPeripheralClock(RCC_AHB1,GPIOAEN,CLK_ON);

//   GPIO_PIN_t GPIO_TX=

//   {

//     GPIO_PORTA,
//     GPIO_PIN9,
//     GPIO_MODE_ALTERNATE,
//     GPIO_SPEED_HIGH,
    
    
//     AF7,
//     0


//   };
  
//   GPIO_PIN_t GPIO_RX=

//   {

//     GPIO_PORTA,
//     GPIO_PIN10,
//     GPIO_MODE_ALTERNATE,
//     GPIO_SPEED_HIGH,
    
    
//     AF7,
//     0


//   };
  

//   GPIO_Init(&GPIO_TX);
//   GPIO_Init(&GPIO_RX);
//    RCC_ControlPeripheralClock(RCC_APB2,USART1RST,CLK_ON);

//   Switch_Init();
//   LCD_INIT_PINS();
// USART_Config Copy_addCFG=

// {


//     USART_Channel_1,
//     0,
//     1,
//     0,
//     0,
//     0,
//     0,
//     1,
//     9600
// };

//  USART_Init(&Copy_addCFG);
 



    
//  Sched_Init();
//  Sched_Start ();
 

//   while(1)
//   {

  

//   }
//   return 0;




// }
 

// // ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "MCAL\RCC\RCC.h"
#include "MCAL\GPIO\GPIO.h"

#include "MCAL\NVIC\NVIC.h"
#include"MCAL/STK/STK.h"
#include"sched.h"
#include"MCAL/UART/UART.h"




void Copy_Cbf(void)
{
//
}







int main(int argc, char* argv[])
{

/*USART TEST */
 RCC_ControlPeripheralClock(RCC_AHB1,GPIOBEN,CLK_ON);
 RCC_ControlPeripheralClock(RCC_AHB1,GPIOCEN,CLK_ON);
RCC_ControlPeripheralClock(RCC_AHB1,GPIOAEN,CLK_ON);
RCC_ControlPeripheralClock(RCC_APB1,USART2RST,CLK_ON);

NVIC_EnableInterrupt(NVIC_USART2_INTERRUPT);


GPIO_PIN_t TX_pin;
	TX_pin.port=GPIO_PORTA;
	TX_pin.pin=GPIO_PIN2;
	TX_pin.speed =GPIO_SPEED_HIGH;
	TX_pin.mode=GPIO_MODE_ALTERNATE;
    //TX_pin.GPIO_OUTPUTTYPE=PUSHPULL;
    TX_pin.pull=AF7;
	GPIO_Init(&TX_pin);
	GPIO_PIN_t RX_pin;
	RX_pin.port=GPIO_PORTA;
	RX_pin.pin=GPIO_PIN3;
    //RX_pin.GPIO_OUTPUTTYPE=PUSHPULL;
	RX_pin.speed =GPIO_SPEED_HIGH;
	RX_pin.mode=GPIO_MODE_ALTERNATE;
    RX_pin.pull=AF7;
	GPIO_Init(&RX_pin);





USART_Config Transmit_frame;
Transmit_frame.Channel= USART_Channel_2;
Transmit_frame.OVER8=0; //oversample by 16
Transmit_frame.UE=1;
Transmit_frame.M=0;
Transmit_frame.PCE=0; //disable parity
Transmit_frame.TCIE=1;
Transmit_frame.TXEIE=0;
Transmit_frame.TE =1; 
Transmit_frame.RE=1;
Transmit_frame.BaudRate=BAUD_RATE;
USART_Init(&Transmit_frame);

  // Prepare a buffer with data to be sent
    uint16_t sendData[] = {'H', 'e', 'l', 'l', 'o', '\r', '\n'};
    uint32_t dataSize = sizeof(sendData) / sizeof(sendData[0]);




    // Initialize a UART transmission request
    Uart_TXRequest_t txRequest = {
        .TX_Buffer.data = sendData,
        .TX_Buffer.size = dataSize,
        .TX_Buffer.position = 0,
        .Channel = USART_Channel_2,
        .state = READY,
        .TX_callBack = Copy_Cbf
    };

 //USART_SendBufferZeroCopy(&txRequest);
  uint8_t Copy_u8Data = 0;
//USART_SendByteSynchronous( USART_Channel_2, 'b');
USART_GetByteSynchronous(USART_Channel_2,Copy_u8Data);


  while (1)
{ 
 USART_SendByteSynchronous( USART_Channel_2,Copy_u8Data ); 

}



}








