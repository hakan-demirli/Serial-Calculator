#ifndef _CONFIG_H
#define _CONFIG_H

//     #pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
//     #pragma config CPUDIV   = OSC1_PLL2
//     #pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
//#pragma config FOSC     = INTOSCIO_EC
#pragma config FOSC     = XT_XT
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = ON
#pragma config BOR      = ON
#pragma config BORV     = 3        //0 TO 3
#pragma config VREGEN   = OFF      //USB Voltage Regulator
#pragma config WDT      = OFF
//#pragma config WDTPS    = 32768
#pragma config WDTPS    = 0x02//50
#pragma config MCLRE    = OFF
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
//      #pragma config CCP2MX   = ON
#pragma config STVREN   = ON
#pragma config LVP      = OFF
//      #pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
#pragma config XINST    = OFF       // Extended Instruction Set
#pragma config CP0      = ON
#pragma config CP1      = ON
//      #pragma config CP2      = OFF
//      #pragma config CP3      = OFF
#pragma config CPB      = OFF
//      #pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
//      #pragma config WRT2     = OFF
//      #pragma config WRT3     = OFF
#pragma config WRTB     = OFF       // Boot Block Write Protection
#pragma config WRTC     = OFF
//      #pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
//      #pragma config EBTR2    = OFF
//      #pragma config EBTR3    = OFF
#pragma config EBTRB    = OFF




#endif

