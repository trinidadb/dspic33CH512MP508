/*
 * File:   main.c
 * Author: Trini
 *
 * Created on 21 de febrero de 2022, 16:54
 */


#define FCY 90000000UL     //MIPS = 90
#define UART1_BAUD 57600

#include <libpic30.h>
    /* 16-bit peripheral library for access to delay_ms() function.
     * __delay_ms() and __delay_us() are defined as macros. They depend on a user-supplied definition of FCY. 
     * For example, to declare FCY for a 10 MHz instruction rate:
     * #define FCY 10000000UL
     */
#include "config.h"
#include "config_PLL.h"
#include "config_MSI_FIFO.h"
#include "interrupt_config.h"
#include "ports.h"
#include "uart1.h"
#include "WDT_SW.h"
#include "../../dsPIC33C/h/p33CH512MP508.h"

#include "Slave.h"

volatile unsigned char buffer[32] = {0}, count = 0 ;

int main(void) {
    WDT_SW_disable();
    configurar_PLL();
    PORT_configurar();
    UART1_Initialize();
    FIFO_configurar();
    _program_secondary(1,0,Slave);
    _start_secondary();
    INTERRUPT_configurar();
    while(1){}
    return 0;
}

void __attribute__((__interrupt__,no_auto_psv)) _CNEInterrupt(void)
{
       
    UART1_Write_Text("Button was pressed \r\n");
    MWSRFDATA = count;
    UART1_Write_Text("Data was sent \r\n");
    
    CNFEbits.CNFE7 = 0;
    IFS4bits.CNEIF = 0;

}

void __attribute__ ((interrupt, no_auto_psv)) _MSIDTInterrupt(void)
{ 
    while (!_RFEMPTY){
        if (count>31){ count = 0; }
        buffer[count] = MRSWFDATA;
        UART1_Write_Text("R:");
        int_2_str(buffer[count]);
        UART1_Write_Text(num_as_string);
        count++;
        MWSRFDATA = count;
        UART1_Write_Text("W:");
        int_2_str(count);
        UART1_Write_Text(num_as_string);
    };
    _MSIDTIF  = 0;  //Master Read FIFO Data Ready
    
}

void __attribute__ ((interrupt, no_auto_psv)) _MSIFLTInterrupt(void)
{
    
    UART1_Write_Text("ERROR: MSI - FIFO overflow or underflow detected\r\n");
    
    if (_RFOF){UART1_Write_Text("RFOF\r\n");} //--> read FIFO overflow
    if (_RFUF){UART1_Write_Text("RFUF\r\n");} //--> read FIFO underflow
    if (_WFOF){UART1_Write_Text("WFOF\r\n");} //--> write FIFO overflow
    if (_WFUF){UART1_Write_Text("WFUF\r\n");} //--> write FIFO underflow  
    
    FIFO_restart();
    UART1_Write_Text("FIFO was restarted\r\n");
    _MSIFLTIF = 0;  //Read or write FIFO Fault (over/underflow)
}

void __attribute__ ((interrupt, no_auto_psv)) _S1RSTInterrupt(void)
{
    INTCON2bits.GIE = 0;
    
    UART1_Write_Text("ERROR: Slave suffered restart\r\n");
    FIFO_restart();
    UART1_Write_Text("FIFO was restarted\r\n");
    
    _S1RSTIF  = 0;  //MSI Slave Reset
    INTCON2bits.GIE = 1;
}
