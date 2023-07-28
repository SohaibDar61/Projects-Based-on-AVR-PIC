/*
 * File:   MICRO_CONTROLLER.h
 * Author: Sohaib Dar
 *
 * Created on 30/5/2023, 70:03 AM
 */

#ifndef MICRO_CONTROLLER_H
#define	MICRO_CONTROLLER_H
#include "config.h"

#define     NO_MCU                      (0)
#define     PIC16F877A                  (1)
#define     PIC18F4620                  (2)
#define     ATMEGA32A                   (3)
#define     ATMEGA16A                   (4)

#define     MCU_NAME                    (PIC16F877A)   // MICRO CONTROLLER NAME


#if (MCU_NAME == PIC16F877A)


/* ************ DATA TYPES ****************** */

typedef     unsigned char               tByte;  // 8 bits
typedef     unsigned short int          tWord; // 16 bits

typedef union {
    tByte Reg;
    struct{
        tByte BIT0 : 1;
        tByte BIT1 : 1;
        tByte BIT2 : 1;
        tByte BIT3 : 1;
        tByte BIT4 : 1;
        tByte BIT5 : 1;
        tByte BIT6 : 1;
        tByte BIT7 : 1;
    }Bits;
}tRegister;

#define         MCU_OUTPUT                      (0)
#define         MCU_INPUT                       (1)

/* *************** GPIO REGISTERS *************** */

#define         TRISA_R                         (*((volatile tRegister *)(0x85)))
#define         TRISB_R                         (*((volatile tRegister *)(0x86)))
#define         TRISC_R                         (*((volatile tRegister *)(0x87)))
#define         TRISD_R                         (*((volatile tRegister *)(0x88)))
#define         TRISE_R                         (*((volatile tRegister *)(0x89)))

#define         PORTA_R                         (*((volatile tRegister *)(0x05)))
#define         PORTB_R                         (*((volatile tRegister *)(0x06)))
#define         PORTC_R                         (*((volatile tRegister *)(0x07)))
#define         PORTD_R                         (*((volatile tRegister *)(0x08)))
#define         PORTE_R                         (*((volatile tRegister *)(0x09)))


/* *************** GENERAL REGISTERS *************** */

#define         INTCON_R                        (*((volatile tRegister *)(0x0B)))
#define         OPTION_REG_R                    (*((volatile tRegister *)(0x81)))

/* *************** INERRUPT COMMANDS *************** */
#define         GLOBAL_INTERRUPT_ENABLE             (INTCON_R.Bits.BIT7 = 1)
#define         GLOBAL_INTERRUPT_DISABLE            (INTCON_R.Bits.BIT7 = 0)

/* *************** TIMER 0 REGISTERS *************** */
#define         TMR0_R                          (*((volatile tRegister *)(0x01)))
#define         PRESC_VAL_BIT0                  (OPTION_REG_R.Bits.BIT0)
#define         PRESC_VAL_BIT1                  (OPTION_REG_R.Bits.BIT1)
#define         PRESC_VAL_BIT2                  (OPTION_REG_R.Bits.BIT2)
#define         PRESC_ASSIGNMENT_BIT            (OPTION_REG_R.Bits.BIT3)
#define         PRESC_TO_WDT                    (1)
#define         PRESC_TO_TMR0                   (0)
#define         TMR0_EDGE_BIT                   (OPTION_REG_R.Bits.BIT4)
#define         TMR0_CS_BIT                     (OPTION_REG_R.Bits.BIT5)
#define         TMR0_OVF_INT_EN_BIT             (INTCON_R.Bits.BIT5)
#define         TMR0_OVF_FLAG_BIT               (INTCON_R.Bits.BIT2)

/* *************** TIMER 0 COMMANDS *************** */

typedef         unsigned char                   TMR0_SIZE;

#define         TMR0_PRESCALLER_2               PRESC_ASSIGNMENT_BIT = PRESC_TO_TMR0;\
                                                 PRESC_VAL_BIT0 = 0;\
                                                 PRESC_VAL_BIT1 = 0;\
                                                 PRESC_VAL_BIT2 = 0

#define         TMR0_PRESCALLER_4               PRESC_ASSIGNMENT_BIT = PRESC_TO_TMR0;\
                                                 PRESC_VAL_BIT0 = 1;\
                                                 PRESC_VAL_BIT1 = 0;\
                                                 PRESC_VAL_BIT2 = 0

#define         TMR0_PRESCALLER_8               PRESC_ASSIGNMENT_BIT = PRESC_TO_TMR0;\
                                                 PRESC_VAL_BIT0 = 0;\
                                                 PRESC_VAL_BIT1 = 1;\
                                                 PRESC_VAL_BIT2 = 0

#define         TMR0_PRESCALLER_16              PRESC_ASSIGNMENT_BIT = PRESC_TO_TMR0;\
                                                 PRESC_VAL_BIT0 = 1;\
                                                 PRESC_VAL_BIT1 = 1;\
                                                 PRESC_VAL_BIT2 = 0

#define         TMR0_PRESCALLER_32              PRESC_ASSIGNMENT_BIT = PRESC_TO_TMR0;\
                                                 PRESC_VAL_BIT0 = 0;\
                                                 PRESC_VAL_BIT1 = 0;\
                                                 PRESC_VAL_BIT2 = 1

#define         TMR0_PRESCALLER_64              PRESC_ASSIGNMENT_BIT = PRESC_TO_TMR0;\
                                                 PRESC_VAL_BIT0 = 1;\
                                                 PRESC_VAL_BIT1 = 0;\
                                                 PRESC_VAL_BIT2 = 1

#define         TMR0_PRESCALLER_128             PRESC_ASSIGNMENT_BIT = PRESC_TO_TMR0;\
                                                 PRESC_VAL_BIT0 = 0;\
                                                 PRESC_VAL_BIT1 = 1;\
                                                 PRESC_VAL_BIT2 = 1

#define         TMR0_PRESCALLER_256             PRESC_ASSIGNMENT_BIT = PRESC_TO_TMR0;\
                                                 PRESC_VAL_BIT0 = 1;\
                                                 PRESC_VAL_BIT1 = 1;\
                                                 PRESC_VAL_BIT2 = 1

#define         TMR0_VAL_REG                    (TMR0_R.Reg)
#define         TMR0_START_VAL                  (0xFF)
#define         TMR0_TIMER_MODE                 (TMR0_CS_BIT = 0)                
#define         TMR0_COUNTER_MODE               (TMR0_CS_BIT = 1) 
#define         TMR0_COUNT_RISING               (TMR0_EDGE_BIT = 0)
#define         TMR0_COUNT_FALLING              (TMR0_EDGE_BIT = 1)
#define         TMR0_OVF_INT_ENABLE             (TMR0_OVF_INT_EN_BIT = 1)             
#define         TMR0_OVF_INT_DISABLE            (TMR0_OVF_INT_EN_BIT = 0)
#define         TMR0_OVF_FLAG                   (TMR0_OVF_FLAG_BIT)
#define         TMR0_ON                         ()
#define         TMR0_OFF                        ()


#endif

#endif	/* MICRO_CONTROLLER_H */

