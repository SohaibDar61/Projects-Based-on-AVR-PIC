/* 
    *** FILE : EEPROM.c 
    *** AUTHOR : Sohaib Dar
    *** DATE   : 12 / 5 /  2022
 */


/* *** PRIVATE INCLUDES *** */
#include "EEPROM.h"

/* *** PRIVATE CONSTANTS *** */
/* *** PRIVATE DATATYPES *** */
/* *** PRIVATE VARIABLES *** */
/* *** PRIVATE FUNCTIONS PROTOTYPE *** */
/* *** PUBLIC FUNCTIONS IMPLEMENTATIONS *** */

void EEPROM_init(tEEPROM_INTERRUPT_STATE state){
    
    if(state == EEPROM_INT_ENABLE){
        EEPROM_INTERRUPT_ENABLE;
        PERIPHERAL_INTERRUPT_ENABLE;
        GLOBAL_INTERRUPT_ENABLE;
    }else {
        EEPROM_INTERRUPT_DISABLE;
    }

}

void EEPROM_writeByte(tByte address, tByte data){
    
    /* *** CHECK ADDRESS *** */
    
    if(address >= EEPROM_START_ADDRESS && address <= EEPROM_END_ADDRESS){
        
        /* *** WAIT UNTIL EEPROM BE NOT BUSY *** */
       while(EEPROM_IS_BUSY);
        
        /* *** SET SELECTED ADDRESS *** */
        EEPROM_SET_ADDRESS(address);
        
        /* *** SET SELECTED DATA *** */
        EEPROM_SET_DATA(data);  
       

        /* *** READ GLOBAL INTERRUPT STATE *** */
        tByte state = GLOBAL_INTERRUPT_STATE;

        /* *** DISABLE GLOABAL INTERRUPT *** */
        GLOBAL_INTERRUPT_DISABLE;

        /* *** START WRITE SQUENCE *** */
        EEPROM_START_WRITE;
        
        /* *** SET GLOBAL INTERRUPT TO ITS PREVIOUS STATE *** */
        if (state){
            GLOBAL_INTERRUPT_ENABLE;
        }
    
    }
    
    
    
}

void EEPROM_readByte(tByte address, tByte *pData){

    /* *** CHEACK ADDRESS *** */
    
    if(address >= EEPROM_START_ADDRESS && address <= EEPROM_END_ADDRESS){
        
         /* *** SET SELECTED ADDRESS *** */
        EEPROM_SET_ADDRESS(address);
        
        /* *** WAIT UNTIL EEPROM BE NOT BUSY *** */
        while(EEPROM_IS_BUSY);
        
        /* *** START READ OPERATION *** */
        EEPROM_START_READ;
        
        /* *** READ DATA *** */
        *pData = EEPROM_GET_DATA;
    }
   
    
}

void EEPROM_write4Bytes(tByte startAddress, tDword data){
    
    if(startAddress >= EEPROM_START_ADDRESS && (startAddress + 3) <= EEPROM_END_ADDRESS){
         tByte oneByte;
        
        for (tByte i = 0; i < 4; i++){
            oneByte = (tByte)(data >> (8*i));
            EEPROM_writeByte(startAddress + i, oneByte);
        }
        
    }
    
}

void EEPROM_read4Bytes(tByte startAddress , tDword * pData){
    
     if(startAddress >= EEPROM_START_ADDRESS && (startAddress + 3) <= EEPROM_END_ADDRESS){
         tByte oneByte;
         tDword data = 0x00000000;
         
        for (tByte i = 0; i < 4; i++){
            EEPROM_readByte(startAddress + i, &oneByte);
            data |= ((tDword)oneByte) << (8 * i);
        }
        
         *pData = data;
    }
}

void EEPROM_writeStr(tByte startAddress, tByte * pStr){
    
    tByte i = 0;
    
    while(*pStr != '\0'){
        EEPROM_writeByte(startAddress + i,*pStr);
        i++;
        pStr++;
    }
    EEPROM_writeByte(startAddress + i,*pStr);
}

void EEPROM_readStr(tByte startAddress , tByte * pStr){
    
    tByte ch = 5;
    tByte i = 0;
    
    while (ch != '\0'){
        EEPROM_readByte(startAddress + i,&ch);
        pStr[i] = ch;
        i++;
    }
}


/* *** PRIVATE FUNCTIONS IMPLEMENTATIONS *** */