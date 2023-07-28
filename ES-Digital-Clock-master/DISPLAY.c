/* 
 * File:   DISPLAY.c
 * Author: Sohaib Dar
 *
 * Created on 06/06/2023   02:01  PM
 */

/*
    INCLUDES
*/
#include "TIME.h"
#include "SSD.h"

#define         DISPLAY_PERIOD              (20)
#define         MODE_BLINK_PERIOD           (500)
#define         DOT_BLINK_PERIOD            (1000)
#define         ZERO                        (0)

static tTime display_time;
static tMode display_mode;
static tWord dot_blink_counter = ZERO;
static tWord mode_blink_counter = ZERO;

/*
    Prototype Static Function
*/
static void normal_mode_display(void);
static void adjust_hours_mode_display(void);
static void adjust_minutes_mode_display(void);



void display_init(void){
    
    get_time(&display_time);
    
    ssd_init(ssd_minute_units);
    ssd_init(ssd_minute_tens);
    ssd_init(ssd_hour_units);
    ssd_init(ssd_hour_tens);
    
    ssd_setSymbol(ssd_minute_units , display_time.minutes % 10);
    ssd_setSymbol(ssd_minute_tens , display_time.minutes / 10);
    ssd_setSymbol(ssd_hour_units , display_time.hours % 10);
    ssd_setSymbol(ssd_hour_tens , display_time.hours / 10);
    ssdDot_setState(DOT_OFF);
}

void display_update(void){
    
    static tByte current_disp_period = ZERO;
    
    
    current_disp_period += SYSTEM_TICK;
    dot_blink_counter += SYSTEM_TICK;
    mode_blink_counter += SYSTEM_TICK;
    
    if(current_disp_period < DISPLAY_PERIOD){
        return;
    }
    
    current_disp_period = ZERO;
    
    
    get_time(&display_time);
    get_mode(&display_mode);
    
    
    switch(display_mode){
        
        case MODE_NORMAL :
            
            normal_mode_display();
  
            break;
            
        case MODE_ADJUST_HOURS :
            
            adjust_hours_mode_display();
            
            break;
            
        case MODE_ADJUST_MINUTES :

            adjust_minutes_mode_display();
            
        break;
        
        default : 
            /* DO NOTHING */
            break;
    }
}

static void normal_mode_display(void){
    ssd_setSymbol(ssd_minute_units , display_time.minutes % 10);
    ssd_setSymbol(ssd_minute_tens , display_time.minutes / 10);
    ssd_setSymbol(ssd_hour_units , display_time.hours % 10);
    ssd_setSymbol(ssd_hour_tens , display_time.hours / 10);
    if(dot_blink_counter == DOT_BLINK_PERIOD){
        dot_blink_counter = ZERO;
        ssdDot_setState(!ssdDot_getState());
    }
    mode_blink_counter = ZERO;
}

static void adjust_hours_mode_display(void){
    ssd_setSymbol(ssd_minute_units , display_time.minutes % 10);
    ssd_setSymbol(ssd_minute_tens , display_time.minutes / 10);
    ssdDot_setState(DOT_OFF);

    if(mode_blink_counter == MODE_BLINK_PERIOD){
        mode_blink_counter = ZERO;
        if(ssd_getSymbol(ssd_hour_units) == SSD_NULL){
            ssd_setSymbol(ssd_hour_units , display_time.hours % 10);
            ssd_setSymbol(ssd_hour_tens , display_time.hours / 10);   
        }else {
            ssd_setSymbol(ssd_hour_units , SSD_NULL);
            ssd_setSymbol(ssd_hour_tens ,  SSD_NULL);   
        }
    }else { /* DO NOTHING */}
    dot_blink_counter = ZERO;   
}

static void adjust_minutes_mode_display(void){
    
    ssd_setSymbol(ssd_hour_units , display_time.hours % 10);
    ssd_setSymbol(ssd_hour_tens , display_time.hours / 10);
    ssdDot_setState(DOT_OFF);
    
    if(mode_blink_counter == MODE_BLINK_PERIOD){
        mode_blink_counter = ZERO;
        if(ssd_getSymbol(ssd_minute_units) == SSD_NULL){
            ssd_setSymbol(ssd_minute_units , display_time.minutes % 10);
            ssd_setSymbol(ssd_minute_tens , display_time.minutes / 10);   
        }else {
            ssd_setSymbol(ssd_minute_units , SSD_NULL);
            ssd_setSymbol(ssd_minute_tens ,  SSD_NULL);   
        }
    }else { /* DO NOTHING */}
    
    dot_blink_counter = ZERO;   
}