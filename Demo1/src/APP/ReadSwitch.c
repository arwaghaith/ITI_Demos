#include"DEMO.h"

#include "../LIB/STD_TYPES.h"
#include "../HAL/HSWITCH/HSWITCH.h"
#include "../MCAL/UART/UART.h"
#include <stdlib.h>


#define CHECKSUM_    0b0010
#define PREFIX_MASK 0b1100
#define PREFIX_VAL  0b0100

extern uint8_t  DISPLAY_MODE ;
 uint16_t volatile buttonConditions = 0;
uint16_t prevButtonConditions = 0;
extern uint8_t  current_edit_position;
extern volatile StopWatch_State_t SW_State;


// Function to read switch conditions
void ReadSwitch(void) {
  
    GPIO_PIN_t GPIOA7 = { GPIO_PORTA, GPIO_PIN7, GPIO_MODE_OUTPUT, GPIO_SPEED_HIGH, GPIO_OUTPUT_TYPE_PUSH_PULL, GPIO_LOW };
    GPIO_Init(&GPIOA7);

    GPIO_PIN_t GPIOA8 = { GPIO_PORTA, GPIO_PIN8, GPIO_MODE_OUTPUT, GPIO_SPEED_HIGH, GPIO_OUTPUT_TYPE_PUSH_PULL, GPIO_LOW };
    GPIO_Init(&GPIOA8);


    static volatile uint8_t  receivedIndex = 0; // Variable to store received index as integer


    // Start receiving button index asynchronously
    USART_GetByteASynchronous(USART_Channel_2, &receivedIndex); // Assuming USART_GetByteASynchronous receives the index as string
  // receivedIndex = atoi(receivedIndex_str);

 switch ( receivedIndex ) {
            case START_STOP:
                buttonConditions = (1 << START_STOP);
                if ((buttonConditions & (1 << START_STOP))) 
                   { 
                        if (SW_State == SWstate_Initial)
                        {
                            SW_State = SWstate_Running;
                        }
                        else if (SW_State == SWstate_Running)
                        {
                            SW_State = SWstate_Initial;
                        }
                        else if (SW_State == SWstate_Paused)
                        {
                            SW_State = SWstate_Initial;
                         
                        }

                  }

              GPIO_SET_PIN_VALUE(GPIO_PORTA , GPIO_PIN8 ,GPIO_HIGH);
                break;
            case PAUSE_CONT:
                buttonConditions = (1 << PAUSE_CONT);
                if ((buttonConditions & (1 << PAUSE_CONT))) 
                   { 
                        if (SW_State == SWstate_Running)
                        {
                            SW_State = SWstate_Paused;
                        }
                        else if (SW_State == SWstate_Paused)
                        {
                            SW_State = SWstate_Running;
                         
                        }

                  }
                  GPIO_SET_PIN_VALUE(GPIO_PORTA , GPIO_PIN8 ,GPIO_HIGH);
                break;
            case EDIT:
                buttonConditions = (1 << EDIT);
                break;
            case MODE:
                buttonConditions = (1 << MODE); 
                if ((buttonConditions & (1 << MODE))) 
                   { 
                   DISPLAY_MODE ^=1;

                  }

                  GPIO_SET_PIN_VALUE(GPIO_PORTA , GPIO_PIN8 ,GPIO_HIGH);
                break;
            case UP:
                buttonConditions = (1 << UP);
                break;
            case DOWN: //06
                buttonConditions = (1 << DOWN);
                break;
            case LEFT: //07
                buttonConditions = (1 << LEFT);
                  current_edit_position-=3;
                break;
            case RIGHT: //08
                buttonConditions = (1 << RIGHT);
                 current_edit_position += 3;
                 GPIO_SET_PIN_VALUE(GPIO_PORTA , GPIO_PIN8,GPIO_HIGH);
                break;
            default:
                break;
        }

receivedIndex =0;
}

void clearButtonCondition(uint16_t button) {
    buttonConditions &= ~(1 << button);
}

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   











