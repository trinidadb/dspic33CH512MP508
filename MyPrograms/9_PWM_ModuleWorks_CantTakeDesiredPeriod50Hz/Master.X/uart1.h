#ifndef UART1_H
#define	UART1_H

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
                               //  0 = Uses legacy divide-by-x counter for baud clock generation
    U1MODEbits.BRGH = 1;       //  1 = High Speed: Baud rate is baudclk/4
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

void UART1_Write_int16(int num){
    int i=1, is_Negative = num<0;   //To check the sign
    int max_number_of_digits = 5+1; //-32,768 to 32,767 (5 digits)
                                    //The '+1' is to consider an extra space in the string for the '-' if the number is negative
    char number_str[6+1] = {'\0'};  //This '+1' is to consider the EOL '\0'
                                    //6 is the "max_number_of_digits" but I can't create a variable length and array, so I can't pass a variable (even if the variable is fixed)
    char *start_of_string;

    if (is_Negative){ num = -num; }
    if (num == 0){number_str[max_number_of_digits-i]='0';i++;} //This 'i++' is to set the "start_of_string" correctly

    while (num>0){
        number_str[max_number_of_digits-i] = num%10+48;
        num = num / 10;
        i++;
    }
    
    if (is_Negative){number_str[max_number_of_digits-i] = '-';}
    
    start_of_string = number_str+max_number_of_digits+1-i-is_Negative;
    UART1_Write_Text(start_of_string);
}

#endif