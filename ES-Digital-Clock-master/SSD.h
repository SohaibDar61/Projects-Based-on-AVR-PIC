/* 
 * File:   SSD.h
 * Author: Sohaib Dar
 *
 * Created on 06/06/2023   04:01  PM
 */

#ifndef SSD_H
#define	SSD_H


typedef enum  {
    SSD_0 ,
    SSD_1,
    SSD_2,
    SSD_3,
    SSD_4,
    SSD_5,
    SSD_6,
    SSD_7,
    SSD_8,
    SSD_9,
    SSD_NULL
}tSSD_SYMBOL;

typedef enum {
    ssd_minute_units = 0,
    ssd_minute_tens,
    ssd_hour_units,
    ssd_hour_tens
}tSSD;

typedef enum {
    DOT_OFF = 0,
    DOT_ON
}tDotState;

void ssd_init(tSSD);
void ssd_setSymbol(tSSD, tSSD_SYMBOL);
tSSD_SYMBOL ssd_getSymbol(tSSD);
void ssd_update(void);
void ssd_display(tSSD,tSSD_SYMBOL);
void ssdDot_setState(tDotState state);
tDotState ssdDot_getState();
#endif	/* SSD_H */

