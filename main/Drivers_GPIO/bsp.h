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

#define GPI_HIGH  VCC
#define GPI_LOW   GND


#define
/* Definición de botones . */
//Definiciones de Puertos


#define BOTON1    0x40000 // IO 18
#define BOTON2    0x80000 // IO 19

/* DEFINICIONES DE LEDS INDEPENDIENTES*/

#define Led_1     0x20000  // IO 17
#define Led_2     0x10000  // IO 16
#define Led_3     0x10     // IO 4
#define Led_4     0x04     // IO 2
#define Led_B     0x20     // IO 5

/* DEFINICIONES RGB*/

#define RGB_ROJO     (0x4000)  // IO 14
#define RGB_VERDE    (0x1000)  // IO 12
#define RGB_AZUL     (0x2000)  // IO 13


