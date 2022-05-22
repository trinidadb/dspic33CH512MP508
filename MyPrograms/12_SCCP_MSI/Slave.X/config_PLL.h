void configurar_PLL(void){ 
    CLKDIVbits.PLLPRE = 1;      // N1=1
    PLLFBDbits.PLLFBDIV = 200;  // M = 200
    PLLDIVbits.POST1DIV = 4;    // N2=4 
    PLLDIVbits.POST2DIV = 1;    // N3=1

    // Wait for PLL to lock
    while (!OSCCONbits.LOCK); //1 = Indicates that PLL is in lock or the PLL start-up timer is satisfied 
}

#if 1
#warning "MUCHO CUIDADO, EN ESTOS CASOS FCY es FPLLOUT/4 no '/2' como se esperaria ya que Fcy=Fosc/2"
#endif