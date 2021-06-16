
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
#define timeTest 2000 
#include <xc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"

void addCharSpecial(char character[]);
unsigned int getLengthArr(char character[]);
void showContent(char character_firt[], char character_second[]);

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

void showContent(char character_firt[], char character_second[]) {
    unsigned int i;
    unsigned int length_1 = getLengthArr(character_firt);
    lcd_putc('\f');
    lcd_gotoxy(0, 0);
    for(i = 0; i < length_1; i++) {
        lcd_putc(character_firt[i]);
    }
    unsigned int length_2 = getLengthArr(character_second);
    lcd_gotoxy(0, 1);
    for(i = 0; i < length_2; i++) {
        lcd_putc(character_second[i]);
    }
}

void main(void) {
    const char your_name[] = {'N', 'g', 'u', 'y', 0x00 , 'n',' ', 'T', 0x01 , 'n', ' ', 'P', 'h', 0x02, 'p', '\n'};
    const char your_born[] = {'N','g',0X03,'y','S','i','n','h', ':', '1', '2', '/', '2', '0', '0', '1', '\n'};
    const char your_live[] = {'N',0x04,'i','S',':', 'N', 'i', 'n', 'h', 'T', 'h', 'u', 0x05 , 'n' , '\n'};
    const char HKTT[] = {'H' ,'K' ,'T', 'T', ':','G', 0x01, ' ', 'V', 0x02, 'p', '\n'};
    const char class[] = {'L', 0x03, 'p', ':', 0x00, 'H', 'V', 'T' ,'1', '5' , 'A', '\n'};
    const char MSSV[] = "MSSV:19436481\n";
    const char special_name_born_live[] 
    = {
        13, 18, 8, 20, 8, 20, 30, 0,// eex 0x00
        1, 10, 20, 0, 28, 20, 31, 0,// aas 0x01
        0, 4, 8, 0, 28, 20, 30, 0, //as 0x02
        8, 4, 0, 12, 18, 18, 15, 0, // af 0x03
        0, 6, 2, 12, 18, 18, 12, 0, // ow 0x04
        8, 20, 0, 28, 20, 30, 8, 0, // oof 0x05
        0X99
    }; // Ma ket thuc chuoi la 99H
    const char special_HKTT_class[] 
    = {
        14, 9, 9, 29, 9, 9, 14, 0, //dd 0x04
        8, 4, 0, 12, 18, 18, 12, 0, // of 0x06
        1, 10, 20, 0, 28, 20, 31, 0, // aas 0x07 
        1, 13, 5, 28, 20, 20, 28, 0, // ows 0x08
        0X99
    };
    unsigned int i = 0, length = 0;
    lcd_init();
    addCharSpecial(special_name_born_live); // add character
    showContent(your_name, MSSV);
    __delay_ms(timeTest);
    showContent(your_born, your_live);
    __delay_ms(timeTest);
    addCharSpecial(special_HKTT_class); // add character
    showContent(HKTT, class);
    __delay_ms(timeTest);
}
