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
#define delaySee 2000
//#define timeTest 2000 
#define flash 500
#include <xc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"

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
    const char title[] = {'T', 'H', ' ', 'V', 'i', ' ', 'x', 0x03, ' ', 'l', 0x04, '\n'};
    const char your_name[] = {'N', 'g', 'u', 'y', 0x00 , 'n',' ', 'T', 0x01 , 'n', ' ', 'P', 'h', 0x02, 'p', '\n'};
    const char special_name_title[] 
    = {
        13, 18, 8, 20, 8, 20, 30, 0,// eex 0x00
        1, 10, 20, 0, 28, 20, 31, 0,// aas 0x01
        0, 4, 8, 0, 28, 20, 30, 0, //as 0x02
        12, 4, 11, 1, 18, 18, 12, 0, // uwr 0x03
        4, 4, 18, 18, 14, 2, 14, 0, // is 0x04
        0X99
    };
    unsigned int i = 0, length = 0, times = 3;
    lcd_init();
    addCharSpecial(special_name_title);
    while(1) {
        lcd_putc('\f');
        __delay_ms(flash);
        lcd_gotoxy(1, 0);
        length = getLengthArr(title);
        for(i = 0; i < length; i++) {
            lcd_putc(title[i]);
        }
        lcd_gotoxy(0, 1);
        length = getLengthArr(your_name);
        for(i = 0; i < length; i++) {
            lcd_putc(your_name[i]);
        }
        __delay_ms(flash);
    }
}

void __interrupt() myIsr() {
    INTF = 0;
    TRISB = 0b00100000;
    PORTB = 0b00001000; 
    __delay_ms(500);
    TRISB = 0b00100000;
    PORTB = 0b00010000; 
    __delay_ms(500);
    TRISB = 0b00001000;
    PORTB = 0b00010000;
    __delay_ms(500);
    TRISB = 0b00001000;
    PORTB = 0b00100000; 
    __delay_ms(500);
    TRISB = 0b00010000;
    PORTB = 0b00100000; 
    __delay_ms(500);
    TRISB = 0b00010000;
    PORTB = 0b00001000; 
    __delay_ms(500);
    declarePort();
}
