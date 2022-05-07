#ifndef CONFIG_ADC_H
#define	CONFIG_ADC_H


void ADC_configurar(){

    ADCON1Hbits.FORM   = 0;      // Data Output format bit: Integer
    
    
    
    
    
    ADCON3Hbits.CLKSEL = 0; //Fcy
    ADCON3Hbits.CLKDIV = 0;
    ADCON3Hbits.SHREN  = 0; //Shared ADC Core Enable bit
    
    //ADIEL.IE --> falta definir el channel
    //ADSTATL: 
}

void turn_on_ADC(){
    ADCON1Lbits.ADON = 1;
}

#endif