#ifndef GPIO_H
#define GPIO_H


/*****************************************************************************************************************/
/*****************************************   INCLUDING LIBRARIES **************************************************/
#include "../../LIB/STD_TYPES.h"
#include  "GPIO_private.h"




/*****************************************************************************************************************/
/*****************************************   GPIO PINS NUMBER **************************************************/
#define GPIO_PINS_NUMBER 35

#define GPIOA_SIZE 16
#define GPIOB_SIZE 16
#define GPIOC_SIZE 3
/*****************************************   GPIO ERROR STATUS **************************************************/

typedef enum
{
    GPIO_OK = 0,
    GPIO_NOK = 1
}GPIO_Error_t;
/*****************************************************************************************************************/
/*****************************************   GPIO PORTS **************************************************/

#define  GPIO_PORTA 0
#define  GPIO_PORTB 1
#define  GPIO_PORTC 2

/*****************************************************************************************************************/
/*****************************************   GPIO PINS **************************************************/

#define  GPIO_PIN0    0
#define  GPIO_PIN1    1
#define  GPIO_PIN2    2
#define  GPIO_PIN3    3
#define  GPIO_PIN4    4
#define  GPIO_PIN5    5
#define  GPIO_PIN6    6
#define  GPIO_PIN7    7
#define  GPIO_PIN8    8
#define  GPIO_PIN9    9
#define  GPIO_PIN10   10
#define  GPIO_PIN11   11
#define  GPIO_PIN12   12
#define  GPIO_PIN13   13
#define  GPIO_PIN14   14
#define  GPIO_PIN15   15


/*****************************************************************************************************************/
/*****************************************   GPIO MODES **************************************************/
#define  GPIO_MODE_ANALOG       3
#define  GPIO_MODE_INPUT        0
#define  GPIO_MODE_OUTPUT       1
#define  GPIO_MODE_ALTERNATE    2
/*****************************************************************************************************************/



/*****************************************   GPIO SPEED **************************************************/

#define  GPIO_SPEED_LOW         0
#define  GPIO_SPEED_MEDIUM      1
#define  GPIO_SPEED_HIGH        2
#define  GPIO_SPEED_VERY_HIGH   3
/*****************************************************************************************************************/
#define AF0                     0
#define AF1                     1
#define AF2                     2
#define AF3                     3
#define AF4                     4
#define AF5                     5
#define AF6                     6
#define AF7                     7
#define AF8                     8
#define AF9                     9
#define AF10                    10
#define AF11                    11
#define AF12                    12
#define AF13                    13
#define AF14                    14
#define AF15                    15

/*****************************************   GPIO PUPDR **************************************************/

#define  GPIO_PUPDR_NO_PULL     0
#define  GPIO_PUPDR_PULL_UP     1
#define  GPIO_PUPDR_PULL_DOWN   2
/*****************************************************************************************************************/
/*****************************************  OTYPER **************************************************/
#define  GPIO_OUTPUT_OFFSET  3

#define  GPIO_OUTPUT_TYPE_PUSH_PULL     3
#define  GPIO_OUTPUT_TYPE_OPEN_DRAIN    4

/*****************************************************************************************************************/
#define GPIO_LOW  0
#define GPIO_HIGH 1

typedef struct 
{
    uint32_t  port;
    uint32_t pin;
    uint32_t mode;
    uint32_t speed;
    uint32_t pull;
    uint32_t value;
    
}GPIO_PIN_t;




    




/*****************************************************************************************************************/

/*This function  
    
    * 1. Configures the GPIO pin according to the configuration
    * 2. Returns the Error status of the configuration
    * 3. The configuration includes the following:
        * 1. Port
        * 2. Pin
        * 3. Mode
        * 4. Speed
        * 5. Pull
        * 6. Value
*/

GPIO_Error_t GPIO_Init(GPIO_PIN_t *GPIO_PIN);

/*****************************************************************************************************************/

/*This function  
    
    * 1. Sets the value of the GPIO pin according to the user input
    * 2. Returns the Error status of the configuration
    * 3. The input includes the following:
        * 1. Port
        * 2. Pin
        * 3. Value
*/


GPIO_Error_t GPIO_SET_PIN_VALUE(uint32_t port, uint32_t pin, uint32_t value);

/*****************************************************************************************************************/

/*This function  
    
    * 1. Gets the value of the GPIO pin 
    * 2. Returns the Error status of the configuration
    * 3. The input includes the following:
        * 1. Port
        * 2. Pin
        * 3. Value
*/

GPIO_Error_t GPIO_GET_PIN_VALUE(uint32_t port, uint32_t pin, uint32_t *value);

/*****************************************************************************************************************/
/*This function  
    
    * 1. Gets a pointer to the mode of the GPIO pin 
    * 2. Returns the Error status of the configuration
    *    the mode is returned through the pointer
    * 3. The input includes the following:
        * 1. Port
        * 2. Pin
        * 3. pointer to the Mode
*/


GPIO_Error_t GPIO_GETMODE(uint32_t port, uint32_t pin, uint32_t *mode);


#endif