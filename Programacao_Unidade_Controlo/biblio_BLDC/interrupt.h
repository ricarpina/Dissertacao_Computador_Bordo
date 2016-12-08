void ocorreu_int_ext();
void init_external_interrupt();

void __attribute__((__interrupt__,no_auto_psv)) _ADCP0Interrupt (void);
void __attribute__((__interrupt__, no_auto_psv)) _CNInterrupt(void);
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void);
void __attribute__((__interrupt__, auto_psv)) _T2Interrupt(void);
void __attribute__((__interrupt__, auto_psv)) _T3Interrupt(void);
void __attribute__((__interrupt__, auto_psv)) _T4Interrupt(void);
void __attribute__((__interrupt__, auto_psv)) _INT2Interrupt(void);