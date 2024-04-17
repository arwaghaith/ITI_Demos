
/***************************************including the necessary libraries******************************/

/*******************************************************************************************************/
#include  "../../LIB/STD_TYPES.h"
#include  "../../LIB/STD_MATH.h"
#include  "RCC.h"
#include "RCC_Private.h"


/*******************************************************************************************************/


/*this function  is  for controlling any clock in the system as ON or OFF*/
/* it takes two parameters
    * 1- clock_type: which is the clock that you want to control
    * 2- state: what is the state of the clock ON or OFF
    * it returns:
    * 1- RCC_OK: if the clock is controlled successfully
    * 2- RCC_NOK: if the clock is not controlled successfully
 */
RCC_ERROR_STATUS RCC_ControlClock(RCC_CLK_TYPE clock_type, RCC_STATE state)

{

    RCC_ERROR_STATUS loc_RCC_err_status = RCC_NOK;
    uint32_t loc_RCC_CR_counter = 0;

    uint32_t loc_RCC_CFGR_temp =(RCC_CFGR & RCC_CFGR_SWS_MASK)>>2;
    if(loc_RCC_CFGR_temp==clock_type)
    {
        loc_RCC_err_status = RCC_NOK;
    }
    else
    {
    switch (clock_type)
    {
        case RCC_HSI:
      


            switch (state)
            {
                case CLK_ON:
                    SET_BIT(RCC_CR, RCC_CR_HSION);
                    while(!GET_BIT(RCC_CR, RCC_CR_HSIRDY) && loc_RCC_CR_counter < 1000000)
            {
                loc_RCC_CR_counter++;
            }
            if (loc_RCC_CR_counter == 1000000)
            {
                loc_RCC_err_status = RCC_NOK;
            }
            else
            {
                loc_RCC_err_status = RCC_OK;
                loc_RCC_CR_counter = 0;
            }

                    break;
                case CLK_OFF:
                    CLR_BIT(RCC_CR, RCC_CR_HSION);
                    loc_RCC_err_status = RCC_OK;
                    break;
                default:
                    loc_RCC_err_status = RCC_NOK;
                    break;
            }
                
            break;
        case RCC_HSE:
       


            switch (state)
            {
                case CLK_ON:
                    SET_BIT(RCC_CR, RCC_CR_HSEON);

                    while(!GET_BIT(RCC_CR, RCC_CR_HSERDY) && loc_RCC_CR_counter < 1000000)
            {
                loc_RCC_CR_counter++;
            }
            if (loc_RCC_CR_counter == 1000000)
            {
                loc_RCC_err_status = RCC_NOK;
            }
            else
            {
                loc_RCC_err_status = RCC_OK;
                loc_RCC_CR_counter = 0;
            }
                    break;
                case CLK_OFF:
                    CLR_BIT(RCC_CR, RCC_CR_HSEON);
                    loc_RCC_err_status = RCC_OK;
                    break;
                default:
                    loc_RCC_err_status = RCC_NOK;
                    break;
            }
            
            break;
        case RCC_PLL:
      
        
            switch (state)
            {
                case CLK_ON:
                    SET_BIT(RCC_CR, RCC_CR_PLLON);

                     while(!GET_BIT(RCC_CR, RCC_CR_PLLRDY) && loc_RCC_CR_counter < 1000000)
            {
                loc_RCC_CR_counter++;
            }
            if (loc_RCC_CR_counter == 1000000)
            {
                loc_RCC_err_status = RCC_NOK;
            }
            else
            {
                loc_RCC_err_status = RCC_OK;
                loc_RCC_CR_counter = 0;
            }
                    break;
                case CLK_OFF:
                    CLR_BIT(RCC_CR, RCC_CR_PLLON);
                    loc_RCC_err_status = RCC_OK;
                    break;
                default:
                    loc_RCC_err_status = RCC_NOK;
                    break;
            }
        
            break;
            default:
                loc_RCC_err_status = RCC_NOK;
                break;
        
    }}

    return loc_RCC_err_status;

}

/*this function is for configuring the PLL clock*/
/* it takes four parameters
    * 1- PLL_M: the value of the PLL_M  "DIVISION FACTOR"
    * 2- PLL_N: the value of the PLL_N  "MULTIPLICATION FACTOR"
    * 3- PLL_P: the value of the PLL_P  "DIVISION FACTOR"
    * 4- PLL_Q: the value of the PLL_Q  "DIVISION FACTOR"
    * it returns:
    * 1- RCC_OK: if the PLL is configured successfully
    * 2- RCC_NOK: if the PLL is not configured successfully
 */

RCC_ERROR_STATUS RCC_ConfigurePLL(uint8_t PLL_M, uint16_t PLL_N, uint8_t PLL_P, uint8_t PLL_Q,uint32_t PLL_SRC)
{
     RCC_PLLCFGR =  0x24003010;

    uint32_t loc_RCC_PLL_CFGR_temp=RCC_PLLCFGR;
    if((PLL_M > 1) && (PLL_M < 64) && (PLL_N > 191) && (PLL_N < 433) && (PLL_P == 2 || PLL_P == 4 || PLL_P == 6 || PLL_P == 8) && (PLL_Q > 1) && (PLL_Q < 16))
    {
       

        loc_RCC_PLL_CFGR_temp= (loc_RCC_PLL_CFGR_temp &~(PLL_M_MASK)) | ((PLL_M) << (RCC_PLLCFGR_PLLM_SHIFT));
        loc_RCC_PLL_CFGR_temp= (loc_RCC_PLL_CFGR_temp &~(PLL_N_MASK)) | ((PLL_N) << (RCC_PLLCFGR_PLLN_SHIFT));
        loc_RCC_PLL_CFGR_temp= (loc_RCC_PLL_CFGR_temp &~(PLL_P_MASK)) | ((PLL_P) << (RCC_PLLCFGR_PLLP_SHIFT));
        loc_RCC_PLL_CFGR_temp= (loc_RCC_PLL_CFGR_temp &~(PLL_Q_MASK)) | ((PLL_Q) << (RCC_PLLCFGR_PLLQ_SHIFT));

        loc_RCC_PLL_CFGR_temp= (loc_RCC_PLL_CFGR_temp | PLL_SRC);
        RCC_PLLCFGR = loc_RCC_PLL_CFGR_temp;
    }
    else
    {
        return RCC_NOK;
    }



    return RCC_OK;
}




    



/*this function is for selecting the system clock*/
/* it takes one parameter
    * 1- clock_type: the clock that you want to select as a system clock
    * it returns:
    * 1- RCC_OK: if the clock is selected successfully
    * 2- RCC_NOK: if the clock is not selected successfully
 */

RCC_ERROR_STATUS RCC_SelectSysClk(RCC_CLK_TYPE clock_type)
{
    RCC_ERROR_STATUS loc_RCC_err_status = RCC_NOK;
    uint32_t loc_RCC_CFGR_temp = RCC_CFGR &~(RCC_CFGR_SW_MASK);
   

    switch (clock_type)

    {

            
            
        case RCC_HSI:
       if(GET_BIT(RCC_CR,RCC_CR_HSION) && GET_BIT(RCC_CR,RCC_CR_HSIRDY))
       {
           
            RCC_CFGR = loc_RCC_CFGR_temp | HSI_SW_MASK;
            loc_RCC_err_status=RCC_OK;
       }
       else
       {
            loc_RCC_err_status = RCC_NOK;
       }

            
            break;
        case RCC_HSE:
        if(GET_BIT(RCC_CR,RCC_CR_HSEON) && GET_BIT(RCC_CR,RCC_CR_HSERDY))
        {

        
            RCC_CFGR = loc_RCC_CFGR_temp | HSE_SW_MASK;
                  loc_RCC_err_status=RCC_OK;
       }
       else
       {
            loc_RCC_err_status = RCC_NOK;
       }
            
            break;
        case RCC_PLL:
        if (GET_BIT(RCC_CR,RCC_CR_PLLON)&& GET_BIT(RCC_CR,RCC_CR_PLLRDY))
        {
                        RCC_CFGR = loc_RCC_CFGR_temp | PLL_SW_MASK;


            RCC_CFGR = loc_RCC_CFGR_temp | HSE_SW_MASK;
                  loc_RCC_err_status=RCC_OK;
       }
       else
       {
            loc_RCC_err_status = RCC_NOK;
       }
           
            break;
        default:
            loc_RCC_err_status = RCC_NOK;
            break;
    }
    return loc_RCC_err_status;


}

/*this function is for controlling the clock of any peripheral in the system */
/* it takes two parameters
    * 1- peripheral: the peripheral that you want to control its clock
    * 2- state: what is the state of the peripheral clock ON or OFF
    * it returns:
    * 1- RCC_OK: if the peripheral clock is controlled successfully
    * 2- RCC_NOK: if the peripheral clock is not controlled successfully
 */

RCC_ERROR_STATUS RCC_ControlPeripheralClock(RCC_PERIPHERAL_BUS_TYPE RCC_bus,uint8_t peripheral, RCC_STATE state)
{
    RCC_ERROR_STATUS loc_RCC_err_status = RCC_NOK;

    switch (RCC_bus)
    {
        case RCC_AHB1:
            if (state == CLK_ON)
            {
                SET_BIT(RCC_AHB1ENR, peripheral);
                loc_RCC_err_status = RCC_OK;
            }
            else if (state == CLK_OFF)
            {
                CLR_BIT(RCC_AHB1ENR, peripheral);
                loc_RCC_err_status = RCC_OK;
            }
            else
            {
                loc_RCC_err_status = RCC_NOK;
            }
            break;
        case RCC_AHB2:
            if (state == CLK_ON)
            {
                SET_BIT(RCC_AHB2ENR, peripheral);
                loc_RCC_err_status = RCC_OK;
            }
            else if (state == CLK_OFF)
            {
                CLR_BIT(RCC_AHB2ENR, peripheral);
                loc_RCC_err_status = RCC_OK;
            }
            else
            {
                loc_RCC_err_status = RCC_NOK;
            }
            break;
            case RCC_APB1:
            if (state == CLK_ON)
            {
                SET_BIT(RCC_APB1ENR, peripheral);
                loc_RCC_err_status = RCC_OK;
            }
            else if (state == CLK_OFF)
            {
                CLR_BIT(RCC_APB1ENR, peripheral);
                loc_RCC_err_status = RCC_OK;
            }
            else
            {
                loc_RCC_err_status = RCC_NOK;
            }
            break;
            case RCC_APB2:
            if (state == CLK_ON)
            {
                SET_BIT(RCC_APB2ENR, peripheral);
                loc_RCC_err_status = RCC_OK;
            }
            else if (state == CLK_OFF)
            {
                CLR_BIT(RCC_APB2ENR, peripheral);
                loc_RCC_err_status = RCC_OK;
            }
            else
            {
                loc_RCC_err_status = RCC_NOK;
            }
            break;
            default:
                loc_RCC_err_status = RCC_NOK;
                break;

    }
    return loc_RCC_err_status;
                

        


}



/*This function is for configuring any  prescalar in the system*/

/* it takes two parameters
    * 1- peripheral: the peripheral that you want to control its clock
    * 2- prescalar: the value of the prescalar
    * it returns:
    * 1- RCC_OK: if the prescalar is configured successfully
    * 2- RCC_NOK: if the prescalar is not configured successfully
 */

RCC_ERROR_STATUS RCC_ConfigurePrescalar(RCC_PERIPHERAL_BUS_TYPE_prescalar RCC_BUS, RCC_PRECALAR prescalar)
{
    RCC_ERROR_STATUS loc_RCC_err_status = RCC_NOK;
    uint32_t loc_RCC_CFGR_temp = RCC_CFGR;
    switch( RCC_BUS)
    {
        case RCC_AHB_SCALER:
            loc_RCC_CFGR_temp&=~(RCC_HPRE_MASK);
            loc_RCC_CFGR_temp |= (prescalar & RCC_HPRE_MASK);
            RCC_CFGR = loc_RCC_CFGR_temp;
            loc_RCC_err_status = RCC_OK;
            break;
        case RCC_APB1_SCALER:
            loc_RCC_CFGR_temp&=~(RCC_PPRE1_MASK);
            loc_RCC_CFGR_temp |= (prescalar & RCC_PPRE1_MASK);
            RCC_CFGR = loc_RCC_CFGR_temp;
            loc_RCC_err_status = RCC_OK;
            break;
        case RCC_APB2_SCALER:
            loc_RCC_CFGR_temp&=~(RCC_PPRE2_MASK);
            loc_RCC_CFGR_temp |= (prescalar & RCC_PPRE2_MASK);
            RCC_CFGR = loc_RCC_CFGR_temp;
            loc_RCC_err_status = RCC_OK;
            
            break;
        default:
            loc_RCC_err_status = RCC_NOK;
            break;

    }
    return loc_RCC_err_status;
        
            


}
