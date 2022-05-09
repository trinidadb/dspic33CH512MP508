#ifndef PORTS_H
#define	PORTS_H

void PORT_configurar(){
        
    //LEDS
    ANSELE = 0;
    TRISEbits.TRISE1 = 0;
    
    // PWM Output
    ANSELCbits.ANSELC0 = 0;
    TRISCbits.TRISC0 = 0;
    
    //UART
    __builtin_write_RPCON(0x0000); // Unlock RPORn registers
    //RPOR9bits.RP50R = 14;          // Port Pin RC2 tied to S1REFCLKO
    RPOR8bits.RP48R = 16;          // Port Pin RC0 tied to SCCP2 Output (S1OCM2)
    RPOR13bits.RP59R = 1;          // Set PPS up for the UART TX. It is located in RC11
    __builtin_write_RPCON(0x0800); // Lock RPORn registers
    

}

#endif