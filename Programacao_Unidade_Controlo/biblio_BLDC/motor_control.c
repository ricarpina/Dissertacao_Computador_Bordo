#include <p33FJ64GS606.h>

#include "motor_control.h"
#include "initMeu.h"
#include <stdint.h>
//#include <delay.h>
#include <libpic30.h>
#include<stdio.h>
#include "CAN/easy_can1.h"

// global variables
extern float meanCurrent, u;
extern unsigned char proc_RTR, ADC_RSLT0_accel[3], ADC_RSLT1_brake[3];
unsigned int count;
extern volatile unsigned int countTimer;
extern int HallValue,oldHallValue;
 // flag que me diz a direcção do motor
extern unsigned char direction[3]; // 1 para CCW e 0 para CW
unsigned int temp_count;
extern int motorSpeed[3];
extern EASY_CAN1_MSG envio;

//extern float sineWaveLut;



void delay_us( unsigned int delayUs_count )
{
	temp_count = delayUs_count +1;
	asm volatile("outer1: dec _temp_count");
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done1");
	asm volatile("do #1500, inner1" );
	asm volatile("nop");
	asm volatile("inner1: nop");
	asm volatile("bra outer1");
	asm volatile("done1:");
}




// ********** function that reads hall sensors *********************************
void readHallSens(void)
{
    unsigned char old=0, aux=0;

    do{
    //oldHallValue = HallValue;
    // read hall position sensors
     read_hall_pos(&aux);
    

    __delay32(108);

    old = aux;
    
// read hall position sensors
     read_hall_pos(&aux);

    /*
    HallValue = (int)PORTBbits.RB15;
    HallValue = (((int)PORTBbits.RB5) << 1) | HallValue;
    HallValue = (((int)PORTBbits.RB6) << 2) | HallValue;
    HallValue = HallValue & 0x0007;
    */

    }while(old!=aux);

        HallValue=aux;
}
void read_hall_pos(unsigned char* var_aux){

    *var_aux = (unsigned char)PORTGbits.RG8;
    *var_aux = (((unsigned )PORTGbits.RG6) << 1) | *var_aux;
    *var_aux = (((unsigned char)PORTGbits.RG7) << 2) | *var_aux;
    *var_aux = *var_aux & 0x0007;

}

void setPWMacordingToHallSens(int close_loop) {

    unsigned char duty2 = 0;

    if(close_loop == 1){
        duty2 = u;
    }
    else if (close_loop == 0){
        duty2 = ADC_RSLT0_accel[0];
//        sineWaveLut[configNUM_SINE_LUT_ENTRIES] = {0};
    }

    // limitar o duty-cycle nos respectivos valores
    if (duty2 > 100){
        duty2 = 100;
    } else if (duty2 < 0) {
        duty2 = 0;
    }


    if (direction[0] == 0) // CW direction
    {
            setDutyCycle2(duty2, HallValue);
    }else if(direction[0] == 1){
            setDutyCycle2(duty2, 7-HallValue);
    }
    
}



void setPWMacordingToHallSens1(int close_loop) {

    unsigned char duty2 = 0;

    if(close_loop == 1){
        duty2 = u;
    }
    else if (close_loop == 0){
        duty2 = ADC_RSLT1_brake[0];
//        sineWaveLut[configNUM_SINE_LUT_ENTRIES] = {0};
    }

    // limitar o duty-cycle nos respectivos valores
    if (duty2 > 100){
        duty2 = 100;
    } else if (duty2 < 0) {
        duty2 = 0;
    }
    if (direction[0] == 0) // CW direction
    {
            setDutyCycle(duty2, HallValue);
    }else if(direction[0] == 1){
            setDutyCycle(duty2, 7-HallValue);
    }

}

void setDutyCycle(unsigned char duty, unsigned char phase) {

    float dutyf;

    dutyf = (float) (duty / 100.0);
    __delay32(407);

    if (phase == 1) {

        //IOCON2bits.PENL = 0;
        //IOCON3bits.PENH = 0;
        IOCON1bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENH = 0;
        IOCON2bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENL = 0;
        IOCON2bits.PENL = 0;
        __delay32(108);
        IOCON1bits.PENL = 1;

    } else if (phase == 2) {
        // PWM Output pin control assigned to PWM generator

        //IOCON2bits.PENL = 0;
        //IOCON3bits.PENH = 0;
        IOCON1bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENH = 0;
        IOCON2bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENL = 0;
        IOCON2bits.PENL = 0;
        __delay32(108);
        IOCON1bits.PENL = 1;

    } else if (phase == 3) {

        //IOCON2bits.PENL = 0;
        //IOCON3bits.PENH = 0;
        IOCON1bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENL = 0;
        IOCON2bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENH = 0;
        IOCON1bits.PENL = 0;
        __delay32(108);
        IOCON2bits.PENL = 1;

    } else if (phase == 4) {

        //IOCON2bits.PENL = 0;
        //IOCON3bits.PENH = 0;
        IOCON1bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENL = 0;
        IOCON2bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENH = 0;
        IOCON1bits.PENL = 0;
        __delay32(108);
        IOCON2bits.PENL = 1;


    } else if (phase == 5) {

        //IOCON2bits.PENL = 0;
        //IOCON3bits.PENH = 0;
        IOCON1bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON2bits.PENL = 0;
        IOCON2bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENH = 0;
        IOCON1bits.PENL = 0;
        __delay32(108);
        IOCON3bits.PENL = 1;

    } else if (phase == 6) {

        //IOCON2bits.PENL = 0;
        //IOCON3bits.PENH = 0;
        IOCON1bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON2bits.PENL = 0;
        IOCON2bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENH = 0;
        IOCON1bits.PENL = 0;
        __delay32(108);
        IOCON3bits.PENL = 1;

    }
            __delay32(108);
            SDC1 = SDC2 = SDC3 = PDC1 = PDC2 = PDC3 = (int) (PTPER * dutyf);
}


int calcDutyAcordingToAcell_brake (void)
{
    int x = 0;

    // se nao estivermos a travar e estivermos a acelerar
    if((ADC_RSLT1_brake[0]>=0 && ADC_RSLT1_brake[0] <= 0.3) )//&& ADC_RSLT0_accel!=0)
    {
        // fazer com que o PWM seja proporcional ao potenciometro do acelerador
        x = ADC_RSLT0_accel[0];
    }
    else x = ADC_RSLT1_brake[0];

    
    return x;
}

void setDutyCycle2(unsigned char duty, unsigned char phase) {

     //  printf("duty: %d\n",duty);

    /*IOCON1bits.PENH = 0;    // PWM Output pin control assigned to PWM generator
     IOCON1bits.PENL = 0;
     IOCON2bits.PENH = 0;    // PWM Output pin control assigned to PWM generator
     IOCON2bits.PENL = 0;
     IOCON3bits.PENH = 0;    // PWM Output pin control assigned to PWM generator
     IOCON3bits.PENL = 0;*/


    float dutyf;

    dutyf = (float) (duty / 100.0);
    __delay32(407);

    if (phase == 1) {

        //IOCON2bits.PENL = 0;
        //IOCON3bits.PENH = 0;
        IOCON1bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON1bits.PENL = 0;
        IOCON2bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENL = 0;
        __delay32(108);
        IOCON2bits.PENL = 1;
        IOCON3bits.PENH = 1;

    } else if (phase == 2) {
        // PWM Output pin control assigned to PWM generator

        //IOCON1bits.PENL = 0;
        //IOCON2bits.PENH = 0;
        IOCON1bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON2bits.PENL = 0;
        IOCON3bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENL = 0;
        __delay32(108);
        IOCON1bits.PENL = 1;
        IOCON2bits.PENH = 1;

    } else if (phase == 3) {

        //IOCON3bits.PENH = 0;
        //IOCON1bits.PENL = 0;
        IOCON1bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON2bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON2bits.PENL = 0;
        IOCON3bits.PENL = 0;
        __delay32(108);
        IOCON3bits.PENH = 1;
        IOCON1bits.PENL = 1;

    } else if (phase == 4) {

        //IOCON1bits.PENH = 0;
        //IOCON3bits.PENL = 0;
        IOCON1bits.PENL = 0;
        IOCON2bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON2bits.PENL = 0;
        IOCON3bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        __delay32(108);
        IOCON1bits.PENH = 1;
        IOCON3bits.PENL = 1;

    } else if (phase == 5) {

        //IOCON1bits.PENH = 0;
        //IOCON2bits.PENL = 0;
        IOCON1bits.PENL = 0;
        IOCON2bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON3bits.PENL = 0;
        __delay32(40);
        IOCON1bits.PENH = 1;
        IOCON2bits.PENL = 1;

    } else if (phase == 6) {

        //IOCON3bits.PENL = 0;
        //IOCON2bits.PENH = 0;
        IOCON1bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        IOCON1bits.PENL = 0;
        IOCON2bits.PENL = 0;
        IOCON3bits.PENH = 0; // PWM Output pin control assigned to PWM generator
        __delay32(108);
        IOCON3bits.PENL = 1;
        IOCON2bits.PENH = 1;

    }

            __delay32(108);

        SDC1 = SDC2 = SDC3 = PDC1 = PDC2 = PDC3 = (int) (PTPER * dutyf);
}

void velocity (void){

    //int aux=0;
    float temp;

    count++;

           if(count==138){                    // 24 porque o motor tem 12 polos -> 24 = uma volta
                                         // 56 porque o motor tem 28 polos -> 56 = uma volta
        temp = ((float)TMR1*0.001)/(float)PR1;
        temp = (float)(0.001*countTimer) +  temp;

        meanCurrent = 1/(temp/12.5);     // freq desejada para o timer 2
        changeT2Freq();

        temp = (1/temp)*60;

        // 1 hz = 60 rmp;
        // 1 rpm = 1/60 hz;
        motorSpeed[0] = (unsigned int)(temp*5.792);   //velocidade em RPM

      //  motorSpeed[0] = (unsigned int)(temp*11.2);   //velocidade em RPM
       //  proc_RTR=0;
      //  proc_RTR=1;

        countTimer = 0;
        count=0;
        TMR1=0;
    }


    /*
    long int aux = 0;

    aux = (((TMR1+(count*58))*1000)/58);      // calcula o tempo entre duas interrupçoes

    aux = aux*48;                   // calcula o tempo que demora cada volta
                                    // 48 = 6 valores para os sensores de Hall * 8 polos
    aux=(1/aux);                    // calcula a frequencia com que o motor da uma volta
    aux = aux*60;                   // calcula as RPM (rotaçoes por minuto) do motor

    motorSpeed = aux;
    */


}


void changeT2Freq(void){

    T2CONbits.TON = 0; // Turn on Timer 2

    PR2 = (int)((1/meanCurrent)/(8*(1/3685000)));          // Set Timer 2 to the respective frequency
    T2CONbits.TON = 1; // Turn on Timer 2
}


void stopMotor(void){
    //RD0 it's the port of the control signal that makes the PWM's on of off
    PORTDbits.RD0 = 0;      // disable PWM's
}

void startMotor(void){
    //RD0 it's the port of the control signal that makes the PWM's on of off
    PORTDbits.RD0 = 1;      // able PWM's
}

void motor_direction(void){
    // see if the user want to move CW or CCW
    // 1 para CW e 0 para CCW
    direction[0] = PORTBbits.RB8;
    char_verificar_enviar(&envio, direction,0);

}


int isMotorStopped(void){
    return (oldHallValue == HallValue);
}



void calcDutyAcordingToSineWave (void){

   // SDC1 = SDC2 = SDC3 = PDC1 = PDC2 = PDC3 = (int) (PTPER * dutyf);

}






