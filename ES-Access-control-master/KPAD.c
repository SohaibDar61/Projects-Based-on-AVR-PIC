/* 
    *** FILE   : KPAD.c
    *** AUTHOR : Sohaib Dar
    *** DATE   : 12 / 4 /  2022
 */

/* *** PRIVATE INCLUDES *** */
#include "MICRO_CONTROLLER.h"
#include "HARDWARE.h"
#include "KPAD.h"

/* *** PRIVATE CONSTANTS *** */

#define   PROTEUS

#define   KPAD_ROWS_PULL_UP         (OPTION_REG_R.Bits.BIT7 = 0)
#define   KPAD_ROWS_DEFAULT         (0x0F)
#define   KPAD_COLUMNS_DEFAULT      (0x0F)
#define   N_COLUMNS                 (4)
#define   N_ROWS                    (4)
#define   KPAD_ROWS_READ            (GPIO_LOWER_NIBBLE_READ(KPAD_DATA))
#define   KPAD_COLUMNS_WRITE(VAL)   (GPIO_HIGHER_NIBBLE_WRITE(KPAD_DATA,VAL))
#define   ROW_0                     (0x0E)
#define   ROW_1                     (0x0D)
#define   ROW_2                     (0x0B)
#define   ROW_3                     (0x07)

/* *** PRIVATE DATATYPES *** */
/* *** PRIVATE VARIABLES *** */

#ifdef  PROTEUS

static tByte KEYS[N_ROWS][N_COLUMNS] = {
                            {'7','8','9','/'},
                            {'4','5','6','*'},
                            {'1','2','3','-'},
                            {'#','0','=','+'}
                           };
#endif

#ifdef   KIT

static tByte KEYS[N_ROWS][N_COLUMNS] = {
                           {'1','2','3','/'},
                           {'4','5','6','-'},
                           {'7','8','9','+'},
                           {'*','0','#','='},
                           };

#endif
/* *** PRIVATE FUNCTIONS PROTOTYPE *** */

/* *** PUBLIC  FUNCTIONS IMPLEMENTATION *** */

void KPAD_init(void){
    
    
    /* *** MAKE ROWS PINS INPUT *** */
    GPIO_LOWER_NIBBLE_DIRECTION(KPAD_CTRL,GPIO_INPUT);
    
    /* *** MAKE COLUMNS PINS OUTPUT *** */
    GPIO_HIGHER_NIBBLE_DIRECTION(KPAD_CTRL,GPIO_OUTPUT);
    
    /* *** INTIALIZE COLUMNS PINS AS HIGH LEVEL *** */
    
    GPIO_HIGHER_NIBBLE_WRITE(KPAD_DATA,KPAD_COLUMNS_DEFAULT);
    
    /* *** INTIALIZE ROWS PINS AS PULL UP EXTERNAL OR INTERNAL IF IT IS POSSIBLE *** */
    KPAD_ROWS_PULL_UP;
    
    
}

void KPAD_getKey(tByte * pKey){
    
    tByte row;
    tByte col;
    tByte key = NULL_KEY;
    /* *** ASSIGN ONE COLUMN AS A LOW LEVEL AND THEN READ ROWS VALUE IF CHANGED BREAK THE LOOP ***/
    
    /* THIS TO AVOID MANY READING FOR THE SAME BUTTON : THIS WAY IS BETTER THAN WHILE LOOP BELOW */ 
    if(KPAD_ROWS_READ != KPAD_ROWS_DEFAULT){return;}
    
    for(col = 0; col < N_COLUMNS; col++){
        
        KPAD_COLUMNS_WRITE(KPAD_COLUMNS_DEFAULT);
        GPIO_PIN_WRITE(KPAD_DATA,col + N_ROWS, GPIO_LOW);
        
        row = KPAD_ROWS_READ;
        if (row != KPAD_ROWS_DEFAULT){
            //while(KPAD_ROWS_READ != KPAD_ROWS_DEFAULT); /* THIS TO AVOID MANY READING FOR THE SAME BUTTON : THIS WAY CUASE SYSTME TO HANG */
            break;
        }
    }
    
    if (col < N_COLUMNS){
        
        switch(row){
            
            case ROW_0 : row = 0; break;
            case ROW_1 : row = 1; break;
            case ROW_2 : row = 2; break;
            case ROW_3 : row = 3; break;
            default : break;
        }
        
        key = KEYS[row][col];
    }
    
    
    /* *** ADD KEY VALUE TO KEY POINTER *** */
    *pKey = key;
}

void KPAD_waitKey(tByte * pKey){
    
    tByte key = NULL_KEY;
    
    do {
    
        KPAD_getKey(&key);
        
    }while(key == NULL_KEY);
    
    *pKey = key; 
}
