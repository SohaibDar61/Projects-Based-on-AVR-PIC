/* 
    *** FILE   : UTILITY.c
    *** AUTHOR : Sohaib Dar
    *** DATE   : 12 / 3 /  2022
 */

/* *** PRIVATE INCLUDES *** */
#include "UTILITY.h"

/* *** PRIVATE CONSTANTS *** */
/* *** PRIVATE DATATYPES *** */
/* *** PRIVATE VARIABLES *** */
/* *** PRIVATE FUNCTIONS PROTOTYPE *** */
/* *** PUBLIC FUNCTIONS IMPLEMENTATIONS *** */

void UTIL_INTtoSTR(tDword num, tByte ** ppStr,tByte max){
    
    (*ppStr)[--max] = '\0';
    
    if (num == 0) { 
        (*ppStr)[--max] = '0';
    }
    
    while(num > 0){
        (*ppStr)[--max] = (num % 10) + '0';
        num = num / 10;
    }
    
    (*ppStr) += max;
}

tCOMPARE_RESULT UTIL_STRcompare(tByte * strA,tByte * strB){
    
    tCOMPARE_RESULT res = DISSIMILAR;
    
    if(UTIL_STRlength(strA) > 0 && UTIL_STRlength(strB) > 0 ) {
        
        while (*strA != '\0' && *strB != '\0' && *strA == *strB){
            strA++;
            strB++;
        }
        if(*strA == '\0' && *strB == '\0'){
            res = SIMILAR;
        }
    }
    
    
    return res;
    
}

void UTIL_STRcopy(tByte * source, tByte * destination){
    
    while(*source != '\0'){
        *destination = *source;
        source++;
        destination++;
    }
    *destination = *source;
}

tWord UTIL_STRlength(tByte * pStr){
    
    tWord len = 0;
    
    while(*pStr != '\0'){
        len++;
        pStr++;
    }
    
    return len;
}