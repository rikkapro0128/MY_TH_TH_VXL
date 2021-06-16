#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 4000000
#define speed 200
#define delaySee 500
//#define timeTest 2000 
#define flash 1000
#include <xc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"

unsigned int count = 0;
const char your_name[] = "Nguyen Tan Phap";

void addCharSpecial(char character[]) {
    unsigned int i = 0;
    lcd_put_byte(0, 0x40);
    while(lcd_busy());
    while(character[i] != 0x99) {
        lcd_put_byte(1, character[i]);
        while(lcd_busy());
        i++;
    }
}

unsigned int getLengthArr(char character[]) {
    unsigned int i = 0;
    while(1) {
        if(character[i] == '\n')
        {
            break;
        }
        i++;
    }
    return i;
}

void declarePort() { // declare port
    ANSEL = ANSELH = 0;
    TRISB = WPUB = 0x01;
    // declare resistance pull-up
    nRBPU = 0; // set permit all PORTB have resistance pull-up
    GIE = 1;
    INTF = 0;
    INTE = 1;
    INTEDG = 1;
}

void main(void) {
    declarePort();
    lcd_init();
    lcd_gotoxy(0, 0);
    lcd_puts(your_name);
    while(1);
}

void __interrupt() myIsr() {
    INTF = 0;
    count = (count == 20) ? 0 : count + 1;
    lcd_init();
    lcd_gotoxy(0, 0);
    lcd_puts(your_name);
    lcd_gotoxy(7, 1);
    printf("%d", count);
}