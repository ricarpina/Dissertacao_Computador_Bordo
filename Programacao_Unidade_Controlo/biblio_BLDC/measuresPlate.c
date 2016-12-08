#include <p33FJ64GS606.h>
#include "measuresPlate.h"
#include "initMeu.h"
#include "motor_control.h"
#include "outras_funcoes.h"
#include<stdio.h>

// global variables
extern float meanCurrent,u;
extern unsigned char ADC_RSLT0_accel[3];
extern unsigned char ADC_RSLT1_brake[3];
extern unsigned int count, countTimer;
extern int HallValue,oldHallValue;
 // flag que me diz a direcção do motor
extern unsigned char direction[3]; // 1 para CCW e 0 para CW
//extern unsigned int temp_count;
extern unsigned int motorSpeed[3];

float readHallSense50_filt(void){

    unsigned int val=readADC10(2);
    float value=0.0;
    value = (float)((val*3.3)/1023);
   // printf("Tensao: %.4f\n",value);

    // o sensor dá 25mV/A e está centrado em 2,5V->1,36627907 devido ao divisor resistivo
  value = value-2.5774;
  //  printf("%.4f\n",value);

    return (value/0.0125);
}
float readHallSense50 (void){

    unsigned char i=0, j=0, iter=4, rep=2;
    unsigned int medidas[iter];
    unsigned int val=0;
    float value=0.0;

    for(j=0; j<rep; j++){

    for(i=0; i<iter; i++){
        medidas[i] = readADC10(3);
       }
    medidas[min_array(medidas, iter)]=0;
    medidas[max_array(medidas, iter)]=0;

    val += somatorio_array(medidas, iter)/(rep*(iter-2));
    }
   // val = val-200;  // calibração -> por defeito o sensor dá 200 (de 0 até 1023) a mais

    value = (float)((val*3.3)/1023);
  //  printf("Tensao: %.4f\n",value);
    value=2.56-value;
    // o sensor dá 25mV/A e está centrado em 2,5V->1,36627907 devido ao divisor resistivo
//  value = value-2.74;
   //  printf("Tensao: %.4f\n",value);
  //  return 0.0;
    return (value/0.0125);
}

float readHallSense20 (void){

    unsigned int val;
    float value;
    unsigned char i=0;

    for(i=0; i<20; i++){
        val = readADC10(3)*0.05;
    }

    value = (float)((val/1023)*3.3);

    // o sensor dá 25mV/A e está centrado em 2,5V->1,67 devido ao divisor resistivo
    value = value - 1,67;

    return (value/0.025);
}

float read_temperature(unsigned char cn){

    unsigned long int val=0;
    float value;
    unsigned char i=0;

    for(i=0; i<10; i++){
        val += readADC10(cn); //5
    }
    val=val/i;

    value = ((float)(val)/(1023.0))*3.3;
    value *= 100.0;
      // printf("value=%.2f\n",value);

       //value-=18.0;
      // if (cn==2)
       //    return 0.0;
    return value;
}

float read_tensao_bat12(){

     unsigned long int val=0, A=5600, B=100;
    float value;
    unsigned char i=0;

    for(i=0; i<10; i++){
        val += readADC10(13);
    }
    val=val/i;

    float abc=4.0*(((float)B*28000.0/((float)B+28000.0))/((float)A+((float)B*28000.0/((float)B+28000.0))));
    value =((float)(val)/(1023.0))*3.3;
  //  value=2.80-value;
    value=2.57-value;
     //  printf("adc=%.2f\n",value);


    value/=abc;
    //   printf("value=%.2f\n",value);
    return value;
}

float read_tensao_bat36(){

     unsigned long long int val=0, A=15800, B=100;
    float value;
    unsigned char i=0;

    for(i=0; i<10; i++){
        val += readADC10(12);
    }   
    val=val/i;
    float abc=4.0*(((float)B*28000.0/((float)B+28000.0))/((float)A+((float)B*28000.0/((float)B+28000.0))));
   // printf("value=%.5f\n",abc);
    //value = 2.80-((float)(val)/(1023.0))*3.3;
    value = 2.640-((float)(val)/(1023.0))*3.3;
  //     printf("value_36=%.2f\n",value);

    // printf("value=%.2f\n",((float)((B*28000/(B+28000))/(A+(B*28000/(B+28000))))*8.0));
    value/=abc;
   // printf("value=%.2f\n",value);

    return value;
}