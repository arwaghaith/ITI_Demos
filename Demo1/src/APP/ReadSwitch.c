#include"DEMO.h"

#include "../LIB/STD_TYPES.h"
#include "../HAL/HSWITCH/HSWITCH.h"
#include "../MCAL/UART/UART.h"
#define BUFFER_SIZE 9  // Assuming 9 buttons in the array

// Function prototype for button processing
//void processButtonConditions(uint8_t buttonConditions[]);
    uint16_t buttonConditions=0;

void ReadSwitch(void) {


    // Initialize UART configuration

   USART_Config UART_frame;
   UART_frame.Channel= USART_Channel_2;
   UART_frame.OVER8=0; //oversample by 16
   UART_frame.UE=1;
   UART_frame.M=0;
   UART_frame.PCE=0; //disable parity
   UART_frame.TCIE=1;
   UART_frame.TXEIE=0;
   UART_frame.TE =1; 
   UART_frame.RE=1;
   UART_frame.BaudRate=BAUD_RATE;

   USART_Init(&UART_frame);



    // Create a buffer to receive button conditions

    // Create a UART receive request
    Uart_RXRequest_t rxRequest = {
        .RX_Buffer = {0},   
        .Channel = USART_Channel_2,  
        .state = 0,         
        .RX_callBack = NULL 
    };

    // Start receiving button conditions asynchronously
    USART_ReceiveBuffer(&rxRequest);

    // Check if button conditions have been received
    if (rxRequest.state == 1) {
        // Copy received data from the buffer to the button conditions array
        for (int i = 0; i < BUFFER_SIZE; i++) {
            buttonConditions|= (1<<rxRequest.RX_Buffer.data[i]);
        }

        // Process button conditions
        //processButtonConditions(buttonConditions);
    }
}

// Function to process button conditions







