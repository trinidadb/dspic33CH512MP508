/*
 * File:   main.c
 * Author: Trini
 *
 * Created on 21 de febrero de 2022, 16:54
 */


#define FCY 90000000UL     //MIPS = 90
#define UART1_BAUD 57600

#include <xc.h>
#include <libpic30.h>
#include "config.h"
#include "config_PLL.h"
#include "i2c.h"
#include "interrupt_config.h"
#include "MPU6050.h"
#include "MPU6050_registers.h"
#include "ports.h"
#include "uart1.h"
#include "../../dsPIC33C/h/p33CH512MP508.h"


int main(void) {
    WDTCONLbits.ON   = 0;  //Disables WDT if it was enables by software
    configurar_PLL();
    PORT_configurar();
    UART1_Initialize();
    INTERRUPT_configurar();
    while(1){
        if (MPU6050_new_data_available){
            display_MPU6050_raw_data();
            MPU6050_new_data_available = 0;
        }
    };
    return 0;
}

void __attribute__((__interrupt__,no_auto_psv)) _CNEInterrupt(void)
{
    INTCON2bits.GIE = 0;
       
    if (!PORTEbits.RE0){
        LATEbits.LATE0 = 1;
        LATEbits.LATE1 = 0;
        init_enable_i2c();
        __delay_ms(20);
        MPU6050_test_i2c();
        MPU6050_config();
    }
    else {
        LATEbits.LATE0 = 0;
        LATEbits.LATE1 = 1;
        disable_i2c();
    }
    
    CNFEbits.CNFE7 = 0;  // SI O SI SE LA TIENE QUE LIMPIAR ANTES DE BAJAR _CNEIF
                         // or CNFE=0;
    IFS4bits.CNEIF = 0;  // or _CNEIF = 0; o para todos los bits IFS4=0
    INTCON2bits.GIE = 1;
}

void __attribute__((__interrupt__,no_auto_psv)) _CNBInterrupt(void)
{
    MPU6050_read_accel_gyro();
    MPU6050_new_data_available = 1;
}



void __attribute__((__interrupt__,no_auto_psv)) _I2C1BCInterrupt(void)
{
    UART1_Write_Text("Bus Collision Detected");
    _I2C1BCIF = 0;
}

void __attribute__((__interrupt__,no_auto_psv)) _MI2C1Interrupt(void)
{
    if (_IWCOL || _I2COV || _BCL ){
        if (_IWCOL){UART1_Write_Text("Write Collision Detect Bit was set"); _IWCOL = 0; }
        if (_I2COV){UART1_Write_Text("Receive Overflow Flag Bit"); _I2COV = 0; }
        if (_BCL){  //It is cleared when I2C module is disabled, I2CEN = 0
            UART1_Write_Text("Bus Collision Detect bit. Restarting i2c...");
            disable_i2c();
            init_enable_i2c();
            UART1_Write_Text("i2c restarted");
            _BCL = 0;
        }
    }
    _MI2C1IF = 0;
}