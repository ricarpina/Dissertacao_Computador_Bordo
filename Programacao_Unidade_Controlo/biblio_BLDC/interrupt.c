#include "initMeu.h"
#include "measuresPlate.h"
#include <xc.h>
#include "CAN/easy_can1.h"
extern float v_bat_36[3],v_bat_12[3];
extern volatile unsigned int countTimer;
extern unsigned char enviar_estado_controlador,proc_RTR,ADC_RSLT0_accel[3],ADC_RSLT1_brake[3],alta_temp, controlador_on_off[3],direction[3];
extern int flag, flagI, indexSineTable,  timer_cont;
extern unsigned int motorSpeed[3],id_temp,timer_cont_controlador;
extern float current[3], temp_bat[3], temp_motor[3], lim_temp[3],lim_current[3],current_buck[3];
extern EASY_CAN1_MSG envio, recep;

void __attribute__((__interrupt__, no_auto_psv)) _ADCP0Interrupt(void) {
    ADC_RSLT0_accel[0] = ((ADCBUF1 >> 2)*100) / 255; //*3.3;             // Read AN1 conversion result
    ADC_RSLT1_brake[0] = ((ADCBUF0 >> 2)*100) / 255; //*3.3;             // Read AN0 conversion result

    if(ADC_RSLT1_brake[0]>10)//&& ADC_RSLT0_accel!=0)
    {
        // fazer com que o PWM seja proporcional ao potenciometro do acelerador
        ADC_RSLT0_accel[0]=0;
    }
     /*   char_verificar_enviar(&mens[1], ADC_RSLT0_accel);
        char_verificar_enviar(&mens[0], ADC_RSLT1_brake);*/
    ADSTATbits.P0RDY = 0; // Clear the data is ready in buffer bits
    IFS6bits.ADCP0IF = 0;
}

void ocorreu_int_ext(){
       IFS1bits.INT2IF=0;
    INTCON2bits.INT2EP=!controlador_on_off[0];//1-transicao negativa
}


void init_external_interrupt(){
    TRISDbits.TRISD9=1;
    IFS1bits.INT2IF=0;
    IEC1bits.INT2IE=1;
    IPC7bits.INT2IP=7;  //
    ocorreu_int_ext();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void __attribute__((__interrupt__, auto_psv)) _INT2Interrupt(void) {
    ocorreu_int_ext();
}
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void __attribute__((__interrupt__, auto_psv)) _CNInterrupt(void) {

    // read hall sensors
    // set PWM acording to hall sensors (make a table with the comutation values)
    readHallSens();

    velocity();
    flagI = flag;
    flag++;

    if(ADC_RSLT1_brake[0]>10)//&& ADC_RSLT0_accel!=0)
    {
        // travagem regenerativa
        setPWMacordingToHallSens1(0);
    }   // fazer com que o PWM seja proporcional ao potenciometro do acelerador
    else setPWMacordingToHallSens(0);

    //setDutyCycle(60,HallValue);

    IFS1bits.CNIF = 0; // clear IF
       //     unsigned_int_verificar_enviar(&mens[4], motorSpeed);
}

// Timer 1 interrupt service routine
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void) {
                        unsigned_int_verificar_enviar(&envio, motorSpeed ,0);
    countTimer++;
    //motorSpeed=0;
    //TMR1=0;

    if (countTimer == 500) {
        if ((flagI + 1) == flag) {
            motorSpeed[0] = 0;
        }else{
        }
    }


    //if(countTimer==50){
    //    motorSpeed=0;
    //}


    // Clear Timer 1 interrupt flag
    _T1IF = 0;
}


void __attribute__((__interrupt__, auto_psv)) _T2Interrupt(void){

    float valor=0.0;

    if(indexSineTable > 50)
        indexSineTable=0;

    //valor = (ADC_RSLT0_accel/100)*sineWaveLut[indexSineTable];
    //printf("B%05d\n",valor*100);

    SDC1 = SDC2 = SDC3 = PDC1 = PDC2 = PDC3 = (int) (PTPER * valor);

    indexSineTable++;

    // Clear Timer 1 interrupt flag
    _T2IF = 0;
}/*
void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt(void) {

//float_verificar_enviar(&mens[9], &temp_motor,1);
 //   read_tensao_bat36();
// printf("temp_motor=%.2f \n", temp_motor);
    // printf("temp_bat=%.2f \n", temp_bat);
   //  printf("bat36V=%.2f \n", );
    // printf("bat12V=%.2f \n", read_tensao_bat12());

  _T3IF = 0;
}*/

void __attribute__((__interrupt__, auto_psv)) _T4Interrupt(void) {
   // if(timer_cont_controlador<2)
    //    timer_cont_controlador++;

   if(proc_RTR==0){

     if(timer_cont==0){
        timer_cont++;
            char_verificar_enviar(&envio, ADC_RSLT0_accel ,0);
    }else if(timer_cont==1){
        timer_cont++;
            char_verificar_enviar(&envio, ADC_RSLT1_brake ,0);
    }else if(timer_cont==2){
        timer_cont++;
                float_verificar_enviar(&envio, current ,1);
    }else if(timer_cont==3){
                timer_cont++;

                     v_bat_12[0]=read_tensao_bat12();
     float_verificar_enviar(&envio, v_bat_12,1);
    } else if(timer_cont==4){
                timer_cont++;

                     v_bat_36[0]=read_tensao_bat36();
     float_verificar_enviar(&envio, v_bat_36,1);
    }
       else if(timer_cont==5){
           temp_bat[0]=read_temperature(5);
     float_verificar_enviar(&envio, &temp_bat,1);
                timer_cont++;

    } else if(timer_cont==6){
    temp_motor[0]=read_temperature(2);
     float_verificar_enviar(&envio, &temp_motor,1);
     timer_cont=0;
   }/*else if(timer_cont==7){
             unsigned_int_verificar_enviar(&envio, motorSpeed ,1);
   timer_cont=0;
   }*/
   }else{

     //  enviar_RTR (&recep, 2);
   }
  _T4IF = 0;
}