/*
 * File:   main.c
 * Author: Trini
 *
 * Created on 21 de febrero de 2022, 16:54
 */


#define FCY 90000000UL     //MIPS = 90

#include <xc.h>
#include <libpic30.h>
#include "config.h"
#include "config_PLL.h"
#include "WDT_SW.h"
#include "../../dsPIC33C/h/p33CH512MP508.h"

#include "Slave.h"


int main(void) {
    WDT_SW_disable();
    configurar_PLL();
    _program_secondary(1,0,Slave);
    _start_secondary();
    while(1){}
    return 0;
}
