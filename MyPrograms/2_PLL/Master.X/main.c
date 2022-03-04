/*
 * File:   main.c
 * Author: Trini
 *
 * Created on 21 de febrero de 2022, 16:54
 */


#define FCY 90000000UL     //MIPS = 90
#define UART1_BAUD 57600

#include <xc.h>
#include <libpic30.h>
    /* 16-bit peripheral library for access to delay_ms() function.
     * __delay_ms() and __delay_us() are defined as macros. They depend on a user-supplied definition of FCY. 
     * For example, to declare FCY for a 10 MHz instruction rate:
     * #define FCY 10000000UL
     */

#include "config.h"
#include "config_PLL.h"
#include "ports.h"
#include "interrupt_config.h"
#include "uart1.h"
#include "../../dsPIC33C/h/p33CH512MP508.h"


int main(void) {
    WDTCONLbits.ON   = 0;  //Disables WDT if it was enables by software
    configurar_PLL();
    PORT_configurar();
    UART1_Initialize();
    INTERRUPT_configurar();
    while(1){}
    return 0;
}

void __attribute__((__interrupt__,no_auto_psv)) _CNEInterrupt(void)
{
    INTCON2bits.GIE = 0;
    
    //__delay_ms(300) // Para evitar el rebote del boton, solo necesario si detecto tanto los flancos positivos como negativos
       
    if (!PORTEbits.RE0){
        LATEbits.LATE0 = 1;
        LATEbits.LATE1 = 0;
        UART1_Write_Text("LED1 is ON\r\n");
    }
    else {
        LATEbits.LATE0 = 0;
        LATEbits.LATE1 = 1;
        UART1_Write_Text("LED2 is ON\r\n");
    }
    
    CNFEbits.CNFE7 = 0;  // SI O SI SE LA TIENE QUE LIMPIAR ANTES DE BAJAR _CNEIF
                         // or CNFE=0;
    IFS4bits.CNEIF = 0;  // or _CNEIF = 0; o para todos los bits IFS4=0
    INTCON2bits.GIE = 1;
}
