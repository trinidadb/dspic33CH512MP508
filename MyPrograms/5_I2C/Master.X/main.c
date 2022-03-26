/*
 * File:   main.c
 * Author: Trini
 *
 * Created on 21 de febrero de 2022, 16:54
 */


#define FCY 90000000UL     //MIPS = 90
#define UART1_BAUD 500000//57600

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
#include "WDT_SW.h"
#include "../../dsPIC33C/h/p33CH512MP508.h"


int main(void) {
    WDT_SW_disable();
    configurar_PLL();
    PORT_configurar();
    UART1_Initialize();
    UART1_Write_Text("\n\r-------------------------------------------------\n\r");
    UART1_Write_Text("\n\r              STARTING DEVICE!!!!!!              \n\r");
    init_enable_i2c();
    INTERRUPT_config_general();
    setup_MPU6050();
    while(1){
        if(MPU6050_new_data_available){display_MPU6050_raw_data(); MPU6050_new_data_available = 0;}
        }
    return 0;
}

void __attribute__((__interrupt__,no_auto_psv)) _CNEInterrupt(void)
{
    INTCON2bits.GIE = 0;
       
    if (!PORTEbits.RE0){
        LATEbits.LATE0 = 1;
        LATEbits.LATE1 = 0;
        INTERRUPT_enable_MPU6050();
    }
    else {
        LATEbits.LATE0 = 0;
        LATEbits.LATE1 = 1;
        INTERRUPT_disable_MPU6050();
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
    CNFBbits.CNFB11 = 0;
    IFS0bits.CNBIF  = 0;  
}

void __attribute__((__interrupt__,no_auto_psv)) _I2C1BCInterrupt(void)
{
    BUS_Collision_rutine();
    _I2C1BCIF = 0; //-->just in case it isn't cleared by hardware after restart as BCL. There is not much description about this register
}

void __attribute__((__interrupt__,no_auto_psv)) _MI2C1Interrupt(void)
{
    if (_IWCOL || _I2COV || _BCL ){
        if (_IWCOL){UART1_Write_Text("Write Collision Detect Bit was set\n\r"); _IWCOL = 0; }
        if (_I2COV){UART1_Write_Text("Receive Overflow Flag Bit\n\r"); _I2COV = 0; }
        if (_BCL){  //It is cleared when I2C module is disabled, I2CEN = 0
            BUS_Collision_rutine();
        }
    }
    _MI2C1IF = 0;
}