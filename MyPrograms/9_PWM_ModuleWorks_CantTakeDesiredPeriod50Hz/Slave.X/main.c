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
#include "pwm.h"
#include "uart1.h"
#include "WDT_SW.h"


int main(void) {
    WDT_SW_disable();
    configurar_PLL();
    configurar_AUXILIARY_PLL();
    PORT_configurar();
    UART1_Initialize();
    UART1_Write_Text("\n\r-------------------------------------------------\n\r");
    UART1_Write_Text("\n\r              STARTING SLAVE!!!!!!              \n\r");
    //INTERRUPT_configurar();
    PWM1_configurar();
    turn_on_PWM1();
    while(1){
        LATEbits.LATE1  = 1;
        //set_angle(30);
        //__delay_ms(1500);
        //set_angle(40);
        //__delay_ms(1500);
        //set_angle(0);
        //__delay_ms(1500);
    }
    return 0;
}

