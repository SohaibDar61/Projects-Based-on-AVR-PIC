/*
    *** FILE : ACCESS_CTRL.c
    *** AUTHOR : Sohaib Dar
    *** DATE   : 12 / 6 /  2022
 */


/* *** PRIVATE INCLUDES *** */

#include "EEPROM.h"
#include "PASSWORD.h"
#include "LCD.h"
#include "KPAD.h"

/* *** PRIVATE CONSTANTS *** */

#define     FLAG_ADDRESS            (0x00)
#define     ENTERED_BEFORE          (99)
#define     PASSWORD_ADDRESS        (0x50)

/* *** PRIVATE VARIABLES *** */

static tByte flag;

static tByte user_password[6];

/* *** PUBLIC FUNCTIONS IMPLEMENTATIONS *** */

void AC_init(void){
    
    PCFG1 = 1;
    PCFG2 = 1;
    LCD_init(LCD_8_MODE);
    
    KPAD_init();
    EEPROM_init(EEPROM_INT_DISABLE);
    
}

void AC_authentication(void){
    
    EEPROM_readByte(FLAG_ADDRESS,&flag);
    
    if(flag == ENTERED_BEFORE){
            LCD_str("PASSWORD : ",L1,C1);
            tByte password[6];
            tByte i = 0;
            EEPROM_readStr(PASSWORD_ADDRESS,password);
            PASSWORD_init(password);
            do{
                if(i > 0) {
                    LCD_clear();
                    LCD_str("ACCESS DENIED !",L1,C1);
                    LCD_str("Try Times : ",L2,C1);
                    LCD_num(i,L2,C13);
                    __delay_ms(3000);
                    LCD_clear();
                    LCD_str("PASSWORD : ",L1,C1);
                }
                PASSWORD_read(user_password);
                i++;
            }while(PASSWORD_check(user_password) == PASSWORD_WRONG);
            
        }else{
            LCD_str("NEW PASSWORD : ",L1,C1);
            PASSWORD_read(user_password);
            EEPROM_writeStr(PASSWORD_ADDRESS,user_password);
            EEPROM_writeByte(0x00,ENTERED_BEFORE);
            PASSWORD_init(user_password);
        }
    
    LCD_clear();
    LCD_str("ACCESS",L1,C5);
    LCD_str("SUCCESS",L2,C5);
    
}