/*****************************************************
 * FileName:        bsp.h
 * Dependencies:
 * Processor:       ESP32
 * Board:           ESP32-PANTHER48
 * Program version: Espressif-IDE
 * Company:         TecNM /IT Chihuahua
 * Description:     PROTOTIPOS DE FUNCIONES DEL DRIVER
 * Authors:         JORGE GABRIEL LOZANO RODRIGUEZ
 * Nota: La interfaz definida de este DRIVER hace uso de las estructuras
 *       declarados en gpio_config_2021.h
 *  Created on: 15 de mayo del 2024
 *  updated: 20/11/2021
////////////////////////////////////////////////////////////////////////////////////////////////////
 * * Copyright (C) 2021 by Alfredo Chacon - TecNM /IT Chihuahua
 *
 * Se permite la redistribucion, modificacion o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 * Alfredo Chacon y el TecNM /IT Chihuahua no son responsables del mal uso de este material.
 *************************************************************************************************/

/* Definición de alimentacion. */

#define VCC 1
#define GND 0

/* DEFINICIONES estados*/

#define HIGH  VCC
#define LOW   GND

#define RGB_HIGH  GND // Logica inversa, consulte el esquematico de la tarjeta
#define RGB_LOW   VCC

#define PULL_UP   8
#define PULL_DOWM 7
/* Definición de botones . */
//Definiciones de Puertos


#define BOTON1    18//   0x40000 IO 18
#define BOTON2    19//   0x80000 IO 19

/* DEFINICIONES DE LEDS INDEPENDIENTES*/

#define Led_1     17 // IO 17
#define Led_2     16  // IO 16
#define Led_3     4     // IO 4
#define Led_4     2    // IO 2
#define Led_B     5    // IO 5

/* DEFINICIONES RGB*/

#define RGB_ROJO     14 // IO 14
#define RGB_VERDE    12 // IO 12
#define RGB_AZUL     13  // IO 13


/* DEFINICIONES standart*/
#define MAX_VALID_PIN  39
#define MAX_OUTPUT_PIN 34 // Los pines por encima de 34 son solo de entrada



