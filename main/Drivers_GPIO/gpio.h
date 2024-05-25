/*****************************************************
 * FileName:        gpio.h
 * Dependencies:
 * Processor:       ESP32
 * Board:           ESP32-PANTHER48
 * Program version: Espressif-IDE
 * Company:         TecNM /IT Chihuahua
 * Description:     PROTOTIPOS DE FUNCIONES DEL DRIVER
 * Authors:         JORGE GABRIEL LOZANO RODRIGUEZ
 *                  PEDRO MANCINAS HERNANDEZ
 *                  RAÚL MONTES MONTES
 * Nota: La interfaz definida de este DRIVER hace uso de las estructuras
 *       declarados en gpio_config_2021.h
 *  Created on: 15 de mayo del 2024
 *  updated: 20/11/2021
 **************************************************/
/************************************************************************************************
 * * Copyright (C) 2024 by JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTES  - TecNM /IT Chihuahua
 *
 * Se permite la redistribucion, modificacion o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 * JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTES  y el TecNM /IT Chihuahua no son responsables del mal uso de este material.
 *************************************************************************************************/
#include "addresses.h"
#ifndef GPIO_H
#define GPIO_H
/************************************************
            IO_MUX_x_REG  ADDRESSES MAP
************************************************/

volatile uint32_t GPIO_PINX_REG[] = {
		IO_0_REG,
		IO_1_REG,
		IO_2_REG,
		IO_3_REG,
		IO_4_REG,
		IO_5_REG,
		IO_6_REG,
		IO_7_REG,
		IO_8_REG,
		IO_9_REG,
		IO_10_REG,
		IO_11_REG,
		IO_12_REG,
		IO_13_REG,
		IO_14_REG,
		IO_15_REG,
		IO_16_REG,
		IO_17_REG,
		IO_18_REG,
		IO_19_REG,
		IO_20_REG,
		IO_21_REG,
		IO_22_REG,
		IO_23_REG,
		0x00,
		IO_25_REG,
		IO_26_REG,
		IO_27_REG,
		0x00,
		0x00,
		0x00,
		0x00,
		IO_32_REG,
		IO_33_REG,
		I_34_REG,
		I_35_REG,
		I_36_REG,
		I_37_REG,
		I_38_REG,
		I_39_REG,
};


/************************************************
             RTC MAP
************************************************/
 volatile uint32_t GPIO_RTC_X[] = {
      RTC_11,   // IO_0_REG
      0x00,     // IO_1_REG
      RTC_12,   // IO_2_REG
      0x00,     // IO_3_REG
      RTC_10,   // IO_4_REG
      0x00,     // IO_5_REG
      0x00,     // IO_6_REG
      0x00,     // IO_7_REG
      0x00,     // IO_8_REG
      0x00,     // IO_9_REG
      0x00,     // IO_10_REG
      0x00,     // IO_11_REG
      RTC_15,   // IO_12_REG
      RTC_14,   // IO_13_REG
      RTC_16,   // IO_14_REG
      RTC_13,   // IO_15_REG
      0x00,     // IO_16_REG
      0x00,     // IO_17_REG
      0x00,     // IO_18_REG
      0x00,     // IO_19_REG
      0x00,     // IO_20_REG
      0x00,     // IO_21_REG
      0x00,     // IO_22_REG
      0x00,     // IO_23_REG
      0x00,     // 0x00
      RTC_6,    // IO_25_REG
      RTC_7,    // IO_26_REG
      RTC_17,   // IO_27_REG
      0x00,     // 0x00
      0x00,     // 0x00
      0x00,     // 0x00
      0x00,     // 0x00
      RTC_9,    // IO_32_REG
      RTC_8,    // IO_33_REG
      RTC_4,    // I_34_REG
      RTC_5,    // I_35_REG
      RTC_0,    // I_36_REG
      RTC_1,    // I_37_REG
      RTC_2,    // I_38_REG
      RTC_3     // I_39_REG
 };

/************************************************
             FUCTION PROTOTYPE OF GPIO
************************************************/
extern void ini_board_GPIO();
extern void GPIO_OUT(uint_fast16_t selectedPins);
extern void GPIO_WRITTE(uint_fast16_t selectedPins, uint_fast8_t state);
extern void GPIO_INPUT(uint_fast16_t selectedPins, uint_fast16_t MODE_PULL);
extern int  GPIO_READ(uint_fast16_t selectedPins);

/************************************************
             FUCTION PROTOTYPE OF CAR
************************************************/
extern void start_CAR();

extern void MOTOR_UP();
extern void MOTOR_DOWN();
extern void MOTOR_RIGHT();
extern void MOTOR_LEFT();
extern void MOTOR_STOP();
extern void MOTOR_LED_ON();
extern void MOTOR_LED_OFF();
#endif // GPIO_H
