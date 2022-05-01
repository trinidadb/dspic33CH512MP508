void INTERRUPT_configurar(){
    INTCON1bits.NSTDIS = 0;       //Disables nestling interrupts 
    
    //INTERRUPT SCCP1
    IFS0bits.CCT1IF=0;
    IEC0bits.CCT1IE=1;
    
    INTCON2bits.GIE = 1;
}