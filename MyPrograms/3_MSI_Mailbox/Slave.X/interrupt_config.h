void INTERRUPT_configurar(){
    INTCON1bits.NSTDIS = 0;       //Disables nestling interrupts 
    
    //MSI INTERRUPT ENABLE -->necessary to receive master interrupt
    IEC8bits.MSIAIE=1; //enable interrupt for protocol A
    _MSIAIF = 0;
    _MSIAIP = 2;
    
    INTCON2bits.GIE = 1;
}