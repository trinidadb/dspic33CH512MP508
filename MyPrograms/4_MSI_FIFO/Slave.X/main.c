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
#include "config_MSI_FIFO.h"
#include "config_PLL.h"
#include "interrupt_config.h"
#include "ports.h"
#include "WDT_SW.h"

volatile unsigned char buffer[32] = {0}, count = 0 ;

int main(void) {
    WDT_SW_disable();
    configurar_PLL();
    PORT_configurar();
    FIFO_configurar();
    INTERRUPT_configurar();
    while(1){
        LATEbits.LATE0  = 1;
    }
    return 0;
}

void __attribute__ ((interrupt, no_auto_psv)) _MSIDTInterrupt(void)
{
    while (!_SRFEMPTY){
        if (count>31){ count = 0; }
        buffer[count] = SRMWFDATA;
        SWMRFDATA = count;
        count++;
    }
    _MSIDTIF  = 0;  //Master Read FIFO Data Ready
    
}