/*****************************************************
 * FileName:        bsp.h
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
////////////////////////////////////////////////////////////////////////////////////////////////////
 * * Copyright (C) 2024 by  JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTES- TecNM /IT Chihuahua
 *
 * Se permite la redistribucion, modificacion o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 *  JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTESy el TecNM /IT Chihuahua no son responsables del mal uso de este material.
 *************************************************************************************************/

/************************************************
       SOURCE DEFINITIONS
************************************************/

#define VCC 1
#define GND 0

#define HIGH  VCC
#define LOW   GND

#define RGB_HIGH  GND // REVERSE LOGIC FOR RGB
#define RGB_LOW   VCC

/************************************************
        RESISTENCES DEINITIONS
************************************************/
#define PULL_UP   8
#define PULL_DOWN 7

/************************************************
      MAP OF BOARD  ESP32-PANTHER48
************************************************/

#define BTN1    18     //   0x40000 IO 18
#define BTN2    19     //   0x80000 IO 19

#define LED_1     17   // IO 17
#define LED_2     16   // IO 16
#define LED_3     4    // IO 4
#define LED_4     2    // IO 2
#define LED_B     5    // IO 5


#define RGB_RED     14 // IO 14
#define RGB_GREEN   13 // IO 12
#define RGB_BLUE    12  // IO 13

#define MAX_VALID_PIN  39
#define MAX_OUTPUT_PIN 34


/************************************************
      MAP OF BOARD MOTORS  ESP32-PANTHER48
************************************************/ // PINES DE EJEMPLO
#define GPIO_UP 2
#define GPIO_DOWN 4
#define GPIO_UP2 16
#define GPIO_DOWN2 17
#define LED_CAR 5


