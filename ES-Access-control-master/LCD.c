/*
    *** FILE : LCD.c
    *** AUTHOR : Sohaib Dar
    *** DATE   : 12 / 4 /  2022
 */

/* *** DIRECTIVES *** */

#include "LCD.h"
#include "HARDWARE.h"
#include "GPIO.h"
#include "MICRO_CONTROLLER.h"
#include "UTILITY.h"

/* *** PRIVATE CONSTANTS *** */

#define     LCD_START_RESET             (0x30)
#define     LCD_CLEAR                   (0x01)

#define     LCD_RETURN_HOME             (0x02)

#define     LCD_START_MODE_MASK         (0x04)
#define     LCD_CURS_INC                (0x02)
#define     LCD_CURS_DEC                (0x00)
#define     LCD_AUTO_DSP_SHIFT          (0x01)
#define     LCD_NO_DSP_SHIFT            (0x00)

#define     LCD_DSP_CTRL_MASK           (0x08)
#define     LCD_DSP_ON                  (0x04)
#define     LCD_DSP_OFF                 (0x00)
#define     LCD_CURS_ON                 (0x02)
#define     LCD_CURS_OFF                (0x00)
#define     LCD_CURS_BLINK_ON           (0x01)
#define     LCD_CURS_BLINK_OFF          (0x00)

#define     LCD_DSP_CURS_CTRL_MASK      (0x10)
#define     LCD_DSP_MOVE_CURS_FIX       (0x08)
#define     LCD_DSP_FIX_CURS_MOVE       (0x00)
#define     LCD_DSP_CURS_MOVE_LEFT      (0x00)
#define     LCD_DSP_CURS_MOVE_RIGHT     (0x04)

#define     LCD_DATA_SHOW_CTRL_MASK     (0x20)
#define     LCD_DATA_FOUR_MODE          (0x00)
#define     LCD_DATA_EIGHT_MODE         (0x10)
#define     LCD_LINE_SINGLE             (0x00)
#define     LCD_LINE_DOUBLE             (0x08)
#define     LCD_FONT_SMALL              (0x00)
#define     LCD_FONT_LARGE              (0x04)

#define     LCD_SET_CGRAM_ADDRESS       (0x40)
#define     LCD_SET_DDRAM_ADDRESS       (0x80)

#define     LCD_LINE_SIZE               (40)    
#define     LCD_L2_C1_ADDRESS           (0x40)

#define     LCD_FOUR_MODE_CONFIG_1      (0x33)
#define     LCD_FOUR_MODE_CONFIG_2      (0x32)

#define     RS_COMMAND                  (GPIO_LOW)
#define     RS_DATA                     (GPIO_HIGH)

#define     LCD_UPDATE_PERIOD           (200)

/* *** PRIVATE DATATYPES *** */

/* *** PRIVATE VARIABLES *** */

static tLCD_Mode currentMode;

/* *** PRIVATE FUNCTIONS PROTOTYPES *** */

static void LCD_cmd(tByte);

static void LCD_goTo(tLine,tColumn);

static void LCD_latch(void);

static void LCD_out(tByte);

static void Convert_IntToString(tDword,tByte **);

/* *** PUBLIC FUNCTIONS IMPLEMENTATION *** */

void LCD_init(tLCD_Mode mode){
    
    /* *** INTIALIZE RS PIN AS OUTPUT *** */
    GPIO_PIN_WRITE(LCD_RS_CTRL,LCD_RS_PIN,GPIO_OUTPUT);
    
    /* *** INTIALIZE EN PIN AS OUTPUT *** */
    GPIO_PIN_WRITE(LCD_EN_CTRL,LCD_EN_PIN,GPIO_OUTPUT);
    
    /* *** INTIALIZE LCD DATA BINS AS OUTPUT AND LOW LEVEL *** */
    GPIO_PIN_WRITE(LCD_DATA_CTRL,LCD_DATA_PIN_0,GPIO_OUTPUT);
    GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_0,GPIO_LOW);
    
    GPIO_PIN_WRITE(LCD_DATA_CTRL,LCD_DATA_PIN_1,GPIO_OUTPUT);
    GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_1,GPIO_LOW);
    
    GPIO_PIN_WRITE(LCD_DATA_CTRL,LCD_DATA_PIN_2,GPIO_OUTPUT);
    GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_2,GPIO_LOW);
    
    GPIO_PIN_WRITE(LCD_DATA_CTRL,LCD_DATA_PIN_3,GPIO_OUTPUT);
    GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_3,GPIO_LOW);
    
    currentMode = mode;
    
    if(LCD_8_MODE == mode){
        GPIO_PIN_WRITE(LCD_DATA_CTRL,LCD_DATA_PIN_4,GPIO_OUTPUT);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_4,GPIO_LOW);
        
        GPIO_PIN_WRITE(LCD_DATA_CTRL,LCD_DATA_PIN_5,GPIO_OUTPUT);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_5,GPIO_LOW);
    
        GPIO_PIN_WRITE(LCD_DATA_CTRL,LCD_DATA_PIN_6,GPIO_OUTPUT);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_6,GPIO_LOW);

        GPIO_PIN_WRITE(LCD_DATA_CTRL,LCD_DATA_PIN_7,GPIO_OUTPUT);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_7,GPIO_LOW);
        
    }
    
    /* *** INERNAL RESET CIRCUIT ON BY SW *** */
    __delay_ms(20);
    LCD_cmd(LCD_START_RESET);
    __delay_ms(5);
    LCD_cmd(LCD_START_RESET);
    __delay_ms(1);
    LCD_cmd(LCD_START_RESET);
    
    if(LCD_8_MODE == currentMode){
        
        /* *** MODE EIGHT BITS AND TWO LINES AND SMALL FONT *** */
        LCD_cmd(LCD_DATA_SHOW_CTRL_MASK | LCD_DATA_EIGHT_MODE | LCD_LINE_DOUBLE | LCD_FONT_SMALL);
        
    }else {
    
        /* *** MODE FOUR SPECILA TWO COMMAND THEN CHOOSE FOUR BITS MODE  AND TWO LINES AND SMALL FONT *** */
        LCD_cmd(LCD_FOUR_MODE_CONFIG_1);
        LCD_cmd(LCD_FOUR_MODE_CONFIG_2);
        LCD_cmd(LCD_DATA_SHOW_CTRL_MASK | LCD_DATA_FOUR_MODE | LCD_LINE_DOUBLE | LCD_FONT_SMALL);
    }
    
    /* *** DISPLAY ON AND CURRSOR OFF AND CURSOR BLINKING OFF *** */
   LCD_cmd(LCD_DSP_CTRL_MASK | LCD_DSP_ON | LCD_CURS_OFF | LCD_CURS_BLINK_OFF);
    
    /* *** CLEAR SCREEN *** */
    LCD_cmd(LCD_CLEAR);
    __delay_ms(2);
}

void LCD_char(tByte ch ,tLine line ,tColumn col){
    
    /* *** SET LINE AND COL *** */
    LCD_goTo(line,col);
    
    /* *** MAKE RS AS DATA *** */
    GPIO_PIN_WRITE(LCD_RS_VAL,LCD_RS_PIN,RS_DATA);
    
    /* *** SEND DATA *** */
    LCD_out(ch);
}

void LCD_str(tByte * str ,tLine line ,tColumn col){
    
    while(*str != '\0'){
        LCD_char(*str,line,col);
        str++;
        col++;
    }
}

void LCD_num(tDword num , tLine line , tColumn col){
    
    tByte str[17]; 
    tByte * pStr = str;
    
    UTIL_INTtoSTR(num,&pStr,17);
    
    LCD_str(pStr,line,col);
}

void LCD_clear(void){
    
    LCD_cmd(LCD_CLEAR);
    LCD_cmd(LCD_RETURN_HOME);
    __delay_ms(1);
}

void LCD_ON(void){
    LCD_cmd(LCD_DSP_CTRL_MASK | LCD_DSP_ON | LCD_CURS_OFF | LCD_CURS_BLINK_OFF);
}

void LCD_OFF(void){
    LCD_cmd(LCD_DSP_CTRL_MASK | LCD_DSP_OFF | LCD_CURS_OFF | LCD_CURS_BLINK_OFF);
}

void LCD_custom(tByte * arr){
    
    LCD_cmd(LCD_SET_CGRAM_ADDRESS);
    for(tByte i = 0; i < 8; i++){
        LCD_out(arr[i]);
    }
}

void LCD_update(void){
    
    
    static tByte LCD_counter = ZERO;
    static tByte Limit = 6;
    static tByte direction = 0;
    
    static tByte i = ZERO;
    
    LCD_counter += SYSTEM_TICK;
    
    
    if(LCD_counter < LCD_UPDATE_PERIOD){
        return;
    }
    
    LCD_counter = ZERO;
    
    if(direction == 0){
        LCD_cmd(LCD_DSP_CURS_CTRL_MASK | LCD_DSP_MOVE_CURS_FIX | LCD_DSP_CURS_MOVE_RIGHT);
        i++;
        if (i == 12) direction = 1;
    }
    
    if(direction == 1){
        LCD_cmd(LCD_DSP_CURS_CTRL_MASK | LCD_DSP_MOVE_CURS_FIX | LCD_DSP_CURS_MOVE_LEFT);
        i--;;
        if (i == 0) direction = 0;
    }
    /*
    for(i = 0; i < Limit; i++){
        LCD_char(' ',L1,i);
        LCD_char(' ',L2,i);
    }
    
    LCD_str("Ahmed",L1,Limit);
    LCD_str("Galal",L2,Limit);
    
    i = i + 5;
    
    while(i < 16){
         LCD_char(' ',L1,i);
         LCD_char(' ',L2,i++);
    }
    
    if(direction == 0) {
        Limit++;
        if((Limit + 5) == 16) direction = 1;
    }else if (direction == 1){
        Limit--;
        if(Limit == 0) direction = 0;
    }
     */
}
/* *** PRIVATE FUNCTIONS IMPLEMENTATION *** */

static void LCD_cmd(tByte cmd){

    /* *** MAKE RS PIN AS COMMAND SEND CMD *** */
    
    GPIO_PIN_WRITE(LCD_RS_VAL,LCD_RS_PIN,RS_COMMAND);
    LCD_out(cmd);
    __delay_us(50);
    
}

static void LCD_goTo(tLine line,tColumn col){

    
    tByte address;
            
    address = (line * LCD_L2_C1_ADDRESS) + col;

    LCD_cmd(LCD_SET_DDRAM_ADDRESS | address);
}

static void LCD_latch(void){
    
    /* *** SEND PULSE FROM HIGH TO LOW ON ENABLE PIN *** */
    
    GPIO_PIN_WRITE(LCD_EN_VAL,LCD_EN_PIN,GPIO_HIGH);
    __delay_us(1);
    GPIO_PIN_WRITE(LCD_EN_VAL,LCD_EN_PIN,GPIO_LOW);
    __delay_us(1);
    
}

static void LCD_out(tByte data){
    
    if(LCD_4_MODE == currentMode){
        
        /* *** SEND HIGHER NIBBLE  *** */
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_0,(data & (1 << 4)) >> 4);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_1,(data & (1 << 5)) >> 5);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_2,(data & (1 << 6)) >> 6);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_3,(data & (1 << 7)) >> 7);
        
        LCD_latch();
        
        __delay_us(100);
        /* *** SEND LOWER NIBBLE *** */
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_0,(data & (1 << 0)) >> 0);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_1,(data & (1 << 1)) >> 1);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_2,(data & (1 << 2)) >> 2);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_3,(data & (1 << 3)) >> 3);
        
        LCD_latch();
        __delay_us(100);
    }else {
        
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_0,(data & (1 << 0)) >> 0);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_1,(data & (1 << 1)) >> 1);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_2,(data & (1 << 2)) >> 2);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_3,(data & (1 << 3)) >> 3);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_4,(data & (1 << 4)) >> 4);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_5,(data & (1 << 5)) >> 5);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_6,(data & (1 << 6)) >> 6);
        GPIO_PIN_WRITE(LCD_DATA_VAL,LCD_DATA_PIN_7,(data & (1 << 7)) >> 7);
        LCD_latch();
        
    }
    
}

static void Convert_IntToString(tDword num,tByte ** ppstr){

    static tByte nStr [11]; /* ***  MAX NUMBER LENGTH  BECUASE MAX INT NUM IS OF LENGTH 10 *** */
    tByte i = 10;
    
    nStr[i] = '\0';
    
    while(num >= 0){
        i--;
        nStr[i] = (num == 0) ? '0' : ((num % 10) + '0');
        num = num / 10;
        if (num == 0)  break;
        
    }
    
    *ppstr = nStr + i; 

}