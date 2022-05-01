//----------------------------------------------------------------------
// Funkcje start i stop
//----------------------------------------------------------------------
void i2c_start( void )
{
    I2C1CONLbits.ACKDT = 0;	//Reset any previous Ack
    I2C1CONLbits.SEN = 1;	//Initiate Start condition
    //the hardware will automatically clear Start Bit
    //wait for automatic clear before proceding
    while (I2C1CONLbits.SEN);
    //__delay_us(22);
}
void i2c_stop( void )
{
    //initiate stop bit
    I2C1CONLbits.PEN = 1;    //Initiate stop bit
    while(I2C1CONLbits.PEN);         // Wait for stop condition to finish
                        // PEN automatically cleared by hardware
    // __delay_us(22);
}

//----------------------------------------------------------------------
// Funkcja inicjalizacji modulu MSSP oraz pinow uC
//----------------------------------------------------------------------
void i2c_init( long int Fscl2 )
{
   int temp;

   //I2C1BRG = 39;
   I2C1BRG = (FCY/Fscl2 - FCY/10000000) - 1;
   I2C1CONLbits.I2CEN = 0;           // Disable I2C Mode
   I2C1CONLbits.DISSLW = 1;          // Disable slew rate control
   IFS1bits.MI2C1IF = 0;            // Clear Interrupt
   I2C1CONLbits.I2CEN = 1;           // Enable I2C Mode
   temp = I2C1RCV;                  // read buffer to clear buffer full
   i2c_stop();                      // set bus to idle
}

//----------------------------------------------------------------------
// Funkcja ponownego startu
//----------------------------------------------------------------------
void i2c_restart( void )
{
    I2C1CONLbits.RSEN = 1;	//Initiate restart condition
    //the hardware will automatically clear restart bit
    //wait for automatic clear before proceding
    while (I2C1CONLbits.RSEN);
    //__delay_us(22);
}

//----------------------------------------------------------------------
// Funkcje ??? jak to sie ladnie nazywa
//----------------------------------------------------------------------
void i2c_ack( void )
{
    I2C1CONLbits.ACKDT = 0;          // Acknowledge data bit, 0 = ACK
    I2C1CONLbits.ACKEN = 1;          // Ack data enabled
    while(I2C1CONLbits.ACKEN);       // wait for ack data to send on bus
}
void i2c_nack( void )
{
    I2C1CONLbits.ACKDT = 1;          // Acknowledge data bit, 1 = NAK
    I2C1CONLbits.ACKEN = 1;          // Ack data enabled
    while(I2C1CONLbits.ACKEN);       // wait for ack data to send on bus
}

//----------------------------------------------------------------------
// Funkcja, ktora czeka na bierzacy transfer                        OK
//----------------------------------------------------------------------
void i2c_wait( void )
{
    // Wait until I2C Bus is Inactive
    while(I2C1CONLbits.SEN || I2C1CONLbits.RSEN || I2C1CONLbits.PEN || I2C1CONLbits.RCEN ||
          I2C1CONLbits.ACKEN || I2C1STATbits.TRSTAT);
}

//----------------------------------------------------------------------
// Funkcja wysylajaca 1 bajt                                        OK
//----------------------------------------------------------------------
void i2c_send( unsigned char dat )
{
    //while (I2C1STATbits.TBF);
    //IFS1bits.MI2C1IF = 0; // Clear Interrupt
    I2C1TRN = dat;    // Move data to SSPBUF */
    while(I2C1STATbits.TRSTAT);       // wait till complete data is sent from buffer */
    //i2c_wait();      // wait for any pending transfer */
}

//----------------------------------------------------------------------
// Funkcja odczytujaca 1 bajt                                       OK
//----------------------------------------------------------------------
unsigned char i2c_get( void )
{
    //unsigned char temp;
// Reception works if transfer is initiated in read mode
    I2C1CONLbits.RCEN = 1;        // Enable data reception
    while(I2C1CONLbits.RCEN);      // wait for buffer full
    I2C1STATbits.I2COV = 0;
    return(I2C1RCV);
    //i2c_wait();       ??
}

void i2c_send_str(unsigned char *str)
{
    while( *str)                    //Transmit Data Until Pagesize
    {
        i2c_send(*str);             //Write 1 byte
        i2c_wait();                 //Wait for Idle bus
        str++;
    }
}
void i2c_get_str(unsigned char *str, unsigned char length)
{
    while (length --)
    {
        *str++ = i2c_get();		//get a single byte
        if(length)
            i2c_ack();				//Acknowledge until all read
        else
        i2c_nack();
    }
}

//----------------------------------------------------------------------
// Funkcja wysylajaca dane (1 bajt) do wybranego slave'a
//----------------------------------------------------------------------
void i2c_write_byte(unsigned char ControlByte, unsigned char LowAdd, unsigned char data)
{

    i2c_wait();                     //Ensure Module is Idle
    i2c_start();                    //Generate Start COndition

    i2c_send( ControlByte );        //Write Control byte
    i2c_wait();

    i2c_send( LowAdd );             //Write Low Address
    i2c_wait();

    i2c_send(data);                 //Write Data
    i2c_wait();

    i2c_stop();                     //Initiate Stop Condition
}

//----------------------------------------------------------------------
// Funkcja wysylajaca dane (string) do wybranego slave'a
//----------------------------------------------------------------------
void i2c_write_str(unsigned char ControlByte, unsigned char LowAdd, unsigned char *str)
{
    i2c_wait();                     //wait for bus Idle
    i2c_start();                    //Generate Start condition

    i2c_send( ControlByte );        //send controlbyte for a write
    i2c_wait();                     //wait for bus Idle

    i2c_send( LowAdd );             //send low address
    i2c_wait();                     //wait for bus Idle

    i2c_send_str( str );            //send data
    i2c_wait();                     //wait for bus Idle

    i2c_stop();                     //Generate Stop
}

//----------------------------------------------------------------------
// Funkcja odbierajaca dane o zadanej dlugosci
//----------------------------------------------------------------------
void i2c_read_str(unsigned char ControlByte, unsigned char Address, unsigned char *Data, unsigned char Length)
{
    i2c_wait();                     //wait for bus Idle
    i2c_start();                    //Generate Start Condition

    i2c_send( ControlByte );        //Write Control Byte
    i2c_wait();                     //wait for bus Idle

    i2c_send( Address );            //Write start address
    i2c_wait();                     //wait for bus Idle

    i2c_restart();                  //Generate restart condition
    i2c_send( ControlByte | 0x01 ); //Write control byte for read
    i2c_wait();                     //wait for bus Idle

    i2c_get_str(Data, Length);      //read Length number of bytes
    i2c_nack();                     //Send Not Ack
    i2c_stop();                     //Generate Stop
}
