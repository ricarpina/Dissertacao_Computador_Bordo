#include "can_carro_eletrico_impl.h"
#include "easy_can1.h"
#include <stdint.h>
#include <stdio.h>
#include <xc.h>
extern unsigned char proc_RTR;
extern const unsigned int id_ini;

 void printframe(EASY_CAN1_MSG *msg){
     unsigned int kk;
    printf("Comp: %lu   ",msg->data_length);
    printf("ID: %lu \n",msg->id);
    for(kk=0;kk<msg->data_length;kk++){
            printf("dados[%u]: %d\n",kk,msg->data[kk]);
    }
        printf("RTR: %u \n",msg->Request);

}
void inicializar_parametros_can(EASY_CAN1_MSG *msg){
    	unsigned int i=0, id=id_ini;
                 msg[0].data_length=1;

         msg[0].id=id;
         msg[0].data[0]=1;
     //    easy_can1_send_msg(&msg[0]);
	for(i=1;i<4;i++){
            msg[i].data_length=1;
            msg[i].id=++id;
            msg[i].data[0]=255;
        }
                msg[i].id=++id;
             msg[i].data_length=2;
             msg[i].data[0]=255;
             msg[i].data[1]=255;          // u_ints
         for(i=5;i<12;i++){ // float's
             msg[i].id=++id;
             msg[i].data_length=4;
             msg[i].data[0]=255;
             msg[i].data[1]=255;
             msg[i].data[3]=255;
             msg[i].data[4]=255;
         }
}

void enviar_todas_variaveis(EASY_CAN1_MSG *msg, unsigned char tam){
	unsigned char i=0;
	for(i=1;i<tam;i++){
	easy_can1_send_msg(&msg[i]);
	}
}

void  unsigned_int_verificar_enviar(EASY_CAN1_MSG *temp, unsigned int val[],unsigned char enviar){
    unsigned char tam =sizeof(unsigned int);
      unsigned char i;

   if(enviar||val[0]!=val[1]){
      for(i=0;i<tam;i++){
          temp->data[i]=(unsigned char)((val[0] >> (8*i)) & 0xFF);
      }
      temp->data_length=tam;
      temp->id=(unsigned int)val[2];
           easy_can1_send_msg(temp);
           val[1]=val[0];
        //   printframe(temp);
  }
}


void char_verificar_enviar(EASY_CAN1_MSG *temp, unsigned char val[], unsigned char enviar){
           if(enviar||val[0]!=val[1]){
               temp->id=val[2];
               temp->data_length=sizeof(val[0]);
               temp->data[0]=val[0];
               val[1]=val[0];
               easy_can1_send_msg(temp);
    }
}

void enviar_RTR (EASY_CAN1_MSG *temp,unsigned long id){

    temp->Request=1;
    temp->id=id;
    temp->data_length=0;
    easy_can1_send_msg(temp);
}

void float_verificar_enviar(EASY_CAN1_MSG *temp, float val[], unsigned char enviar){

 union{
    float floating;
    unsigned long int integer;
  } uniao;
  uniao.integer=0;
    unsigned char tam=sizeof(float);
      unsigned char i=0;


   if(!((val[0]<=(val[1]*1.2))&(val[0]>=(val[1]*0.8)))||enviar){
       uniao.floating=val[0];
       temp->data_length=tam;
       temp->id=(unsigned int)val[2];
      for(i=0;i<tam;i++){
        temp->data[i]=(unsigned char)(((uniao.integer)>>(8*i))&0xFF);
      }
     easy_can1_send_msg(temp);
       val[1]=val[0];
}
}

void inicializar_vars_can(unsigned char controlador[] ,unsigned char acelarador[], unsigned char travao[],unsigned char direction[], int RPM[],float current[], float current_buck[], float lim_current[],float v_bat_36[], float v_bat_12[],float temp_motor[], float temp_bat[], float lim_temp[]){
    	unsigned int id=id_ini;
        controlador[2]=id;
        acelarador[2]=++id;
        travao[2]=++id;
        direction[2]=++id;
        RPM[2]=++id;
        current[2]=(float)++id;
    current_buck[2]=(float)++id;
     lim_current[2]=(float)++id;
    v_bat_36[2]=(float)++id;
    v_bat_12[2]=(float)++id;
    temp_motor[2]=(float)++id;
    temp_bat[2]=(float)++id;
    lim_temp[2]=(float)++id;
}
        void atender_RTR(EASY_CAN1_MSG *temp,unsigned int id_temp, unsigned char on_off[],unsigned char acelarador[], unsigned char travao[],unsigned char direction[], unsigned int RPM[],float current[], float current_buck[], float lim_current[],float v_bat_36[], float v_bat_12[],float temp_motor[], float temp_bat[], float lim_temp[]){
         //   enviar_RTR(temp, id_temp);

            if (((unsigned int)on_off[2])==id_temp){

            char_verificar_enviar(temp, &on_off[0],1);
                }
            else if (((unsigned int)acelarador[2])==id_temp){

            char_verificar_enviar(temp, &acelarador[0],1);
                }

       else if (((unsigned int)travao[2])==id_temp){
            char_verificar_enviar(temp,&travao[0],1);

       }

        else if(((unsigned int)direction[2])==id_temp){
            char_verificar_enviar(temp, &direction[0],1);

        }
        else if(((unsigned int)RPM[2])==id_temp){
            unsigned_int_verificar_enviar(temp, &RPM[0],1);
        }

        else if(((unsigned int)current[2])==id_temp){
           float_verificar_enviar(temp, &current[0],1);
        }

        else if(((unsigned int)current_buck[2])==id_temp){
           float_verificar_enviar(temp, &current_buck[0],1);
        }
          else if(((unsigned int)lim_current[2])==id_temp){
               float_verificar_enviar(temp, &lim_current[0],1);
         }

        else if(((unsigned int)v_bat_36[2])==id_temp){
           float_verificar_enviar(temp, v_bat_36,1);
        }
        else if(((unsigned int)v_bat_12[2])==id_temp){
           float_verificar_enviar(temp, &v_bat_12[0],1);
        }
        else if(((unsigned int)temp_motor[2])==id_temp){
           float_verificar_enviar(temp, &temp_motor[0],1);
        }
        else if(((unsigned int)temp_bat[2])==id_temp){
           float_verificar_enviar(temp, &temp_bat[0],1);
        }
        else if(((unsigned int)lim_temp[2])==id_temp){
           float_verificar_enviar(temp, &lim_temp[0],1);
        }else{
        }

        }