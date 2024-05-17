/*****************************************************
 * FileName:        gpio.h
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
 **************************************************/
/************************************************************************************************
 * * Copyright (C) 2024 by JORGE GABRIEL LOZANO RODRIGUEZ - TecNM /IT Chihuahua
 *
 * Se permite la redistribucion, modificacion o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 * JORGE GABRIEL LOZANO RODRIGUEZ y el TecNM /IT Chihuahua no son responsables del mal uso de este material.
 *************************************************************************************************/

/************************************************
  DEFINICIONES DE CONSTANTES Y/O MASCARAS
 ************************************************/

/************************************************
  DEFINICIONES DE CONSTANTES Y/O MASCARAS
 ************************************************/

#define GPIO_HIGH      (0x01)
#define GPIO_LOW       (0x00)
#define FUN_IE         (0x200)

#define SEL0           (0x1000)
#define SEL1           (0x2000)
#define SEL2           (0x4000)
#define HWREG32(x) (*((volatile uint32_t *)(x)))


#define GPIO_OUT  (HWREG32(0x3FF44004))

#define GPIO_ENABLE_REG (HWREG32(0x3FF44020)) //GPIO 0-31 output enable register
#define GPIO_ENABLE1_REG (HWREG32(0x3FF4402C)) //GPIO 32-39 output enable register

#define GPIO_OUT_WITS (HWREG32(0x3FF44014))
#define GPIO_OUT_W1TC_REG HWREG32(0x3FF4400C)
#define DIR_GPIO2_BASE  0x3FF49000

// MAPEADO DE PINES
#define IO_0_REG  0x44
#define IO_1_REG  0x88
#define IO_2_REG  0x40
#define IO_3_REG  0x84
#define IO_4_REG  0x48
#define IO_5_REG  0x6C
#define IO_6_REG  0x60
#define IO_7_REG  0x364
#define IO_8_REG  0x68
#define IO_9_REG  0x354
#define IO_10_REG 0x58
#define IO_11_REG 0x5C
#define IO_12_REG 0x34
#define IO_13_REG 0x38
#define IO_14_REG 0x30
#define IO_15_REG 0x3C
#define IO_16_REG 0x4C
#define IO_17_REG 0x50
#define IO_18_REG 0x70
#define IO_19_REG 0x74
#define IO_20_REG 0x78
#define IO_21_REG 0x7C
#define IO_22_REG 0x80
#define IO_23_REG 0x8C
#define IO_24_REG 0x00              // NO DISPONIBLE
#define IO_25_REG 0x24
#define IO_26_REG 0x28
#define IO_27_REG 0x2C
#define IO_28_REG 0x00 				// NO DISPONIBLE
#define IO_29_REG 0x00              // NO DISPONIBLE
#define IO_30_REG 0x00				// NO DISPONIBLE
#define IO_31_REG 0x00			    // NO DISPONIBLE
#define IO_32_REG 0x1C
#define IO_33_REG 0x20

 //SOLO ENTRADAS
#define I_34_REG 0x14
#define I_35_REG 0x18
#define I_36_REG 0x04
#define I_37_REG 0x08
#define I_38_REG 0x0C
#define I_39_REG 0x01
//Definiciones de pines para las funciones
// Matriz de registros de mapeo de GPIO
// Definición de la estructura de los registros de mapeo de pines GPIO




/************************************************
    PROTOTIPO DE FUNCIONES
************************************************/

extern void inicializar_GPIO();
extern uint32_t pinMap(uint_fast32_t  pin);
extern void GPIO_Out_pin(uint_fast16_t selectedPins);
extern void GPIO_OUTSET_1(uint_fast16_t selectedPins, );
extern void GPIO_READ_pin();




