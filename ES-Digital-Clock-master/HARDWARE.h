/* 
 * File:   HARDWARE.h
 * Author: Sohaib Dar
 *
 * Created on 30/5/2023 07:07 Am
 */

#ifndef HARDWARE_H
#define	HARDWARE_H
#include "GPIO.h"

// SYSTEM
#define         SYSTEM_TICK                                                         (5) // 5 ms is HCF OF ALL TASKS

// SWITCHES 
#define         SW_PLUS_CTRL                                                        (GPIO_B_CTRL)
#define         SW_PLUS_DATA                                                        (GPIO_B_DATA)
#define         SW_PLUS_PIN                                                         (GPIO_PIN_0)

#define         SW_MINUS_CTRL                                                       (GPIO_B_CTRL)
#define         SW_MINUS_DATA                                                       (GPIO_B_DATA)
#define         SW_MINUS_PIN                                                        (GPIO_PIN_1)

#define         SW_SETTING_CTRL                                                     (GPIO_B_CTRL)
#define         SW_SETTING_DATA                                                     (GPIO_B_DATA)
#define         SW_SETTING_PIN                                                      (GPIO_PIN_2)

/* *** SSD DEFENITIONS ******** */

#define         SSD_MINUTE_UNITS_DATA_DIR                                           (GPIO_D_CTRL)
#define         SSD_MINUTE_UNITS_DATA_VAL                                           (GPIO_D_DATA)
#define         SSD_MINUTE_UNITS_CTRL_DIR                                           (GPIO_B_CTRL)
#define         SSD_MINUTE_UNITS_CTRL_VAL                                           (GPIO_B_DATA)
#define         SSD_MINUTE_UNITS_CTRL_PIN                                           (GPIO_PIN_4)

#define         SSD_MINUTE_TENS_DATA_DIR                                            (GPIO_D_CTRL)
#define         SSD_MINUTE_TENS_DATA_VAL                                            (GPIO_D_DATA)
#define         SSD_MINUTE_TENS_CTRL_DIR                                            (GPIO_B_CTRL)
#define         SSD_MINUTE_TENS_CTRL_VAL                                            (GPIO_B_DATA)
#define         SSD_MINUTE_TENS_CTRL_PIN                                            (GPIO_PIN_5)      

#define         SSD_HOUR_UNITS_DATA_DIR                                             (GPIO_D_CTRL)
#define         SSD_HOUR_UNITS_DATA_VAL                                             (GPIO_D_DATA)
#define         SSD_HOUR_UNITS_CTRL_DIR                                             (GPIO_B_CTRL)
#define         SSD_HOUR_UNITS_CTRL_VAL                                             (GPIO_B_DATA)
#define         SSD_HOUR_UNITS_CTRL_PIN                                             (GPIO_PIN_6)

#define         SSD_HOUR_TENS_DATA_DIR                                              (GPIO_D_CTRL)
#define         SSD_HOUR_TENS_DATA_VAL                                              (GPIO_D_DATA)
#define         SSD_HOUR_TENS_CTRL_DIR                                              (GPIO_B_CTRL)
#define         SSD_HOUR_TENS_CTRL_VAL                                              (GPIO_B_DATA)
#define         SSD_HOUR_TENS_CTRL_PIN                                              (GPIO_PIN_7)


#endif	/* HARDWARE_H */

