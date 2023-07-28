/* 
 * File:   SWITCH.h
 * Author: Sohaib Dar
 *
 * Created on 06/06/2023   05:01  PM
 */

#ifndef SWITCH_H
#define SWITCH_H

#define     N_SWITCHES              (3)  // Number of switches

typedef enum {
    sw_plus = 0,
    sw_minus,
    sw_setting
}tSwitch;

typedef enum {
    sw_released,
    sw_prepressed,
    sw_pressed,
    sw_prereleased
}tSw_State;

void switch_init(tSwitch);
tSw_State switch_getState(tSwitch);
void switch_setState(tSwitch,tSw_State);
void switch_update(void);
#endif

