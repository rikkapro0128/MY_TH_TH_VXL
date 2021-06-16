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
#include <xc.h>
#include "lcd.h"

void resetPort() {
    TRISC1 = TRISC2 = 1;
}

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

void contentStop() {
    const char your_name[] = {'N', 'g', 'u', 'y', 0x00 , 'n',' ', 'T', 0x01 , 'n', ' ', 'P', 'h', 0x02, 'p', '\n'};
    const char bye[] = {'T', 0x03, 'm', ' ', 'b', 'i', 0x04, 't', '\n'};
    unsigned int i = 0, length = 0;
    const char special_name_bye[] 
    = {
        13, 18, 8, 20, 8, 20, 30, 0,// eex 0x00
        1, 10, 20, 0, 28, 20, 31, 0,// aas 0x01
        0, 4, 8, 0, 28, 20, 30, 0, //as 0x02
        0, 14, 18, 18, 15, 0, 4, 0, // aj 0x03
        4, 10, 4, 10, 15, 0, 4, 0, // eej 0x04
        0X99
    };
    addCharSpecial(special_name_bye);
    lcd_init();
    length = getLengthArr(your_name);
    lcd_gotoxy(0, 0);
    for(i = 0; i< length; i++) {
        lcd_putc(your_name[i]);
    }
    length = getLengthArr(bye);
    lcd_gotoxy(5, 1);
    for(i = 0; i< length; i++) {
        lcd_putc(bye[i]);
    }
}

void contentConfigPwm_1() {
    lcd_init();
    lcd_gotoxy(5, 0);
    lcd_puts("f=4KHz");
    lcd_gotoxy(5, 1);
    lcd_puts("D=30%");
}

void contentConfigPwm_2() {
    lcd_init();
    lcd_gotoxy(5, 0);
    lcd_puts("f=3KHz");
    lcd_gotoxy(5, 1);
    lcd_puts("D=80%");
}

void configPwm_1() {
    TRISC2 = 1;
    TRISC1 = 1;
    TMR2 = 0;
    PR2 = 62;
    CCPR1L = 18;
    CCP1CON = 0x0C;
    CCP2CON = 0x00;
    DC1B1 = 1;
    DC1B0 = 1;
    TRISC2 = 0;
    T2CON = 0x00;
    T2CKPS1 = 0;
    T2CKPS0 = 1;
    TMR2ON = 1;
}

void configPwm_2() {
    TRISC2 = 1;
    TRISC1 = 1;
    TMR2 = 0;
    PR2 = 82;
    CCPR2L = 67;
    CCP2CON = 0x0C;
    CCP1CON = 0x00;
    DC2B1 = 1;
    DC2B0 = 0;
    TRISC1 = 0;
    T2CON = 0x00;
    T2CKPS1 = 0;
    T2CKPS0 = 1;
    TMR2ON = 1;
}

void declarePort() {
    ANSEL = ANSELH = 0;
    TRISB0 = 1;
    TRISB1 = 1;
    TRISB2 = 1;
    nRBPU = 0;
    WPUB = 0x07;
    TRISE0 = 0;
    RE0 = 1;
//    TRISA1 = 0;
//    RA1 = 1;
}

void main(void) {
    declarePort();
    while(1) {
        if(!RB0) {
            while(!RB0);
            RE0 = 1;
            // do something!
            configPwm_1();
            contentConfigPwm_1();
        }else if(!RB1) {
            while(!RB1);
            RE0 = 1;
            // do something!
            configPwm_2();
            contentConfigPwm_2();
        }else if(!RB2) {
            while(!RB2);
            // do something!
            TRISC1 = TRISC2 = 1;
            RE0 = 0;
            contentStop();
        }
    }
}
