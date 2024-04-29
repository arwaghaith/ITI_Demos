

#ifndef __RCC_H
#define __RCC_H
/*including the necessary libraries for The RCC peripheral*/

#include  "../../LIB/STD_TYPES.h"



#include  "../../LIB/STD_TYPES.h"


/**********************************************************************************/
/*RCC_AHB1 peripheral register*/
/*clock reset register */
/*********************************************************************************/
#define DMA2RST 22
#define DMA1RST 21
#define CRCRST 12
#define GPIOHRST 7
#define GPIOERST 4
#define GPIODRST 3
#define GPIOCRST 2
#define GPIOBRST 1

/*****************************************************************************************/

/*RCC_AHB2 peripheral register*/
/*clock reset register */
#define OTGFSRST 7

/*****************************************************************************************/

/*RCC_APB1 peripheral register*/
/*clock reset register */
#define PWRRST 28
#define I2C3RST 23
#define I2C2RST 22
#define I2C1RST 21
#define USART3RST 18
#define SPI3RST 15
#define SPI2RST 14
#define WWDGRST 11
#define TIM5RST 3
#define TIM4RST 2
#define TIM3RST 1
#define TIM2RST 0
#define USART2RST 17
/*****************************************************************************************/

/*RCC_APB2 peripheral register*/
    /*clock reset register */
#define TIM11RST 18
#define TIM10RST 17
#define TIM9RST 16
#define SYSCFGRST 14
#define SPI5RST 20
#define SPI4RST 15
#define SPI1RST 12
#define SDIORST 11
#define ADC1RST 8
#define USART6RST 5
#define USART1RST 4
#define TIM8RST 1
#define TIM1RST 0
/*****************************************************************************************/

/*RCC_AHB1 peripheral register*/

/*clock enable register */
#define DMA2EN 22
#define DMA1EN 21
#define CRCEN 12
#define GPIOHEN 7
#define GPIOEEN 4
#define GPIODEN 3
#define GPIOCEN 2
#define GPIOBEN 1
#define GPIOAEN 0
/*****************************************************************************************/

/*RCC_AHB2 peripheral register*/
/*clock enable register */
#define OTGFSEN 7
/*****************************************************************************************/

/*RCC_APB1 peripheral register*/
/*clock enable register */
#define PWREN 28
#define I2C3EN 23
#define I2C2EN 22
#define I2C1EN 21
#define USART3EN 18
#define SPI3EN 15
#define SPI2EN 14
#define WWDGEN 11
#define TIM5EN 3
#define TIM4EN 2
#define TIM3EN 1
#define TIM2EN 0
/*****************************************************************************************/

/*RCC_APB2 peripheral register*/
/*clock enable register */
#define TIM11EN 18
#define TIM10EN 17
#define TIM9EN 16
#define SYSCFGEN 14
#define SPI4EN 13
#define SPI1EN 12
#define SDIOEN 11
#define ADC1EN 8
#define USART6EN 5
#define USART1EN 4
#define TIM8EN 1
#define TIM1EN 0
/*****************************************************************************************/

/*RCC_AHB1 peripheral register*/

/*clock low power enable register */

#define DMA2LPEN 22
#define DMA1LPEN 21
#define SRAM2LPEN 17
#define SRAM1LPEN 16
#define FLITFLPEN 15
#define CRCLPEN 12
#define GPIOHLPEN 7
#define GPIOELPEN 4
#define GPIODLPEN 3
#define GPIOCLPEN 2
#define GPIOBLPEN 1
#define GPIOALPEN 0
/*****************************************************************************************/

/*RCC_AHB2 peripheral register*/

/*clock low power enable register */
#define OTGFSLPEN 7
/*****************************************************************************************/

/*RCC_APB1 peripheral register*/

/*clock low power enable register */
#define PWRLPEN 28
#define I2C3LPEN 23
#define I2C2LPEN 22
#define I2C1LPEN 21
#define USART3LPEN 18
#define SPI3LPEN 15
#define SPI2LPEN 14
#define WWDGLPEN 11
#define TIM5LPEN 3
#define TIM4LPEN 2
#define TIM3LPEN 1
#define TIM2LPEN 0
/*****************************************************************************************/

/*RCC_APB2 peripheral register*/
/*clock low power enable register */

#define TIM11LPEN 18
#define TIM10LPEN 17
#define TIM9LPEN 16
#define SYSCFGLPEN 14
#define SPI5LPEN 20
#define SPI4LPEN 13
#define SPI1LPEN 12
#define SDIOLPEN 11
#define ADC1LPEN 8
#define USART6LPEN 5
#define USART1LPEN 4
#define TIM8LPEN 1
#define TIM1LPEN 0
/*****************************************************************************************/

#define PLL_HSI_SRC 0
#define PLL_HSE_SRC 1
#define PLLSRC_HSE 0x00400000
#define PLLSRC_HSI 0x00000000


     
typedef enum{
    RCC_HSI,
    RCC_HSE,
    RCC_PLL
}RCC_CLK_TYPE;

typedef enum{
    CLK_OFF,
    CLK_ON
}RCC_STATE;

typedef enum{
    RCC_NOK,

    RCC_OK
}RCC_ERROR_STATUS;

typedef enum{
    RCC_AHB1,
    RCC_AHB2,
    RCC_APB1,
    RCC_APB2
}RCC_PERIPHERAL_BUS_TYPE;

typedef enum{
    RCC_AHB_SCALER,
    RCC_APB1_SCALER,
    RCC_APB2_SCALER
}RCC_PERIPHERAL_BUS_TYPE_prescalar;



     




















typedef enum
{



    /*APB low-speed PRESCALAR bits*/
    RCC_APB1_PRESCALAR_2=4,
    RCC_APB1_PRESCALAR_4=5,
    RCC_APB1_PRESCALAR_8=6,
    RCC_APB1_PRESCALAR_16=7,

    /*APB high-speed PRESCALAR bits*/
    RCC_APB2_PRESCALAR_2=4,
    RCC_APB2_PRESCALAR_4=5,
    RCC_APB2_PRESCALAR_8=6,
    RCC_APB2_PRESCALAR_16=7,

    /*HSE PRESCALAR bits*/

    RCC_AHB_PRESCALAR_2=8,
    RCC_AHB_PRESCALAR_4=9,
    RCC_AHB_PRESCALAR_8=10,
    RCC_AHB_PRESCALAR_16=11,
    RCC_AHB_PRESCALAR_64=12,
    RCC_AHB_PRESCALAR_128=13,
    RCC_AHB_PRESCALAR_256=14,
    RCC_AHB_PRESCALAR_512=15,
}RCC_PRECALAR;


/*this function  is  for controlling any clock in the system as ON or OFF*/
/* it takes two parameters
    * 1- clock_type: which is the clock that you want to control
    * 2- state: what is the state of the clock ON or OFF
    * it returns:
    * 1- RCC_OK: if the clock is controlled successfully
    * 2- RCC_NOK: if the clock is not controlled successfully
 */
RCC_ERROR_STATUS RCC_ControlClock(RCC_CLK_TYPE clock_type, RCC_STATE state);

/*this function is for configuring the PLL clock*/
/* it takes four parameters
    * 1- PLL_M: the value of the PLL_M  "DIVISION FACTOR"
    * 2- PLL_N: the value of the PLL_N  "MULTIPLICATION FACTOR"
    * 3- PLL_P: the value of the PLL_P  "DIVISION FACTOR"
    * 4- PLL_Q: the value of the PLL_Q  "DIVISION FACTOR"
    * it returns:
    * 1- RCC_OK: if the PLL is configured successfully
    * 2- RCC_NOK: if the PLL is not configured successfully
 */

RCC_ERROR_STATUS RCC_ConfigurePLL(uint8_t PLL_M, uint16_t PLL_N, uint8_t PLL_P, uint8_t PLL_Q,uint32_t PLL_SRC);

/*this function is for selecting the system clock*/
/* it takes one parameter
    * 1- clock_type: the clock that you want to select as a system clock
    * it returns:
    * 1- RCC_OK: if the clock is selected successfully
    * 2- RCC_NOK: if the clock is not selected successfully
 */

RCC_ERROR_STATUS RCC_SelectSysClk(RCC_CLK_TYPE clock_type);

/*this function is for controlling the clock of any peripheral in the system */
/* it takes two parameters
    * 1- peripheral: the peripheral that you want to control its clock
    * 2- state: what is the state of the peripheral clock ON or OFF
    * it returns:
    * 1- RCC_OK: if the peripheral clock is controlled successfully
    * 2- RCC_NOK: if the peripheral clock is not controlled successfully
 */

RCC_ERROR_STATUS RCC_ControlPeripheralClock(RCC_PERIPHERAL_BUS_TYPE RCC_bus,uint8_t peripheral, RCC_STATE state);



/*This function is for configuring any  prescalar in the system*/

/* it takes two parameters
    * 1- peripheral: the peripheral that you want to control its clock
    * 2- prescalar: the value of the prescalar
    * it returns:
    * 1- RCC_OK: if the prescalar is configured successfully
    * 2- RCC_NOK: if the prescalar is not configured successfully
 */

RCC_ERROR_STATUS RCC_ConfigurePrescalar(RCC_PERIPHERAL_BUS_TYPE_prescalar RCC_BUS, RCC_PRECALAR prescalar);
#endif
