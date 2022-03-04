/*
 * File:   main.c
 * Author: Trini
 *
 * Created on March 1, 2022, 5:45 PM
 */

#define FCY 100000000UL     //MIPS = 100
#define UART1_BAUD 57600

#include <xc.h>
#include <libpic30.h>
#include "config_PLL.h"
#include "interrupt_config.h"
#include "ports.h"
#include "WDT_SW.h"


int main(void) {
    WDT_SW_disable();
    configurar_PLL();
    PORT_configurar();
    INTERRUPT_configurar();
    while(1){
        LATEbits.LATE0  = 1;
    }
    return 0;
}

void __attribute__ ((interrupt, no_auto_psv)) _MSIAInterrupt(void)
{
    char temp0;
      
    INTCON2bits.GIE = 1;
    IFS8bits.MSIAIF=0;
    if (!PORTEbits.RE1){
        LATEbits.LATE1 = 1;
    }
    else {
        LATEbits.LATE1 = 0;
    }
    
    temp0 = SI1MBX0D;  //EN EL SLAVE LOS PUERTOS QUE SE LEEN/ESCRIBEN NO SON "MSI1MBX0D"
                       // Pero en este caso este es analogo al MSI1MBX0D
                       // Como este ultimo esta asignado al handshake cuando lo lee se levanta la flag 
                       // para interrummpir al master
    
    if (temp0==17){
        LATEbits.LATE0  = 0;
        __delay_ms(300);
        LATEbits.LATE0  = 1;
        __delay_ms(300);
        LATEbits.LATE0  = 0;
        __delay_ms(300);
    }
    IFS8bits.MSIAIF=0;
    INTCON2bits.GIE = 1;
}
