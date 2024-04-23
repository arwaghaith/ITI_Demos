#include "../../LIB/STD_TYPES.h"
#include "NVIC_private.h"
#include "NVIC.h"





#define NVIC_PRIORITY_GROUP_SUB PRIORITY_GROUP_3_SUB_1

typedef struct {
    volatile uint32_t ISER[8];               /* NVIC Interrupt Set Enable Register */
    uint32_t RESERVED0[24];                  /* Reserved */
    volatile uint32_t ICER[8];               /* NVIC Interrupt Clear Enable Register */
    uint32_t RESERVED1[24];                  /* Reserved */
    volatile uint32_t ISPR[8];               /* NVIC Interrupt Set Pending Register */
    uint32_t RESERVED2[24];                  /* Reserved */
    volatile uint32_t ICPR[8];               /* NVIC Interrupt Clear Pending Register */
    uint32_t RESERVED3[24];                  /* Reserved */
    volatile uint32_t IABR[8];               /* NVIC Interrupt Active Bit Register */
    uint32_t RESERVED4[56];                  /* Reserved */
    volatile uint8_t IPR[240];               /* NVIC Interrupt Priority Register */
    uint32_t RESERVED5[580];                 /* Reserved */
    volatile uint32_t STIR;                  /* NVIC Software Trigger Interrupt Register */
} NVIC_Registers;

static NVIC_Registers * const NVIC = (NVIC_Registers *)NVIC_BASE_ADDRESS;
static const uint32_t NVIC_PRIORITY_GROUP_VALUES[] = {
    SCB_AIRCR_PRIORITY_GROUP_4_SUB_0,
    SCB_AIRCR_PRIORITY_GROUP_3_SUB_1,
    SCB_AIRCR_PRIORITY_GROUP_2_SUB_2,
    SCB_AIRCR_PRIORITY_GROUP_1_SUB_3,
    SCB_AIRCR_PRIORITY_GROUP_0_SUB_4

   
};

static const uint8_t NVIC_PREEMPTION_PRIORITY_MASKS[] = {
    0x0F,
    0x1F,
    0x3F,
    0x7F,
    0xFF
};

static const uint8_t NVIC_SUB_PRIORITY_MASKS[] = {
    0xFF,
    0xEF,
    0xCF,
    0x8F,
    0x0F
};

void NVIC_INIT() {

   volatile uint32_t loc_SCB_AIRCR = SCB_AIRCR_VECTKEY_MASK & SCB_AIRCR;
    loc_SCB_AIRCR = loc_SCB_AIRCR | SCB_AIRCR_VECTKEY_WRITE;
        loc_SCB_AIRCR = loc_SCB_AIRCR & ~(SCB_AIRCR_PRIGROUP_MASK);
    loc_SCB_AIRCR = loc_SCB_AIRCR | NVIC_PRIORITY_GROUP_VALUES[NVIC_PRIORITY_GROUP_SUB];
    SCB_AIRCR = loc_SCB_AIRCR;
}

NVIC_Status NVIC_EnableInterrupt(NVIC_InterruptType interrupt) {

    NVIC_Status loc_NVIC_Enable_status=NVIC_NOK;
    if(interrupt < 0 || interrupt > 240)
     
       loc_NVIC_Enable_status=NVIC_NOK;
       else{

    NVIC->ISER[interrupt / 32] = 1 << (interrupt % 32);
           loc_NVIC_Enable_status=NVIC_OK;

       }
       return loc_NVIC_Enable_status;

       
}

NVIC_Status NVIC_DisableInterrupt(NVIC_InterruptType interrupt) {

    NVIC_Status loc_NVIC_Disable_status=NVIC_NOK;


    if(interrupt < 0 || interrupt > 240)
        
        loc_NVIC_Disable_status=NVIC_NOK;
        else{

    NVIC->ICER[interrupt / 32] = 1 << (interrupt % 32);
        loc_NVIC_Disable_status=NVIC_OK;
        }
        return loc_NVIC_Disable_status;
}

NVIC_Status NVIC_SetPendingFlag(NVIC_InterruptType interrupt) {
    NVIC_Status loc_NVIC_SetPending_status=NVIC_NOK;
    if(interrupt < 0 || interrupt > 240)
            
            loc_NVIC_SetPending_status=NVIC_NOK;
            else{

    

    NVIC->ISPR[interrupt / 32] = 1 << (interrupt % 32);
    loc_NVIC_SetPending_status=NVIC_OK;
            }
            return loc_NVIC_SetPending_status;
}

NVIC_Status NVIC_ClearPendingInterrupt(NVIC_InterruptType interrupt) {
    NVIC_Status loc_NVIC_ClearPending_status=NVIC_NOK;
    if(interrupt < 0 || interrupt > 240)

        loc_NVIC_ClearPending_status=NVIC_NOK;
        else{
    NVIC->ICPR[interrupt / 32] = 1 << (interrupt % 32);
    loc_NVIC_ClearPending_status=NVIC_OK;
        }
        return loc_NVIC_ClearPending_status;
}

NVIC_Status NVIC_GetActiveInterrupt(NVIC_InterruptType interrupt, NVIC_ActiveType *active) {

    NVIC_Status loc_NVIC_GetActive_status=NVIC_NOK;
    if(interrupt < 0 || interrupt > 240)
        loc_NVIC_GetActive_status=NVIC_NOK;
        else{
    *active = (NVIC->IABR[interrupt / 32] >> (interrupt % 32)) & 1;
    loc_NVIC_GetActive_status=NVIC_OK;
        }
        return loc_NVIC_GetActive_status;
}

NVIC_Status NVIC_SetPremptionPriority(NVIC_InterruptType interrupt, uint8_t priority) {

    NVIC_Status loc_NVIC_SetPremption_status=NVIC_NOK;
    if(interrupt < 0 || interrupt > 240 || priority >= (1 << (Priority_Bits - NVIC_PRIORITY_GROUP_SUB)))

        loc_NVIC_SetPremption_status=NVIC_NOK;
        else{
    NVIC->IPR[interrupt] = (NVIC->IPR[interrupt] & NVIC_PREEMPTION_PRIORITY_MASKS[NVIC_PRIORITY_GROUP_SUB]) | (priority << (Priority_Bits + NVIC_PRIORITY_GROUP_SUB));
    loc_NVIC_SetPremption_status=NVIC_OK;
        }
        return loc_NVIC_SetPremption_status;
}

NVIC_Status NVIC_SetSubPriority(NVIC_InterruptType interrupt, uint8_t priority) {
    NVIC_Status loc_NVIC_SetSub_status=NVIC_NOK;
    if(interrupt < 0 || interrupt > 240 || priority >= (1 << NVIC_PRIORITY_GROUP_SUB))

        loc_NVIC_SetSub_status=NVIC_NOK;
        else{
    NVIC->IPR[interrupt] = (NVIC->IPR[interrupt] & NVIC_SUB_PRIORITY_MASKS[NVIC_PRIORITY_GROUP_SUB]) | (priority << (Priority_Bits));
    loc_NVIC_SetSub_status=NVIC_OK;
        }
        return loc_NVIC_SetSub_status;
}

NVIC_Status NVIC_GetInterruptPriority(NVIC_InterruptType interrupt, uint8_t *priority) {

    NVIC_Status loc_NVIC_GetInterrupt_status=NVIC_NOK;
    if(interrupt < 0 || interrupt > 240)
        loc_NVIC_GetInterrupt_status=NVIC_NOK;
        else{
    *priority = (NVIC->IPR[interrupt] >> Priority_Bits);
    loc_NVIC_GetInterrupt_status=NVIC_OK;
        }
        return loc_NVIC_GetInterrupt_status;
}

NVIC_Status NVIC_SetPriority(NVIC_InterruptType interrupt, uint8_t preemption, uint8_t sub) {

    NVIC_Status status = NVIC_SetPremptionPriority(interrupt, preemption);
    if(status == NVIC_OK)
        status = NVIC_SetSubPriority(interrupt, sub);
    return status;
}

NVIC_Status NVIC_SystemReset(NVIC_InterruptType interrupt) {

    NVIC_Status loc_NVIC_SystemReset_status=NVIC_NOK;
    if(interrupt < 0 || interrupt > 240)
        loc_NVIC_SystemReset_status=NVIC_NOK;
        else{
    NVIC->STIR = interrupt;
    loc_NVIC_SystemReset_status=NVIC_OK;
        }
        return loc_NVIC_SystemReset_status;
}
