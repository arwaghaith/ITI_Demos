#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H


/*****************************************************************************************************************/

/*****************************************   GPIO Register Map  **************************************************/
#define GPIO_BASE_ADDRESS 0x40020000
#define GPIO_SIZE 0x400
#define GPIO_PIN_SIZE 0X01

#define GPIOA_BASE_ADDRESS (uint32_t)0x40020000
#define GPIOB_BASE_ADDRESS (uint32_t)0x40020400
#define GPIOC_BASE_ADDRESS (uint32_t)0x40020800

//#define GPIOC_OSPEEDR   *((volatile uint32_t*)(0x40020800+GPIO_OSPEEDR_OFFSET))

/*****************************************************************************************************************/
/*****************************************   GPIO_MODER **************************************************/

#define GPIO_MODER_OFFSET 0x00
#define GPIOA_MODER_RESET_VALUE 0x0C000000
#define GPIOB_MODER_RESET_VALUE 0x00000280
#define GPIOC_MODER_RESET_VALUE 0x00000000


/*****************************************************************************************************************/
/*****************************************   GPIO_OTYPER  **************************************************/

#define GPIO_OTYPER_OFFSET 0x04
#define GPIOA_OTYPER_RESET_VALUE 0x00000000
#define GPIOB_OTYPER_RESET_VALUE 0x00000000
#define GPIOC_OTYPER_RESET_VALUE 0x00000000


/*****************************************************************************************************************/
/*****************************************   GPIO_OSPEEDR **************************************************/

#define GPIO_OSPEEDR_OFFSET 0x08
#define GPIOA_OSPEEDR_RESET_VALUE 0x0C000000
#define GPIOB_OSPEEDR_RESET_VALUE 0x000000C0
#define GPIOC_OSPEEDR_RESET_VALUE 0x00000000

/*****************************************************************************************************************/
/*****************************************   GPIO_PUPDR **************************************************/

#define GPIO_PUPDR_OFFSET 0x0C
#define GPIOA_PUPDR_RESET_VALUE 0x64000000
#define GPIOB_PUPDR_RESET_VALUE 0x00000100
#define GPIOC_PUPDR_RESET_VALUE 0x00000000

/*****************************************************************************************************************/
/*****************************************   GPIO_IDR **************************************************/

#define GPIO_IDR_OFFSET 0x10
#define GPIOA_IDR_RESET_VALUE 0x00000000
#define GPIOB_IDR_RESET_VALUE 0x00000000
#define GPIOC_IDR_RESET_VALUE 0x00000000

/*****************************************************************************************************************/

/*****************************************   GPIO_ODR **************************************************/

#define GPIO_ODR_OFFSET 0x14
#define GPIOA_ODR_RESET_VALUE 0x00000000
#define GPIOB_ODR_RESET_VALUE 0x00000000
#define GPIOC_ODR_RESET_VALUE 0x00000000

/*****************************************************************************************************************/
/*****************************************   GPIO_BSRR **************************************************/

#define GPIO_BSRR_OFFSET 0x18
#define GPIOA_BSRR_RESET_VALUE 0x00000000
#define GPIOB_BSRR_RESET_VALUE 0x00000000
#define GPIOC_BSRR_RESET_VALUE 0x00000000

/*****************************************************************************************************************/
/*****************************************   GPIO_LCKR **************************************************/

#define GPIO_LCKR_OFFSET 0x1C
#define GPIOA_LCKR_RESET_VALUE 0x00000000
#define GPIOB_LCKR_RESET_VALUE 0x00000000
#define GPIOC_LCKR_RESET_VALUE 0x00000000

/*****************************************************************************************************************/
/*****************************************   GPIO_AFRL **************************************************/

#define GPIO_AFRL_OFFSET 0x20
#define GPIOA_AFRL_RESET_VALUE 0x00000000
#define GPIOB_AFRL_RESET_VALUE 0x00000000
#define GPIOC_AFRL_RESET_VALUE 0x00000000

/*****************************************************************************************************************/
/*****************************************   GPIO_AFRH **************************************************/

#define GPIO_AFRH_OFFSET 0x24
#define GPIOA_AFRH_RESET_VALUE 0x00000000
#define GPIOB_AFRH_RESET_VALUE 0x00000000
#define GPIOC_AFRH_RESET_VALUE 0x00000000

/*****************************************************************************************************************/
/*****************************************   GPIO_MASKS **************************************************/

#define GPIO_MODER_MASK 0x3
#define GPIO_OTYPER_MASK 0x1
#define GPIO_OSPEEDR_MASK 0x3
#define GPIO_PUPDR_MASK 0x3
#define GPIO_IDR_MASK 0x1
#define GPIO_ODR_MASK 0x1
#define GPIO_BSRR_MASK 0x1
#define GPIO_LCKR_MASK 0x1
#define GPIO_AFRL_MASK 0x0F
#define GPIO_AFRH_MASK 0x0F

/*****************************************************************************************************************/

/*****************************************   GPIO_REG_bits **************************************************/

#define GPIO_MODER_BITS 2
#define GPIO_OTYPER_BITS 1
#define GPIO_OSPEEDR_BITS 2
#define GPIO_PUPDR_BITS 2
#define GPIO_IDR_BITS 1
#define GPIO_ODR_BITS 1
#define GPIO_BSRR_BITS 1
#define GPIO_LCKR_BITS 1
#define GPIO_AFRL_BITS 4
#define GPIO_AFRH_BITS 4
/*****************************************************************************************************************/




/*****************************************************************************************************************/
/*****************************************   GPIO_MODER **************************************************/

#define GPIOA_MODER  ((volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIO_MODER_OFFSET))
#define GPIOB_MODER  ((volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIO_MODER_OFFSET))
#define GPIOC_MODER  ((volatile uint32_t *)(GPIOC_BASE_ADDRESS + GPIO_MODER_OFFSET))

/*****************************************************************************************************************/
/*****************************************   GPIO_OTYPER **************************************************/

#define GPIOA_OTYPER  ((volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIO_OTYPER_OFFSET))
#define GPIOB_OTYPER  ((volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIO_OTYPER_OFFSET))
#define GPIOC_OTYPER  ((volatile uint32_t *)(GPIOC_BASE_ADDRESS + GPIO_OTYPER_OFFSET))
/*****************************************************************************************************************/
/*****************************************   GPIO_OSPEEDR **************************************************/

#define GPIOA_OSPEEDR  ((volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIO_OSPEEDR_OFFSET))
#define GPIOB_OSPEEDR  ((volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIO_OSPEEDR_OFFSET))
#define GPIOC_OSPEEDR  ((volatile uint32_t *)(0x40020800 + GPIO_OSPEEDR_OFFSET))
/*****************************************************************************************************************/
/*****************************************   GPIO_PUPDR **************************************************/

#define GPIOA_PUPDR  ((volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIO_PUPDR_OFFSET))
#define GPIOB_PUPDR  ((volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIO_PUPDR_OFFSET))
#define GPIOC_PUPDR  ((volatile uint32_t *)(GPIOC_BASE_ADDRESS + GPIO_PUPDR_OFFSET))

/******************************************************************************************************************/
/*****************************************   GPIO_IDR **************************************************/

#define GPIOA_IDR  ((volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIO_IDR_OFFSET))
#define GPIOB_IDR  ((volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIO_IDR_OFFSET))
#define GPIOC_IDR  ((volatile uint32_t *)(GPIOC_BASE_ADDRESS + GPIO_IDR_OFFSET))
/******************************************************************************************************************/
/*****************************************   GPIO_ODR **************************************************/

#define GPIOA_ODR  ((volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIO_ODR_OFFSET))
#define GPIOB_ODR  ((volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIO_ODR_OFFSET))
#define GPIOC_ODR  ((volatile uint32_t *)(GPIOC_BASE_ADDRESS + GPIO_ODR_OFFSET))

/******************************************************************************************************************/
/*****************************************   GPIO_BSRR **************************************************/
#define GPIOA_BSRR  ((volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIO_BSRR_OFFSET))
#define GPIOB_BSRR  ((volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIO_BSRR_OFFSET))
#define GPIOC_BSRR  ((volatile uint32_t *)(GPIOC_BASE_ADDRESS + GPIO_BSRR_OFFSET))

/******************************************************************************************************************/
/*****************************************   GPIO_LCKR **************************************************/
#define GPIOA_LCKR  ((volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIO_LCKR_OFFSET))
#define GPIOB_LCKR  ((volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIO_LCKR_OFFSET))
#define GPIOC_LCKR  ((volatile uint32_t *)(GPIOC_BASE_ADDRESS + GPIO_LCKR_OFFSET))

/******************************************************************************************************************/
/*****************************************   GPIO_AFRL **************************************************/
#define GPIOA_AFRL  ((volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIO_AFRL_OFFSET))
#define GPIOB_AFRL  ((volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIO_AFRL_OFFSET))
#define GPIOC_AFRL  ((volatile uint32_t *)(GPIOC_BASE_ADDRESS + GPIO_AFRL_OFFSET))
/******************************************************************************************************************/
/*****************************************   GPIO_AFRH **************************************************/
#define GPIOA_AFRH  ((volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIO_AFRH_OFFSET))
#define GPIOB_AFRH  ((volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIO_AFRH_OFFSET))
#define GPIOC_AFRH  ((volatile uint32_t *)(GPIOC_BASE_ADDRESS + GPIO_AFRH_OFFSET))
/******************************************************************************************************************/


#define MODER_MASK 0x3

#endif
