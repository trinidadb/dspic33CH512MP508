#ifndef MPU6050_H
#define MPU6050_H

#include "MPU6050_registers.h"
#include "i2c.h"
#include "uart1.h"

typedef struct {
	int16_t ax, ay, az;
	int16_t gx, gy, gz;
    int16_t te;
} MPU6050_data;

volatile MPU6050_data raw_data;
volatile char MPU6050_config_succeded = 0, MPU6050_i2c_test_succeded = 0;
volatile char MPU6050_new_data_available = 0; // To validate if there is data to print (to take out the UART1_Write... of the ISR)


void MPU6050_test_i2c(void);
void MPU6050_config(void);
void MPU6050_read_accel_gyro(void);
void display_MPU6050_raw_data(void);

void MPU6050_test_i2c(void){
    unsigned char byte;
    MPU6050_i2c_test_succeded = 0;
    UART1_Write_Text("Running communication test (dspic-MPU6050)\n");
    request_data_to_slave_i2c(MPU6050_address, MPU6050_WHO_AM_I,1, &byte);
    if(byte == 0x68) { UART1_Write_Text("EUREKA!! WHO_AM_I register worked as expected \n"); MPU6050_i2c_test_succeded = 1; }
    else { UART1_Write_Text("James Bond : Time to cry"); MPU6050_i2c_test_succeded = 0;}
}

void MPU6050_config(void){
    UART1_Write_Text("Configuring MPU6050....\n");
    write_data_to_slave_i2c(MPU6050_address, MPU6050_PWR_MGMT_1,0x01);   //MPU6050 clock source: PLL with X axis gyro reference, temperature sensor enabled
    write_data_to_slave_i2c(MPU6050_address, MPU6050_SMPLRT_DIV,0x07);   //Gyro Sample Rate : 1kHz, Accelerometer Sample Rate: 1kHz --> for FIFO to work correctly
    write_data_to_slave_i2c(MPU6050_address, MPU6050_CONFIG,0x00);       //FSYNC sampling disable, Digital Low Pass Filter disable
    write_data_to_slave_i2c(MPU6050_address, MPU6050_GYRO_CONFIG,0x00);  //Gyro self-test disable, Full Scale Range: +/- 250°/s
    write_data_to_slave_i2c(MPU6050_address, MPU6050_ACCEL_CONFIG,0x10); //Accel self-test disable, Full Scale Range: +/- 8g
    write_data_to_slave_i2c(MPU6050_address, MPU6050_USER_CTRL,0x00);    //FIFO disable
    write_data_to_slave_i2c(MPU6050_address, MPU6050_INT_PIN_CFG,0x14);  //Enable interrupts, FSYN pin used to generate interrupt
    write_data_to_slave_i2c(MPU6050_address, MPU6050_INT_ENABLE,0x01);   //Data ready interrupt (each time a write operation to all of the sensor registers has been completed)    
    MPU6050_config_succeded = 1;
    UART1_Write_Text("MPU6050 successfully configured\n");
}

void MPU6050_read_accel_gyro(void){
    int bytes_to_read = 14; //Including temperature bytes
    unsigned char aux[bytes_to_read];
    request_data_to_slave_i2c(MPU6050_address, MPU6050_ACCEL_XOUT_H, bytes_to_read, aux);
    raw_data.ax = (aux[0]<<8) | aux[1];
    raw_data.ay = (aux[2]<<8) | aux[3];
    raw_data.az = (aux[4]<<8) | aux[5];
    raw_data.te = (aux[6]<<8) | aux[7];
    raw_data.gx = (aux[8]<<8) | aux[9];
    raw_data.gy = (aux[10]<<8) | aux[11];
    raw_data.gz = (aux[12]<<8) | aux[13];
}

void display_MPU6050_raw_data(void){
    UART1_Write_Text("Accel[x,y,z]-Gyro[x,y,z]-Temp:  ");
    UART1_Write_int16(raw_data.ax);UART1_Write_Text("  ");
    UART1_Write_int16(raw_data.ay);UART1_Write_Text("  ");
    UART1_Write_int16(raw_data.az);UART1_Write_Text("  ");
    UART1_Write_int16(raw_data.gx);UART1_Write_Text("  ");
    UART1_Write_int16(raw_data.gy);UART1_Write_Text("  ");
    UART1_Write_int16(raw_data.gz);UART1_Write_Text("  ");
    UART1_Write_int16(raw_data.te);UART1_Write_Text("  \n");
}

void BUS_Collision_rutine(void){
    UART1_Write_Text("Bus Collision Detect bit(BCL). Restarting I2C...\n");
    disable_i2c();
    init_enable_i2c();
    UART1_Write_Text("i2c restarted\n");
    UART1_Write_Text("Testing and checking configuration of MPU6050\n");
    while(!MPU6050_i2c_test_succeded){ MPU6050_test_i2c();}
    if(!MPU6050_config_succeded){MPU6050_config();__delay_ms(400);}; //If Bus Collision occurred in the middle of MPU6050 configuration
    UART1_Write_Text("MPU6050 in order\n");
}

void setup_MPU6050(void){
    __delay_ms(500);
    while(!MPU6050_i2c_test_succeded){MPU6050_test_i2c();}
    __delay_ms(500);
    if(!MPU6050_config_succeded){MPU6050_config();} //In case a bus event occurred before and config was already set
}


#endif

/*
void MPU6050_clean_FIFO(void){
    // FIFO RESTART
    write_data_to_slave_i2c(MPU6050_address, MPU6050_USER_CTRL,0x00);    //FIFO disable
    __delay_ms(2);
    write_data_to_slave_i2c(MPU6050_address, MPU6050_USER_CTRL,0x08);    //FIFO restarted/cleaned
    __delay_ms(2);
}*/