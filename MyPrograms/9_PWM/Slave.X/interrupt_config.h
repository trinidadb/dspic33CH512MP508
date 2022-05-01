void INTERRUPT_configurar(){
    INTCON1bits.NSTDIS = 0;       //Disables nestling interrupts 
    

    
    INTCON2bits.GIE = 1;
}