#include <libpic30.h>

#ifndef FCY
#error "FCY defintion required to calculate baud rate.  Please define."
#endif

void FIFO_configurar(void){
    
    MSI1FIFOCSbits.WFEN = 1; //enables master write FIFO
    MSI1FIFOCSbits.RFEN = 1; //enables master read FIFO
    
    MSI1CONbits.RFITSEL = 0; //00 = Triggers data valid interrupt when 1st FIFO entry is written by Slave
}

void FIFO_restart(void){

    MSI1FIFOCSbits.WFEN = 0; //disables master write FIFO
    MSI1FIFOCSbits.RFEN = 0; //disables master read FIFO
    
    __delay_ms(20)
    
    MSI1FIFOCSbits.WFEN = 1; //enables master write FIFO
    MSI1FIFOCSbits.RFEN = 1; //enables master read FIFO
}