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
    
    //MSI INTERRUPT ENABLE -->necessary to receive ACK of the slave
    IEC8bits.MSIAIE=1; //enable interrupt for protocol A
    _MSIAIF = 0;
    _MSIAIP = 2;
    
    
    
    INTCON2bits.GIE = 1;
}