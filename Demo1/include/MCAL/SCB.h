#include "Typedefs.h"

#define SCB_BASEADD   ((volatile uint32_t *const)0xE000ED0C)
#define SCB_Ptr_type   volatile SCB_resgisters_t *const

typedef volatile unsigned int vuint32_t;


typedef struct 
{
    vuint32_t SCB_ACTLR;
    vuint32_t reserved[829];
    vuint32_t SCB_CPUID;
    vuint32_t SCB_ICSR;
    vuint32_t SCB_VTOR;
    vuint32_t SCB_AIRCR;
    vuint32_t SCB_SCR;
    vuint32_t SCB_CCR;
    vuint32_t SCB_SHPR1;
    vuint32_t SCB_SHPR2;
    vuint32_t SCB_SHPR3;
    vuint32_t SCB_SHCSR;
    vuint32_t SCB_CFSR;/*SCB_MMSR,SCB_BFSR,SCB_UFSR*/
    vuint32_t SCB_HFSR;
    vuint32_t reserved1;
    vuint32_t SCB_MMAR;
    vuint32_t SCB_BFAR;
    vuint32_t SCB_AFSR;

}SCB_resgisters_t;

 SCB_Ptr_type SCB_REG_Ptr = (volatile SCB_resgisters_t *const)SCB_BASEADD;