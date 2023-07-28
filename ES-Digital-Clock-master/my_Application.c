/*
 * File:   my_Application.c
 * Author: Sohaib Dar
 *
 * Created on 30/5/2023  10:43 AM
 */


#include <xc.h>
#include "SWITCH.h"
#include "TIME.h"
#include "DISPLAY.h"
#include "SSD.h"
#include "TIMER0.h"

/*
    Prototype static Function
*/
static void Hardware_Init(void);


void main(void) {
    
    Hardware_Init();
    
    while(1){
        switch_update();
        time_update();
        display_update();
        ssd_update();
        __delay_ms(5);
    }
}



static void Hardware_Init(void)
{
    time_init();
    display_init();
    switch_init(sw_plus);
    switch_init(sw_minus);
    switch_init(sw_setting);
    timer0_init(T0_PRESCALLER_256,T0_TIMER_MODE,T0_OVF_ENABLE);
    timer0_reload(216);
    T0_timer_mode_state(T0_ON);
}


void __interrupt (high_priority) APP_UPDATE(void){

    if(TMR0_OVF_FLAG){
        TMR0_OVF_FLAG = GPIO_LOW;
        timer0_reload(216);
        
        ssd_update();
        switch_update();
        time_update();
        display_update();
    }
    
}
