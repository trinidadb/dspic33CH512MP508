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
#include "config_PLL.h"
#include "interrupt_config.h"
#include "ports.h"
#include "uart1.h"
#include "SCCP2_pwm.h"
#include "WDT_SW.h"


int main(void) {
    WDT_SW_disable();
    configurar_PLL();
    PORT_configurar();
    SCCP2_config();
    UART1_Initialize();
    UART1_Write_Text("\n\r-------------------------------------------------\n\r");
    UART1_Write_Text("\n\r              STARTING SLAVE!!!!!!              \n\r");
    turn_on_SCCP2();
    INTERRUPT_configurar();
    while(1){
        LATEbits.LATE1  = 1; //To check if I'm programming the slave
        set_angle(0);
        __delay_ms(1000);
        set_angle(30);
        __delay_ms(1000);
        set_angle(60);
        __delay_ms(1000);
        set_angle(90);
        __delay_ms(1000);
        set_angle(120);
        __delay_ms(1000);
        set_angle(180);
        __delay_ms(1000);
       
    }
    return 0;
}
 
void __attribute__((interrupt, no_auto_psv)) _CCP2Interrupt(void)
{
    UART1_Write_Text("INT\n");
    IFS1bits.CCP2IF=0;
}