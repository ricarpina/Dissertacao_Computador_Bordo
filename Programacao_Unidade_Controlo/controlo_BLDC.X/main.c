#include <p33FJ64GS606.h>
#include <stdint.h>
#include <stdio.h>
#include "../biblio_BLDC/initMeu.h"
#include "../biblio_BLDC/CAN/easy_can1.h"
#include "../biblio_BLDC/CAN/can_carro_eletrico_impl.h"

//#include "../biblio_BLDC/interrupt.h"
#include "../biblio_BLDC/motor_control.h"
#include "../biblio_BLDC/measuresPlate.h"
#include "../biblio_BLDC/controlLoop.h"

_FOSCSEL (FNOSC_PRI & IESO_OFF);
_FOSC (POSCMD_HS & FCKSM_CSECMD & OSCIOFNC_OFF);
_FWDT (FWDTEN_OFF);

int __C30_UART = 2;
EASY_CAN1_MSG envio, recep;


// NOTA: é necessario ter em atenção a ligação dos sensores de Hall! ligar nas portas correctas!

extern const unsigned long int FCY;
extern const unsigned long int taxa_can;

// global variables
extern float meanCurrent,u;
extern unsigned char ADC_RSLT0_accel[3], ADC_RSLT1_brake[3];
extern unsigned  int count;
unsigned int timer_cont=0,timer_cont_controlador=0;;
extern volatile unsigned int countTimer;

extern int HallValue;
// flag que me diz a direcção do motor
unsigned char controlador_on_off[3],alta_temp=0, proc_RTR=0,enviar_estado_controlador=0;
extern unsigned char direction[3]; // 1 para CCW e 0 para CW
extern unsigned int motorSpeed[3];
const unsigned int id_ini=0x0;
unsigned int  id_temp=0;
float current[3], current_buck[3], lim_current[3], v_bat_36[3], v_bat_12[3], temp_motor[3], temp_bat[3],lim_temp[3];

int main(void){

    lim_current[0] = 30.0;
    lim_current[1] = 0.0;
    lim_temp[0] = 100.0;
    lim_temp[1] = 0.0;

 int oldirection = 0;
    float val = 0.0;
    int a, b = 0;
    v_bat_12[0]=12.0;
    current_buck[0]=0.0;
    /*ID's CAN
     15=controlador ON/OFF
     16=acelerador
     17= travão
     18=sentido de rotação (ON/OFF);
     19=RPM
     1A=Corrente motor com sinal (float)
     1B=corrente buck (float)
     1C=Limite I Motor[A]
     1D=tensão bat 36; (float)
     1E=tensão bat 12V; (float)
     1F=temperatura motor (float)
     20=temperatura bateria (float)
     21=limite temperatura (float);

     0=controlador ON/OFF
     1=acelerador
     2= travão
     3=sentido de rotação (ON/OFF);
     4=RPM
     5=Corrente motor com sinal (float)
     6=corrente buck (float)
     7=Limite I Motor[A]
     8=tensão bat 36; (float)
     9=tensão bat 12V; (float)
     A=temperatura motor (float)
     B=temperatura bateria (float)
     C=limite temperatura (float);
     */
   //  init_external_interrupt();
     ocorreu_int_ext();
    InitMCPWM();
    UART2_Config();

    //initSPI ();
    InitADC10();

    setupInputCN();
    inits();
    startMotor();
    readHallSens();
    initTimer1();
    //initTimer2();
    initTimer3();
    initTimer4();


    envio.Request = 0;

    recep.Request=1;
    easy_can1_init(FCY/taxa_can, 1, 0); //razao, nº do pino do porto D que serve de enable dp transcvr e o valor a que está ligado
 inicializar_vars_can(controlador_on_off,ADC_RSLT0_accel, ADC_RSLT1_brake,direction, motorSpeed, current,  current_buck, lim_current,v_bat_36, v_bat_12, temp_motor, temp_bat, lim_temp);
 


    //Bldc_FillSineLut();
    TRISDbits.TRISD8=0;
     PORTDbits.RD8=1;
    TRISDbits.TRISD9=1;

    while (1){
        if(controlador_on_off[0]!=PORTDbits.RD9){
            proc_RTR=2;
                        PORTDbits.RD1=0;
                     controlador_on_off[0]=PORTDbits.RD9;
                     char_verificar_enviar(&envio, controlador_on_off,1);
                     
                   //  for(timer_cont_controlador=0;timer_cont_controlador<2;timer_cont_controlador++){
                          while(_T3IF==0);
                              _T3IF=0;
                             current[0]=0.0;
                float_verificar_enviar(&envio, current,1);
                     while(_T3IF==0);
                              _T3IF=0;

           PORTDbits.RD0 = controlador_on_off[0];
           PORTDbits.RD1=!controlador_on_off[0];
            /*if(controlador_on_off[0]==1){
             PORTDbits.RD8=0;
                char_verificar_enviar(&envio, controlador_on_off,1);
        }
           */
           proc_RTR=0;
        }
           motor_direction();
      //  Putchar('a');
      //   printf("Travao: %d\n",ADC_RSLT1_brake);
   //     printf("Acelerador: %d\n",ADC_RSLT0_accel);
    //   printf("Motor Speed: %d\n",motorSpeed);
   //    printf("FCY: %lu\n",FCY);
        //printf("B%05d\n",motorSpeed);
        //printf("HallValue: %d\n",HallValue);
  //      printf("u_l_int: %d\n",sizeof(unsigned long int));
       // printf("float: %d\n",sizeof(float));
      //  printf("char: %d\n",sizeof(char));
     //   printf("current: %.2f\n",current);
        //printf("u: %f\n",u);
       // printf("Temperaratura=: %f\n",temp_motor);
        if (ADC_RSLT1_brake[0]>10) {
            setPWMacordingToHallSens1(0);
        }

        if (motorSpeed[0] == 0) {
            setPWMacordingToHallSens(0);
        }

        //if(countTimer % 100 == 0){
        //    PID(motorSpeed, ADC_RSLT0_accel*40);
        //}

        // testar os sensores de hall
        current[0] = readHallSense50()*1.0;
      //  temp_motor = read_temperature();
        
        // protecção contra sobre-corrente
        if (current[0]>lim_current[0]&!controlador_on_off[0]){
            //fazer o set do PWM para zero
            stopMotor();
         }
         else if (current[0]<lim_current[0]&controlador_on_off[0]){
             startMotor();
         }
        

     // atualizar_mens_can(mens, &ADC_RSLT0_accel, &ADC_RSLT1_brake, &direction, &motorSpeed, &current, &current_buck, &v_bat_36, &v_bat_12, &temp_motor, &temp_bat);

        if (easy_can1_recv_msg(&recep)==1){
            if(recep.Request==1){
                PORTDbits.RD8=!PORTDbits.RD8;
               printf("Pedido: \n");
        printframe(&recep);
              // if(recep.Request==0)
               recep.Request=0;
               id_temp=recep.id;
         // timer_cont=id_temp;
               proc_RTR =1;

                atender_RTR(&recep,id_temp,controlador_on_off,ADC_RSLT0_accel, ADC_RSLT1_brake,direction, motorSpeed, current,  current_buck,lim_current, v_bat_36, v_bat_12, temp_motor, temp_bat, lim_temp);
                if(id_temp==(unsigned int)lim_temp[2])
                    proc_RTR=0;
                          //proc_RTR =0;
            }
      }
     //   unsigned_int_verificar_enviar(&mens[4], motorSpeed);

    }
}