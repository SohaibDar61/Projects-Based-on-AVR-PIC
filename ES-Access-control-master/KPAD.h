/* 
 *** File:   KPAD.h
 *** AUTHOR : Sohaib Dar
 *** DATE   : 12 / 4 /  2022
 */

#ifndef KPAD_H
#define	KPAD_H

/* *** PUBLIC INCLUDES *** */
#include "MICRO_CONTROLLER.h"

/* *** PUBLIC CONSTANTS *** */
#define     NULL_KEY                (0)
/* *** PUBLIC DATATYPES *** */
/* *** PUBLIC VARIABLES *** */
/* *** PUBLIC FUNCTIONS PROTOTYPE *** */

void KPAD_init(void);
void KPAD_getKey(tByte * );
void KPAD_waitKey(tByte *);

#endif	/* KPAD_H */

