
void WDT_SW_disable(void){
    WDTCONLbits.ON   = 0;  //Disables WDT if it was enables by software
}