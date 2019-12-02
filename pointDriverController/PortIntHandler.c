#include "int_handler.h"
#include "tm4c1294ncpdt.h"
#include "inc/hw_memmap.h"
#include <stdbool.h>
#include "stdio.h"

// PM0 servo, PM1 motor
void PortAHandler(void)
{
    if((GPIO_PORTA_AHB_DATA_R & 0x40) & (GPIO_PORTD_AHB_DATA_R & 0x80)){
        printf("Error");
        return;
    }
    else if(GPIO_PORTA_AHB_DATA_R & 0x40){
        GPIO_PORTC_AHB_DATA_R |= 0x80; // PC7 high
    }

    GPIO_PORTA_AHB_ICR_R = 0x40;
}

// PORT E INTERRUPT HANDLER
void PortEHandler(void)
{
    if(GPIO_PORTE_AHB_DATA_R & 0x03){
        printf("Error");
        return;
    }
    else if(GPIO_PORTE_AHB_DATA_R & 0x01){
        GPIO_PORTC_AHB_DATA_R |= 0x10; // PC4 high
    }
    else if(GPIO_PORTE_AHB_DATA_R & 0x02){
        GPIO_PORTC_AHB_DATA_R |= 0x02; //PC5 high
    }

    if(GPIO_PORTE_AHB_DATA_R & 0x0C){
        printf("Error");
    }
    else if(GPIO_PORTE_AHB_DATA_R & 0x04){
        GPIO_PORTC_AHB_DATA_R |= 0x40; // PC6 high
    }
    else if(GPIO_PORTE_AHB_DATA_R & 0x08){
        GPIO_PORTE_AHB_DATA_R |= 0x20; //PE5 high
    }

    GPIO_PORTE_AHB_ICR_R = 0x0F;
}

// PORT D INTERRUPT HANDLER
void PortDHandler(void)
{
    if((GPIO_PORTD_AHB_DATA_R & 0x80) & (GPIO_PORTA_AHB_DATA_R & 0x04)){
        printf("Error");
        return;
    }
    else if(GPIO_PORTD_AHB_DATA_R & 0x80){
        GPIO_PORTD_AHB_DATA_R |= 0x08; // PC4 high
    }

    GPIO_PORTD_AHB_ICR_R = 0x80;
}

// PORT M INTERRUPT HANDLER
void PortMHandler(void)
{
    if(GPIO_PORTM_DATA_R & 0x30){
        printf("Error");
        return;
    }
    else if(GPIO_PORTM_DATA_R & 0x10){
        GPIO_PORTB_AHB_DATA_R |= 0x04; // PB2 high
    }
    else if(GPIO_PORTM_DATA_R & 0x20){
        GPIO_PORTB_AHB_DATA_R |= 0x08; // PB3 high
    }
    GPIO_PORTM_ICR_R = 0x30;
}

