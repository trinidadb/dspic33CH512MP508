#ifndef PORTS_H
#define	PORTS_H

void PORT_configurar(){
    
    ANSELE = 0;            // Port E as digital
    
    //LEDS
    TRISEbits.TRISE0 = 0;
    
    //BUTTON
    TRISEbits.TRISE7 = 1;
    
    //UART
    __builtin_write_RPCON(0x0000); // Unlock RPORn registers
    RPOR13bits.RP59R = 1;          // Set PPS up for the UART TX. It is located in RC11
    __builtin_write_RPCON(0x0800); // Lock RPORn registers
    
    //MPU6050 - Interrupt
    TRISBbits.TRISB11 = 1;
}

#endif