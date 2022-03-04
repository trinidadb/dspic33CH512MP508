void INTERRUPT_configurar(){
    INTCON2bits.GIE = 0;
    INTCON1bits.NSTDIS = 1;       //Disables nestling interrupts 
    
    //MSI INTERRUPT ENABLE (FIFO)
    _MSIDTIE  = 1;  //Slave Read FIFO Data Ready
    //_MSIFLTIE = 1;  //Read or write FIFO Fault (over/underflow)
                      // It was already configured in the master:
                      // The MSI FIFOs will generate a FIFO error interrupt to both the Master and Slave processors in
                      // the event of a FIFO overflow or underflow condition

    _MSIDTIP  = 2;  //Slave Read FIFO Data Ready
    
    _MSIDTIF  = 0;  //Slave Read FIFO Data Ready
 
    
    INTCON2bits.GIE = 1;
}