/*
 * File:   main.c
 * Author: Trini
 *
 * Created on 21 de febrero de 2022, 16:54
 */


#define FCY 90000000UL     //MIPS = 90
#define UART1_BAUD 500000//57600

#include <xc.h>
#include <libpic30.h>
#include "config.h"
#include "config_PLL.h"
#include "interrupt_config.h"
#include "ports.h"
#include "uart1.h"
#include "WDT_SW.h"
#include "../../dsPIC33C/h/p33CH512MP508.h"

#include "Slave.h"


int main(void) {
    WDT_SW_disable();
    configurar_PLL();
    PORT_configurar();
    _program_secondary(1,0,Slave);
    _start_secondary();
    INTERRUPT_config_general();
    while(1){}
    return 0;
}

void __attribute__((__interrupt__,no_auto_psv)) _CNEInterrupt(void)
{
    INTCON2bits.GIE = 0;
       
    if (!PORTEbits.RE0){
        LATEbits.LATE0 = 1;
    }
    else {
        LATEbits.LATE0 = 0;
    }
    
    CNFEbits.CNFE7 = 0;  // SI O SI SE LA TIENE QUE LIMPIAR ANTES DE BAJAR _CNEIF
                         // or CNFE=0;
    IFS4bits.CNEIF = 0;  // or _CNEIF = 0; o para todos los bits IFS4=0
    INTCON2bits.GIE = 1;
}

