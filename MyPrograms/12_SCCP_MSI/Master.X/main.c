/*
 * File:   main.c
 * Author: Trini
 *
 * Created on 21 de febrero de 2022, 16:54
 */


#define FCY 90000000UL     //MIPS = 90
#define UART1_BAUD 500000

#include <xc.h>
#include <libpic30.h>
#include "config.h"
#include "config_MSI.h"
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
    UART1_Initialize();
    UART1_Write_Text("\n\r-------------------------------------------------\n\r");
    UART1_Write_Text("\n\r              STARTING MASTER!!!!!!              \n\r");
    _program_secondary(1,0,Slave);
    _start_secondary();
    INTERRUPT_configurar();
    while(1){
        __delay_ms(1000);
        UART1_Write_Text("OK \r\n");
        
    }
    return 0;
}

void __attribute__((__interrupt__,no_auto_psv)) _CNEInterrupt(void)
{
    INTCON2bits.GIE = 0;
       
    UART1_Write_Text("Button was pressed \r\n");
    
    MSI1MBX0D=90;   //write random word in mailbox assigned to handshake
                    //It will initiate the transfer to the slave and set MSIAIF of slave
    UART1_Write_Text("Data was sent \r\n");
    
    CNFEbits.CNFE7 = 0;
    IFS4bits.CNEIF = 0;
   
    INTCON2bits.GIE = 1;
}

void __attribute__ ((interrupt, no_auto_psv)) _MSIAInterrupt(void)
{
    INTCON2bits.GIE = 0;
    
    UART1_Write_Text("Data was acknowledge by the slave \r\n");
    
    _MSIAIF=0;
    INTCON2bits.GIE = 1;
}