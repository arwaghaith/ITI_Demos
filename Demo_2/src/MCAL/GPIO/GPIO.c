
#include "GPIO_private.h"
#include "GPIO.h"
#include  "../../LIB/STD_TYPES.h"

#include "../../LIB/STD_MATH.h"



uint32_t GPIO_PORT[3] =
{
   GPIOA_BASE_ADDRESS,
    GPIOB_BASE_ADDRESS,
    GPIOC_BASE_ADDRESS
};

GPIO_Error_t GPIO_Init(GPIO_PIN_t *GPIO_PIN)
{

    GPIO_Error_t local_Error_status = GPIO_NOK;
 
   volatile uint32_t temp=0;

    if(GPIO_PIN->port <= GPIO_PORTC && GPIO_PIN->port>=GPIO_PORTA)
    {
       
        if((GPIO_PIN->port==GPIO_PORTC && GPIO_PIN->pin>=GPIO_PIN13 && GPIO_PIN->pin<=GPIO_PIN15) || (GPIO_PIN->port!=GPIO_PORTC && GPIO_PIN->pin<=GPIO_PIN15 && GPIO_PIN->pin>=GPIO_PIN0))
        {
            if(GPIO_PIN->mode<=GPIO_MODE_ANALOG && GPIO_PIN->mode >=GPIO_MODE_INPUT)
            {
                if(GPIO_PIN->mode ==GPIO_MODE_OUTPUT)
                {
                    if(GPIO_PIN->value) *((volatile uint32_t *)(GPIO_PORT[GPIO_PIN->port]+GPIO_ODR_OFFSET)) |= (1<<GPIO_PIN->pin);
                    else *((volatile uint32_t *)(GPIO_PORT[GPIO_PIN->port]+GPIO_ODR_OFFSET)) &= ~((uint32_t)(1<<GPIO_PIN->pin));
                } 
                temp=*((volatile uint32_t*)((GPIO_PORT[GPIO_PIN->port]+GPIO_MODER_OFFSET)));
                temp&=~(GPIO_MODER_MASK<<((GPIO_PIN->pin)*GPIO_MODER_BITS));
                temp|=(GPIO_PIN->mode<<((GPIO_PIN->pin)*GPIO_MODER_BITS));
                *((volatile uint32_t*)((GPIO_PORT[GPIO_PIN->port])+GPIO_MODER_OFFSET))=temp;
              
            }
            else
            {
                local_Error_status=GPIO_NOK;
            }

            if(GPIO_PIN->speed<=GPIO_SPEED_HIGH && GPIO_PIN->speed >=GPIO_SPEED_LOW)
            {
                temp=*((volatile uint32_t*)(GPIO_PORT[GPIO_PIN->port]+GPIO_OSPEEDR_OFFSET));
                temp&=~(GPIO_OSPEEDR_MASK<<((GPIO_PIN->pin)*GPIO_OSPEEDR_BITS));
                temp|=(GPIO_PIN->speed<<((GPIO_PIN->pin)*GPIO_OSPEEDR_BITS));
                *((volatile uint32_t*)((GPIO_PORT[GPIO_PIN->port])+GPIO_OSPEEDR_OFFSET))=temp;
            }
            else
            {
                local_Error_status=GPIO_NOK;
            }

            if(GPIO_PIN->mode ==GPIO_MODE_INPUT  &&GPIO_PIN->pull>=GPIO_PUPDR_NO_PULL && GPIO_PIN->pull <=GPIO_PUPDR_PULL_DOWN)
            {
                temp=*((volatile uint32_t*)(GPIO_PORT[GPIO_PIN->port]+GPIO_PUPDR_OFFSET));
                temp&=~(GPIO_PUPDR_MASK<<((GPIO_PIN->pin)*GPIO_PUPDR_BITS));
                temp|=(GPIO_PIN->pull<<((GPIO_PIN->pin)*GPIO_PUPDR_BITS));

                *((volatile uint32_t*)((GPIO_PORT[GPIO_PIN->port])+GPIO_PUPDR_OFFSET))=temp;
            }
            else if (GPIO_PIN->mode ==GPIO_MODE_OUTPUT  &&GPIO_PIN->pull>=GPIO_OUTPUT_TYPE_PUSH_PULL && GPIO_PIN->pull <=GPIO_OUTPUT_TYPE_OPEN_DRAIN)
            {
                temp=*((volatile uint32_t*)(GPIO_PORT[GPIO_PIN->port]+GPIO_PUPDR_OFFSET));
                temp&=~(GPIO_PUPDR_MASK<<((GPIO_PIN->pin)*GPIO_PUPDR_BITS));
                temp|=((GPIO_PIN->pull-GPIO_OUTPUT_OFFSET)<<((GPIO_PIN->pin)*GPIO_PUPDR_BITS));
                *((volatile uint32_t*)((GPIO_PORT[GPIO_PIN->port])+GPIO_PUPDR_OFFSET))=temp;
            }

            else if ( GPIO_PIN->mode ==  GPIO_MODE_ALTERNATE  && GPIO_PIN->pull>=AF0  && GPIO_PIN->pull<=AF15)

            {

                if(GPIO_PIN->pin<8)
                {
                temp=*((volatile uint32_t*)(GPIO_PORT[GPIO_PIN->port]+GPIO_AFRL_OFFSET));

                temp&=~(uint32_t)(GPIO_AFRL_MASK<<((GPIO_PIN->pin)*GPIO_AFRL_BITS));
                temp|=(uint32_t)(GPIO_PIN->pull<<((GPIO_PIN->pin)*GPIO_AFRL_BITS));
                *((volatile uint32_t*)((GPIO_PORT[GPIO_PIN->port])+GPIO_AFRL_OFFSET))=temp;
                }

                else
                {
                    temp=*((volatile uint32_t*)(GPIO_PORT[GPIO_PIN->port]+GPIO_AFRH_OFFSET));
                    temp&=~(uint32_t)(GPIO_AFRH_MASK<<((GPIO_PIN->pin-8)*GPIO_AFRH_BITS));
                    temp|=(uint32_t)(GPIO_PIN->pull<<((GPIO_PIN->pin-8)*GPIO_AFRH_BITS));
                    *((volatile uint32_t*)((GPIO_PORT[GPIO_PIN->port])+GPIO_AFRH_OFFSET))=temp;
                }


            }
            else
            
            {
                local_Error_status=GPIO_NOK;
            }
        }
        else
        {
            local_Error_status=GPIO_NOK;
        }
    }
    else
    {
        local_Error_status=GPIO_NOK;
    }
    
    return local_Error_status;
}

            

GPIO_Error_t GPIO_SET_PIN_VALUE(uint32_t port, uint32_t pin, uint32_t value)
{
    GPIO_Error_t local_Error_status = GPIO_NOK;
    uint32_t loc_mode;
    

    if(port <= GPIO_PORTC && port>=GPIO_PORTA)
    {
        if((port==GPIO_PORTC && pin>=GPIO_PIN13 && pin<=GPIO_PIN15) || (port!=GPIO_PORTC && pin<=GPIO_PIN15 && pin>=GPIO_PIN0))
        {
            if(GPIO_GETMODE(port,pin,&loc_mode)==GPIO_OK)
            {
                if(loc_mode==GPIO_MODE_OUTPUT)
                {
                    if(value) *((volatile uint32_t *)(GPIO_PORT[port]+GPIO_ODR_OFFSET)) |= (1<<pin);
                    else *((volatile uint32_t *)(GPIO_PORT[port]+GPIO_ODR_OFFSET)) &= ~((uint32_t)(1<<pin));
                   local_Error_status=GPIO_OK;
                }
                else
                {
                    local_Error_status=GPIO_NOK;
                }

        }
        else
        {
            local_Error_status=GPIO_NOK;
        }
    }
    else
    {
        local_Error_status=GPIO_NOK;
    }
}
    return local_Error_status;

}

         




GPIO_Error_t GPIO_GET_PIN_VALUE(uint32_t port, uint32_t pin, uint32_t *value)

{
    GPIO_Error_t local_Error_status = GPIO_NOK;
    if(port <= GPIO_PORTC && port>=GPIO_PORTA)
    {
        if((port==GPIO_PORTC && pin>=GPIO_PIN13 && pin<=GPIO_PIN15) || (port!=GPIO_PORTC && pin<=GPIO_PIN15 && pin>=GPIO_PIN0))
        {
           *value=(*((volatile uint32_t *) (GPIO_PORT[port]+GPIO_IDR_OFFSET))>> pin) & 1;
            local_Error_status=GPIO_OK;
        }
        else
        {
            local_Error_status=GPIO_NOK;
        }
    }
    else
    {
        local_Error_status=GPIO_NOK;
    }
    return local_Error_status;
   



}
GPIO_Error_t GPIO_GETMODE(uint32_t port, uint32_t pin, uint32_t *mode)
{
    GPIO_Error_t local_Error_status = GPIO_NOK;
    if(port <= GPIO_PORTC && port>=GPIO_PORTA)
    {
        if((port==GPIO_PORTC && pin>=GPIO_PIN13 && pin<=GPIO_PIN15) || (port!=GPIO_PORTC && pin<=GPIO_PIN15 && pin>=GPIO_PIN0))
        {
          *mode=(GPIO_PORT[port]+GPIO_MODER_OFFSET) && ~(GPIO_MODER_MASK<<((pin)*GPIO_MODER_BITS))>>((pin)*GPIO_MODER_BITS);
            local_Error_status=GPIO_OK;
        }
        else
        {
            local_Error_status=GPIO_NOK;
        }
    }
    else
    {
        local_Error_status=GPIO_NOK;
    }
    return local_Error_status;
}