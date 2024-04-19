#include "RCC.h"
#include "Display.h"
#include "SCHED.h"
#include "NVIC.h"
#include "APP_READSWITCH.h"
#include "APP_UPDATESWITCH.h"

int main_XX(int argc, char* argv[])
{
    RCC_AHB1DisablePeri(PERI_AHB1_GPIOA);
    RCC_AHB1DisablePeri(PERI_AHB1_GPIOB);
    RCC_APB2DisablePeri(PERI_APB2_USART1);
    RCC_APB1DisablePeri(PERI_APB1_USART2);
    NVIC_EnableIRQ(NVIC_USART1);

    Display_Init();
    SCHED_Init();
    SCHED_Start();

    return 0;
}