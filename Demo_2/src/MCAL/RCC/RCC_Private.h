/* BEGIN: ed8c6549bwf9 */
/* RCC Base Address*/

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/***************************************************************************************************************************/
                                           /* RCC Base Address*/
/***************************************************************************************************************************/                                          
#define RCC_BASE_ADDRESS 0x40023800

/***************************************************************************************************************************/
                                           /* RCC Registers addresses*/
/***************************************************************************************************************************/

#define RCC_CR          (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x00))    /* RCC clock control register */
#define RCC_PLLCFGR     (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x04))    /* RCC PLL configuration register */
#define RCC_CFGR        (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x08))    /* RCC clock configuration register */
#define RCC_CIR         (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x0C))    /* RCC clock interrupt register */
#define RCC_AHB1RSTR    (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x10))    /* RCC AHB1 peripheral reset register */
#define RCC_AHB2RSTR    (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x14))    /* RCC AHB2 peripheral reset register */
#define RCC_APB1RSTR    (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x20))    /* RCC APB1 peripheral reset register */
#define RCC_APB2RSTR    (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x24))    /* RCC APB2 peripheral reset register */
#define RCC_AHB1ENR     (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x30))    /* RCC AHB1 peripheral clock enable register */
#define RCC_AHB2ENR     (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x34))    /* RCC AHB2 peripheral clock enable register */
#define RCC_AHB3ENR     (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x38))    /* RCC AHB3 peripheral clock enable register */
#define RCC_APB1ENR     (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x40))    /* RCC APB1 peripheral clock enable register */
#define RCC_APB2ENR     (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x44))    /* RCC APB2 peripheral clock enable register */
#define RCC_AHB1LPENR   (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x50))    /* RCC AHB1 peripheral clock enable in low power mode register */
#define RCC_AHB2LPENR   (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x54))    /* RCC AHB2 peripheral clock enable in low power mode register */
#define RCC_AHB3LPENR   (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x58))    /* RCC AHB3 peripheral clock enable in low power mode register */
#define RCC_APB1LPENR   (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x60))    /* RCC APB1 peripheral clock enable in low power mode register */
#define RCC_APB2LPENR   (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x64))    /* RCC APB2 peripheral clock enable in low power mode register */
#define RCC_BDCR        (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x70))    /* RCC Backup domain control register */
#define RCC_CSR         (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x74))    /* RCC clock control & status register */
#define RCC_SSCGR       (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x80))    /* RCC spread spectrum clock generation register */
#define RCC_PLLI2SCFGR  (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x84))    /* RCC PLLI2S configuration register */
#define RCC_DCKCFGR     (*(volatile uint32_t*const)(RCC_BASE_ADDRESS + 0x8C))    /* RCC Dedicated Clock Configuration Register */
/***************************************************************************************************************************/


/****************************************************************************************************************************/
                                           /*Register Masks*/
/****************************************************************************************************************************/

/*Selecting System Clock Mask*/
#define RCC_CFGR_SW_MASK 0x3

/*Selecting System Clock Status Mask*/
#define RCC_CFGR_SWS_MASK 0xC

/*Selecting PLL Source Mask*/
# define PLL_M_MASK 0x3F
# define PLL_N_MASK 0x7FC0
# define PLL_P_MASK 0x30000
# define PLL_SRC_MASK 0x400000
# define PLL_Q_MASK 0xF000000

/*RCC_PLLCFGR_MASK*/

#define HSI_SW_MASK 0x0
#define HSE_SW_MASK 0x1
#define PLL_SW_MASK 0x2

/*RCC_CFGR_PRESCALAR_MASK*/

#define RCC_HPRE_MASK 0xF0
#define RCC_PPRE1_MASK 0x1C00
#define RCC_PPRE2_MASK 0xE000



/****************************************************************************************************************************/
                                           /*Register shifts*/
/****************************************************************************************************************************/                                           


/*Selecting prescalar shift*/

#define RCC_HPRE_SHIFT 4
#define RCC_PPRE1_SHIFT 10
#define RCC_PPRE2_SHIFT 13

/*configuring the PLL shift*/

#define RCC_PLLCFGR_PLLM_SHIFT 0
#define RCC_PLLCFGR_PLLN_SHIFT 6
#define RCC_PLLCFGR_PLLP_SHIFT 16
#define RCC_PLLCFGR_PLLSRC_SHIFT 22
#define RCC_PLLCFGR_PLLQ_SHIFT 24
/****************************************************************************************************************************/


/* RCC_CR Register Bits*/


#define RCC_CR_HSION    0
#define RCC_CR_HSIRDY   1
#define RCC_CR_HSITRIM  3
#define RCC_CR_HSICAL   8
#define RCC_CR_HSEON    16
#define RCC_CR_HSERDY   17
#define RCC_CR_HSEBYP   18
#define RCC_CR_CSSON    19
#define RCC_CR_PLLON    24
#define RCC_CR_PLLRDY   25
#define RCC_CR_PLLI2SON 26
#define RCC_CR_PLLI2SRDY 27
#define RCC_CR_PLLSAION 28
#define RCC_CR_PLLSAIRDY 29

/* RCC_PLLCFGR Register Bits*/
#define RCC_PLLCFGR_PLLM 0
#define RCC_PLLCFGR_PLLN 6
#define RCC_PLLCFGR_PLLP 16
#define RCC_PLLCFGR_PLLSRC 22
#define RCC_PLLCFGR_PLLQ 24
#define RCC_PLLCFGR_PLLR 28

/* RCC_CFGR Register Bits*/
#define RCC_CFGR_SW 0
#define RCC_CFGR_SWS 2
#define RCC_CFGR_HPRE 4
#define RCC_CFGR_PPRE1 10
#define RCC_CFGR_PPRE2 13
#define RCC_CFGR_RTCPRE 16
#define RCC_CFGR_MCO1 21
#define RCC_CFGR_I2SSRC 23
#define RCC_CFGR_MCO1PRE 24
#define RCC_CFGR_MCO2PRE 27
#define RCC_CFGR_MCO2 30

/* RCC_CFGR_MC02PRE Bits*/
#define RCC_CFGR_SW0 0
#define RCC_CFGR_SW1 1
#define RCC_CFGR_SW2 2




/* RCC_CIR Register Bits*/
#define RCC_CIR_LSIRDYF 0
#define RCC_CIR_LSERDYF 1
#define RCC_CIR_HSIRDYF 2
#define RCC_CIR_HSERDYF 3
#define RCC_CIR_PLLRDYF 4
#define RCC_CIR_PLLI2SRDYF 5
#define RCC_CIR_PLLSAIRDYF 6
#define RCC_CIR_CSSF 7
#define RCC_CIR_LSIRDYIE 8
#define RCC_CIR_LSERDYIE 9
#define RCC_CIR_HSIRDYIE 10
#define RCC_CIR_HSERDYIE 11
#define RCC_CIR_PLLRDYIE 12
#define RCC_CIR_PLLI2SRDYIE 13
#define RCC_CIR_PLLSAIRDYIE 14
#define RCC_CIR_LSIRDYC 16
#define RCC_CIR_LSERDYC 17
#define RCC_CIR_HSIRDYC 18
#define RCC_CIR_HSERDYC 19
#define RCC_CIR_PLLRDYC 20
#define RCC_CIR_PLLI2SRDYC 21
#define RCC_CIR_PLLSAIRDYC 22
#define RCC_CIR_CSSC 23

/**************************************************************************************/

#endif








