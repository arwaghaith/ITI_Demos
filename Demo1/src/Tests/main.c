#include "RCC.h"
#include "Display.h"
#include "SCHED.h"

int main(int argc, char* argv[])
{
    RCC_AHB1DisablePeri(PERI_AHB1_GPIOA);
    RCC_AHB1DisablePeri(PERI_AHB1_GPIOB);
    Display_Init();
    SCHED_Init();
    SCHED_Start();

    return 0;
}