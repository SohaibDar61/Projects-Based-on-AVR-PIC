/* 
 * File:   SSD.c
 * Author: Sohaib Dar
 *
 * Created on 06/06/2023   04:01  PM
 */

#include "SSD.h"
#include "GPIO.h"
#include "HARDWARE.h"

#define         ANODE                                                               (1)
#define         CATHODE                                                             (0)
#define         SSD_NUMBERS                                                         (4)
#define         N_SYMBOLS                                                           (11)
#define         SSD_COMMON                                                          (CATHODE)
#define         SSD_ON_LEVEL                                                        (GPIO_HIGH)
#define         SSD_OFF_LEVEL                                                       (GPIO_LOW)
#define         SSD_UPDATE_PERIOD_MS                                                (5) // 5 ms
#define         DOT_PIN                                                             (GPIO_PIN_7)

typedef struct {
    tByte * data_direction_reg;
    tByte * data_value_reg;
    tByte * ctrl_direction_reg;
    tByte * ctrl_value_reg;
    tByte ctrl_pin;
    tSSD_SYMBOL symbol;
}tSSD_INFO;

/* PRIVATE VARIBLES */

static tSSD_INFO ssd_data[SSD_NUMBERS];
static tSSD current_ssd = ssd_minute_units;
static tDotState dot_state;   

#if (SSD_COMMON == CATHODE)
static tByte ssd_decoder[N_SYMBOLS] = {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F,0X00};//   COMMON CATHODE
#elif (SSD_COMMON == ANODE)
static tByte ssd_decoder[N_SYMBOLS] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF}; //  COMMON  ANODE
#endif


/* **** PRIVATE FUNCTIONS **** */
static void ssd_schematic_init(void);
static void dot_display(tDotState);
static void ssd_on(tSSD);
static void ssd_off(tSSD);
/* **** END : PRIVATE FUNCTIONS **** */

void ssd_init(tSSD ssd){
    
        ssd_schematic_init();
    // MAKE DATA PINS OUTPUT
    GPIO_PORT_DIRECTION(*(ssd_data[ssd].data_direction_reg),GPIO_OUTPUT);
    // WRITE SYMBOL ON DATA PINS;
    ssd_display(ssd,SSD_NULL);
    
    // MAKE CTRL PIN OUTPUT AND MAKE IT OFF
    GPIO_PIN_DIRECTION(*(ssd_data[ssd].ctrl_direction_reg),ssd_data[ssd].ctrl_pin,GPIO_OUTPUT);
    GPIO_PIN_WRITE(*(ssd_data[ssd].ctrl_value_reg),ssd_data[ssd].ctrl_pin,SSD_OFF_LEVEL);
     
    
}
void ssd_setSymbol(tSSD ssd, tSSD_SYMBOL symbol){
    ssd_data[ssd].symbol = symbol;
}
tSSD_SYMBOL ssd_getSymbol(tSSD ssd){
    return ssd_data[ssd].symbol;
}

void ssd_update(void){
    static tByte ssd_update_counter = 0;
    
    ssd_update_counter += SYSTEM_TICK;
    
    if (ssd_update_counter == SSD_UPDATE_PERIOD_MS){
        ssd_update_counter = 0;
        
         tByte index = 0;
    
        // TURN OFF ALL SSDS

        for(index = ssd_minute_units; index < SSD_NUMBERS; index++){
            ssd_off(index);
        }

        // DISPLAY CURRENT SSD DATA
        ssd_display(current_ssd,ssd_data[current_ssd].symbol);
        
        
        // TURN ON CURRENT SSD

        ssd_on(current_ssd);

        // CURRENT SSD = NEXT SSD

        current_ssd++;
        current_ssd = current_ssd % SSD_NUMBERS;
    
    }else {
        // Do nothing
    }
   
}

static void ssd_schematic_init(void){
    /* *** CREATE YOUR SSD HERE *** */
    
     ssd_data[0] = (tSSD_INFO){&SSD_MINUTE_UNITS_DATA_DIR,&SSD_MINUTE_UNITS_DATA_VAL,&SSD_MINUTE_UNITS_CTRL_DIR,&SSD_MINUTE_UNITS_CTRL_VAL,SSD_MINUTE_UNITS_CTRL_PIN,SSD_NULL}; 
     ssd_data[1] = (tSSD_INFO){&SSD_MINUTE_TENS_DATA_DIR,&SSD_MINUTE_TENS_DATA_VAL,&SSD_MINUTE_TENS_CTRL_DIR,&SSD_MINUTE_TENS_CTRL_VAL,SSD_MINUTE_TENS_CTRL_PIN,SSD_NULL};
     ssd_data[2] = (tSSD_INFO){&SSD_HOUR_UNITS_DATA_DIR,&SSD_HOUR_UNITS_DATA_VAL,&SSD_HOUR_UNITS_CTRL_DIR,&SSD_HOUR_UNITS_CTRL_VAL,SSD_HOUR_UNITS_CTRL_PIN,SSD_NULL};
     ssd_data[3] = (tSSD_INFO){&SSD_HOUR_TENS_DATA_DIR,&SSD_HOUR_TENS_DATA_VAL,&SSD_HOUR_TENS_CTRL_DIR,&SSD_HOUR_TENS_CTRL_VAL,SSD_HOUR_TENS_CTRL_PIN,SSD_NULL};
     /* *** END : CREATE YOUR SSD HERE *** */
     
}
 void ssd_display(tSSD ssd, tSSD_SYMBOL symbol){
    GPIO_PORT_WRITE(*(ssd_data[ssd].data_value_reg),ssd_decoder[symbol]);
    if(ssd == ssd_hour_units) {
        dot_display(dot_state);
    }else {
        // DO NOTHING
    }
}

static void ssd_on (tSSD ssd){
    GPIO_PIN_WRITE(*(ssd_data[ssd].ctrl_value_reg),ssd_data[ssd].ctrl_pin,SSD_ON_LEVEL);
}

static void ssd_off(tSSD ssd){
    GPIO_PIN_WRITE(*(ssd_data[ssd].ctrl_value_reg),ssd_data[ssd].ctrl_pin,SSD_OFF_LEVEL);
}

void ssdDot_setState(tDotState state){
    dot_state = state;
}
tDotState ssdDot_getState(){
    return dot_state;
}

static void dot_display(tDotState state){
    GPIO_PIN_WRITE(*(ssd_data[ssd_hour_units].data_value_reg),DOT_PIN,state);
}