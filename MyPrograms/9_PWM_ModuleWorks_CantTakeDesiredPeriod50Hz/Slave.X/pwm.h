#ifndef PWM1_H
#define	PWM1_H

#define PWM_DIVIDER 8
#define AFPLLO 8000000 // When PLL in bypassed ACLKCON1bits.APLLEN = 0;
#define FOSC 2*FCY

#ifndef AFPLLO
#error "AFPLLO defintion required to set PWM.  Please define."
#endif

float desired_period = 0.02; //I want a 20ms period to control de servos
float minimum_duty = 0.0005;
float duty_slope = 0.002;


void PWM1_configurar();
void turn_on_PWM1();
void set_angle(float angle);


void PWM1_configurar(){

    PCLKCONbits.MCLKSEL = 3; //PWM Master Clock Selection bits: 11 = AFPLLO ? Auxiliary PLL post-divider output.
   
    PCLKCONbits.DIVSEL = 0b11;  //PWM Clock Divider Selection bits: 01 = Divide ratio is 1:4
        
    PG1CONLbits.HREN = 0;   //0 = PWM Generator x operates in Standard Resolution mode
    PG1CONLbits.CLKSEL = 1; //01 = PWM Generator uses Master clock selected by the MCLKSEL[1:0] (PCLKCON[1:0]) control bits
    PG1CONLbits.MODSEL = 0; //0 =  Independent Edge PWM mode. 
                            /* Create edge-aligned PWM signals. Two Data registers must be written to define the rising and falling edges
                            PGxPHASE: Determines the position of the PWM signal rising edge from the start of the timer count cycle
                            PGxDC: Determines the position of the PWM signal falling edge from the start of the timer count cycle
                            PGxPER: Determines the end of the PWM timer count cycle */
    
    PG1CONHbits.MDCSEL = 0; //0 = PWM Generator uses the PGxDC register
    PG1CONHbits.MPERSEL = 0;//0 = PWM Generator uses the PGxPER register
    PG1CONHbits.MPHSEL = 0; //0 = PWM Generator uses the PGxPHASE register
    PG1CONHbits.UPDMOD = 1; //Update Data registers immediately, or as soon as possible, if UPDREQ = 1
    PG1CONHbits.SOCS = 0;   //PWM Generator is self-triggered
    
    PG1IOCONHbits.PMOD = 1; //01 = PWM Generator outputs operate in Independent mode
                            /*In Independent Output mode, the output of the PWM Generator is connected to both the PWMxH and PWMxL pins.
                            In most application scenarios, only the PWMxH or PWMxL pin would be enabled. The other pin remains available for
                            GPIO or other peripheral functions. If the Dual PWM mode is selected, the PWM Generator will produce independent
                            pulse widths on PWMxH and PWMxL, as described in 4.2.2.3 Dual PWM Mode. No dead-time switching delay is
                            used in Independent Output mode. No restrictions exist for the states of the PWMxH and PWMxL pins; they can be
                            controlled by external hardware signals or by software overrides. Independent Output mode is selected when
                            PMOD[1:0] (PGxIOCONH[5:4]) = 01*/
    PG1IOCONHbits.PENH = 1; //1 = PWM Generator controls the PWMxH output pin
    PG1IOCONHbits.POLH = 0; //0 = Output pin is active-high
     
    //PG1PER = AFPLLO*desired_period/PWM_DIVIDER - 1; // EL "-1" sale del datasheet
    //PG1PHASE = 0;
    //PG1DC = AFPLLO*minimum_duty/PWM_DIVIDER;
    //PG1DC = PG1PER/2;
    PG1PER = 200;//AFPLLO *0.01;
    PG1PHASE = 0;
    PG1DC = PG1PER/2;
}

void turn_on_PWM1(){
    PG1CONLbits.ON = 1;
}

void set_angle(float angle){
    float required_duty = minimum_duty + duty_slope * angle/180.0;
    PG1DC = AFPLLO*required_duty/PWM_DIVIDER - 1; // EL "-1" sale del datasheet
    PG1STATbits.UPDREQ = 1; //Setting the UPDREQ bit ?commits? the new values to the PWM Generator and user software can not modify PWM data values until the bit is cleared by hardware.

}

#endif