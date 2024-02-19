#include<All_header.h>

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
    setup();
    __enable_irq();
    while(1){
        oneSample();
}
}

