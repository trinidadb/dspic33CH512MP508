/*
 * File:   main.c
 * Author: Trini
 *
 * Created on March 1, 2022, 5:45 PM
 */

#define FCY 100000000UL     //MIPS = 100
#define UART1_BAUD 1000000

#include <xc.h>
#include <libpic30.h>
#include "adc.h"
#include "config_PLL.h"
#include "interrupt_config.h"
#include "ports.h"
#include "uart1.h"
#include "SCCP1_timer.h"
#include "WDT_SW.h"


int main(void) {
    WDT_SW_disable();
    configurar_PLL();
    PORT_configurar();
    SCCP1_config();
    UART1_Initialize();
    UART1_Write_Text("\n\r-------------------------------------------------\n\r");
    UART1_Write_Text("\n\r              STARTING SLAVE!!!!!!              \n\r");
    ADC_configurar();
    turn_on_SCCP1();
    INTERRUPT_configurar();
    turn_on_ADC();
    while(1){
        LATEbits.LATE1  = 1;
    }
    return 0;
}

void __attribute__((interrupt, no_auto_psv)) _ADCAN0Interrupt(void)
{
    UART1_Write_int16(ADCBUF0);UART1_Write_Text("\n");
    _ADCAN0IF = 0; // clear interrupt flag
}