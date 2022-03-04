void INTERRUPT_configurar(){
    
    INTCON2bits.GIE = 0;
    INTCON1bits.NSTDIS = 1;       //Enables nestling interrupts
    
    // CHANGE NOTIFICATION INTERRUPT CONFIG
    CNCONEbits.ON      = 1;   //To enable the Change Notification feature for the port, the ON bit (CNCONx[15]) must be set.
    CNCONEbits.CNSTYLE = 1;
    CNEN0Ebits.CNEN0E7 = 0;   // To detect negative edge only
    CNEN1Ebits.CNEN1E7 = 1;
    IEC4bits.CNEIE  = 1;      //Enable CN interrupts in PORT E (C4)
    IPC19bits.CNEIP = 1;
    IFS4bits.CNEIF  = 0;      //Put down flag
    
    //MSI INTERRUPT ENABLE (FIFO)
    _MSIDTIE  = 1;  //Master Read FIFO Data Ready
    _MSIFLTIE = 1;  //Read or write FIFO Fault (over/underflow)
    _S1RSTIE  = 1;  //MSI Slave Reset
    
    _MSIDTIP  = 2;  //Master Read FIFO Data Ready
    _MSIFLTIP = 3;  //Read or write FIFO Fault (over/underflow)
    _S1RSTIP  = 4;  //MSI Slave Reset
    
    _MSIDTIF  = 0;  //Master Read FIFO Data Ready
    _MSIFLTIF = 0;  //Read or write FIFO Fault (over/underflow)
    _S1RSTIF  = 0;  //MSI Slave Reset
    
    
    INTCON2bits.GIE = 1;
}