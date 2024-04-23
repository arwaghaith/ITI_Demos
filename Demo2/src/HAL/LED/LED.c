




#include "LEDCfg.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../LIB/STD_TYPES.h"
#include "LED.h"


/* 
   This function is used to initialize the LEDs used
    * Inputs: void
    * Outputs: Error_Status
*/
 extern LED_t LEDS[LEDs_NUM];

LED_Error_Status LED_Init(void)
{

    LED_Error_Status local_Error_status = LED_NOK;
    GPIO_PIN_t LED_PIN;
    for(uint32_t i=0;i<LEDs_NUM;i++)
    {
        LED_PIN.port=LEDS[i].port;
        LED_PIN.pin=LEDS[i].pin;
        LED_PIN.mode=GPIO_MODE_OUTPUT;
        LED_PIN.speed=GPIO_SPEED_HIGH;
        LED_PIN.pull=GPIO_OUTPUT_TYPE_PUSH_PULL;
        LED_PIN.value=LEDS[i].LED_STATE^ LEDS[i].connection;
        local_Error_status=GPIO_Init(&LED_PIN);
        }
    return local_Error_status;
}

/* 
   This function is used to set the state of the LED
    * Inputs: LED_t led,uint32_t state
    * Outputs: Error_Status
*/
LED_Error_Status LED_SetState(LED_NAME led,uint32_t state)
{

    LED_Error_Status local_Error_status = LED_NOK;
    local_Error_status=GPIO_SET_PIN_VALUE(LEDS[led].port,LEDS[led].pin,state^LEDS[led].connection);
    return local_Error_status;
   
    
    

}

/* 
   This function is used to get the state of the LED
    * Inputs: LED_t led,uint32_t *state
    * Outputs: Error_Status
*/
LED_Error_Status LED_getState(LED_NAME led,uint32_t *state)
{
    LED_Error_Status local_Error_status = LED_NOK;
    uint32_t led_value;
    local_Error_status=GPIO_GET_PIN_VALUE(LEDS[led].port,LEDS[led].pin,&led_value);
    *state=led_value^LEDS[led].connection;
    return local_Error_status;

}


void Toggle_LED(LED_NAME led)
{
  uint32_t state;
  LED_getState(led,&state);
  if(state==LED_ON)
  {
    LED_SetState(led,LED_OFF);
  }
  else
  {
    LED_SetState(led,LED_ON);
  }
  
}
