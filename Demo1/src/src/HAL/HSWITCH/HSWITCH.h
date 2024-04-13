#ifndef  HSWITCH_H
#define  HSWITCH_H

#include  "../../LIB/STD_TYPES.h"
#include "HSWITCH_cfg.h"
#define SWITCH_STABLE_STATE  5


typedef enum
{
    SWITCH_NOK,
    SWITCH_OK
}Switch_ErrorStatus;


/*               Switch Functions                */
/*               Switch_Init                */
/*Description: This Function is used to initialize the switch
 * Input: void
 * Output: ErrorStatus
 */
Switch_ErrorStatus Switch_Init(void);

/*               Switch_SetState                */
/*Description: This Function is used to set the state of the switch
 * Input: Channel, State
 * Output: ErrorStatus
 */


/*               Switch_GetState                */
/*Description: This Function is used to get the state of the switch
 * Input: Channel, State
 * Output: ErrorStatus
 */
void Switch_GetInstant(void);
Switch_ErrorStatus Switch_GetState(Switch_ChannelType Channel, uint32_t *State);


#endif