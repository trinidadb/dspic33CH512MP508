void INTERRUPT_configurar(){
    INTCON1bits.NSTDIS = 0;       //Disables nestling interrupts 
    
    //INTERRUPT ADC
    //_ADCAN0IF = 0; // clear interrupt flag for AN0
    //_ADCAN0IE = 1; // enable interrupt for AN0
    
    //INTERRUPT SCCP2
    IFS1bits.CCP2IF=0;
    IEC1bits.CCP2IE=1;
    
    INTCON2bits.GIE = 1;
}