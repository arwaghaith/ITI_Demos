

#include  "../../LIB/STD_TYPES.h"
#include  "../../MCAL/STK/STK.h"
#include "Sched.h"
#include "Sched_Runnables.h"

extern const Runnables_t sys_Runnables[MAX_RUNNABLES];
static volatile uint32_t pendingTicks = 0;
#define SCHED_TICK_MS 5


void Sched_Init()

{

    STK_Init(STK_AHB_DIVIDED_BY_8,STK_PERIOD_INTERVAL,0,Tick_cb);
    STK_SetTimeMS(SCHED_TICK_MS);
    

}

void Sched_Start()

{
    STK_Start();
    while(1)
    {
        if(pendingTicks )
        {
            pendingTicks--;
            Sched();
        }
    }

}

static void Sched()

{
    uint32_t idx;
    static uint32_t TIMESTAMP=0;

    for(idx = 0; idx < MAX_RUNNABLES; idx++)
    {
        if(sys_Runnables[idx].CB != NULL && TIMESTAMP % sys_Runnables[idx].periodicity_ms == 0)
        {
            sys_Runnables[idx].CB();
        }

    }
                TIMESTAMP+=SCHED_TICK_MS;

        

}

static void Tick_cb()

{
    pendingTicks++;


}