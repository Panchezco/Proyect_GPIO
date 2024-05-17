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
// Función para obtener el valor del registro para un pin dado
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
/******************************************************************************
 * Function: GPIO_Out_pin
 * Preconditions:
 * Overview: Establece como salida el pin seleccionado.
 * Input: Pin(x).
 * Output: GND
 *
 *****************************************************************************/
void GPIO_Out_pin(uint_fast16_t selectedPins)
{
    uint_fast16_t inputPinValue_withoffsett;

//    if(GPIO_PINX_REG[selectedPins]){
//    printf("Error el pin %d no disponible.",selectedPins);
//    exit(1);
//    }

    inputPinValue_withoffsett = DIR_GPIO2_BASE + selectedPins;

    /*DESACTIVAMOS EL PIN COMO ENTRADA*/
     HWREG32(GPIO_PINX_REG[selectedPins]) &= ~(1<<9);

    //                                            | SEL0 || SEL1|| SEL2 |
    // FUNCION 2 GPIO                                 0      1       0
    HWREG32(GPIO_PINX_REG[selectedPins]) &= ~(1<<12); //2'12
    HWREG32(GPIO_PINX_REG[selectedPins]) |= (1<<13); //2'13
    HWREG32(GPIO_PINX_REG[selectedPins]) &= ~(1<<14);// 2'14

    switch (selectedPins) {
        case 32:
        case 33:
        	GPIO_ENABLE1_REG |= (1 << (selectedPins - 32));
            break;
        default:
        	 GPIO_ENABLE_REG  |= 1 << selectedPins;
            break;
    }
}

/******************************************************************************
 * Function: GPIO_OUTSET_1
 * Preconditions:   GPIO_Out_pin
 * Overview: Establece la salida del pin seleccionado en 1 o 0.
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
				        	GPIO_OUT1_W1TC_REG  |= (1 << (selectedPins- 32));
				            break;
				        default:
				        	GPIO_OUT_W1TC_REG = 1<<selectedPins;
				            break;
				    }
	}
}


