#include "pic16bits.h"
#include "ecan.h"
#include "dma.h"
#include "easy_can1.h"
#include "easy_can1.config.h"

#define ECAN_MSG_BUF_LENGTH 32
#define ECAN_IDX 1

static ECAN_MSG ecan1_msg_buf[ECAN_MSG_BUF_LENGTH] __attribute__((space(dma), aligned(ECAN_MSG_BUF_LENGTH*sizeof(ECAN_MSG))));

void conf_transceiver(unsigned char enable_pin, unsigned char en){
    TRISD &= ~(1 << enable_pin);
    PORTD ^= (-en ^ PORTF) & (1 << enable_pin);
}

void easy_can1_init_remap(unsigned int speed_ratio, unsigned char tx_pin,
        unsigned char rx_pin,unsigned char enable_pin, unsigned char en)
{
        conf_transceiver(enable_pin, en);
    easy_can1_fundamental(speed_ratio);

    #if defined(__dsPIC33FJ128GP802__)


    __builtin_write_OSCCONL(OSCCON & ~(1 << 6));

  
            RPINR26bits.C1RXR = rx_pin;
            ((unsigned char *) &RPOR0)[tx_pin] = 0b10000;

    __builtin_write_OSCCONL(OSCCON | (1 << 6));

    #endif
}
void easy_can1_init(unsigned int speed_ratio,unsigned char enable_pin, unsigned char en)
{
    conf_transceiver(enable_pin, en);
    easy_can1_fundamental(speed_ratio);
}
void easy_can1_fundamental(unsigned int speed_ratio)
{
    
    ecan_enter_config_mode(ECAN_IDX);

    /*
     Bit Time = (Sync Segment + Propagation Delay + Phase Segment 1 + Phase Segment 2)=20*TQ
     Phase Segment 1 = 8TQ
     Phase Segment 2 = 6TQ
     Propagation Delay = 5TQ
     Sync Segment = 1TQ
     CiCFG1<BRP> =(FCAN /(2 Ã?NÃ?FBAUD))â?? 1
     */
   // ecan_set_clock_source_fcy(ECAN_IDX); Funcao agoraa inexistente
    //ecan_synchronization_jump_width_TQ(ECAN_IDX, 1);
    ecan_synchronization_jump_width_TQ(ECAN_IDX, 4);
    ecan_phase_segment_1_bits(ECAN_IDX, 0x08); // Definir comprimento segmento 1 da fase de ajustamento
    ecan_phase_segment_2_bits_freely(ECAN_IDX);
    ecan_phase_segment_2_bits(ECAN_IDX, 0x06);
    ecan_propagation_time_segment(ECAN_IDX, 0x05);
    ecan_baud_rate_prescaler(ECAN_IDX, speed_ratio / (2 * 20));
    ecan_sample_3_times(ECAN_IDX);

    // FIFO Buffers
    ecan_start_buffer(ECAN_IDX, 8);
    ecan_32_buffers(ECAN_IDX);

    // Pins

   // ecan_pins(ECAN_IDX, tx_pin, rx_pin);

    // Default Filters
    ecan_write_rx_acpt_filter(ECAN_IDX, 0, 0x1FFFFFFF, 1, 15, 0);
    ecan_write_rx_acpt_mask(ECAN_IDX, 0, 0x00000000, 1, 0);

    ecan_enter_normal_mode(ECAN_IDX);

    C1RXFUL1 = C1RXFUL2 = C1RXOVF1 = C1RXOVF2 = 0x0000;

    // Fifo Buffers
    C1TR01CONbits.TXEN0 = 1; // ECAN1, Buffer 0 is a Transmit Buffer
    C1TR01CONbits.TXEN1 = 1; // ECAN1, Buffer 1 is a Transmit Buffer
    C1TR23CONbits.TXEN2 = 1; // ECAN1, Buffer 2 is a Transmit Buffer
    C1TR23CONbits.TXEN3 = 1; // ECAN1, Buffer 3 is a Transmit Buffer
    C1TR45CONbits.TXEN4 = 1; // ECAN1, Buffer 4 is a Transmit Buffer
    C1TR45CONbits.TXEN5 = 1; // ECAN1, Buffer 5 is a Transmit Buffer
    C1TR67CONbits.TXEN6 = 1; // ECAN1, Buffer 6 is a Transmit Buffer
    C1TR67CONbits.TXEN7 = 1; // ECAN1, Buffer 7 is a Transmit Buffer

    C1TR01CONbits.TX0PRI = 0b11; // Message Buffer 0 Priority Level
    C1TR01CONbits.TX1PRI = 0b11; // Message Buffer 1 Priority Level
    C1TR23CONbits.TX2PRI = 0b11; // Message Buffer 2 Priority Level
    C1TR23CONbits.TX3PRI = 0b11; // Message Buffer 3 Priority Level
    C1TR45CONbits.TX4PRI = 0b11; // Message Buffer 4 Priority Level
    C1TR45CONbits.TX5PRI = 0b11; // Message Buffer 5 Priority Level
    C1TR67CONbits.TX6PRI = 0b11; // Message Buffer 6 Priority Level
    C1TR67CONbits.TX7PRI = 0b11; // Message Buffer 7 Priority Level

    //
    // DMAs
    //
    dma_dpsram_to_peripheral(EASY_CAN1_DMA_TX_IDX);
    dma_size_word(EASY_CAN1_DMA_TX_IDX);
    dma_peripheral_address(EASY_CAN1_DMA_TX_IDX);
    dma_continuous(EASY_CAN1_DMA_TX_IDX);
    //dma_set_peripheral(EASY_CAN1_DMA_TX_IDX, &C1TXD); // ECAN 1 (C1TXD). Experimentar com 0x0442.
    dma_set_peripheral(EASY_CAN1_DMA_TX_IDX, &C1TXD); // ECAN 1 (C1TXD). Experimentar com 0x0442.

    dma_set_count(EASY_CAN1_DMA_TX_IDX, 8);
    //dma_set_irq(EASY_CAN1_DMA_TX_IDX, &MODCON); // ECAN 1 Transmit. Experimentar com 0x0046
    dma_set_irq(EASY_CAN1_DMA_TX_IDX, 0x0046); // ECAN 1 Transmit. Experimentar com 0x0046
    dma_set_sta(EASY_CAN1_DMA_TX_IDX, __builtin_dmaoffset(ecan1_msg_buf));
    dma_on(EASY_CAN1_DMA_TX_IDX);

    dma_peripheral_to_dpsram(EASY_CAN1_DMA_RX_IDX);
    dma_size_word(EASY_CAN1_DMA_RX_IDX);
    dma_peripheral_address(EASY_CAN1_DMA_RX_IDX);
    dma_continuous(EASY_CAN1_DMA_RX_IDX);

    dma_set_peripheral(EASY_CAN1_DMA_RX_IDX, &C1RXD); // ECAN 1 (C1RXD). Experimentar com 0x0440

    dma_set_count(EASY_CAN1_DMA_RX_IDX, 8);

//    dma_set_irq(EASY_CAN1_DMA_RX_IDX, &ACCAL); // ECAN 1 Receive. Experimentar 0x0022
    dma_set_irq(EASY_CAN1_DMA_RX_IDX, 0x0022); // ECAN 1 Receive. Experimentar 0x0022
    dma_set_sta(EASY_CAN1_DMA_RX_IDX, __builtin_dmaoffset(ecan1_msg_buf));
    dma_on(EASY_CAN1_DMA_RX_IDX);

 //   C1TR01CONbits.TXEN0=1;
  //  C1TR01CONbits.TXEN1=0;
    
    /* Enable ECAN1 Interrupt   */
    //IEC2bits.C1IE = 1;
    C1INTEbits.TBIE = 0;
    C1INTEbits.RBIE = 0;

   // C1TR01CONbits.RTREN0=1;
 //   C1TR01CONbits.RTREN1=1;

    //IEC2bits.C1RXIE = 1;
    //IEC4bits.C1TXIE = 1;
}

int easy_can1_send_msg(EASY_CAN1_MSG *msg)
{
    //printframe(msg);
    // TODO Locate first free space
    ECAN_MSG *buf = &ecan1_msg_buf[C1FIFObits.FNRB];

    int buf_id = 0;
    buf->RTR = msg->Request;

   /* ecan_write_tx_msg_id(&ecan1_msg_buf[buf_id], msg->id % 0x1FFFFFFF, msg->id &
            EASY_CAN1_MSG_EXTENDED_ID ? 1 : 0, msg->id &
            EASY_CAN1_MSG_RTR ? 1 : 0);*/
    ecan_write_tx_msg_id(&ecan1_msg_buf[buf_id], msg->id % 0x1FFFFFFF, msg->id &
            EASY_CAN1_MSG_EXTENDED_ID ? 1 : 0,  buf->RTR);

    buf->RTR = msg->Request;
    ecan_write_tx_msg_data(&ecan1_msg_buf[buf_id], msg->data_length,
    ((unsigned int *) msg->data)[0], ((unsigned int *) msg->data)[1],
    ((unsigned int *) msg->data)[2], ((unsigned int *) msg->data)[3]); //convem ser melhorado para se enviar exatemente as palavras ou bytes necessario

    ecan_tx_request(ECAN_IDX, buf_id);

    return 1;
}

int easy_can1_recv_msg(EASY_CAN1_MSG *msg)
{
    ECAN_MSG *buf = &ecan1_msg_buf[C1FIFObits.FNRB];

  if (ecan_buffer_is_full(ECAN_IDX, C1FIFObits.FNRB))
    {
  //   printf("val=    %d\n",(int)C1TR01CONbits.TXREQ0);
    //  printf("val=    %d\n",(int)C1TR01CONbits.TXREQ1);
  //      C1TR01CONbits.RTREN0=0;
   // C1TR01CONbits.RTREN1=0;
    //    C1TR01CONbits.RTREN0=1;
   // C1TR01CONbits.RTREN1=1;
//C1TR01CONbits.TXREQ0=0;
//C1TR01CONbits.TXREQ1=0;
      if(buf->DLC==0)
       msg->Request = 1;
      else
       msg->Request = 0;
      
        if (buf->IDE == 1)
        {
            msg->id = EASY_CAN1_MSG_EXTENDED_ID
                    | (((unsigned long long) buf->SID) << 18)
                    | (buf->EIDa << 6) | (buf->EIDb);
        }
        else
        {
            msg->id = buf->SID;
        }        
       // printf("RTR= %d",(int)buf->RTR);

          //  msg->id |= EASY_CAN1_MSG_RTR;

        msg->data_length = buf->DLC;
        msg->data[0] = (buf->words[0] >> 0) & 0xFF; //assim tem que ser char
        msg->data[1] = (buf->words[0] >> 8) & 0xFF;
        msg->data[2] = (buf->words[1] >> 0) & 0xFF;
        msg->data[3] = (buf->words[1] >> 8) & 0xFF;
        msg->data[4] = (buf->words[2] >> 0) & 0xFF;
        msg->data[5] = (buf->words[2] >> 8) & 0xFF;
        msg->data[6] = (buf->words[3] >> 0) & 0xFF;
        msg->data[7] = (buf->words[3] >> 8) & 0xFF;

        msg->reserved = 0;

        ecan_buffer_clear_is_full(ECAN_IDX, C1FIFObits.FNRB);
        ecan_buffer_clear_is_overflow(ECAN_IDX, C1FIFObits.FNRB);

        return 1;
    }

    return 0;
}

void __attribute__((interrupt, no_auto_psv)) _C1Interrupt(void)
{
    IFS2bits.C1IF = 0; // clear interrupt flag
    unsigned long long int icode; //nao deve ser necessario

    icode = C1VECbits.ICODE;

   // serial1_tx_str("_C1Interrupt ");
    //serial1_tx_int16_hexa(icode);
   // serial1_tx_str("\n");

    if (C1INTFbits.TBIF) //Ocorreu pedido de interrupcao TX buffer 
    {
        C1INTFbits.TBIF = 0; 
   //     serial1_tx_str("TX\n");
    }

    if (C1INTFbits.RBIF)
    {
        C1INTFbits.RBIF = 0; //Ocorreu pedido de interrupcao RX buffer 

     //   serial1_tx_str("RX\n");
        /*
         serial1_tx_int16_hexa(icode);
         serial1_tx_str(" ");

         serial1_tx_int16_hexa(C1FIFObits.FBP);
         serial1_tx_str(" ");
         serial1_tx_int16_hexa(C1FIFObits.FNRB);

         if ( ecan_buffer_is_full(ECAN_IDX, C1FIFObits.FNRB) )
         {
         ecan_buffer_clear_is_full(ECAN_IDX, C1FIFObits.FNRB);
         ecan_buffer_clear_is_overflow(ECAN_IDX, C1FIFObits.FNRB);
         serial1_tx_str(" R ");
         serial1_tx_int16_hexa(C1FIFObits.FNRB);
         }
         */
        /*if ( icode <= 15 )
         {
         //C1RXFUL1 = 0; //&= ~(1 << icode);
         //C1RXOVF1 = 0; //&= ~(1 << icode);
         }
         else
         {
         //C1RXFUL2 = 0; //&= ~(1 << (icode-16));
         //C1RXOVF2 = 0; //&= ~(1 << (icode-16));
         }*/
        /*
         serial1_tx_str(" || ");
         serial1_tx_int16_hexa(C1RXFUL1);
         serial1_tx_str(" ");
         serial1_tx_int16_hexa(C1RXOVF1);
         serial1_tx_str(" ");
         serial1_tx_int16_hexa(C1RXFUL2);
         serial1_tx_str(" ");
         serial1_tx_int16_hexa(C1RXOVF2);
         serial1_tx_str("\n");
         */
        //ECAN_MSG * msg = &ecan1_msg_buf[icode];

        //ecan_write_tx_msg_id(&ecan1_msg_buf[1], 0x101, 0, 0);
        //ecan_write_tx_msg_data(&ecan1_msg_buf[1], 8, 0x1122, 0x3344, 0x5566,
        //        0x7788);
        //ecan_tx_request(ECAN_IDX, 1);

    }
}
