/* 
 * File:   TIME.c
 * Author: Sohaib Dar
 *
 * Created on 09/06 2023, 10:56 AM
 */

#include "TIME.h"
#include "SWITCH.h"

/* *********** PRIVATE CONSTANTS ******************* */

#define        TIME_UPDATE_PERIOD           (20)
#define        SECOND_PERIOD                (1000)
#define        RESET_ZERO                   (0)
#define        N_HOURS                      (24)
#define        N_MINUTES                    (60)
#define        N_SECOUNDS                   (60)

/* *********** PRIVATE VARIABLES ******************* */

static tTime current_time;
static tMode current_mode;
static tWord current_sec_period;

/* *********** PRIVATE FUNCTIONS PROTOTYPES ******************* */

static void sw_plus_handler(void);
static void sw_minus_handler(void);
static void sw_setting_handler(void);
static void update_current_time(void);

/* *********** PUBLIC FUNCTIONS BODY ******************* */

void time_init(void){
    
    /* *********** SET CURRENT TIME TO 00:00:00 ******************* */
    
    current_time.secounds = 0;
    
    current_time.minutes = 0;
    
    current_time.hours = 0;
    
    /* *********** SET CURRENT MODE TO NORMAL ******************* */
    
    current_mode = MODE_NORMAL;
}

void get_time(tTime * time){
    
    /* *********** PUT CURRENT_TIME DATA IN ARGUMENT TIME ******************* */
    
    time->secounds = current_time.secounds;
    
    time->minutes = current_time.minutes;
    
    time->hours = current_time.hours;
    
}
void get_mode(tMode * mode){
   
    /* *********** PUT CURRENT MODE IN ARGUMENT MODE ******************* */
    
    *(mode) = current_mode;
}
void time_update(void){
    
    static tByte current_period = RESET_ZERO;
    
    /* *********** INCREASE CURRENT PERIOD AND  SECOUND PERIOD ******************* */
    
    current_period =  current_period + SYSTEM_TICK;
    
    current_sec_period = current_sec_period + SYSTEM_TICK;
   
    /* *********** CHECK CURRENT PERIOD ******************* */
    
        if (current_period == TIME_UPDATE_PERIOD){
      
            /* *********** IF TRUE RESET PERIOD AND MAKE THE LOGIC ******************* */
            
            current_period = RESET_ZERO;
            
            /* *********** READ EACH SWITCH STATE IF PRESSED >> HANDLE IT ******************* */
            
            tByte index = 0;
            
            for(index = sw_plus; index < N_SWITCHES; index++){
                
                switch(index){
                    case sw_plus :  
                        // IF SW_PLUS IS PRESSED AND CURRENT_MODE NOT NORMAL SO HANDLE IT
                 
                        ((switch_getState(sw_plus) == sw_prepressed) && (current_mode != MODE_NORMAL)) ?  sw_plus_handler() : 0 /* do nothing */ ;
                        
                        break;
                        
                     case sw_minus : 
                         // IF SW_MINUS IS PRESSED AND CURRENT_MODE NOT NORMAL SO HANDLE IT
                         
                        ((switch_getState(sw_minus) == sw_prepressed) && (current_mode != MODE_NORMAL)) ?  sw_minus_handler() : 0 /* do nothing */ ;
                        
                        break;
                        
                     case sw_setting :
                         // IF SW_SETTING IS PRESSED SO HANDLE IT
                         
                        (switch_getState(sw_setting) == sw_prepressed) ?  sw_setting_handler() : 0 /* do nothing */ ;
                        
                        break;
                        
                    default : 
                        /* DO NOTHING */
                        break;
                }
                
            }
            
            /* *********** UPDATE TIME ******************* */

                    update_current_time();
                        
        }else {
            // do nothing
        }
}


/* ************ STATIC FUNCTIONS BODY *********** */

static void sw_plus_handler(void){

    
    switch(current_mode){
        
        case MODE_ADJUST_HOURS:
            current_time.hours = (current_time.hours + 1) % N_HOURS;
            break;
        case MODE_ADJUST_MINUTES: 
            current_time.minutes = (current_time.minutes + 1) % N_MINUTES;
            break;
        default : 
            /* ** DO NOTHING ** */
            break;
    }
}

static void sw_minus_handler(void){
    switch(current_mode){
        
        case MODE_ADJUST_HOURS:
            current_time.hours--;
            if(current_time.hours == 255){current_time.hours = N_HOURS - 1;}
              /* ** 255 BECAUSE WE USE UNSIGNED CHAR ** */
            break;
        case MODE_ADJUST_MINUTES:
            current_time.minutes--;
            if(current_time.minutes == 255 ){ current_time.minutes = N_MINUTES - 1;}
            //current_time.minutes = (current_time.minutes - 1) % 255;
            break;
        default : 
            /* ** DO NOTHING ** */
            break;
    }
}

static void sw_setting_handler(void){
    // if  current_mode is normal >> move to adjust_hours_mode
    switch(current_mode){
        /* *********** IF CURRENT IS NORMAL MOVE TO ADJUST HOURS ******************* */
        case MODE_NORMAL :
            
            current_mode  = MODE_ADJUST_HOURS;
            
            break;
             /* *********** IF CURRENT IS ADJUST HOURS MOVE TO ADJUST MINUTES ******************* */
        case MODE_ADJUST_HOURS :
            
            current_mode  = MODE_ADJUST_MINUTES;
            
            break;
            /* *********** IF CURRENT IS ADJUST MINUTES MOVE TO NORMAL AND RESET TIME SECONDS AND CURRENT SECOUND PERIOD ******************* */
        case MODE_ADJUST_MINUTES :
            
            current_mode  = MODE_NORMAL;
            
            current_time.secounds = RESET_ZERO;
            
            current_sec_period = RESET_ZERO;
            
            break;
            
        default : 
            /* *********** DO NOTHING ******************* */
            break;
         
    }
}

static void update_current_time(void){
    
    if( ( current_mode == MODE_NORMAL ) && ( current_sec_period >= SECOND_PERIOD )){
        current_sec_period = RESET_ZERO;
        current_time.secounds++;
        //dot_set_state(GPIO_ON);
        if(current_time.secounds == N_SECOUNDS){
            current_time.secounds = RESET_ZERO;
            current_time.minutes++;
            if(current_time.minutes == N_MINUTES){
                current_time.minutes = RESET_ZERO;
                current_time.hours++;
            }else {/* DO NOTHING */}
            
            current_time.hours = current_time.hours % N_HOURS;
        }else { /* DO NOTHING */ }
    }else {
        /* DO NOTHING */
    }
}