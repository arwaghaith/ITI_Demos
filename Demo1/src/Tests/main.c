#include "SYSTICK.h"
#include "SCHED.h"
#include "APP_INIT/APP_Init.h"


int main(void)
{

    
    APP_Init();
    SCHED_Init();
    SCHED_Start();
    

    

    return 0;
}