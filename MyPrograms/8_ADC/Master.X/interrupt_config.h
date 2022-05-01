#ifndef INTERRUPT_CONFIG_H
#define	INTERRUPT_CONFIG_H

void INTERRUPT_config_general(){
    
    INTCON2bits.GIE = 0;
    INTCON1bits.NSTDIS = 1;       //Enables nestling interrupts
    
    // CHANGE NOTIFICATION INTERRUPT PORT "E" CONFIG  --> BUTTON
    CNCONEbits.ON      = 1;   //To enable the Change Notification feature for the port, the ON bit (CNCONx[15]) must be set.
    CNCONEbits.CNSTYLE = 1;   // 1 = Edge style (detects edge transitions)
                              // 0 = Mismatch style (detects change from last port read)
    CNEN0Ebits.CNEN0E7 = 0;   // To detect negative edge only
    CNEN1Ebits.CNEN1E7 = 1;   //
    IPC19bits.CNEIP = 1;
    IFS4bits.CNEIF  = 0;      //Put down flag
    IEC4bits.CNEIE  = 1;      //Enable CN interrupts in PORT E (C4)
    
    
    // CHANGE NOTIFICATION INTERRUPT PORT "B" CONFIG -->SENSOR MPU6050 INTERRUPT
    CNCONBbits.ON       = 1;   //To enable the Change Notification feature for the port, the ON bit (CNCONx[15]) must be set.
    CNCONBbits.CNSTYLE  = 1;
    CNEN0Bbits.CNEN0B11 = 0;   // To detect negative edge only
    CNEN1Bbits.CNEN1B11 = 1;
    IPC0bits.CNBIP  = 2;
    IFS0bits.CNBIF  = 0;      //Put down flag
    IEC0bits.CNBIE  = 0;      //Will start with this interrupt disabled
    
    
    INTCON2bits.GIE = 1;
}


#endif