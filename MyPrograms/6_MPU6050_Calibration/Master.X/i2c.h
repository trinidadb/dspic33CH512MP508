#ifndef I2C_H
#define	I2C_H

#include <libpic30.h>
#include "uart1.h"

#define FSCL 400000
#define delay 130         //ns -->Typical value of delay varies from 110 ns to 150 ns
#define SCALE 1000000000  // To scale de delay (ns-->seg)


#ifndef FCY
#error "FCY defintion required to calculate baud rate.  Please define."
#endif
    
void init_enable_i2c(void);
void disable_i2c(void);
void wait_i2c(void);
void start_event_i2c(void);
void rep_start_event_i2c(void);
void stop_event_i2c(void);;
void ack_event_i2c(void);
void nack_event_i2c(void);
void send_data_i2c(char data);
unsigned char read_i2c(void);
void request_data_to_slave_i2c(char device_address, char register_address, int bytes_to_read, unsigned char *data);
void write_data_to_slave_i2c(char device_address, char register_address, char data);

void init_enable_i2c(void){
    I2C1CONLbits.A10M = 0;  // I2CxADD is a 7-bit Slave address
    I2C1BRG = ( (1.0/FSCL)-(delay*1.0/SCALE) ) * FCY - 2 + 0.5; //The 0.5 is to round up
    I2C1CONLbits.I2CEN = 1; // Enables the I2Cx module, and configures the SDAx and SCLx pins as serial port pins
    __delay_us(1);          // 150ns recommended by datasheet, probably not necessary becuase many events will happen between module ON and Start bus event, but I will include it just in case
                            // but I don't have ns function so will use lower possible us
}

void disable_i2c(void){
    I2C1CONLbits.I2CEN = 0; 
    __delay_us(1);          // 150ns are recommended by datasheet, but I don't have ns function so will use lower possible us
}

void start_event_i2c(void){
    /* OBSERVATION --> In the generation of the first start, checking P and S bits will always return that the bus isn't idle (even if it is idle). 
    "S" will be zero but "P" also, that is because nothing has been sent yet so "S" and "P" have the starting values ->0", they don't represent anything
    if ( !(I2C1STATbits.P && !I2C1STATbits.S) ) ---->  UART1_Write_Text("I2C bus isn't in idle state. Transmission won't start"); */    
    wait_i2c();
    I2C1CONLbits.SEN = 1;     //Writing SEN = 1 initiates a master Start event. BRG starts
}

void rep_start_event_i2c(void){
    wait_i2c();
    I2C1CONLbits.RSEN = 1;     //Writing RSEN = 1 initiates a master repeated start sequence
}

void stop_event_i2c(void){
    wait_i2c();
    I2C1CONLbits.PEN = 1;     //Writing PEN = 1 initiates a master Stop sequence
}

void ack_event_i2c(void){   
    wait_i2c();
    I2C1CONLbits.ACKDT = 0;     // An ACK will be sent (not an NACK)
    I2C1CONLbits.ACKEN = 1;     //Writing ACKEN = 1 initiates a master acknowledge sequence    
}

void nack_event_i2c(void){ //--> before generating stop event
    wait_i2c();
    I2C1CONLbits.ACKDT = 1 ;    // An NACK will be sent (not an ACK)
    I2C1CONLbits.ACKEN = 1;     //Writing ACKEN = 1 initiates a master acknowledge sequence        
}

void send_data_i2c(char data){    
    wait_i2c();
    I2C1TRN = data;   //Writing to the I2CxTRN register will start a master transmission event.
    //UART1_Write_Text("--->IN");
    //UART1_Write_Text("TRSTAT:");UART1_Write_int16(I2C1STATbits.TRSTAT);
    //UART1_Write_Text("\nTBF:");UART1_Write_int16(I2C1STATbits.TBF);
    //UART1_Write_Text("\nBCL:");UART1_Write_int16(_BCL);
    //while((I2C1STATbits.TRSTAT || I2C1STATbits.TBF) &&  !_BCL); // I check both because TBF is set earlier but TRSTAT is cleared after the ACKSTAT was written.
    while((I2C1STATbits.TRSTAT) &&  !_BCL); // I check both because TBF is set earlier but TRSTAT is cleared after the ACKSTAT was written.
    if (I2C1STATbits.ACKSTAT){if(!_BCL){UART1_Write_Text("ACK was not received correctly from Slave\n");}}
    //UART1_Write_Text("\n--->OUT\n");
}

void wait_i2c(void){
    while(I2C1CONLbits.SEN || I2C1CONLbits.RSEN || I2C1CONLbits.PEN || I2C1CONLbits.RCEN || I2C1CONLbits.ACKEN || I2C1STATbits.TRSTAT); //These bits are cleared by hardware
}

unsigned char read_i2c(void){
    wait_i2c();
    I2C1CONLbits.RCEN = 1;        // Enable data reception
    while(I2C1CONLbits.RCEN);     // wait for buffer full
    return  I2C1RCV;
}

void request_data_to_slave_i2c(char device_address, char register_address, int bytes_to_read, unsigned char *data){
    // While transmitting the address byte, the master must shift the address bits<7:0>,
    // left by 1 bit, and configure bit 0 as the R/nW bit.
    // The master can receive data from the slave device after the master has transmitted the slave
    //address with an R/W status bit value of ?1?
    int i=0;
    
    start_event_i2c();
    send_data_i2c( device_address );  // --> write to slave
    send_data_i2c( register_address );
    rep_start_event_i2c();
    send_data_i2c( device_address | 1 ); //--> read from slave
    
    while (i < bytes_to_read){
        data[i] = read_i2c();
        i++;
        if (i!=bytes_to_read){ ack_event_i2c(); };
    };
    
    nack_event_i2c();
    stop_event_i2c();

}

void write_data_to_slave_i2c(char device_address, char register_address, char data){
    
    UART1_Write_Text("Sending data to slave...\n");
    start_event_i2c();
    send_data_i2c( device_address );  // --> write to slave
    send_data_i2c( register_address );
    send_data_i2c( data );
    stop_event_i2c();
    
}

#endif