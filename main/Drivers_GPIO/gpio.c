/*****************************************************
 * FileName:        gpio.c
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
#include "bsp.h"
#include "gpio.h"

/******************************************************************************
 * Function: GPIO_Out_pin
 * Preconditions:
 * Overview: sets the pin as out
 * Input: Pin(x).
 * Output: GND
 *
 *****************************************************************************/
void GPIO_Out_pin(uint_fast16_t selectedPins)
{
    uint_fast16_t inputPinValue_withoffsett;

    if( selectedPins > MAX_VALID_PIN || GPIO_PINX_REG[selectedPins] == 0 || selectedPins > MAX_OUTPUT_PIN){   // Las IO arriba de 34 son solo para entadas
    printf("Error el pin %d no disponible.",selectedPins);
    exit(1);
    }

    inputPinValue_withoffsett = DIR_GPIO2_BASE + GPIO_PINX_REG[selectedPins]; //Obtenemos el alias de el reg

     HWREG32( inputPinValue_withoffsett) &= ~(1<<9);     /*Desactivamos fun_IE*/

    //                                            | SEL0 || SEL1|| SEL2 |
    // FUNCION 2 GPIO                                 0      1       0
    HWREG32( inputPinValue_withoffsett) &= ~(1<<12); //2'12
    HWREG32( inputPinValue_withoffsett) |= (1<<13); //2'13
    HWREG32( inputPinValue_withoffsett) &= ~(1<<14);// 2'14

    switch (selectedPins) {
        case 32:
        case 33:
        	GPIO_ENABLE1_REG |= (1 << (selectedPins - 32));// se restan 32 poeque estamos usando un registro diferente y empieza donde termina  GPIO_ENABLE_REG
            break;
        default:
        	 GPIO_ENABLE_REG  |= 1 << selectedPins;
            break;
    }
}

/******************************************************************************
 * Function: GPIO_WRITE
 * Preconditions:   GPIO_Out_pin
 * Overview: sets the pin 1 or 0
 * Input: Pin(x).
 * Output: GND
 *
 *****************************************************************************/
void GPIO_OUTSET(uint_fast16_t selectedPins, uint_fast8_t state){


	if(state==HIGH)
	{
		switch (selectedPins) {
		        case 32:
		        case 33:
		        	GPIO_OUT1_W1TS_REG  |= (1 << (selectedPins- 32));
		            break;
		        default:
		        	GPIO_OUT_W1TS_REG = 1<<selectedPins;
		            break;
		    }
	}else

	if(state==LOW)
	{
		switch (selectedPins) {
				        case 32:
				        case 33:
				        	GPIO_OUT1_W1TC_REG  |= (1 << (selectedPins- 32));// se restan 32 poeque estamos usando un registro diferente y empieza donde termina  GPIO_ENABLE_REG
				            break;
				        default:
				        	GPIO_OUT_W1TC_REG = 1<<selectedPins;
				            break;
				    }
	}
}

/******************************************************************************
 * Function: GPIO_INPUT_PULLUP
 * Preconditions:
 * Overview: sets the pin as input
 * Input: Pin(x).
 * Output: GND
 *
 *****************************************************************************/
void GPIO_INPUT_PULLUP(uint_fast16_t selectedPins)
{

	uint_fast16_t inputPinValue_withoffsett;

	inputPinValue_withoffsett = DIR_GPIO2_BASE + GPIO_PINX_REG[selectedPins]; //Obtenemos el alias de el reg

	if( selectedPins > MAX_VALID_PIN || GPIO_PINX_REG[selectedPins] == 0 || selectedPins > MAX_OUTPUT_PIN){   // Las IO arriba de 34 son solo para entadas
	    printf("Error el pin %d no disponible.",selectedPins);
	    exit(1);
	    }

    switch (selectedPins) {
        case 32:
        case 33:
        	GPIO_ENABLE1_REG &= ~ (1 << (selectedPins - 32));// se restan 32 poeque estamos usando un registro diferente y empieza donde termina  GPIO_ENABLE_REG
            break;
        default:
        	 GPIO_ENABLE_REG  &= ~1 << selectedPins;
            break;
    }

    HWREG32(inputPinValue_withoffsett) |= (1<<9);     /*Desactivamos fun_IE*/
    //                                            | SEL0 || SEL1|| SEL2 |
      // FUNCION 2 GPIO                                 0      1       0
      HWREG32( inputPinValue_withoffsett) &= ~(1<<12); //2'12
      HWREG32( inputPinValue_withoffsett) |= (1<<13); //2'13
      HWREG32( inputPinValue_withoffsett) &= ~(1<<14);// 2'14



      HWREG32(inputPinValue_withoffsett) |=(1<<PULL_UP);

}

