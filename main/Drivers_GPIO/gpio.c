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
 * Function: GPIO_Out
 * Preconditions:
 * Overview: sets the pin as out
 * Input: Pin(x).
 * Output: GND
 *
 *****************************************************************************/
void GPIO_OUT(uint_fast16_t selectedPins)
{
    uint_fast16_t inputPinValue_withoffsett;

    if( selectedPins > MAX_VALID_PIN || GPIO_PINX_REG[selectedPins] == 0 || selectedPins > MAX_OUTPUT_PIN){
    printf("Error el pin %d no disponible.",selectedPins);
    exit(1);
    }

    inputPinValue_withoffsett = DIR_GPIO2_BASE + GPIO_PINX_REG[selectedPins]; //Obtenemos el alias de el reg

     HWREG32( inputPinValue_withoffsett) &= ~(1<<9);     /*Disable fun_IE*/

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
void  GPIO_WRITTE(uint_fast16_t selectedPins, uint_fast8_t state){


	if(state==HIGH)
	{
		switch (selectedPins) {
		        case 32:
		        case 33:
		        	GPIO_OUT1_W1TS_REG  |= (1 << (selectedPins- 32));
		            break;
		        default:
		        	GPIO_OUT_W1TS_REG |= 1<<selectedPins;
		            break;
		    }
	}

    if(state==LOW)
	{
		switch (selectedPins) {
				        case 32:
				        case 33:
				        	GPIO_OUT1_W1TC_REG  |= (1 << (selectedPins- 32));// se restan 32 poeque estamos usando un registro diferente y empieza donde termina  GPIO_ENABLE_REG
				            break;
				        default:
				        	GPIO_OUT_W1TC_REG |= 1<<selectedPins;
				            break;
				    }
	}
}

/******************************************************************************
 * Function: GPIO_INPUT
 * Preconditions:
 * Overview: sets the pin as input
 * Input: Pin(x) and set pull-up or pull-down.
 * Output: GND
 *
 *****************************************************************************/
void GPIO_INPUT(uint_fast16_t selectedPins, uint_fast16_t MODE_PULL)
{

	uint_fast16_t inputPinValue_withoffsett;

	 inputPinValue_withoffsett = DIR_GPIO2_BASE + GPIO_PINX_REG[selectedPins]; //Obtenemos el alias de el reg

//    if( selectedPins > MAX_VALID_PIN || GPIO_PINX_REG[selectedPins] == 0){   // Las IO arriba de 34 son solo para entadas
//    printf("Error el pin %d no disponible.",selectedPins);
//    exit(1);
//    }
    /*DESACTIVAMOS EL PIN COMO SALIDA*/
    if(selectedPins>=32 && selectedPins<=39){
    GPIO_ENABLE1_REG &= ~(1<<(selectedPins-32));
    }
    else
    GPIO_ENABLE_REG &= ~(1<<selectedPins);

     HWREG32(inputPinValue_withoffsett) |= (1<<9);     /*Activamos fun_IE*/
    //                                            | SEL0 || SEL1|| SEL2 |
      // FUNCION 2 GPIO                                 0      1       0
      HWREG32( inputPinValue_withoffsett) &= ~(1<<12); //2'12
      HWREG32( inputPinValue_withoffsett) |= (1<<13); //2'13
      HWREG32( inputPinValue_withoffsett) &= ~(1<<14);// 2'14

    if(MODE_PULL == PULL_UP)
    {
    	HWREG32( inputPinValue_withoffsett) |= (1<<PULL_UP);
    	HWREG32( inputPinValue_withoffsett) &= ~(1<<PULL_DOWN);
    }

    if(MODE_PULL == PULL_DOWN)
	{
    	HWREG32(inputPinValue_withoffsett) |=(1<<PULL_DOWN);
    	HWREG32(inputPinValue_withoffsett) &= ~(1<<PULL_UP);

	}
}

/******************************************************************************
 * Function: GPIO_READ
 * Preconditions: GPIO_Out_pin
 * Overview: read the pin as input
 * Input: Pin(x) and set pull-up or pull-down.
 * Output: GND
 *
 *****************************************************************************/
int GPIO_READ(uint_fast16_t selectedPins)
{

	if (selectedPins >= 32 && selectedPins <= 39)
	{
	        if (GPIO_IN1_REG & (1 << (selectedPins - 32)))
	        {
	            return 1;
	        }
	        else
	        {
	            return 0;
	        }
	}
	else
	{
	        if (GPIO_IN_REG & (1 << selectedPins))
	        {
	            return 1;
	        }
	        else
	        {
	            return 0;
	        }
	}


}

/******************************************************************************
 * Function:  ini_board_GPIO
 * Preconditions: NONE
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
void ini_board_GPIO()
{
	 GPIO_INPUT(BTN1,PULL_UP); //BTN1 AND BTN2 HAVE ONLY PULL-UP
	 GPIO_INPUT(BTN2,PULL_UP);

	 GPIO_OUT(RGB_RED);
	 GPIO_OUT(RGB_BLUE);
	 GPIO_OUT(RGB_GREEN);

	 GPIO_OUT(LED_1);
	 GPIO_OUT(LED_2);
	 GPIO_OUT(LED_3);
	 GPIO_OUT(LED_4);
	 GPIO_OUT(LED_B);

}
