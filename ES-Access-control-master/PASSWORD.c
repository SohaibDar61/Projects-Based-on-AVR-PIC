/* 
 *** FILE   : PASSWORD.c
 *** AUTHOR : Sohaib Dar
 *** DATE   : 12 / 3 /  2022
*/
 

/* *** PRIVATE INCLUDES *** */
#include    "PASSWORD.h"
#include    "UTILITY.h"
#include    "KPAD.h"
#include    "LCD.h"

/* *** PRIVATE CONSTANTS *** */
#define     MAX_LENGTH          (5)

/* *** PRIVATE DATATYPES *** */

/* *** PRIVATE VARIABLES *** */
static tByte REAL_PASSWORD[MAX_LENGTH + 1];

/* *** PRIVATE FUNCTIONS PROTOTYPE *** */

/* *** PUBLIC FUNCTIONS IMPLEMENTATIONS *** */

void PASSWORD_init(tByte * password){
    
    /* *** SET PASSED PASSWORD TO REAL PASSWORD VARIABLE *** */
    
    UTIL_STRcopy(password,REAL_PASSWORD);
    
}
void PASSWORD_read(tByte * pPassword){
    
    /* *** WRITE THE WAY THAT YOU WANT TO READ PASSWORD AND SET IT IN PASSED POINTER*/
    tByte key = NULL_KEY;
    tByte col = 0;

    while(key != '#'){
        KPAD_waitKey(&key);
        if(key != '#'){
             *pPassword = key;
             LCD_char('*',L2,col);
             pPassword++;
             col++;
        }
       
    }
    *pPassword = '\0';
    
}

tPASSWORD_STATE PASSWORD_check(tByte * password){
    
    /* *** COMPARE  PASSED PASSWORD AND REAL PASSWORD THEN RETURN CORRECT OR WORONG STATE *** */
    
    tPASSWORD_STATE state = ( UTIL_STRcompare(password,REAL_PASSWORD) == SIMILAR ) ? PASSWORD_CORRECT : PASSWORD_WRONG;
    
    return state;
}
