/* 
 * File:   motor_control.h
 * Author: Miguel
 *
 * Created on 18 de Junho de 2013, 14:29
 */

void readHallSens(void);
void read_hall_pos(unsigned char* var_aux);
void setPWMacordingToHallSens (int);
void setPWMacordingToHallSens1 (int);

int calcDutyAcordingToAcell_brake (void);
void setDutyCycle(unsigned char duty, unsigned char phase);

void setDutyCycle2(unsigned char duty, unsigned char phase);
void stopMotor(void);
void startMotor(void);
void motor_direction(void);


void delay_us( unsigned int delayUs_count );

void calcDutyAcordingToSineWave (void);
void changeT2Freq(void);

