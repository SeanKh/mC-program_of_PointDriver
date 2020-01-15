/**
* main.c
*/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tm4c1294ncpdt.h"
#include "inc/hw_memmap.h"

#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

//states[3]=[0,0,0]; //S0,S1,Error
/**
 * main.c
 * 2 out 3,3V
 * 2 in 3,3V
 */
void SysTick_Wait(uint32_t delay);
void SysTickWait10ms();
void SysTickWait40ms();
void SysTickWait5s();

unsigned int n;
char states[4];
char instructionToExec[4];

int main(void)
{
    // Port Clock Gating Control Port A
    SYSCTL_RCGCGPIO_R |= 0x00000001;
    while((SYSCTL_PRGPIO_R & 0x00000001) == 0);
    // Set INPUT direction I/O pin PA6
    GPIO_PORTA_AHB_DIR_R &= 0xBF;
    // Digital I/O pins PA6 enable
    GPIO_PORTA_AHB_DEN_R |= 0x40;
    GPIO_PORTA_AHB_DATA_R &= 0x00;
    //GPIO_PORTA_AHB_AFSEL_R &= ~0x40; // disable alt funct on PA6 (default setting)


    // Port Clock Gating Control Port B
    SYSCTL_RCGCGPIO_R |= 0x00000002;
    while((SYSCTL_PRGPIO_R & 0x00000002) == 0);
    // Set output direction I/O pins PB0 to PB7
    GPIO_PORTB_AHB_DIR_R |= 0xFF;
    // Digital I/O pins PB2 to PB3 enable
    GPIO_PORTB_AHB_DEN_R |= 0x0C;

    // Port Clock Gating Control Port C
    SYSCTL_RCGCGPIO_R |= 0x00000004;
    while((SYSCTL_PRGPIO_R & 0x00000004) == 0);
    // Set output direction I/O pins PC0 to PC7
    GPIO_PORTC_AHB_DIR_R |= 0xFF;
    // Digital I/O pins PC4 to PC7 enable
    GPIO_PORTC_AHB_DEN_R |= 0xF0;


    // Port Clock Gating Control Port D
    SYSCTL_RCGCGPIO_R |= 0x00000008;
    while((SYSCTL_PRGPIO_R & 0x00000008) == 0);
    // Set output direction I/O pins PD3
    GPIO_PORTD_AHB_DIR_R |= 0x0F;
    GPIO_PORTD_AHB_DIR_R &= 0x0F;     // Set INPUT direction I/O pins PD7
    // Digital I/O pins PD3 AND PD7 enable
    GPIO_PORTD_AHB_DEN_R |= 0x88;

    // Port Clock Gating Control Port E
    SYSCTL_RCGCGPIO_R |= (1 << 4);
    while((SYSCTL_PRGPIO_R & (1 << 4)) == 0);
    // Set INPUT direction I/O pins PE0 to PE3
    GPIO_PORTE_AHB_DIR_R &= 0xF0;
    GPIO_PORTE_AHB_DIR_R |= 0xF0;// Set OUTPUT direction I/O pins PE5
    // Digital I/O pins PE0 to PE3 AND PE5 enable
    GPIO_PORTE_AHB_DEN_R |= 0x2F;

    // Port Clock Gating Control Port M
    SYSCTL_RCGCGPIO_R |= (1 << 11);
    while((SYSCTL_PRGPIO_R & (1 << 11)) == 0);
    // Set input direction I/O pins PM4 and PM5
    GPIO_PORTM_DIR_R &= ~(0x30);
    // Digital I/O pins PM4 and PM5 enable
    GPIO_PORTM_DEN_R |= 0x30;

    //DEMO
    //Placing instructions with keyboard

    //unsigned char instructionToExec=0x0;
    //int errorSignal, errorCounter;

    //normal one-shot down-counting timer without interrupt HERE


    while(1){

        SysTickWait3s();

        states[0]=GPIO_PORTE_AHB_DATA_R & 0x03; //PE0 and PE1 Input Pins
        states[1]=((GPIO_PORTE_AHB_DATA_R>> 2) & 0x03) ; // PE2 and PE3 Input Pins
        states[2]=((GPIO_PORTD_AHB_DATA_R | GPIO_PORTA_AHB_DATA_R) & 0xC0) >> 6; //PD7 And PA6 Input Pins
        states[3]=((GPIO_PORTM_DATA_R | GPIO_PORTM_DATA_R) & 0x30) >> 4; //PM4 and PM5 Input Pins

        for(n=0; n<3;n++){

           switch(states[n])
            {
               case 1: instructionToExec[n] = 0x02; /*high*/ break;
               case 2: instructionToExec[n] = 0x01; /* high*/ break;
               default: /*case 0 and case 3*/ instructionToExec[n] &= 0x00; break;
            }
        }

        GPIO_PORTC_AHB_DATA_R |= instructionToExec[0] << 4; // PC4 or PC5 high
        GPIO_PORTC_AHB_DATA_R |= (instructionToExec[1] << 5) & 0x40; //PC6
        GPIO_PORTE_AHB_DATA_R |= (instructionToExec[1] << 5) & 0x20; // PE5
        GPIO_PORTD_AHB_DATA_R |= (instructionToExec[2] << 2) & 0x20; // PD3
        GPIO_PORTC_AHB_DATA_R |= (instructionToExec[2] << 7) & 0x80; // PC7
        GPIO_PORTB_AHB_DATA_R |= (instructionToExec[3] << 1) & 0x04; // PB2
        GPIO_PORTB_AHB_DATA_R |= (instructionToExec[3] << 3) & 0x08; // PB3

        SysTickWait40ms(); // 30 ms wait

        //Clear data values of ports
        GPIO_PORTB_AHB_DATA_R &= 0x00;
        GPIO_PORTC_AHB_DATA_R &= 0x00;
        GPIO_PORTD_AHB_DATA_R &= 0x00;
        GPIO_PORTE_AHB_DATA_R &= 0x00;
    }
}

/* delay is in 62.5ns units */
void SysTick_Wait(uint32_t delay){
    NVIC_ST_CTRL_R = 0;            /* (1) disable SysTick during setup */
    NVIC_ST_RELOAD_R = delay-1;    /* (2) number of counts to wait */
    NVIC_ST_CURRENT_R = 0;         /* (3) any value written to CURRENT clears */
    NVIC_ST_CTRL_R |= 0x5;         /* (4) enable SysTick with core clock */

    while((NVIC_ST_CTRL_R&0x00010000)==0) {}
}

void SysTickWait10ms(){
    SysTick_Wait(16000000/100);//wait for 10 ms
}

void SysTickWait40ms(){
    for(n=0;n<4;n++){
        SysTickWait10ms();
    }
}

void SysTickWait3s(){
    for(n=0;n<300;n++){
        SysTickWait10ms();
    }
}
