#ifndef UART1_BAUD
#warning "UART1_BAUD rate not defined.  Setting to 9600."
#define UART1_BAUD 9600
#endif

#ifndef FCY
#error "FCY defintion required to calculate baud rate.  Please define."
#endif


void UART1_Initialize(void)
{
    uint32_t brg;
    
	U1MODEHbits.BCLKMOD = 0;   //  Baud Clock Generation Mode Select bit.
                               // 0 = Uses legacy divide-by-x counter for baud clock generation
    U1MODEbits.BRGH = 1;       //   1 = High Speed: Baud rate is baudclk/4
	U1MODEHbits.BCLKSEL = 0;   //  Baud Clock Source Selection bits: FCY
    
    brg = (FCY/(4.0*UART1_BAUD)-1) + 0.5; //We add the 0.5 to round up or down so we minimize the error
                                          // between the desired baud rate and the real baud rate
                                          // brg is an int so it truncates the value
    
    U1BRG = (uint16_t)brg;
    U1BRGH = brg>>16;
    
    U1MODEbits.MOD = 0;     // Asynchronous 8-bit UART

	U1MODEbits.UTXEN  = 1;
	U1MODEbits.UARTEN = 1;   
    
}

void UART1_Write(char txData)
{
    while(U1STAHbits.UTXBF == 1){}
    
    U1TXREG = txData;    // Write the data byte to the USART.
}

void UART1_Write_Text(char *text)
{
  int i;
  for(i=0;text[i]!='\0';i++)
	  UART1_Write(text[i]);
}
