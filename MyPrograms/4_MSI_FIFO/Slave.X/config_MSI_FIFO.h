#include <libpic30.h>

#ifndef FCY
#error "FCY defintion required to calculate baud rate.  Please define."
#endif

#if 1
#pragma message "Trying to read a write FIFO may cause overflow of the buffer. Example of reading wrong: buffer[count] = SWMRFDATA;"
#endif

void FIFO_configurar(void){
    
    //SI1FIFOCSbits.SWFEN = 1; //enables slave write FIFO
    //SI1FIFOCSbits.SRFEN = 1; //enables slave read FIFO
    
    while(SI1FIFOCSbits.SWFEN==0); // wait till Master enables the Masters Read FIFO
    while(SI1FIFOCSbits.SRFEN==0); // wait till Master enables the Masters Read FIFO
    
    SI1CONbits.RFITSEL = 0; //00 = Triggers data valid interrupt when 1st FIFO entry is written by Master
}