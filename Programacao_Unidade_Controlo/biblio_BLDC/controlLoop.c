#include <p33FJ64GS606.h>

//#include "motor_control.h"
//#include "initMeu.h"
//#include <stdint.h>
//#include <delay.h>
//#include <libpic30.h>
#include "controlLoop.h"
#include<stdio.h>


// global variables
extern float meanCurrent, u;
extern unsigned char ADC_RSLT0_accel[3], ADC_RSLT1_brake[3];;
extern unsigned int count;
extern volatile unsigned int countTimer;
extern int HallValue,oldHallValue;
// flag que me diz a direcção do motor
extern unsigned char direction[3]; // 1 para CCW e 0 para CW
extern unsigned int motorSpeed[3];


volatile int i_anterior;
volatile float erro_anterior;



// speed -> é a velocidade actual do motor
// setPoint -> é a velocidade desejada para o motor

void PID(float speed,int setPoint)
{
	float erro_actual;
        int val;
	float Kp = 0.7;
	float Ki=0.21;
	float Td=0.43;
	//float h = 2.0/(50.0);
	float p=0.0,i=0.0,d=0.0, Ti=0.0;


        //val = readADC10(2);
        //val = ((val>>2)*100)/255;


        //Kp=(float)ADC_RSLT0_accel/10;
        //Ki=(float)ADC_RSLT1_brake/100;
        //Td=(float)val/100;
        
        //printf("Kp: %f  ",Kp);
        //printf("Ki: %f  ",Ki);
        //printf("Td: %f  ",Td);


        Ti = 1/Ki;


	// Calcula o erro actual
        erro_actual = (float) ((setPoint - speed)/40);
	
	// Inicialmente, testar so compensador proporcional
	// Termo proporcional
	p = Kp*erro_actual;

	// Para des-comentar depois

	// Termo integral
	i = i_anterior + 1*erro_actual/Ti;


	// Termo derivativo
	d = Td*(erro_actual-erro_anterior)/1;

	//Actualiza i e erro
	erro_anterior = erro_actual;
	i_anterior = i;


	// Soma as contribuicoes dos varios compensadores ( P, I, D)
	u = (p+i+d);

        //printf("U: %f  ",u);
        //printf("Motor Speed: %d\n",motorSpeed);
        //printf("B%05d\n",motorSpeed);

        // actuar na velocidade do motor
            //setPWMacordingToHallSens();
            //viraMotor( u);
}
