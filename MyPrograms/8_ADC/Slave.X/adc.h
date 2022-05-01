#ifndef CONFIG_ADC_H
#define	CONFIG_ADC_H

#if 1
#pragma message "You can't configurate masters's module AD the same way. It doesn't have dedicated cores"
#endif

void start_Dedicated_Core0();
void turn_on_ADC();
void ADC_configurar();

void ADC_configurar(){

    ADCON1Hbits.FORM = 0;    // Data Output format bit: Integer
    
    ADCON3Hbits.CLKSEL = 0;  //Fcy
    ADCON3Hbits.CLKDIV = 0;
    ADCON3Hbits.SHREN  = 0;  //Shared ADC Core Enable bit
    
    ADCON4Hbits.C0CHS = 0;   // Dedicated ADC Core 0 Input Channel Selection bits: 00 = S1AN0
    
    ADCON5Hbits.WARMTIME = 0b1011; // Set ADC Cores Initialization Time More than 10 µS (as it is said in the datasheet)
    
    ADCORE0Hbits.RES  = 0b11; // 11 = 12-bit resolution 
    
    ADMOD0Lbits.SIGN0 = 0;   // 0 =  Channel output data are unsigned
    ADMOD0Lbits.DIFF0 = 0;   // 1 = Channel is differential  VS 0 = Channel is single-ended
    
    ADTRIG0Lbits.TRGSRC0 = 0b10100; //ADC Channel Trigger Selection: 10100=Slave SCCP1 input capture/output compare
    
    ADIELbits.IE0 = 1; // 1 = Common and individual interrupts are enabled for the corresponding channel
    //LVLEN ??
    //ADIEL ??
}

void turn_on_ADC(){
    ADCON1Lbits.ADON = 1;
    start_Dedicated_Core0();
}

void start_Dedicated_Core0(){
    ADCON5Lbits.C0PWR = 1;    // ADC Dedicated Core 0 is powered
    while(!ADCON5Lbits.C0RDY){}; // 1 = ADC Core 0 is powered and ready for operation
    ADCON3Hbits.C0EN   = 1;  //Dedicated ADC Core 0 is enabled
}

/*
ADSTATLbits.AN0RDY
        AN[15:0]RDY: Common Interrupt Enable for Corresponding Analog Inputs bits
1 = Channel conversion result is ready in the corresponding ADCBUFx register
0 = Channel conversion result is not ready
*/

#endif