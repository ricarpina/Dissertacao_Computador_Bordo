#include <xc.h>
#include "initMeu.h"

#include "CAN/easy_can1.h"
#include "CAN/can_carro_eletrico_impl.h"
#include "motor_control.h"
#include "measuresPlate.h"
#include "controlLoop.h"
#include "sine_control.h"

const unsigned long int taxa_can = 250000;
const unsigned int BAUDRATE = 57600; //9600
#define FOSC 20000000
const unsigned long int FCY=FOSC/2;
#define BRGVAL ((FCY/BAUDRATE)/4)-1;

// NOTA: é necessario ter em atenção a ligação dos sensores de Hall! ligar nas portas correctas!
// NAO ESQUECER DE METER OS DEAD TIMES no PWM !!!

// global variables
float meanCurrent = 0.0, u = 0.0;
unsigned char ADC_RSLT0_accel[3];
unsigned char ADC_RSLT1_brake[3];
extern unsigned int count;
volatile unsigned int countTimer = 0;

extern unsigned char controlador_on_off[3],alta_temp;
extern float current[3], temp_bat[3], temp_motor[3], lim_temp;

int HallValue = 1, oldHallValue = 0;
// flag que me diz a direcção do motor
unsigned char direction[3]; // 1 para CCW e 0 para CW
unsigned int motorSpeed[3], flag = 0, flagI = 0;

int indexSineTable=0;
//extern float sineWaveLut[];

void inits(void) {
    //RD0 it's the port of the control signal that makes the PWM's on of off
    TRISDbits.TRISD0 = 0; //Agora RD0// configure RD0 as an output
    TRISBbits.TRISB8 = 1; // configure RB8 as an input
    TRISDbits.TRISD8 = 0; // um LED indicador
}

void delay(int n) {
    //cada instrução demora 2 ciclos de relogio a executar, com a FOSC que temos (7370000)
    //cada instrução demora 1/FCY = 271ns a executar
    int i;
    for (i = 0; n < i; i++) {
        //for (i=n;i==0;i--)
        //{
        asm volatile("nop");
        //}
    }
}

void InitMCPWM(void) {

	TRISEbits.TRISE0=0;
	TRISEbits.TRISE1=0;
	TRISEbits.TRISE2=0;
	TRISEbits.TRISE3=0;
	TRISEbits.TRISE4=0;
	TRISEbits.TRISE5=0;

    //__delay_us(100);
    PTCONbits.PTEN = 0; // disable PWM

    PTCONbits.EIPU = 0; // Active Period register updates occur on PWM cycle boundaries

    /* ADC Special Event Trigger configuration */
    SEVTCMP = 1200; // about 25% of PTPER
    PTCONbits.SEIEN = 1; // Special event interrupt is enabled
    PTCONbits.SEVTPS = 0; // 1:1 Postscaler generates a Special Event Trigger on every compare match event
    while (PTCONbits.SESTAT == 1); // wait for special event interrupt status change

    PTCON2bits.PCLKDIV = 1;

    IOCON1bits.PMOD = 3; // PWM I/O pin pair is in the True Independent Mode
    IOCON2bits.PMOD = 3;
    IOCON3bits.PMOD = 3;

    //___________________________________________________________________________
    //
    //    IOCON1bits.PENH = 1;    // PWM Output pin control assigned to PWM generator
    //    IOCON1bits.PENL = 1;
    IOCON1bits.POLH = 0; // High and Low switches set to active-high state
    IOCON1bits.POLL = 0;

    //    IOCON2bits.PENH = 1;    // PWM Output pin control assigned to PWM generator
    //    IOCON2bits.PENL = 1;
    IOCON2bits.POLH = 0; // High and Low switches set to active-high state
    IOCON2bits.POLL = 0;

    //    IOCON3bits.PENH = 1;    // PWM Output pin control assigned to PWM generator
    //    IOCON3bits.PENL = 1;
    IOCON3bits.POLH = 0; // High and Low switches set to active-high state
    IOCON3bits.POLL = 0;

    //___________________________________________________________________________

    TRGCON1 = 0xF080; // PWM TRIGGER CONTROL REGISTER
    TRGCON2 = 0xF080;
    TRGCON3 = 0xF080;

    //dead time of all PWM signalls = 50ns due to mosfet times
    //DTR1 = 25;
    //DTR2 = 25;
    //DTR3 = 25;
    //ALTDTR1 = 25;
    //ALTDTR2 = 25;
    //ALTDTR3 = 25;2

    PWMCON1 = 0x0400; // trigger envent enable
    PWMCON2 = 0x0400; // PDC to control duty-cycle
    PWMCON3 = 0x0400;

    PWMCON1bits.ITB = 0; // PTER provides the PWM time period
    PWMCON2bits.ITB = 0;
    PWMCON3bits.ITB = 0;

    PWMCON1bits.CAM = 1; // For Center-Aligned Mode
    PWMCON2bits.CAM = 1;
    PWMCON3bits.CAM = 1;


    // PWMCON1bits.IUE = 1;         // imediate update enable
    // PWMCON2bits.IUE = 1;
    // PWMCON3bits.IUE = 1;


    PTPER = 48077;

    PTCONbits.PTEN = 1; // enable PWM

    //    PDC1 = 0;//PTPER/2;         // set PWM at 0% duty-cycle for each PWMxH and PWMxL
    //    PDC2 = 0;//PTPER/2;
    //    PDC3 = 0;//PTPER/2;
    //    SDC1 = 0;//PTPER/2;
    //    SDC2 = 0;//PTPER/2;
    //    SDC3 = 0;//PTPER/2;

    /*  IOCON1bits.OVRENH = 1;
      IOCON2bits.OVRENH = 1;
      IOCON3bits.OVRENH = 1;

      IOCON1bits.OVRENL = 1;
      IOCON2bits.OVRENL = 1;
      IOCON3bits.OVRENL = 1;

      IOCON1bits.OVRDAT = 0b00;
      IOCON2bits.OVRDAT = 0b00;
      IOCON3bits.OVRDAT = 0b00;

     */
}


void initTimer1(void) {

    // Configure Timer 1.
    // PR1 and TCKPS are set to call interrupt every 500ms.
    // Period = PR1 * prescaler * Tcy = 58594 * 256 * 33.33ns = 500ms
    T1CON = 0; // Clear Timer 1 configuration
    T1CONbits.TCKPS = 2; // Set timer 1 prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256)

    T1CONbits.TCS=0;     // internal clock as source of timer2
    T1CONbits.TGATE=0;   // Gated time accumulation disabled

    PR1 = 156; // freq=1000hz          // Set Timer 1 period (max value is 65535)
    _T1IP = 2; // Set Timer 1 interrupt priority
    _T1IF = 0; // Clear Timer 1 interrupt flag
    _T1IE = 1; // enable Timer 1 interrupt
    T1CONbits.TON = 1; // Turn on Timer 1

}

void initTimer2(void) {

    // Configure Timer 1.
    // PR1 and TCKPS are set to call interrupt every 500ms.
    // Period = PR1 * prescaler * Tcy = 58594 * 256 * 33.33ns = 500ms
    T2CON = 0; // Clear Timer 1 configuration

    T2CONbits.T32=0;     // use Timer as a 16bit timer //FOI ALTERADO AQUI
    _TCS=0;     // internal clock as source of timer2
    _TGATE=0;   // Gated time accumulation disabled

    T2CONbits.TCKPS = 1; // Set timer 1 prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256)
    PR2 = 553; // freq = 833hz          // Set Timer 1 period (max value is 65535)
    _T2IP = 3; // Set Timer 1 interrupt priority
    _T2IF = 0; // Clear Timer 1 interrupt flag
    _T2IE = 1; // enable Timer 1 interrupt
    T2CONbits.TON = 1; // Turn on Timer 1

}
void initTimer3(void) {

    // Configure Timer 1.
    // PR1 and TCKPS are set to call interrupt every 500ms.
    // Period = PR1 * prescaler * Tcy = 58594 * 256 * 33.33ns = 500ms
    T3CON = 0; // Clear Timer 1 configuration

    T3CONbits.TCS=0;     // internal clock as source of timer2
    T3CONbits.TGATE=0;   // Gated time accumulation disabled

    T3CONbits.TCKPS = 3; //1/64 Set timer 3 prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256)
    // _T3IP = 4; // Set Timer 3 interrupt priority
    _T3IF = 0; // Clear Timer 1 interrupt flag
    _T3IE = 0; // no Timer 3 interrupt
    T3CONbits.TON = 1; // Turn on Timer 1

}


void initTimer4(void) {
    // Configure Timer 1.
    // PR1 and TCKPS are set to call interrupt every 500ms.
    // Period = PR1 * prescaler * Tcy = 58594 * 256 * 33.33ns = 500ms
    T4CON = 0; // Clear Timer 1 configuration

    T4CONbits.T32=0;     // use Timer as a 16bit timer //FOI ALTERADO AQUI
    _TCS=0;     // internal clock as source of timer2
    _TGATE=0;   // Gated time accumulation disabled

    T4CONbits.TCKPS = 2; // Set timer 1 prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256)
    PR4 = 31250/2; //Set Timer 4 period (max value is 65535) T==100ms
    _T4IP = 6; // Set Timer 4 interrupt priority
    _T4IF = 0; // Clear Timer 1 interrupt flag
    _T4IE = 1; // enable Timer 1 interrupt
    T4CONbits.TON = 1; // Turn on Timer 1
}


void InitADC10(void) {

    ADCONbits.ADON = 0; // turn ADC off
    ADCONbits.ASYNCSAMP = 0; // a pair conversion request is synchronized to the ADC clock
    // domain (TAD) and it is prioritized with other requests

    // Input clock: FRCCLK
    // Multiply by 16, FPWM/ADC = 7.37 MHz * 16 = 117.92 MHz
    // ACLKCON: Auxiliary Clock Divisor Control register
    ACLKCON = 0;
    ACLKCONbits.FRCSEL = 1; // Source clock is FRC
    ACLKCONbits.SELACLK = 1; // Primary auxiliary oscillator
    ACLKCONbits.APSTSCLR = 7; // Divide factor = 1
    ACLKCONbits.ENAPLL = 1; // Enable auxiliary clock generation
    // loop waiting for auxiliary PLL lock
    while (!ACLKCONbits.APLLCK);

    //00011 = PWM special event trigger selected
    ADCPC0bits.TRGSRC0 = 3; // on AN0 and AN1 ADC ports
    ADCPC0bits.IRQEN0 = 1;

    ADCPC0bits.TRGSRC1 = 1; // Individual software trigger selected
    ADCPC0bits.SWTRG1 = 0; // Conversion is not started
    ADCPC0bits.IRQEN1 = 1; // Enable the IRQ generation when requested conversion of channels AN2 and AN3 is completed

    ADCPC1bits.TRGSRC2 = 1; // Individual software trigger selected
    ADCPC1bits.SWTRG2 = 0; // Conversion is not started
    ADCPC1bits.IRQEN2 = 1; // Enable the IRQ generation when requested conversion of channels AN4 and AN5 is completed

    ADCPC3bits.TRGSRC6 = 1; // Individual software trigger selected
    ADCPC3bits.SWTRG6 = 0; // Conversion is not started
    ADCPC3bits.IRQEN6 = 1; // Enable the IRQ generation when requested conversion of channels AN12 and AN13 is completed

    //The instructions for the clock selection are:
    ADCONbits.SLOWCLK = 1;
    ADCONbits.ADCS = 5; //ADC clock = FADC/6 = 120MHz / 6 = 20MHz
    // Clock divider is set up for FADC/6
    // TAD = 41.66 ns 50.88ns
    // For simultaneous sampling, the total
    // conversion time for one pair is 0.625 ?s ---> 0.715us

    ADCONbits.FORM = 0; // fractional format -> out = dddd dddd dd00 0000
    ADCONbits.ORDER = 1; // odd ANx are converted first
    //ADCONbits.SEQSAMP = 1;      // shared S&H is sampled at the start of the first conversion
 //   ADPCFG = 0x0FC0; // configure the ANx ports used in ADC as analog inputs
    ADPCFG = 0xCFC0; // configure the ANx ports used in ADC as analog inputs
    //____________________-

    //ADCONbits.EIE = 0;                //Early Interrupt disabled
    ADCONbits.SEQSAMP = 0; //Select simultaneous sampling

    //___________
    //   ADPCFGbits.PCFG0 = 0;          //select CH0 as analog pin
    //   ADPCFGbits.PCFG1 = 0;          //select CH1 as analog pin
    //___________

    IFS6bits.ADCP0IF = 0; //Clear ADC Pair 0 interrupt flag
    IPC27bits.ADCP0IP = 5; //Set ADC Pair 0 interrupt priority
    IEC6bits.ADCP0IE = 1; //Enable the ADC Pair 0 interrupt

    ADSTATbits.P0RDY = 0; //Clear Pair 0 data ready bit
    ADCPC0bits.IRQEN0 = 1; //Enable ADC Interrupt pair 0
    // ADCPC0bits.TRGSRC0 = 4;           //ADC Pair 0 triggered by PWM1 Trigger

    /*   TRGCON1bits.DTM=1;            //dual trigger mode
       TRIG1bits.TRGCMP=0;            //Primary trig compare value
       STRIG1bits.STRGCMP=0xFFF;    //secondary trig compare value

        TRGCON1bits.TRGDIV = 0;        // Trigger generated every PWM cycle
       TRGCON1bits.TRGSTRT = 0;        // enable Trigger generated after 0 PWM cycles
       TRIG1 = 1;

     */
    ADCONbits.ADON = 1; // turn ADC on

}

unsigned int readADC10(int ch) {
    unsigned int a = 0;
    //ADCONbits.ADON = 1;     // turn ADC on

    if (ch == 2) {
        ADCPC0bits.SWTRG1 = 1;
        a = ADCBUF2;
        ADSTATbits.P1RDY = 0;
    }

    if (ch == 3) {
        ADCPC0bits.SWTRG1 = 1;
        a = ADCBUF3;
        ADSTATbits.P1RDY = 0;
    }
    if (ch == 4) {
        ADCPC1bits.SWTRG2 = 1;
        a = ADCBUF4;
        ADSTATbits.P2RDY = 0;
    }
    if (ch == 5) {
        ADCPC1bits.SWTRG2 = 1;
        a = ADCBUF5;
        ADSTATbits.P2RDY = 0;
    }
     if (ch == 12) {
        ADCPC3bits.SWTRG6 = 1;
        a = ADCBUF12;
        ADSTATbits.P6RDY = 0;
    }
 if (ch == 13) {
        ADCPC3bits.SWTRG6 = 1;
        a = ADCBUF13;
        ADSTATbits.P6RDY = 0;
    }

    //ADCONbits.ADON = 0;     // turn ADC off

    return a;
}

void setupInputCN(void) {
    // set the ports connected to hall sensors as digital in's
    TRISGbits.TRISG8 = 1; //CN10
    TRISGbits.TRISG7 = 1; //CN9
    TRISGbits.TRISG6 = 1; //CN8
    // setup input change notification on port RG6, RG7, RG8
    CNEN1bits.CN10IE = 1;
    CNEN1bits.CN9IE = 1;
    CNEN1bits.CN8IE = 1;
    // with pull-up at these pins
    CNPU1bits.CN10PUE = 1;
    CNPU1bits.CN9PUE = 1;
    CNPU1bits.CN8PUE = 1;
    // enable interrupts for input CN
    IEC1bits.CNIE = 1;
    IFS1bits.CNIF = 0;
}

// ********** see if input CH as accurred **************************************
int cnInterruptOcurred(void) {
    return IFS1bits.CNIF;
}

void initSPI(void) {
    //OPEN THE SPI PORT
    // Set SPI Interrupts
    IFS0bits.SPI1IF = 0; // clear spi1 interrupt flag
    IEC0bits.SPI1IE = 0; // disable spi1 interrupt
    //IPC2bits.SPI1IP = 1;          // set spi1 interrupt to lowest priority

    // Configure SPI1CON1 (individual bits for clarity)
    SPI1CON1bits.DISSCK = 0; //Disable SCKx pin bit (SPI Master modes only)
    //  - Internal SPI clock is enabled
    SPI1CON1bits.DISSDO = 0; //enable SDOx pin bit

    SPI1CON1bits.MODE16 = 0; //Word/Byte Communication Select bit
    //  - Communication is byte-wide (8 bits)
    SPI1CON1bits.SMP = 0; //SPIx Data Input Sample Phase bit - Input data
    //  sampled at middle of data output time
    SPI1CON1bits.CKE = 0; //SPIx Clock Edge Select bit - Serial output
    //  data changes on transition from Idle clock
    //  state to active clock state (see bit 6)
    SPI1CON1bits.SSEN = 0; //Slave Select Enable (Slave mode) bit - #SSx#
    //  pin not used by module; pin controlled by
    //  port function
    SPI1CON1bits.CKP = 0; //Idle state for clock is a low level; active state is a high level
    SPI1CON1bits.MSTEN = 1; //Master Mode Enable bit - Master mode
    SPI1CON1bits.SPRE = 7; //Secondary Prescale bits (Master mode)
    //  - Secondary prescale 1:1
    SPI1CON1bits.PPRE = 1; //Primary Prescale bits (Master mode)
    // - Primary prescale 16:1

    //Configure SPI1CON2 (individual bits for clarity)
    SPI1CON2bits.FRMEN = 0; //Framed SPIx Support bit - Framed SPIx
    //  support disabled
    SPI1CON2bits.SPIFSD = 0; //Frame Sync Pulse Direction Control on SSx
    //Pin bit - Frame sync pulse output (master)
    SPI1CON2bits.FRMPOL = 0; //Frame Sync Pulse Polarity bit (Frame mode
    //   only) - Frame sync pulse is active-low
    SPI1CON2bits.FRMDLY = 0; //Frame Sync Pulse Edge Select bit
    // - Frame sync pulse precedes first bit clock


    // Configure SPI1STAT (individual bits for clarity)
    SPI1STATbits.SPIROV = 0; //Receive Overflow Flag bit
    //  - No overflow has occurred
    SPI1STATbits.SPIEN = 1; //SPIx Enable bit - Enables module and
    //  configures SCKx, SDOx, SDIx and #SSx#
    //  as serial port pins

    // configure the RPn pins for SPI function
    //SDO1 000111 RPn tied to SPI1 data output
    //SCK1 001000 RPn tied to SPI1 clock output
    //SS1 001001 RPn tied to SPI1 slave select output
    
    //------------Este novo pic nao pinos remapeaveis
    /*
    __builtin_write_OSCCONL(OSCCON & ~(1 << 6));
    //  SDO1   ->RB15
    //  SCK1   ->RB5
    //  SS1    ->RB6
    RPOR3bits.RP6R = 0b001001;
    RPOR2bits.RP5R = 0b001000;
    RPOR7bits.RP15R = 0b000111;
    __builtin_write_OSCCONL(OSCCON | (1 << 6));
*/

}

// falta escolher em que porta fica o CS para o digiPOT

void sendSPIdata(char data) {
    SPI1STATbits.SPIEN = 1; //SPIx Enable bit - Enables module and
    //  configures SCKx, SDOx, SDIx and #SSx#
    //  as serial port pins

    //LATCbits.LATC6 = 0;    // select the SPI slave device (#CS# signal)

    SPI1BUF = data; // write data to spi tx buffer

    while (SPI1STATbits.SPITBF == 1); // wait till date is transmited

    SPI1STATbits.SPIEN = 0; //SPIx disable bit
}

void sendChar(char c) {
    unsigned int i;

    // wait at least 104 usec (1/9600) before sending first char /
    for (i = 0; i < 4160; i++) {
        Nop();
    }

    U2TXREG = c; // Transmit one character

}

// Send a character through serial port (blocking)

void Putchar(unsigned char c) {
    while (U2STAbits.UTXBF); // Wait till buffer available (TX Buffer Full)
    U2TXREG = c; // Put char in Tx buffer
    return;
}

// Receives a char from the serial port (blocking)

unsigned char Readchar(void) {
    if (U2STAbits.OERR)
        U2STAbits.OERR; // Reset Overrun Eror Flag - if set UART does not receive any chars
    while (!U2STAbits.URXDA); // Wait for char available
    return (U2RXREG); // Return char
}

// UART Configuration function

void UART2_Config(void) {
    DFLT2CONbits.QEOUT=0;

     CNEN2bits.CN17IE = 0;
    CNEN2bits.CN18IE = 0;
   //TRISFbits.TRISF5=0;
   //TRISFbits.TRISF4=1;
    U2MODEbits.UARTEN = 1; // Enable UART
    // From manual, for PBC = 20MHz,
    // UxMODE.BRGH=0 (standard speed x4)
    // 115200,8,N,1 - BRG=10
    // 56000,8,N,1 - BRG = 21
    // Generic configurations
    //U2MODEbits.SIDL=0; //Continue operation in idle mode
    U2MODEbits.IREN = 0; // IRDA disabled
    U2MODEbits.RTSMD = 1; // No hardware flow control
    U2MODEbits.UEN = 0; // No hardware flow control
    U2MODEbits.WAKE = 1; // Wake on start bit if in sleep mode
    U2MODEbits.LPBACK = 0; // Loopack mode disabled
    U2MODEbits.ABAUD = 0; // No auto-baud detection
    //U2STAbits.ADM_EN=0; // Disable auto address detection
    U2MODEbits.BRGH = 1;
     U2BRG = BRGVAL; // BAUD Rate Setting for 9600
    //Character format
    U2MODEbits.PDSEL = 0; // 8 data bits, no parity
    U2MODEbits.STSEL = 0; // 1 stop bit
    // Enable TX, RX and UART
    //U2STAbits.URXEN=1; // Enbale UART receiver
    U2STAbits.UTXEN = 1; // Enbale UART transmiter
    //U2MODEbits.UARTEN = 1; // Enable UART
    //U2MODEbits.ON=1; //Enable UART module

//---FOI ALTERADO AQUI----
/*
    __builtin_write_OSCCONL(OSCCON & ~(1 << 6));
    //  U1TX no pino RPn -> 7
    RPOR3bits.RP7R = 0b000011;
    __builtin_write_OSCCONL(OSCCON | (1 << 6));
*/

}

void printInt(int t) {

    while (t > 0) {
        Putchar('0' + t % 10);
        t /= 10;
    }
    Putchar(0x0D); // Print an carriage return (enter)
}