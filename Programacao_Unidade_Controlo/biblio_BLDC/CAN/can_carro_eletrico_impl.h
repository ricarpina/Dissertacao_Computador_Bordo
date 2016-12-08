#include "easy_can1.h"


 void printframe(EASY_CAN1_MSG *msg);
void inicializar_parametros_can(EASY_CAN1_MSG *msg);

void enviar_todas_variaveis(EASY_CAN1_MSG *msg, unsigned char tam);

void unsigned_int_verificar_enviar(EASY_CAN1_MSG *temp,  unsigned int val[], unsigned char enviar);

void char_verificar_enviar(EASY_CAN1_MSG *temp, unsigned char val[], unsigned char enviar);

void float_verificar_enviar(EASY_CAN1_MSG *temp, float val[], unsigned char enviar);

void inicializar_vars_can(unsigned char controlador[], unsigned char acelarador[], unsigned char travao[],unsigned char direction[], int RPM[],float current[], float current_buck[], float lim_current[],float v_bat_36[], float v_bat_12[],float temp_motor[], float temp_bat[], float lim_temp[]);

void atender_RTR(EASY_CAN1_MSG *temp,unsigned int id_temp,unsigned char on_off[],unsigned char acelarador[], unsigned char travao[],unsigned char direction[], unsigned int RPM[],float current[], float current_buck[], float lim_current[],float v_bat_36[], float v_bat_12[],float temp_motor[], float temp_bat[], float lim_temp[]);
