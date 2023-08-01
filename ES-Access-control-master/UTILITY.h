/* 
 *** File:   UTILITY.h
 *** AUTHOR : Sohaib Dar
 *** DATE   : 12 / 3 /  2022
 */

#ifndef UTILITY_H
#define	UTILITY_H

/* *** PUBLIC INCLUDES *** */
#include "MICRO_CONTROLLER.h"

/* *** PUBLIC CONSTANTS *** */
/* *** PUBLIC DATATYPES *** */

typedef enum {
    SIMILAR,
    DISSIMILAR
}tCOMPARE_RESULT;

/* *** PUBLIC VARIABLES *** */
/* *** PUBLIC FUNCTIONS PROTOTYPE *** */

void UTIL_INTtoSTR(tDword num, tByte ** ppstr,tByte max);
void UTIL_FLOATtoSTR(tFloat64 num, tByte ** ppStr, tByte max);
tCOMPARE_RESULT UTIL_STRcompare(tByte * strA,tByte * strB);
void UTIL_STRcopy(tByte * source, tByte * destination);
tWord UTIL_STRlength(tByte * pStr);

#endif	/* UTILITY_H */

