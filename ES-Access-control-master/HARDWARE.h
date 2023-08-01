/*
 *** File:   HARDWARE.h
 *** AUTHOR : Sohaib Dar
 *** DATE   : 12 / 4 /  2022
 */

#ifndef HARDWARE_H
#define	HARDWARE_H
#include "GPIO.h"

// SYSTEM
#define         SYSTEM_TICK                                                         (5) // 5 ms is HCF OF ALL TASKS

/* **** LED **** */

#define         TICK_CTRL                                                           (GPIO_C_CTRL)
#define         TICK_DATA                                                           (GPIO_C_DATA)
#define         TICK_PIN                                                            (GPIO_PIN_1)

#define         LED_CTRL                                                            (GPIO_C_CTRL)
#define         LED_DATA                                                            (GPIO_C_DATA)
#define         LED_PIN                                                             (GPIO_PIN_2)

/* *** SWITCHES *** */

#define         SW_PLUS_CTRL                                                        (GPIO_B_CTRL)
#define         SW_PLUS_DATA                                                        (GPIO_B_DATA)
#define         SW_PLUS_PIN                                                         (GPIO_PIN_0)

#define         SW_MINUS_CTRL                                                       (GPIO_B_CTRL)
#define         SW_MINUS_DATA                                                       (GPIO_B_DATA)
#define         SW_MINUS_PIN                                                        (GPIO_PIN_1)

#define         SW_DUST_CTRL                                                        (GPIO_B_CTRL)
#define         SW_DUST_DATA                                                        (GPIO_B_DATA)
#define         SW_DUST_PIN                                                         (GPIO_PIN_2)

/* *** SSD DEFENITIONS ******** */

#define         SSD_LOW_DATA_DIR                                                    (GPIO_D_CTRL)
#define         SSD_LOW_DATA_VAL                                                    (GPIO_D_DATA)
#define         SSD_LOW_CTRL_DIR                                                    (GPIO_B_CTRL)
#define         SSD_LOW_CTRL_VAL                                                    (GPIO_B_DATA)
#define         SSD_LOW_CTRL_PIN                                                    (GPIO_PIN_6)

#define         SSD_MID_DATA_DIR                                                    (GPIO_D_CTRL)
#define         SSD_MID_DATA_VAL                                                    (GPIO_D_DATA)
#define         SSD_MID_CTRL_DIR                                                    (GPIO_B_CTRL)
#define         SSD_MID_CTRL_VAL                                                    (GPIO_B_DATA)
#define         SSD_MID_CTRL_PIN                                                    (GPIO_PIN_5)

#define         SSD_HIGH_DATA_DIR                                                   (GPIO_D_CTRL)
#define         SSD_HIGH_DATA_VAL                                                   (GPIO_D_DATA)
#define         SSD_HIGH_CTRL_DIR                                                   (GPIO_B_CTRL)
#define         SSD_HIGH_CTRL_VAL                                                   (GPIO_B_DATA)
#define         SSD_HIGH_CTRL_PIN                                                   (GPIO_PIN_4)

/* **** MOTOR **** */

#define         MOTOR_CTRL                                                          (GPIO_C_CTRL)
#define         MOTOR_DATA                                                          (GPIO_C_DATA)
#define         MOTOR_PIN                                                           (GPIO_PIN_2)


/*  *** LCD  *** */

#define         LCD_DATA_CTRL                                                       (GPIO_D_CTRL)
#define         LCD_DATA_VAL                                                        (GPIO_D_DATA)

#define         LCD_RS_CTRL                                                         (GPIO_E_CTRL)
#define         LCD_RS_VAL                                                          (GPIO_E_DATA)
#define         LCD_RS_PIN                                                          (GPIO_PIN_0)

#define         LCD_EN_CTRL                                                         (GPIO_E_CTRL)
#define         LCD_EN_VAL                                                          (GPIO_E_DATA)
#define         LCD_EN_PIN                                                          (GPIO_PIN_1)

#define         LCD_DATA_PIN_0                                                      (GPIO_PIN_0)
#define         LCD_DATA_PIN_1                                                      (GPIO_PIN_1)
#define         LCD_DATA_PIN_2                                                      (GPIO_PIN_2)
#define         LCD_DATA_PIN_3                                                      (GPIO_PIN_3)

#define         LCD_DATA_PIN_4                                                      (GPIO_PIN_4)
#define         LCD_DATA_PIN_5                                                      (GPIO_PIN_5)
#define         LCD_DATA_PIN_6                                                      (GPIO_PIN_6)
#define         LCD_DATA_PIN_7                                                      (GPIO_PIN_7)

/* *** KEYPAD *** */

    /* ** REMEMBER : CONNECT ROWS ON LOWER NIBBLE AND COLUMNS ON HIGHER NIBBLE ** */
    /* ** COL3 , COL2, COL1, COL0, ROW3, ROW2, ROW1, ROW0 ** */

#define         KPAD_CTRL                                                           (GPIO_B_CTRL)
#define         KPAD_DATA                                                           (GPIO_B_DATA)



#endif	/* HARDWARE_H */

