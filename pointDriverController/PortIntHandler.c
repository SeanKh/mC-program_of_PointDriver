#include "int_handler.h"
#include "tm4c1294ncpdt.h"
#include "inc/hw_memmap.h"

#include <stdint.h>
#include <stdbool.h>
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
// PM0 servo, PM1 motor
void PortAHandler(void)
{
    unsigned int i;
    for(i=0;i<500000;i++);
    unsigned varPortA=GPIO_PORTA_AHB_DATA_R;
    unsigned varPortD=GPIO_PORTD_AHB_DATA_R;
    unsigned varPortC=GPIO_PORTC_AHB_DATA_R;

    if((varPortA & 0x40) & (varPortD & 0x80)){
        printf("Error");
        return;
    }
    else if(varPortA & 0x40){
        varPortC |= 0x80; // PC7 high
        for(i=0;i<500000;i++);
        varPortC &= 0x00; // PC7 low
    }

    GPIO_PORTA_AHB_ICR_R = 0x40;
}

// PORT E INTERRUPT HANDLER
void PortEHandler(void)
{
    unsigned int i;
    for(i=0;i<500000;i++);
    unsigned varPortE=GPIO_PORTE_AHB_DATA_R;
    unsigned varPortC=GPIO_PORTC_AHB_DATA_R;
    if((varPortE & 0x03) == 0x03){
        printf("Error");
        return;
    }
    else if(varPortE & 0x01){
        varPortC |= 0x10; // PC4 high
        for(i=0;i<500000;i++);
        varPortC &= 0x00; // PC4 low
    }
    else if(varPortE & 0x02){
        varPortC |= 0x02; //PC5 high
        for(i=0;i<500000;i++);
        varPortC &= 0x00; // PC4 low
    }

    if(varPortE & 0x0C){
        printf("Error");
    }
    else if(varPortE & 0x04){
        varPortC |= 0x40; // PC6 high
        for(i=0;i<500000;i++);
        varPortC &= 0x00; // PC6 low
    }
    else if(varPortE & 0x08){
        varPortE |= 0x20; //PE5 high
        for(i=0;i<500000;i++);
        varPortE &= 0x00; // PE5 low
    }

    GPIO_PORTE_AHB_ICR_R = 0x0F;
}

// PORT D INTERRUPT HANDLER
void PortDHandler(void)
{
    unsigned int i;
    for(i=0;i<500000;i++);
    unsigned varPortD=GPIO_PORTD_AHB_DATA_R;
    unsigned varPortA=GPIO_PORTA_AHB_DATA_R;

    if((varPortD & 0x80) & (varPortA & 0x04)){
        printf("Error");
        return;
    }
    else if(varPortD & 0x80){
        varPortD |= 0x08; // PD3 high
        for(i=0;i<500000;i++);
        varPortD &= 0x00; // PD3 low
    }

    GPIO_PORTD_AHB_ICR_R = 0x80;
}

// PORT M INTERRUPT HANDLER
void PortMHandler(void)
{
    unsigned int i;
    for(i=0;i<500000;i++);
    unsigned varPortM=GPIO_PORTM_DATA_R;
    unsigned varPortB=GPIO_PORTB_AHB_DATA_R;

    if(varPortM & 0x30){
        printf("Error");
        return;
    }
    else if(varPortM & 0x10){
        varPortB |= 0x04; // PB2 high
        for(i=0;i<500000;i++);
        varPortB &= 0x00; // PB2 low
    }
    else if(varPortM & 0x20){
        varPortB |= 0x08; // PB3 high
        for(i=0;i<500000;i++);
        varPortB &= 0x00; // PB3 low
    }
    GPIO_PORTM_ICR_R = 0x30;
}


