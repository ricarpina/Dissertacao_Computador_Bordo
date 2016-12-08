#include <xc.h>


#ifndef __DMA_H__
#define __DMA_H__

//
// Generic DMA Functions
//
//DMA  Permite um CPU realizar tarefas em paralelo a uma transferencia de dados

#define _DMA_REGISTER( BASE , ID, CAST ) ((CAST *)((&DMA1CON-&DMA0CON)*(ID) + &BASE))

static inline void dma_on (unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->CHEN=1;} //ligar canal dma
static inline void dma_off(unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->CHEN=0;}
static inline void dma_size_byte(unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->SIZE=1;} // definir dados com tamanho de byte
static inline void dma_size_word(unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->SIZE=0;}

static inline void dma_dpsram_to_peripheral(unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->DIR=1;} //Ler RAM DMA, escrever em endereco dum periferico
static inline void dma_peripheral_to_dpsram(unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->DIR=0;}

static inline void dma_peripheral_address             (unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->AMODE=0b10;} //
static inline void dma_register_address               (unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->AMODE=0b01;}
static inline void dma_register_address_post_increment(unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->AMODE=0b00;}

static inline void dma_one_shot_ping_pong  (unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->MODE=0b11;} // modo de operacao do canal DMA
static inline void dma_continuous_ping_pong(unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->MODE=0b10;}
static inline void dma_one_shot            (unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->MODE=0b01;}
static inline void dma_continuous          (unsigned int id){_DMA_REGISTER(DMA0CON, id, DMA0CONBITS)->MODE=0b00;}

static inline void dma_force(unsigned int id){_DMA_REGISTER(DMA0REQ, id, DMA0REQBITS)->FORCE=1;} //transferencia DMA forcada (manual) bit limpo obrigatoriamente pelo hardware

static inline void dma_set_irq(unsigned int id, unsigned int irq){_DMA_REGISTER(DMA0REQ, id, DMA0REQBITS)->IRQSEL=irq;} //interrupt request

static inline void dma_set_sta(unsigned int id, unsigned int buffer){*_DMA_REGISTER(DMA0STA, id, unsigned int) = buffer;} //Primary DMA RAM Start Address bits (source or destination)

static inline void dma_set_peripheral(unsigned int id, unsigned int* peripheral_addr){*_DMA_REGISTER(DMA0PAD, id, unsigned int*) = peripheral_addr;} //Indicar qual o endereço dos dados do perifécico

static inline void dma_set_count(unsigned int id, unsigned int count){*_DMA_REGISTER(DMA0CNT, id, unsigned int) = (count&0x3F) - 1;} //DMAxCNT inidica o numero de transferencias dma realizadas

static inline void dma_interrupt_on(unsigned int id) // habilita interrpcoes dma
{
  //  unsigned char pp[3] ="ola";
   // RS232Tx(&pp[0], 1);
	switch(id)
	{
		case 0:
			IFS0bits.DMA0IF=0;
			IEC0bits.DMA0IE=1;
			break;

		case 1:
			IFS0bits.DMA1IF=0;
			IEC0bits.DMA1IE=1;
			break;

		case 2:
			IFS1bits.DMA2IF=0;
			IEC1bits.DMA2IE=1;
			break;

		case 3:
			IFS2bits.DMA3IF=0;
			IEC2bits.DMA3IE=1;
			break;
               
	}

            #if defined(__dsPIC33FJ128GP802__)

                switch(id)
                	{

		case 4:
			IFS2bits.DMA4IF=0;
			IEC2bits.DMA4IE=1;
			break;

		case 5:
			IFS3bits.DMA5IF=0;
			IEC3bits.DMA5IE=1;
			break;

		case 6:
			IFS4bits.DMA6IF=0;
			IEC4bits.DMA6IE=1;
			break;

		case 7:
			IFS4bits.DMA7IF=0;
			IEC4bits.DMA7IE=1;
			break;
            	}

            #endif

}

//
// DMA 0
//
static inline void dma0_on (void){dma_on (0);}
static inline void dma0_off(void){dma_off(0);}

/*
static inline void dma_size_byte(unsigned int id);
static inline void dma_size_word(unsigned int id);

static inline void dma_dpsram_to_peripheral(unsigned int id);
static inline void dma_peripheral_to_dpsram(unsigned int id);

static inline void dma_peripheral_address             (unsigned int id);
static inline void dma_register_address               (unsigned int id);
static inline void dma_register_address_post_increment(unsigned int id);

static inline void dma_one_shot_ping_pong  (unsigned int id);
static inline void dma_continuous_ping_pong(unsigned int id);
static inline void dma_one_shot            (unsigned int id);
static inline void dma_continuous          (unsigned int id);

static inline void dma_force(unsigned int id);

static inline void dma_set_irq(unsigned int id, unsigned int irq);

static inline void dma_set_sta(unsigned int id, unsigned int buffer);

static inline void dma_set_peripheral(unsigned int id, unsigned int peripheral_addr);

static inline void dma_set_count(unsigned int id, unsigned int count);

static inline void dma_interrupt_on(unsigned int id);
*/
#endif
