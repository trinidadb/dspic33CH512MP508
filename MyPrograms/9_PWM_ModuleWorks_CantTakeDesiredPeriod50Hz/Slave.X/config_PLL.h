#ifndef CONFIG_PLL_H
#define CONFIG_PLL_H

void configurar_PLL(void){ 
    CLKDIVbits.PLLPRE = 1;      // N1=1
    PLLFBDbits.PLLFBDIV = 200;  // M = 200
    PLLDIVbits.POST1DIV = 4;    // N2=4 
    PLLDIVbits.POST2DIV = 1;    // N3=1

    // Wait for PLL to lock
    while (!OSCCONbits.LOCK); //1 = Indicates that PLL is in lock or the PLL start-up timer is satisfied 
}


void configurar_AUXILIARY_PLL(void){ 
    ACLKCON1bits.FRCSEL = 0; // Primary Oscillator is the clock source for APLL
    ACLKCON1bits.APLLEN = 0; // APLLEN: Auxiliary PLL Enable/Bypass Select bit: 0 = AFPLLO is connected to the APLL input clock (bypass enabled)
    // Don't have to wait for PLL to lock APLLEN=0
    //AFPLLO = Primary OSC
}

/*
void configurar_AUXILIARY_PLL(void){ 
 * //The AVCO Output Frequency (AFVCO) must be in the range of 400 MHz to 1600 MHz so the following configuration won't work
    ACLKCON1bits.FRCSEL = 0; // Primary Oscillator is the clock source for APLL
    ACLKCON1bits.APLLPRE = 1; // N1 = 1
    APLLFBD1bits.APLLFBDIV = 1; // M = 125
    APLLDIV1bits.APOST1DIV = 1; // N2 = 2
    APLLDIV1bits.APOST2DIV = 1; // N3 = 1
    // Enable APLL
    ACLKCON1bits.APLLEN = 1;

}*/

#if 1
#warning "MUCHO CUIDADO, EN ESTOS CASOS FCY es FPLLOUT/4 no '/2' como se esperaria ya que Fcy=Fosc/2"
#endif

#endif