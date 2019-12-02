/**
 * main.c
 */
#include <stdio.h>
#include "tm4c1294ncpdt.h"
#include "int_handler.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"


/**
 * main.c
 * 2 out 3,3V
 * 2 in 3,3V
 */
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

    //GPIO_PORTA_AHB_PCTL_R &= ~0x0F000000;// configure PA6 as GPIO (default setting)
    //GPIO_PORTA_AHB_AMSEL_R &= ~0x40;// disable analog functionality on PA6 (default setting)
    GPIO_PORTA_AHB_IS_R &= ~0x40;   // PA6 is edge-sensitive (default setting)
    GPIO_PORTA_AHB_IBE_R &= ~0x40;  // PA6 is not both edges (default setting)
    GPIO_PORTA_AHB_IEV_R |= 0x40;   // PA6 rising edge event
    GPIO_PORTA_AHB_ICR_R = 0x40;    // clear flag6
    GPIO_PORTA_AHB_IM_R |= 0x40;    // enable interrupt on PA6
                                // GPIO PortC=priority 2
    NVIC_EN0_R |= (1<<0); // enable PortA interrupt (Int#0/Vec#16) in NVIC


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

    GPIO_PORTD_AHB_IS_R &= ~0x80;   // PD7 is edge-sensitive (default setting)
    GPIO_PORTD_AHB_IBE_R &= ~0x80;  // PD7 is not both edges (default setting)
    GPIO_PORTD_AHB_IEV_R |= 0x80;   // PD7 rising edge event
    GPIO_PORTD_AHB_ICR_R = 0x80;    // clear flag6
    GPIO_PORTD_AHB_IM_R |= 0x80;    // enable interrupt on PA6

    NVIC_EN0_R |= (1<<3); // enable PortD interrupt (Int#3/Vec#19) in NVIC



    // Port Clock Gating Control Port E
    SYSCTL_RCGCGPIO_R |= (1 << 4);
    while((SYSCTL_PRGPIO_R & (1 << 4)) == 0);
    // Set INPUT direction I/O pins PE0 to PE3
    GPIO_PORTE_AHB_DIR_R &= 0xF0;
    GPIO_PORTE_AHB_DIR_R |= 0xF0;// Set OUTPUT direction I/O pins PE5
    // Digital I/O pins PE0 to PE3 AND PE5 enable
    GPIO_PORTE_AHB_DEN_R |= 0x2F;

    GPIO_PORTE_AHB_IS_R &= ~0x0F;   // PE0 to PE3 is edge-sensitive (default setting)
    GPIO_PORTE_AHB_IBE_R &= ~0x0F;  // PA6 is not both edges (default setting)
    GPIO_PORTE_AHB_IEV_R |= 0x0F;   // PA6 rising edge event
    GPIO_PORTE_AHB_ICR_R = 0x0F;    // clear flag6
    GPIO_PORTE_AHB_IM_R |= 0x0F;    // enable interrupt on PA6
                                // GPIO PortC=priority 2
    NVIC_EN0_R |= (1<<4); // enable PortE interrupt (Int#4/Vec#20) in NVIC


    // Port Clock Gating Control Port M
    SYSCTL_RCGCGPIO_R |= (1 << 11);
    while((SYSCTL_PRGPIO_R & (1 << 11)) == 0);
    // Set input direction I/O pins PM4 and PM5
    GPIO_PORTM_DIR_R &= ~(0x30);
    // Digital I/O pins PM4 and PM5 enable
    GPIO_PORTM_DEN_R |= 0x30;

    GPIO_PORTM_IS_R &= ~0x30;   // PE0 to PE3 is edge-sensitive (default setting)
    GPIO_PORTM_IBE_R &= ~0x30;  // PA6 is not both edges (default setting)
    GPIO_PORTM_IEV_R |= 0x30;   // PA6 rising edge event
    GPIO_PORTM_ICR_R = 0x30;    // clear flag6
    GPIO_PORTM_IM_R |= 0x30;    // enable interrupt on PA6
                                  // GPIO PortC=priority 2
    NVIC_EN2_R |= (1<<8); // enable PortM interrupt (Int#72/Vec#88) in NVIC


    while(1){


    }
}
