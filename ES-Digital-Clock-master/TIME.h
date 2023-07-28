/* 
 * File:   TIME.h
 * Author: Sohaib Dar
 *
 * Created on 09/06 2023, 10:56 AM
 */

#ifndef TIME_H
#define	TIME_H
#include "HARDWARE.h"

typedef struct {
  tByte secounds;
  tByte minutes;
  tByte hours;
}tTime;

typedef enum {
    MODE_NORMAL,
    MODE_ADJUST_MINUTES,
    MODE_ADJUST_HOURS
}tMode;

void time_init(void);
void get_time(tTime * time);
void get_mode(tMode * mode);
void time_update(void);
#endif	/* TIME_H */

