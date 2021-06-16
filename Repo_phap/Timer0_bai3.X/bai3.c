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

void delay100us(unsigned int n) {
    while(n--) {
        TMR0 = 231;
        TMR0IF = 0; //xóa c? ng?t
        T0CS = 0; //ch? ?? ??nh th?i
        GIE=PEIE =TMR0IE = 0;//c?m ng?t
        PSA = 0; PS2 = 0; PS1 = 0; PS0 = 1; //prescaler=4
        while(TMR0IF==0);
    }
}

void main(void) {
    const char title[] = {'B', 0x01, 'i', ' ', 'T', 0x02, 'p', ' ', 'T', 'i', 'm', 'e', 'r', ' ','0' ,'\n'};
    const char your_name[] = {'N', 'g', 'u', 'y', 0x03 , 'n',' ', 'T', 0x04 , 'n', ' ', 'P', 'h', 0x00, 'p', '\n'};
    const char special_name_title[] 
    = {
        0, 4, 8, 0, 28, 20, 30, 0, //as 0x00
        8, 4, 0, 12, 18, 18, 15, 0, // af 0x01
        8, 20, 0, 12, 20, 31, 8, 0,
        13, 18, 8, 20, 8, 20, 30, 0,// eex 0x00
        1, 10, 20, 0, 28, 20, 31, 0,// aas 0x01
        0X99
    };
    unsigned int i = 0, length = 0, times = 3;
    lcd_init();
    addCharSpecial(special_name_title);
    while(times--) {
        lcd_putc('\f');
        delay100us(10000/2);
        lcd_gotoxy(0, 0);
        length = getLengthArr(title);
        for(i = 0; i < length; i++) {
            lcd_putc(title[i]);
        }
        length = getLengthArr(your_name);
        lcd_gotoxy(0, 1);
        for(i = 0; i < length; i++) {
            lcd_putc(your_name[i]);
        }
        delay100us(10000/2);
    }
    for(i = 0; i < 2; i++) {
        delay100us(10000);
        lcd_ShiftRight();
    }
    for(i = 0; i < 2; i++) {
        delay100us(10000);
        lcd_ShiftLeft();
    }
    delay100us(10000);
}
