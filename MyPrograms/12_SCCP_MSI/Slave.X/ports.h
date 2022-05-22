#ifndef PORTS_H
#define	PORTS_H

void PORT_configurar(){
          
    ANSELE = 0; // Port E as digital
    
    //LEDS
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    
    //BUTTON
    TRISEbits.TRISE7 = 1;
    
    
    //PWM Output - SCCP2
    ANSELCbits.ANSELC0 = 0;
    TRISCbits.TRISC0 = 0;
    
    //PPS - PWM
    __builtin_write_RPCON(0x0000); // Unlock RPORn registers
    RPOR8bits.RP48R = 16;          // Port Pin RC0 tied to SCCP2 Output (S1OCM2) - PWM used for ADC
    __builtin_write_RPCON(0x0800); // Lock RPORn registers
    
}

#endif