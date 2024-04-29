
#include "../../LIB/STD_TYPES.h"
#include "UART.h"
#include "UART_private.h"





volatile  USART_t * G_USART[MAX_SIZE]=

{
    (volatile USART_t *)USART1,
    (volatile USART_t *)USART2,
    (volatile USART_t *)USART6

};

volatile static  uint32_t USART_T_FREQ[MAX_SIZE]={

    16000000,
    16000000,
    16000000
};
    

static TX_t G_TX[MAX_SIZE]=

{
   { 
    {
        NULL,
        0,
        0,

    },
    READY,
    NULL,
   },
    { 
    {
        NULL,
        0,
        0,

    },
    READY,
    NULL,
   },
    { 
    {
        NULL,
        0,
        0,

    },
    READY,
    NULL,
   }


};

static RX_t G_RX[MAX_SIZE]=

{
    
    { 
    {
        NULL,
        0,
        0,

    },
    READY,
    NULL,
   }, 
   { 
    {
        NULL,
        0,
        0,

    },
    READY,
    NULL,
   },
    { 
    {
        NULL,
        0,
        0,

    },
    READY,
    NULL,
   }

}; 


USART_enu_STATE UART_INIT(USART_CFG*CFG)
{


    USART_enu_STATE Local_Status = USART_NOK;
    volatile uint32_t Local_CR1 = 0;
    volatile uint32_t Local_CR2 = 0;
    volatile uint32_t Local_BRR = 0;

    volatile uf32_t USARTDIV=0;

    uint16_t Baud_rate_mantissa=0;
    uf32_t Baud_rate_fraction=0;

    if(CFG)
    {
    uint8_t loc_uart_channel=CFG->channel;


        if(loc_uart_channel>=USART1_CH  &&  loc_uart_channel<=USART6_CH )
        {
            Local_Status=USART_OK;

        }

    if(Local_Status == USART_OK)
    {


       


        Local_CR1 = (G_USART[loc_uart_channel])->CR1;
        Local_CR2 = (G_USART[loc_uart_channel])->CR2;
        Local_BRR = (G_USART[loc_uart_channel])->BRR;

        /* Calculating The Baud Rate */

        USARTDIV=(USART_T_FREQ[loc_uart_channel])/(8*CFG->BaudRate*(2-((CFG->OVERSAMPLING)>0)));

        Baud_rate_mantissa = (uint16_t)(USARTDIV);
        Baud_rate_fraction = (USARTDIV- Baud_rate_mantissa) *( 8*(1+((CFG->OVERSAMPLING)<1)));
        Baud_rate_fraction=((Baud_rate_fraction>((uint32_t)Baud_rate_fraction))?Baud_rate_fraction+1:Baud_rate_fraction);
        if(Baud_rate_fraction>( 8*(1+((CFG->OVERSAMPLING)>0))-1))
        {
            Baud_rate_mantissa+=1;
            Baud_rate_fraction=0;
        }
        else
        {

        }




    


        if(CFG->OVERSAMPLING==OVERSAMPLING_8 ||CFG->OVERSAMPLING==OVERSAMPLING_16)
        {
        Local_CR1 &= OVERSAMPLING_MASK;
        Local_CR1 |= CFG->OVERSAMPLING;
        }

        else
        {

        }

        if (CFG->USART_EN ==USART_ENABLE  ||CFG->USART_EN == USART_DISABLE)

        {


        Local_CR1 &= USART_EN_MASK;
        Local_CR1 |= CFG->USART_EN;

        }

        else
        {

        }

        if( CFG->Word_length== WORD_LENGTH_8 ||CFG->Word_length==WORD_LENGTH_9)
        {

        Local_CR1 &= WORD_LENGTH_MASK;
        Local_CR1 |= CFG->Word_length;

        }

        else
        {

        }

        // if(CFG->Wakeup_method==WAKEUP_IDLE_LINE ||CFG->Wakeup_method==WAKEUP_ADDRESS)
        // {

        // Local_CR1 &= PARITY_CTRL_EN_MASK;
        // Local_CR1 |= CFG->Parity_control;

        // }

        // else
        // {

        // }

        if(CFG->Parity_selection==PARITY_EVEN ||CFG->Parity_selection==PARITY_ODD)
        {

        Local_CR1 &= PARITY_SELEC_METHOD;
        Local_CR1 |= CFG->Parity_selection;

        }

        else
        {

        }

        /* set The number of stop bits  */

         

         if(CFG->Stop_Bits==STOP_BITS_1 ||CFG->Stop_Bits==STOP_BITS_0_5|| CFG->Stop_Bits==STOP_BITS_2 || CFG->Stop_Bits==STOP_BITS_1_5)

         {

        Local_CR2&= STOP_BITS_MASK;
        Local_CR2|=CFG->Stop_Bits;
         }

         else

        {
    
        }
       

        /* set CLK_EN  */

        if(CFG->CLK_EN ==CLK_DISABLE ||CFG->CLK_EN==CLK_ENABLE)
        // {

        // Local_CR2&= CLK_EN_MASK;
        // Local_CR2|=CFG->CLK_EN;
        // }

        // else
        // {

        // }

        // /* set CLK_POL  */

        // if(CFG->CLK_POL==CLK_POL_LOW ||CFG->CLK_POL==CLK_POL_HIGH)

        // {
        // Local_CR2&= CLK_POL_MASK;
        // Local_CR2|=CFG->CLK_POL;
        // }
        // else
        // {


        // }

        // /* set CLK_PHASE  */




        // if(CFG->CLK_PH==CLK_PHASE_FIRST ||CFG->CLK_PH==CLK_PHASE_SECOND)
        // {

        // Local_CR2&= CLK_PH_MASK;
        // Local_CR2|=CFG->CLK_PH;

        // }

        // else
        // {

        // }

        /* set Baud Rate  */

    
        Local_BRR&=Baud_Rate_Mask;
        Local_BRR|=(Baud_rate_mantissa<<4);
        Local_BRR|=(uint16_t)Baud_rate_fraction;

        /*  enabling  TE */

        Local_CR1  &=TE_MASK;

        Local_CR1 |=TE;

        /*  enabling  RE */


        Local_CR1  &=RE_MASK;
        Local_CR1|=RE;


      



    (G_USART[loc_uart_channel])->CR1 = Local_CR1;
    (G_USART[loc_uart_channel])->CR2 = Local_CR2;
    (G_USART[loc_uart_channel])->BRR = Local_BRR;





    }
    }

    return Local_Status;
}

USART_enu_STATE UART_SendBuffer(uint8_t USART_channel,uint8_t Buffer,uint16_t length,TXCB UART_CB)
{



       volatile uint32_t TimeOut=60000;
       volatile uint32_t loc_Iterator=0;
        volatile USART_enu_STATE loc_USART_State=USART_NOK;

        if ( USART_channel>= USART1_CH && USART_channel<=USART6_CH)
        {
     loc_USART_State=USART_OK;

        
        if(loc_USART_State==USART_OK)
        {
            for(uint16_t i=0;i<length;i++)
            {
                G_USART[USART_channel]->DR=Buffer;
                while((loc_Iterator<TimeOut ))
                {

                    loc_Iterator++;
                }

                    if(loc_Iterator<TimeOut)
                    {
            
                loc_USART_State=USART_OK;
                    }

                    else
                    {
                        loc_USART_State=USART_NOK;

                        break;
                    }

loc_Iterator=0;
                
            }
        }

        
          if(UART_CB!=NULL  &&loc_USART_State==USART_OK)
                   UART_CB();

            

            else
            {
                loc_USART_State=USART_NOK;
            }
        }

        else

        {

            loc_USART_State=USART_NOK;
        }

        return loc_USART_State;
        


}
USART_enu_STATE UART_RecBuffer(uint8_t USART_channel,uint16_t*buffer,uint16_t length,RXCB UART_CB )


{

        uint32_t TimeOut=10000;
        uint32_t loc_Iterator=0;
        USART_enu_STATE loc_USART_State=USART_NOK;
        if ( USART_channel>= USART1_CH && USART_channel<=USART6_CH)
        {
     loc_USART_State=USART_OK;

        
        if(buffer!=NULL  && loc_USART_State==USART_OK)
        {
            for(uint16_t i=0;i<length;i++)
            {
                buffer[i]= G_USART[USART_channel]->DR;
                while((!(((G_USART[USART_channel]->SR)) & RXNE_FLAG))  &&(loc_Iterator<TimeOut ))
                {

                    loc_Iterator++;
                }

                    if(loc_Iterator<TimeOut)
                    {
                        
                        loc_USART_State=USART_OK;

                    }

                    else
                    {
                        loc_USART_State=USART_NOK;
                    }

                    if(loc_USART_State==USART_OK)
                    {
                        if(UART_CB!=NULL)
                        {
                            UART_CB();
                        }
                    }

                    else
                    {
                    }

            }
        }
        }
            return loc_USART_State;
                    
               



}

USART_enu_STATE UART_SendBuffer_Async(uint8_t USART_channel,uint16_t*Buffer,uint16_t length,TXCB UART_CB)

{

    USART_enu_STATE loc_USART_State=USART_NOK;

    if(Buffer!=NULL)
    {
        loc_USART_State=USART_OK;
        G_TX[USART_channel].Buffer.data=Buffer;
        G_TX[USART_channel].Buffer.length=length;
        G_TX[USART_channel].Buffer.pos=0;
        G_TX[USART_channel].TX_CB=UART_CB;
        G_USART[USART_channel]->DR=Buffer[G_TX[USART_channel].Buffer.pos];
        G_TX[USART_channel].Buffer.pos++;
        G_TX[USART_channel].state=BUSY;
    }

    else

    {
    }


    /* Enabling The TE  Interrupt  */
    /***************************************************************************/
    G_USART[USART_channel]->CR1 &= TEXIE_MASK;
    G_USART[USART_channel]->CR1 |= TEXIE;

    /***************************************************************************/



    return loc_USART_State;

   

    
}

USART_enu_STATE UART_RXBufferAsync(uint8_t USART_channel,uint8_t*buffer,uint16_t length,RXCB UART_CB )
{


    USART_enu_STATE loc_USART_State=USART_NOK;
    
    if(buffer!=NULL)
    {
        loc_USART_State=USART_OK;
        G_RX[USART_channel].Buffer.data=buffer;
        G_RX[USART_channel].Buffer.length=length;
        G_RX[USART_channel].Buffer.pos=0;
        G_RX[USART_channel].RX_CB=UART_CB;
        G_RX[USART_channel].state=BUSY;
    }

    else

    {
    }

    
    /* Enabling The RXE  Interrupt  */
    /***************************************************************************/
    G_USART[USART_channel]->CR1 &= RXNEIE_MASK;
    G_USART[USART_channel]->CR1 |= RXNEIE;

    /***************************************************************************/


    return loc_USART_State;

   

}


void USART1_IRQHandler(void)
{

    if (G_USART[USART1_CH]->CR1 & TXE_FLAG)
    {

        if(G_TX[USART1_CH].Buffer.pos<G_TX[USART1_CH].Buffer.length)
        {
            G_USART[USART1_CH]->DR=G_TX[USART1_CH].Buffer.data[G_TX[USART1_CH].Buffer.pos];
            G_TX[USART1_CH].Buffer.pos++;
        }

                if(G_TX[USART1_CH].Buffer.pos==G_TX[USART1_CH].Buffer.length)

        {
            G_TX[USART1_CH].state=READY;
            G_TX[USART1_CH].Buffer.pos=0;
             G_USART[USART1_CH]->CR1 &= ~TXE_FLAG;


            //G_TX[USART1_CH].TX_CB();
        }
       
    }

    if (G_USART[USART1_CH]->CR1 & RXNE_FLAG)
    {

        if(G_RX[USART1_CH].Buffer.pos<G_RX[USART1_CH].Buffer.length)
        {
            G_RX[USART1_CH].Buffer.data[G_RX[USART1_CH].Buffer.pos]=G_USART[USART1_CH]->DR;
            G_RX[USART1_CH].Buffer.pos++;
        }

    if(G_RX[USART1_CH].Buffer.pos==G_RX[USART1_CH].Buffer.length)

        {
            G_RX[USART1_CH].state=READY;
            G_RX[USART1_CH].Buffer.pos=0;
            G_USART[USART1_CH]->CR1 &= ~RXNE_FLAG;

            //G_RX[USART1_CH].RX_CB();

        }
       
    }
}


void USART2_IRQHandler(void)
{
   
    if (G_USART[USART2_CH]->CR1 & TXE_FLAG)
    {

        if(G_TX[USART2_CH].Buffer.pos<G_TX[USART2_CH].Buffer.length)
        {
           G_USART[USART2_CH]->DR=G_TX[USART2_CH].Buffer.data[G_TX[USART2_CH].Buffer.pos];
            G_TX[USART2_CH].Buffer.pos++;
        }

        else
        {
            G_TX[USART2_CH].state=READY;
            G_TX[USART2_CH].Buffer.pos=0;
            G_TX[USART2_CH].TX_CB();
        }
       
    }

    if (G_USART[USART2_CH]->CR1 & RXNE_FLAG)
    {

        if(G_RX[USART2_CH].Buffer.pos<G_RX[USART2_CH].Buffer.length)
        {
            G_RX[USART2_CH].Buffer.data[G_RX[USART2_CH].Buffer.pos]=G_USART[USART2_CH]->DR;
            G_RX[USART2_CH].Buffer.pos++;
        }

        else
        {
            G_RX[USART2_CH].state=READY;
            G_RX[USART2_CH].Buffer.pos=0;
            G_RX[USART2_CH].RX_CB();
        }
       
    }
}



void USART6_IRQHandler(void)
{
    
    if (G_USART[USART6_CH]->CR1 & TXE_FLAG)
    {

        if(G_TX[USART6_CH].Buffer.pos<G_TX[USART6_CH].Buffer.length)
        {
            G_USART[USART6_CH]->DR=G_TX[USART6_CH].Buffer.data[G_TX[USART6_CH].Buffer.pos];
            G_TX[USART6_CH].Buffer.pos++;
        }

        else
        {
            G_TX[USART6_CH].state=READY;
            G_TX[USART6_CH].Buffer.pos=0;
            G_TX[USART6_CH].TX_CB();
        }
       
    }

    if (G_USART[USART6_CH]->CR1 & RXNE_FLAG)
    {

        if(G_RX[USART6_CH].Buffer.pos<G_RX[USART6_CH].Buffer.length)
        {
            G_RX[USART6_CH].Buffer.data[G_RX[USART6_CH].Buffer.pos]=G_USART[USART6_CH]->DR;
            G_RX[USART6_CH].Buffer.pos++;
        }

        else
        {
            G_RX[USART6_CH].state=READY;
            G_RX[USART6_CH].Buffer.pos=0;
            G_RX[USART6_CH].RX_CB();
        }
       
    }
}





