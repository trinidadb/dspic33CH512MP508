#ifndef SCCP2_PWM_H
#define	SCCP2_PWM_H

#define FREFCLK 12500000

float desired_period = 0.005; //I want a 10ms period to control de servos (BETA VERSION - TRYING)
float minimum_duty = 0.0005;
float duty_slope = 0.002;

void SCCP2_config();
void turn_on_SCCP2();
void set_angle(float angle);
void set_REFCLK();

void SCCP2_config(){

    set_REFCLK();
    
    CCP2CON1Lbits.CLKSEL = 1;   //CCPx Time Base Clock Select bits : 001 = Reference Clock (REFCLKO)
    CCP2CON1Lbits.TMRPS = 0;    //11 = 1:1 Prescaler
    CCP2CON1Lbits.T32 = 0;      //0 = Uses 16-bit time base for timer, single edge output compare or input capture function
    CCP2CON1Lbits.CCSEL = 0;    //0 = Output Compare/PWM/Timer peripheral (exact function is selected by the MOD[3:0] bits)
    CCP2CON1Lbits.MOD = 0b0101; //0101 = Dual Edge Compare mode, buffered
                                //https://www.microchip.com/forums/m1086397.aspx
    CCP2CON1Hbits.TRIGEN = 0;   // Set Sync/Triggered mode (Synchronous)
    CCP2CON1Hbits.SYNC = 0b00000; // Select Sync/Trigger source (Self-sync)
    
    CCP2CON2Hbits.OCAEN = 1;  // 1 = OCx pin is controlled by the CCPx module and produces an output compare or PWM signal
    
    CCP2CON3Hbits.POLACE = 0; //Configure output polarity (Active High)
            
    CCP2TMRL = 0x0000; //Initialize timer prior to enable module.

    CCP2PRL = FREFCLK*desired_period;  //Configure timebase period
    CCP2RA = 0; // If edge-aligned PWM signals are desired, maintain CCPxRA with a value of 0000h. Using a non-zero value for CCPxRA creates PWM signals with arbitrary phase alignments
                // If CCPxRA is 0000h, the OCx output is asserted on the first clock after the Timer Reset (CCPxTMR = 0001h)
    //set_angle(0); //Here I set CCP2RB
    //CCP2RB = CCP2PRL-1;
    CCP2RB = FREFCLK*minimum_duty + 1; //The "+1" is because If CCPxRA is 0000h, the OCx output is asserted on the first clock after the Timer Reset (CCPxTMR = 0001h)
    //CCP2RB = CCP2PRL-1;
}

void turn_on_SCCP2(){
    CCP2CON1Lbits.CCPON = 1; //Module is enabled with an operating mode specified by the MOD[3:0] control bits
}

void set_angle(float angle){
    float required_duty = minimum_duty + duty_slope * angle/180.0;
    CCP2RB = FREFCLK*required_duty + 1; //The "+1" is because If CCPxRA is 0000h, the OCx output is asserted on the first clock after the Timer Reset (CCPxTMR = 0001h)
}

void set_REFCLK(){
    //Generate Reference Clock of 3.125MHz
    REFOCONLbits.ROOUT = 1; //0 = Reference clock external output is enabled. NEEDS TO BE ENABLED SO THAT SCCP2 WORKS!!
    REFOCONLbits.ROSEL = 1; //Reference Clock Source Select bits : 0001 = Fp (FCY) or 0010 = Primary Oscillator
    REFOCONHbits.RODIV = 4; //Base clock value divided by 8 (2 * 4)
    while(_ROSWEN){};       
    REFOCONLbits.ROEN = 1;  //1 = Reference Oscillator is enabled on the REFCLKO pin
    while(!_ROACTIVE){};
}

#endif