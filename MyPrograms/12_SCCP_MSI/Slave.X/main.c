/*
 * File:   main.c
 * Author: Trini
 *
 * Created on March 1, 2022, 5:45 PM
 */

#define FCY 100000000UL     //MIPS = 100
#define UART1_BAUD 500000

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
    LATEbits.LATE1 = 1; //To check if I'm programming the slave
    SCCP2_config();
    turn_on_SCCP2();
    INTERRUPT_config_general();
    while(1){
        set_angle(0);
    }
    return 0;
}
 
void __attribute__ ((interrupt, no_auto_psv)) _MSIAInterrupt(void)
{
    int16_t angle;
      
    if (!PORTEbits.RE1){
        LATEbits.LATE1 = 1;
    }
    else {
        LATEbits.LATE1 = 0;
    }
    
    angle = SI1MBX0D;  //EN EL SLAVE LOS PUERTOS QUE SE LEEN/ESCRIBEN NO SON "MSI1MBX0D"
                       // Pero en este caso este es analogo al MSI1MBX0D
                       // Como este ultimo esta asignado al handshake cuando lo lee se levanta la flag 
                       // para interrummpir al master
    
    set_angle(angle);
    __delay_ms(1000);
    
    IFS8bits.MSIAIF=0;
    INTCON2bits.GIE = 1;
}
