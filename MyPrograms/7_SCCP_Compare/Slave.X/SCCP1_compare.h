#ifndef SCCP1_TIMER_H
#define	SCCP1_TIMER_H

#ifndef FCY
#error "FCY defintion required to calculate baud rate.  Please define."
#endif

void SCCP1_config();
void turn_on_SCCP1();

void SCCP1_config(){
    float desired_period=0.000050; //Voy a querer que trigere el ADC cada 50us

    CCP1CON1Lbits.CLKSEL = 0;   //Reference Fcy
    CCP1CON1Lbits.TMRPS = 0;    //00 = 1:1 Prescaler
    CCP1CON1Lbits.T32 = 0;      //0 = Uses 16-bit time base for timer, single edge output compare or input capture function
    CCP1CON1Lbits.CCSEL = 0;    //0 = Output Compare/PWM/Timer peripheral (exact function is selected by the MOD[3:0] bits)
    CCP1CON1Lbits.MOD = 0b0101; //0101 = Dual Edge Compare mode, buffered
                                //https://www.microchip.com/forums/m1086397.aspx
    CCP1CON1Hbits.TRIGEN = 0;   // Set Sync/Triggered mode (Synchronous)
    CCP1CON1Hbits.SYNC = 0b00000; // Select Sync/Trigger source (Self-sync)
    
    CCP1CON2Hbits.OCAEN = 1; // 1 = OCx pin is controlled by the CCPx module and produces an output compare or PWM signal
    
    CCP1CON3Hbits.POLACE = 0; //Configure output polarity (Active High)
            
    CCP1TMRL = 0x0000; //Initialize timer prior to enable module.
    //Voy a querer que trigere el ADC cada 50us
    CCP1PRL = FCY*desired_period;  //Configure timebase period
    CCP1RA = CCP1PRL/2;               // Set the rising edge compare value
    CCP1RB = CCP1RA+1;               // Set the falling edge compare value
}

void turn_on_SCCP1(){
    CCP1CON1Lbits.CCPON = 1; //Module is enabled with an operating mode specified by the MOD[3:0] control bits
}


#endif