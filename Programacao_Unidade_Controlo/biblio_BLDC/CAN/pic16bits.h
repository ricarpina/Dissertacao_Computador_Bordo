#ifndef __MICRO16_H__
#define __MICRO16_H__

#if !defined (__XC16__)
#error "Compiler not supported/tested."
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__PIC24F__)
#include "p24Fxxxx.h"
#elif defined(__dsPIC33F__)
//#include <p33FJ128GP802.h>
#include "p33Fxxxx.h"
#else
#error "Unknown target micro controller"
#endif

#ifdef __cplusplus
}
#endif

#endif
