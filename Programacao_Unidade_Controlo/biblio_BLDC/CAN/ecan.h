#ifndef __MODULE_ECAN_H__
#define __MODULE_ECAN_H__

#include "pic16bits.h"

/*
 * NOTES:
 *    extern inline __attribute__((always_inline))
 *        This re-creates te pre-processor MACRO effect with the beneficts of the compiler time checks.
 *        extern prevents the funcition code to be generated (and the symbol to not be exported)
 *        inline gives a hint to the compiler to "inline" the function code (only in -O1 -O2 -O3 optimizations modes)
 *        __attribute__((always_inline)) forces the gcc to inline the code
 */

typedef struct
{
        // Word 0
        unsigned IDE :1;
        unsigned SRR :1;
        unsigned SID :11;
        unsigned :3;
        // Word 1
        unsigned EIDa :12;
        unsigned :4;
        // Word 2
        unsigned DLC :4;
        unsigned RB0 :1;
        unsigned :3;
        unsigned RB1 :1;
        unsigned RTR :1;
        unsigned EIDb :6;
        // Word 3/4/5/6
        unsigned int words[4];
        // Word 7
        unsigned :8;
        unsigned FILHIT :5;
        unsigned :3;
} ECAN_MSG;

extern inline __attribute__((always_inline)) void ecan_disable_filters( //
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1CTRL1bits.WIN = 1;
            break;
    }
}

extern inline __attribute__((always_inline)) __attribute__((always_inline)) void ecan_enable_filters(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1CTRL1bits.WIN = 0; 
            break;
    }
}

/*extern inline __attribute__((always_inline)) void ecan_pins(unsigned char n,
        unsigned char tx_rp, unsigned char rx_rp)
{
    __builtin_write_OSCCONL(OSCCON & ~(1 << 6));

    switch (n)
    {
        default:
        case 1:
            RPINR26bits.C1RXR = rx_rp;
            ((unsigned char *) &RPOR0)[tx_rp] = 0b10000;
            break;
    }

    __builtin_write_OSCCONL(OSCCON | (1 << 6));
}*/

extern inline __attribute__((always_inline)) void ecan_set_clock_source_fcy(
        unsigned char n)
{/*
    switch (n)
    {
        default:
        case 1:
            C1CTRL1bits.CANCKS = 1;// Fcan = Fcy
            break;					//(=0 Fcan=fosc
    }*/
}

extern inline __attribute__((always_inline)) void ecan_setclock_source_fosc(
        unsigned char n)
{/*
    switch (n)
    {
        default:
        case 1:
            C1CTRL1bits.CANCKS = 0;
            break;
    }

  */}

extern inline __attribute__((always_inline)) void ecan_synchronization_jump_width_TQ(
        unsigned char n, unsigned char tq)
{
    switch (n)
    {
        default:
        case 1:
            C1CFG1bits.SJW = tq - 1;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_sample_1_times(//tirar apenas uma amostra da linha
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1CFG2bits.SAM = 0;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_sample_3_times(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1CFG2bits.SAM = 1;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_phase_segment_1_bits(
        unsigned char n, unsigned char phase_segment) // Definir comprimento segmento 1 da fase de ajustamento
{
    switch (n)
    {
        default:
        case 1:
            C1CFG2bits.SEG1PH = phase_segment - 1;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_phase_segment_2_bits_freely(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1CFG2bits.SEG2PHTS = 1;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_phase_segment_2_bits_max(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1CFG2bits.SEG2PHTS = 0;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_phase_segment_2_bits(
        unsigned char n, unsigned char tq)
{
    switch (n)
    {
        default:
        case 1:
            C1CFG2bits.SEG2PH = tq - 1;
            break;
    }
}

//
extern inline __attribute__((always_inline)) void ecan_propagation_time_segment(
        unsigned char n, unsigned char tq)
{
    switch (n)
    {
        default:
        case 1:
            C1CFG2bits.PRSEG = tq - 1;
            break;
    }
}

//
extern inline __attribute__((always_inline)) void ecan_start_buffer(// Definir qual o primeiro buffer destinado a ECAN
        unsigned char n, unsigned char count)
{
    switch (n)
    {
        default:
        case 1:
            C1FCTRLbits.FSA = count;
            break;
    }
}

//
extern inline __attribute__((always_inline)) void ecan_32_buffers(// definir tamanho do buffer DMA
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1FCTRLbits.DMABS = 0b110;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_24_buffers(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1FCTRLbits.DMABS = 0b101;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_16_buffers(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1FCTRLbits.DMABS = 0b100;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_12_buffers(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1FCTRLbits.DMABS = 0b011;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_8_buffers(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1FCTRLbits.DMABS = 0b010;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_6_buffers(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1FCTRLbits.DMABS = 0b001;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_4_buffers(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1FCTRLbits.DMABS = 0b000;
            break;
    }
}

//
extern inline __attribute__((always_inline)) void ecan_enter_config_mode(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1CTRL1bits.REQOP = 4;
            while (C1CTRL1bits.OPMODE != 4)
                ;

            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_enter_normal_mode(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1CTRL1bits.REQOP = 0;
            while (C1CTRL1bits.OPMODE != 0)
                ;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_enter_loopback_mode(
        unsigned char n)
{
    switch (n)
    {
        default:
        case 1:
            C1CTRL1bits.REQOP = 2;
            while (C1CTRL1bits.OPMODE != 2)
                ;
            break;
    }
}

//
extern inline __attribute__((always_inline)) void ecan_baud_rate_prescaler(
        unsigned char n, unsigned int brp)
{
    switch (n)
    {
        default:
        case 1:
            C1CFG1bits.BRP = brp - 1;
            break;
    }
}

/*
 *
 *
 *
 *
 *
 *
 *
 */

/*	Filter Configuration

 ecan_write_rx_acpt_filter(int n, long identifier, unsigned int exide, unsigned int bufPnt, unsigned int maskSel)

 filter_id	-> 0 to 15 Filter Number

 identifier	->
 Extended Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
 |____________|_____________________|
 SID10:0           EID17:0


 Standard Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
 |___________|
 SID10:0


 exide		-> 0 Match messages with standard identifier addresses
 -> 1 Match messages with extended identifier addresses

 bufPnt		-> 0 to 14 RX Buffer 0 to 14
 -> 15      RX FIFO Buffer

 maskSel		-> 0 Acceptance Mask 0 register contains mask
 -> 1 Acceptance Mask 1 register contains mask
 -> 2 Acceptance Mask 2 register contains mask
 -> 3 No Mask Selection

 */

extern inline __attribute__((always_inline)) void ecan_write_rx_acpt_filter(
        unsigned char n, int filter_id, long identifier, int exide,
        unsigned int bufPnt, unsigned int maskSel)
{
    C1RXF0SIDBITS *c1_rx_filter_sid_bits; //ACCEPTANCE FILTER STANDARD IDENTIFIER REGISTER
    C1RXF0EIDBITS *c1_rx_filter_eid_bits;

    unsigned int *bufPntRegAddr;
    unsigned int *maskSelRegAddr;

    switch (n)
    {
        default:
        case 1:

            ecan_disable_filters(n);

            // Obtain the Address of CiRXFnSID, CiBUFPNTn, CiFMSKSELn and CiFEN register for a given filter number "filter_id"
            c1_rx_filter_sid_bits = (C1RXF0SIDBITS *) (&C1RXF0SIDbits
                    + (filter_id << 1));
            c1_rx_filter_eid_bits = (C1RXF0EIDBITS *) (&C1RXF0EIDbits
                    + (filter_id << 1));
            bufPntRegAddr = (unsigned int *) (&C1BUFPNT1 + (filter_id >> 2));
            maskSelRegAddr = (unsigned int *) (&C1FMSKSEL1 + (filter_id >> 3));

            if (exide)
            {
                c1_rx_filter_eid_bits->EID = (identifier & 0xFFFF);
                c1_rx_filter_sid_bits->EID = (identifier >> 16) & 0x3;
                c1_rx_filter_sid_bits->SID = (identifier >> 18) & 0x7FF;
            }
            else
            {
                c1_rx_filter_eid_bits->EID = 0;
                c1_rx_filter_sid_bits->EID = 0;
                c1_rx_filter_sid_bits->SID = (identifier & 0x7FF);
            }

            *bufPntRegAddr &= ~(0xF << (4 * (n & 3))); // clear nibble
            *bufPntRegAddr |= bufPnt << (4 * (n & 3)); // Write to C1BUFPNTn Register

            *maskSelRegAddr &= ~(0x3 << (2 * (n & 7))); // clear 2 bits
            *maskSelRegAddr |= maskSel << (2 * (n & 7)); // Write to C1FMSKSELn Register

            C1FEN1 |= 0x1 << filter_id; // Enable this filter // TODO que tal umas funções para activar e desactivar?

            ecan_enable_filters(n);
            break;
    }
}

/*	Mask Configuration

 ecan_write_rx_acpt_mask(int m, long identifier, unsigned int exide, unsigned int mide)

 m		-> 0 to 2 Mask Number

 identifier	->
 Extended Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
 |____________|_____________________|
 SID10:0           EID17:0


 Standard Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
 |___________|
 SID10:0

 exide		-> 0 Match messages with standard identifier addresses
 -> 1 Match messages with extended identifier addresses

 mide		-> 0 Match either standard or extended address message if filters match
 -> 1 Match only message types that correpond to 'exide' bit in filter

 */
extern inline __attribute__((always_inline)) void ecan_write_rx_acpt_mask(
        unsigned char n, int mask_id, long identifier, unsigned int exide,
        unsigned int mide)
{
    C1RXM0SIDBITS * c1_rx_mask_sid_bits;
    C1RXM0EIDBITS * c1_rx_mask_eid_bits;

    switch (n)
    {
        default:
        case 1:
            ecan_disable_filters(n);

            // Obtain the Address of CiRXMmSID register for given Mask number "mask_id"
            c1_rx_mask_sid_bits = (C1RXM0SIDBITS *) (&C1RXM0SID
                    + (mask_id << 1));
            c1_rx_mask_eid_bits = (C1RXM0EIDBITS *) (&C1RXM0EID
                    + (mask_id << 1));

            if (exide)
            {
                c1_rx_mask_eid_bits->EID = (identifier & 0xFFFF);
                c1_rx_mask_sid_bits->EID = (identifier >> 16) & 0x3;
                c1_rx_mask_sid_bits->SID = (identifier >> 18) & 0x7FF;
            }
            else
            {
                c1_rx_mask_eid_bits->EID = 0;
                c1_rx_mask_sid_bits->EID = 0;
                c1_rx_mask_sid_bits->SID = (identifier & 0x7FF);
            }

            c1_rx_mask_sid_bits->MIDE = mide == 1 ? 1 : 0;

            ecan_enable_filters(n);
            break;
    }
}

/*
 *
 *
 *
 *
 *
 *
 *
 */

extern inline __attribute__((always_inline)) unsigned char ecan_buffer_is_full(
        unsigned char n, unsigned int buffer_id)
{
    switch (n)
    {
        default:
        case 1:
            if (buffer_id >= 16)
                return (C1RXFUL2 >> (buffer_id - 16)) & 1;

            return (C1RXFUL1 >> buffer_id) & 1;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_buffer_clear_is_full(
        unsigned char n, unsigned int buffer_id)
{
    switch (n)
    {
        default:
        case 1:
            if (buffer_id >= 16)
                C1RXFUL2 &= ~(1 << (buffer_id - 16));
            else
                C1RXFUL1 &= ~(1 << (buffer_id));
            break;
    }
}

extern inline __attribute__((always_inline)) unsigned char ecan_buffer_is_overflow(
        unsigned char n, unsigned int buffer_id)
{
    switch (n)
    {
        default:
        case 1:
            if (buffer_id >= 16)
                return (C1RXOVF2 >> (buffer_id - 16)) & 1;

            return (C1RXOVF1 >> buffer_id) & 1;
            break;
    }
}

extern inline __attribute__((always_inline)) void ecan_buffer_clear_is_overflow(
        unsigned char n, unsigned int buffer_id)
{
    switch (n)
    {
        default:
        case 1:
            if (buffer_id >= 16)
                C1RXOVF2 &= ~(1 << (buffer_id - 16));
            else
                C1RXOVF1 &= ~(1 << (buffer_id));
            break;
    }
}

/*
 ECAN Transmit Message Buffer Configuration

 buf		-> Transmit Buffer pointer

 identifier	->
 Extended Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
 |____________|_____________________|
 SID10:0           EID17:0


 Standard Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
 |___________|
 SID10:0


 ide		-> "0"  Message will transmit standard identifier
 -> "1"  Message will transmit extended identifier


 remoteTransmit	-> "0" Message transmitted is a normal message
 -> "1" Message transmitted is a remote message
 */
extern inline __attribute__((always_inline)) void ecan_write_tx_msg_id(
        ECAN_MSG *buf, unsigned long identifier, unsigned int ide,
        unsigned int remoteTransmit)
{
    buf->RTR = remoteTransmit == 1 ? 1 : 0;
    buf->SRR = remoteTransmit == 1 ? 1 : 0;

    if (ide)
    {
        buf->IDE = 1;

        buf->SID = (identifier >> 18) & 0x7FF;
        buf->EIDa = (identifier >> 6) & 0xFFF;
        buf->EIDb = (identifier & 0x3F);
    }
    else
    {
        buf->IDE = 0;

        buf->SID = (identifier & 0x7FF);
        buf->EIDa = 0;
        buf->EIDb = 0;
    }

    buf->DLC = 0;
    buf->RB0 = 0;
    buf->RB1 = 0;

}

/* ECAN Transmit Data

 Inputs :
 buf		-> Transmit Buffer pointer

 dataLength	-> Length of Data in Bytes to be transmitted

 data1/2/3/4	->  Transmit Data Bytes

 */
extern inline __attribute__((always_inline)) void ecan_write_tx_msg_data(
        ECAN_MSG *buf, unsigned int dataLength, unsigned int word1,
        unsigned int word2, unsigned int word3, unsigned int word4)
{
    buf->DLC = dataLength;

    buf->words[0] = word1;
    buf->words[1] = word2;
    buf->words[2] = word3;
    buf->words[3] = word4;
}

//void ecan_tx_buf_init(unsigned char id){((unsigned char *)&C1TR01CON)[id] |= 1<<3;}

extern inline __attribute__((always_inline)) void ecan_tx_request(
        unsigned char n, unsigned char id)
{
    switch (n)
    {
        default:
        case 1:
            ((unsigned char *) &C1TR01CON)[id] |= 1 << 3;
            break;
    }
}

#endif
