void INTERRUPT_configurar(){
    INTCON1bits.NSTDIS = 0;       //Disables nestling interrupts 
    CNCONEbits.ON =1;             //To enable the Change Notification feature for the port, the ON bit (CNCONx[15]) must be set.
    CNCONEbits.CNSTYLE = 1;
    CNEN0Ebits.CNEN0E7 = 0;       // To detect negative edge only
    CNEN1Ebits.CNEN1E7 = 1;
       
    // BE VERY AWARE WITH THE FOLLOWING TWO BITS. PORTE E is equivalent to C4/S4, PORT A is equivalent to C0/S0
    // ALSO THE ISR NAME CHANGE DEPENDING ON WHICH PORT. _CNAInterrupt,...,_CNEInterrupt,...
    // TAKE A LOOK AT TABLE 3.25 in "dsPIC33CH512MP508 Family Data Sheet"
    IEC4bits.CNEIE  = 1;          //Enable CN interrupts in PORT E (C4)
    IPC19bits.CNEIP = 1;
    IFS4bits.CNEIF = 0;           //Put down flag
    // If I would have wanted to Set Interrupt on change on PORT C
    // IEC1bits.CNCIE = 1;
    // IFS1bits.CNCIF = 0;
    
    INTCON2bits.GIE = 1;
}