void configurar_PLL(void){
    PLLFBDbits.PLLFBDIV = 90;  // M = 45
    CLKDIVbits.PLLPRE   = 1;     // N1 = 1
    PLLDIVbits.POST1DIV = 2; // N2 = 2
    PLLDIVbits.POST2DIV = 1; // N3 = 1

    // Wait for PLL to lock
    while (!OSCCONbits.LOCK); //1 = Indicates that PLL is in lock or the PLL start-up timer is satisfied 
    
    //Fin=crystal
    //FCY=Fin*M/(4*N1*N2*N3)
    //MUCHO CUIDADO, EN ESTOS CASOS FCY es FPLLOUT/4 no "/2" como se esperaria ya que Fcy=Fosc/2
}

#if 1
#warning "MUCHO CUIDADO, EN ESTOS CASOS FCY es FPLLOUT/4 no '/2' como se esperaria ya que Fcy=Fosc/2"
#endif