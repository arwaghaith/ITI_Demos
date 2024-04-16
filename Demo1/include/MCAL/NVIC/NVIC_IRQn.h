
#ifndef	 _NVIC_IRQN_H_
#define	 _NVIC_IRQN_H_

#include "Typedefs.h"

typedef enum 
{
    NVIC_WWDG = 0,                        /* Window WatchDog Interrupt */
    NVIC_PVD,                             /* PVD through EXTI Line detection Interrupt */
    NVIC_TAMP_STAMP,                      /* Tamper and TimeStamp interrupts through the EXTI line */
    NVIC_RTC_WKUP,                        /* RTC Wakeup interrupt through the EXTI line */
    NVIC_FLASH,                           /* FLASH global Interrupt */
    NVIC_RCC,                             /* RCC global Interrupt */
    NVIC_EXTI0,                           /* EXTI Line0 Interrupt */
    NVIC_EXTI1,                           /* EXTI Line1 Interrupt */
    NVIC_EXTI2,                           /* EXTI Line2 Interrupt */
    NVIC_EXTI3,                           /* EXTI Line3 Interrupt */
    NVIC_EXTI4,                           /* EXTI Line4 Interrupt */
    NVIC_DMA1_Stream0,                    /* DMA1 Stream 0 global Interrupt */
    NVIC_DMA1_Stream1,                    /* DMA1 Stream 1 global Interrupt */
    NVIC_DMA1_Stream2,                    /* DMA1 Stream 2 global Interrupt */
    NVIC_DMA1_Stream3,                    /* DMA1 Stream 3 global Interrupt */
    NVIC_DMA1_Stream4,                    /* DMA1 Stream 4 global Interrupt */
    NVIC_DMA1_Stream5,                    /* DMA1 Stream 5 global Interrupt */
    NVIC_DMA1_Stream6,                    /* DMA1 Stream 6 global Interrupt */
    NVIC_ADC,                             /* ADC1, ADC2 and ADC3 global Interrupts */
    NVIC_EXTI9_5 = 23,                    /* External Line[9:5] Interrupts */
    NVIC_TIM1_BRK_TIM9,                   /* TIM1 Break interrupt and TIM9 global interrupt */
    NVIC_TIM1_UP_TIM10,                   /* TIM1 Update Interrupt and TIM10 global interrupt */
    NVIC_TIM1_TRG_COM_TIM11,              /* TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
    NVIC_TIM1_CC,                         /* TIM1 Capture Compare Interrupt */
    NVIC_TIM2,                            /* TIM2 global Interrupt */
    NVIC_TIM3,                            /* TIM3 global Interrupt */
    NVIC_TIM4,                            /* TIM4 global Interrupt */
    NVIC_I2C1_EV,                         /* I2C1 Event Interrupt */
    NVIC_I2C1_ER,                         /* I2C1 Error Interrupt */
    NVIC_I2C2_EV,                         /* I2C2 Event Interrupt */
    NVIC_I2C2_ER,                         /* I2C2 Error Interrupt */
    NVIC_SPI1,                            /* SPI1 global Interrupt */
    NVIC_SPI2,                            /* SPI2 global Interrupt */
    NVIC_USART1,                          /* USART1 global Interrupt */
    NVIC_USART2,                          /* USART2 global Interrupt */
    NVIC_EXTI15_10 = 40,                  /* External Line[15:10] Interrupts */
    NVIC_RTC_Alarm,                       /* RTC Alarm (A and B) through EXTI Line Interrupt */
    NVIC_OTG_FS_WKUP,                     /* USB OTG FS Wakeup through EXTI line interrupt */
    NVIC_DMA1_Stream7,                    /* DMA1 Stream7 Interrupt */
    NVIC_SDIO,                            /* SDIO global Interrupt */
    NVIC_TIM5,                            /* TIM5 global Interrupt */
    NVIC_SPI3,                            /* SPI3 global Interrupt */
    NVIC_DMA2_Stream0,                    /* DMA2 Stream 0 global Interrupt */
    NVIC_DMA2_Stream1,                    /* DMA2 Stream 1 global Interrupt */
    NVIC_DMA2_Stream2,                    /* DMA2 Stream 2 global Interrupt */
    NVIC_DMA2_Stream3,                    /* DMA2 Stream 3 global Interrupt */
    NVIC_DMA2_Stream4,                    /* DMA2 Stream 4 global Interrupt */
    NVIC_OTG_FS,                          /* USB OTG FS global Interrupt */
    NVIC_DMA2_Stream5,                    /* DMA2 Stream 5 global interrupt */
    NVIC_DMA2_Stream6,                    /* DMA2 Stream 6 global interrupt */
    NVIC_DMA2_Stream7,                    /* DMA2 Stream 7 global interrupt */
    NVIC_USART6,                          /* USART6 global interrupt */
    NVIC_I2C3_EV,                         /* I2C3 event interrupt */
    NVIC_I2C3_ER,                         /* I2C3 error interrupt */
    NVIC_FPU,                             /* FPU global interrupt */
    NVIC_SPI4,                            /* SPI4 global Interrupt */
    _NVIC_IRQn                           /* num of IRQs */

} NVIC_IRQn_Type;

#endif /*_NVIC_IRQN_H_*/
