#ifndef NVIC_H
#define NVIC_H

#include "NVIC_private.h"
#include "../../LIB/STD_TYPES.h"

typedef enum
{
    NVIC_OK = 0,
    NVIC_NOK = 1
}NVIC_Status;

typedef enum 

{

    INTERRUPT_NOT_ACTIVE = 0,
    INTERRUPT_ACTIVE = 1

}NVIC_ActiveType;




/*****************************************  NVIC prototypes **********************************************/

/***********************************************************************************************************/
    void NVIC_INIT();

 /* @brief  Enable interrupt
 * @param  interrupt: interrupt number
 * @retval NVIC_Status
 * @note   none
 */
/***********************************************************************************************************/

NVIC_Status NVIC_EnableInterrupt(NVIC_InterruptType interrupt);
/***********************************************************************************************************/
/* @brief  Disable interrupt
 * @param  interrupt: interrupt number
 * @retval NVIC_Status
 * @note   none
 */
/***********************************************************************************************************/
NVIC_Status NVIC_DisableInterrupt(NVIC_InterruptType interrupt);

/***********************************************************************************************************/
/* @brief  Set pending flag
 * @param  interrupt: interrupt number
 * @retval NVIC_Status
 * @note   none
 */
/***********************************************************************************************************/
NVIC_Status NVIC_SetPendingFlag(NVIC_InterruptType interrupt);

/***********************************************************************************************************/

/* @brief  Clear pending flag
 * @param  interrupt: interrupt number
 * @retval NVIC_Status
 * @note   none
 */
/***********************************************************************************************************/
NVIC_Status NVIC_ClearPendingFlag(NVIC_InterruptType interrupt);
/***********************************************************************************************************/
/* @brief  Get active flag
 * @param  interrupt: interrupt number
* @param  active: active flag
 * @retval NVIC_Status
 * @note   none
 */
NVIC_Status NVIC_GetActiveFlag(NVIC_InterruptType interrupt, NVIC_ActiveType *active);


/***********************************************************************************************************/
/* @brief  Reset system
 * @param  none
 * @retval NVIC_Status
 * @note   none
 */

NVIC_Status NVIC_SetPremptionPriority(NVIC_InterruptType interrupt, uint8_t priority);
/***********************************************************************************************************/

/* @brief  Set sub priority
 * @param  interrupt: interrupt number
 * @param  priority: priority
 * @retval NVIC_Status
 * @note   none
 */

NVIC_Status NVIC_SetSubPriority(NVIC_InterruptType interrupt, uint8_t priority);
/***********************************************************************************************************/




/* @brief Set priority
 * @param  interrupt: interrupt number
 * @param  preemption: preemption
 * @param  sub: sub
 * @retval NVIC_Status
 * @note   none
 */
NVIC_Status NVIC_SetPriority(NVIC_InterruptType interrupt, uint8_t preemption, uint8_t sub);
/***********************************************************************************************************/
NVIC_Status NVIC_SystemReset(NVIC_InterruptType interrupt);
/***********************************************************************************************************/




    


#endif // NVIC_H
