#include"DEMO.h"
 #include "MCAL/RCC/RCC.h"


#include "MCAL\GPIO\GPIO.h"
#include "MCAL/NVIC/NVIC.h"

#include "MCAL/UART/UART.h"





void APP_Init(void)
{



//   RCC_ControlClock(RCC_HSE,CLK_ON);
//   RCC_SelectSysClk(RCC_HSE);

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
LCD_INIT_PINS();
Switch_Init();

}
