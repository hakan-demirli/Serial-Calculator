#ifndef MAIN_H
#define	MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>

#include "config.h"

#define _XTAL_FREQ 20000000

#define	BAUD	    19200   //500=0f9f
#define SPBRGx      (((_XTAL_FREQ/4)/BAUD)-1)
#define SPBRG_LO    (unsigned char)  SPBRGx
#define SPBRG_HI    (unsigned char) (SPBRGx/256)

#define TMR1_TIMEOUT     0.001
#define T10MS_TIMEOUT    0.01
#define T100MS_TIMEOUT   0.1
#define BUZZER_DUR       (unsigned char) (1/TMR1_TIMEOUT)
#define DOUBLEKEY_DUR    (unsigned char) (3/T100MS_TIMEOUT)
#define ALTERNATEKEY_DUR (unsigned char) (3/T100MS_TIMEOUT)


//_______________________________________________________

#define  BTN_PIN     PORTAbits.RA0
#define  TRIS_A         0b11111111


#define  DB7_PIN     PORTBbits.RB7
#define  DB6_PIN     PORTBbits.RB6       //O
#define  DB5_PIN     PORTBbits.RB5       //O
#define  DB4_PIN     PORTBbits.RB4
#define  RW_PIN      PORTBbits.RB2
#define  RS_PIN      PORTBbits.RB1
#define  E_PIN       PORTBbits.RB0
#define  TRIS_B          0b00000000

#define  RO1_PIN PORTDbits.RD0
#define  RO2_PIN PORTDbits.RD1
#define  RO3_PIN PORTDbits.RD2
#define  RO4_PIN PORTDbits.RD3
#define  L1_PIN  PORTDbits.RD4
#define  L2_PIN  PORTDbits.RD5
#define  L3_PIN  PORTDbits.RD6
#define  L4_PIN  PORTDbits.RD7
#define  TRIS_D          0b11110000

#define  LED_PIN  PORTCbits.RC0
#define  LED1_PIN PORTCbits.RC1
#define  TRIS_C          0b11111110

#define  BUZZER_PIN PORTCbits.RC2
#define  OFFSET_PIN PORTCbits.RC6
//---------------------------------------

//---------------------------------------


#endif	/* MAIN_H */



