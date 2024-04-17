// /*
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

// ----------------------------------------------------------------------------

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


// ----------------------------------------------------------------------------

// Standalone STM32F4 empty sample (trace via DEBUG).

// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).


// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.




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
 /*
 * This file is part of the �OS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


#include "LIB/STD_TYPES.h"
#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/NVIC/NVIC.h"

#include "HAL/HSWITCH/HSWITCH.h"
#include "MCAL/SysTick/SysTick.h"
#include  "SCHED/SCHED.h"
#include "HAL/LCD/LCD.h"
#include "MCAL/UART/UART.h"
/***********************************************************************************************/





extern void Toggle_LED_GREEN(void);
extern user_request_t LCD_user_requests;

int main()
{

  RCC_ControlClock(RCC_HSE,CLK_ON);
  RCC_SelectSysClk(RCC_HSE);
  RCC_ControlPeripheralClock(RCC_AHB1,GPIOBEN,CLK_ON);
  RCC_ControlPeripheralClock(RCC_AHB1,GPIOCEN,CLK_ON);
  RCC_ControlPeripheralClock(RCC_AHB1,GPIOAEN,CLK_ON);

  GPIO_PIN_t GPIO_TX=

  {

    GPIO_PORTA,
    GPIO_PIN9,
    GPIO_MODE_ALTERNATE,
    GPIO_SPEED_HIGH,
    
    
    AF7,
    0


  };
  
  GPIO_PIN_t GPIO_RX=

  {

    GPIO_PORTA,
    GPIO_PIN10,
    GPIO_MODE_ALTERNATE,
    GPIO_SPEED_HIGH,
    
    
    AF7,
    0


  };
  

  GPIO_Init(&GPIO_TX);
  GPIO_Init(&GPIO_RX);
   RCC_ControlPeripheralClock(RCC_APB2,USART1RST,CLK_ON);

  Switch_Init();
  LCD_INIT_PINS();
USART_Config Copy_addCFG=

{


    USART_Channel_1,
    0,
    1,
    0,
    0,
    0,
    0,
    1,
    9600
};

 USART_Init(&Copy_addCFG);
 



    
 Sched_Init();
 Sched_Start ();
 

  while(1)
  {

  

  }
  return 0;




}
 

