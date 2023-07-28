/* 
 * File:   SWITCH.C
 * Author: Sohaib Dar
 *
 * Created on 06/06/2023   05:01  PM
 */

#include "MICRO_CONTROLLER.h"
#include "HARDWARE.h"
#include "GPIO.h"
#include "SWITCH.h"



#define     SWITCH_UPDATE_PERIOD    (20)  // 20 ms becuase Baouncing time is maximam 20 ms
#define     N_SAMPLES               (2)  // Samples for each switch


#define     SW_RELEASED_LEVEL       (GPIO_HIGH) // HIGH LEVEL 
#define     SW_PRESSED_LEVEL        (GPIO_LOW)  // LOW LEVEL

#define     OLDER                   (0) // older sample index
#define     NEWER                   (1) // newer sample index

typedef struct {
    volatile tByte * ctrl_reg;
    volatile tByte * data_reg;
    tByte pin_number;
    tByte samples[N_SAMPLES];
    tSw_State state;
}tSwitch_Info;

static tSwitch_Info switches_data[N_SWITCHES];

static void switches_Schematic_init(void);
/* INTIALIZE CHOOSED SWITCH*/

void switch_init(tSwitch sw){
    
    tByte index = 0;
    
    switches_Schematic_init();
    //make  switch pin as input
    
    GPIO_PIN_DIRECTION(*(switches_data[sw].ctrl_reg),switches_data[sw].pin_number,GPIO_INPUT);
    
    // Intialization samples as Released LEVEL and make state as released
    
    for (index = 0; index < N_SAMPLES;index++){
        
        switches_data[sw].samples[index] = SW_RELEASED_LEVEL;
    }
    
    switches_data[sw].state = sw_released;
}

tSw_State switch_getState(tSwitch sw){
    // return switch state
    tSw_State ret;
    
    ret = switches_data[sw].state;
    
    return ret;
    
}
void switch_setState(tSwitch sw ,tSw_State state){
    // set switch state
    switches_data[sw].state = state;
}

void switch_update(void){
    
    static tByte sw_update_counter = 0;
    tByte sw_index = 0;
    tByte sample_index = 0;
    sw_update_counter = sw_update_counter + SYSTEM_TICK;
    
    //CHECK THE PERIOD IS PASSED
    
    if(sw_update_counter == SWITCH_UPDATE_PERIOD){
        
        sw_update_counter = 0;
        
        for(sw_index = sw_plus; sw_index < N_SWITCHES; sw_index++){
            
            //SHIFT OLD SAMPLES
            for(sample_index = 0; sample_index < N_SAMPLES - 1; sample_index++){
                switches_data[sw_index].samples[sample_index] = switches_data[sw_index].samples[sample_index + 1];
            }
            
           // ADD NEW SAMPLE
            switches_data[sw_index].samples[N_SAMPLES - 1] = GPIO_PIN_READ(*(switches_data[sw_index].data_reg),switches_data[sw_index].pin_number);
            
            // DECIDE THE CURRENT STATE FROM PREVIOUS STATE AND CURRENT SAMPLES
            
            // IF (RELEASED AND PRESSED_LEVEL AND PRESSED_LEVEL >>  MOVE TO PRE_PRESSED)
            if(switches_data[sw_index].state == sw_released &&
               switches_data[sw_index].samples[N_SAMPLES - 2] == SW_PRESSED_LEVEL &&
               switches_data[sw_index].samples[N_SAMPLES - 1] == SW_PRESSED_LEVEL
               )
            {
                switches_data[sw_index].state = sw_prepressed;
            } 
            // IF (PREPRESSED AND PRESSED_LEVEL  >> MOVE TO PRESSED)
            else if(switches_data[sw_index].state == sw_prepressed && switches_data[sw_index].samples[N_SAMPLES - 1] == SW_PRESSED_LEVEL) 
            {
                switches_data[sw_index].state = sw_pressed;
            }
            // IF (PRESSED AND RELEASED_LEVEL AND RELEASED_LEVEL >>  MOVE TO PRE_PRERELEASED)
            else if(switches_data[sw_index].state == sw_pressed &&
                    switches_data[sw_index].samples[N_SAMPLES - 2] == SW_RELEASED_LEVEL &&
                    switches_data[sw_index].samples[N_SAMPLES - 1] == SW_RELEASED_LEVEL
                   )
                   {
                        switches_data[sw_index].state = sw_prereleased;
                   }
            // IF (PRERELEASED AND RELEASED_LEVEL  >> MOVE TO PRESSED)
            else if(switches_data[sw_index].state == sw_prereleased && switches_data[sw_index].samples[N_SAMPLES - 1] == SW_RELEASED_LEVEL)
            {
                switches_data[sw_index].state = sw_released;
            }else {/* do nothing */}
            
        }
        
    }else {
        // do nothing 
    }
}

static void switches_Schematic_init(void){
    
    // SW_PLUS
    
    switches_data[sw_plus].ctrl_reg         = &SW_PLUS_CTRL;
    switches_data[sw_plus].data_reg         = &SW_PLUS_DATA;
    switches_data[sw_plus].pin_number       = SW_PLUS_PIN;
    
    // SW_minus
    
    switches_data[sw_minus].ctrl_reg        = &SW_MINUS_CTRL;
    switches_data[sw_minus].data_reg        = &SW_MINUS_DATA;
    switches_data[sw_minus].pin_number      = SW_MINUS_PIN;
    
    // SW_SETTING
    
    switches_data[sw_setting].ctrl_reg      = &SW_SETTING_CTRL;
    switches_data[sw_setting].data_reg      = &SW_SETTING_DATA;
    switches_data[sw_setting].pin_number    = SW_SETTING_PIN;
    
}