#ifndef PORTS_H
#define	PORTS_H

void PORT_configurar(){
        
    //LEDS
    TRISEbits.TRISE1 = 0;
    
    //UART
    __builtin_write_RPCON(0x0000); // Unlock RPORn registers
    RPOR13bits.RP59R = 1;          // Set PPS up for the UART TX. It is located in RC11
    __builtin_write_RPCON(0x0800); // Lock RPORn registers
    
}

#endif