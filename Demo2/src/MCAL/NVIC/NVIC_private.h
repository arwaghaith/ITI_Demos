#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

#include "../../LIB/STD_TYPES.h"

/* Base addresses of NVIC and EXTI peripherals */
#define NVIC_BASE_ADDRESS  0xE000E100
#define EXTI_BASE_ADDRESS  0x40010400

/* Base address of SCB register */
#define SCB_AIRCR    *((volatile uint32_t *)(0xE000ED0C))

/* Priority group mask for SCB_AIRCR */
#define SCB_AIRCR_PRIORITY_GROUP_MASK  

/* Number of bits used for priority */
#define Priority_Bits 4

/* SCB_AIRCR priority group/sub priority settings */
#define SCB_AIRCR_PRIORITY_GROUP_4_SUB_0 (uint32_t)(0x00000000)
#define SCB_AIRCR_PRIORITY_GROUP_3_SUB_1 (uint32_t)(0X00000400)
#define SCB_AIRCR_PRIORITY_GROUP_2_SUB_2 (uint32_t)(0x00000500)
#define SCB_AIRCR_PRIORITY_GROUP_1_SUB_3 (uint32_t)(0x00000600)
#define SCB_AIRCR_PRIORITY_GROUP_0_SUB_4 (uint32_t)(0x00000700)



/*****************************************************************/
#define PRIORITY_GROUP_4_SUB_0 0x00
#define  PRIORITY_GROUP_3_SUB_1 0x01
#define  PRIORITY_GROUP_2_SUB_2 0x02  
#define  PRIORITY_GROUP_1_SUB_3 0x03
#define  PRIORITY_GROUP_0_SUB_4 0x04

#define SCB_AIRCR_VECTKEY_MASK  0X0000FFFF
#define SCB_AIRCR_PRIGROUP_MASK 0X00000700
#define SCB_AIRCR_VECTKEY_WRITE 0X05FA0000

/*****************************************************************/

/* Number of NVIC interrupt types */
#define NVIC_InterruptType_COUNT  85

/* Enumeration of NVIC priority groups */

/* Enumeration of NVIC interrupt types */
typedef enum {
    WWDG_IRQn = 0,              /* Window Watchdog interrupt */
    PVD_IRQn = 1,               /* PVD through EXTI Line detection interrupt */
    TAMPER_IRQn = 2,            /* Tamper interrupt */
    RTC_WKUP_IRQn = 3,          /* RTC global interrupt */
    FLASH_IRQn = 4,             /* Flash global interrupt */
    RCC_IRQn = 5,               /* RCC global interrupt */
    EXTI0_IRQn = 6,             /* EXTI Line0 interrupt */
    EXTI1_IRQn = 7,             /* EXTI Line1 interrupt */
    EXTI2_IRQn = 8,             /* EXTI Line2 interrupt */
    EXTI3_IRQn = 9,             /* EXTI Line3 interrupt */
    EXTI4_IRQn = 10,            /* EXTI Line4 interrupt */
    DMA1_Channel1_IRQn = 11,    /* DMA1 Channel1 global interrupt */
    /* Add more interrupt types here */
    SPI4_IRQn = 84              /* SPI4 global interrupt */
} NVIC_InterruptType;

#endif // NVIC_PRIVATE_H
