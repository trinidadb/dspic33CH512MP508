/*
 * File:   main.c
 * Author: Trini
 *
 * Created on 10 de febrero de 2022, 21:12
 */

#define FCY 4000000UL

#include <xc.h>
#include "config.h"
#include "../../dsPIC33C/h/p33CH512MP508.h"
#include <libpic30.h>
    /* 16-bit peripheral library for access to delay_ms() function.
     * __delay_ms() and __delay_us() are defined as macros. They depend on a user-supplied definition of FCY. 
     * For example, to declare FCY for a 10 MHz instruction rate:
     * #define FCY 10000000UL
     */


int main(void) {
    WDTCONLbits.ON   = 0;  //Disables WDT if it was enables by software
    ANSELE = 0;            // Port E as digital
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE7 = 1;
    
    INTCON1bits.NSTDIS = 0;       //Disables nestling interrupts 
    CNCONEbits.ON =1;             //To enable the Change Notification feature for the port, the ON bit (CNCONx[15]) must be set.
    CNCONEbits.CNSTYLE = 1;
    CNEN0Ebits.CNEN0E7 = 0;       // To detect negative edge only
    CNEN1Ebits.CNEN1E7 = 1;
       
    // BE VERY AWARE WITH THE FOLLOWING TWO BITS. PORTE E is equivalent to C4/S4, PORT A is equivalent to C0/S0
    // ALSO THE ISR NAME CHANGE DEPENDING ON WHICH PORT. _CNAInterrupt,...,_CNEInterrupt,...
    // TAKE A LOOK AT TABLE 3.25 in "dsPIC33CH512MP508 Family Data Sheet"
    IEC4bits.CNEIE  = 1;          //Enable CN interrupts in PORT E (C4)
    IPC19bits.CNEIP = 1;
    IFS4bits.CNEIF = 0;           //Put down flag
    // If I would have wanted to Set Interrupt on change on PORT C
    // IEC1bits.CNCIE = 1;
    // IFS1bits.CNCIF = 0;
    
    INTCON2bits.GIE = 1;

    while(1){
    }
    return 0;
}

void __attribute__((__interrupt__,no_auto_psv)) _CNEInterrupt(void)
{
    INTCON2bits.GIE = 0;
    
    //__delay_ms(300) // Para evitar el rebote del boton, solo necesario si detecto tanto los flancos positivos como negativos
       
    if (!PORTEbits.RE0){
        LATEbits.LATE0 = 1;
        LATEbits.LATE1 = 0;
    }
    else {
        LATEbits.LATE0 = 0;
        LATEbits.LATE1 = 1;
    }
    
    CNFEbits.CNFE7 = 0;  // SI O SI SE LA TIENE QUE LIMPIAR ANTES DE BAJAR _CNEIF
                         // or CNFE=0;
    IFS4bits.CNEIF = 0;  // or _CNEIF = 0; o para todos los bits IFS4=0
    INTCON2bits.GIE = 1;
}