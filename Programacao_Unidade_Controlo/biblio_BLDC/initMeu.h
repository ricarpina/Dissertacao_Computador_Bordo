void delay(int n);
void InitMCPWM(void);
unsigned int readADC10 (int);
void InitADC10(void);

void velocity (void);
void initTimer1 (void);
void initTimer2(void);
void initTimer3(void);
void initTimer4(void);

void setupInputCN(void);
int cnInterruptOcurred(void);

extern void UART1_Config(void);
extern void UART2_Config(void);

extern unsigned char Readchar(void);
extern void Putchar(unsigned char c);
extern void sendChar(char c);
extern void inits(void);
extern void printInt(int t);

