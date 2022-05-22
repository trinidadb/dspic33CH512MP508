#ifndef INTERRUPT_CONFIG_H
#define	INTERRUPT_CONFIG_H

void INTERRUPT_config_general(){
    
    INTCON2bits.GIE = 0;
    INTCON1bits.NSTDIS = 1;       //Enables nestling interrupts
    
    //MSI INTERRUPT ENABLE -->necessary to receive master interrupt
    IEC8bits.MSIAIE=1; //enable interrupt for protocol A
    _MSIAIF = 0;
    _MSIAIP = 2;
    
    INTCON2bits.GIE = 1;
}    


#endif
