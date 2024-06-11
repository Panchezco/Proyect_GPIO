/*****************************************************
 * FileName:        gpio.c
 * Dependencies:
 * Processor:       ESP32
 * Board:           ESP32-PANTHER48
 * Program version: Espressif-IDE
 * Company:         TecNM /IT Chihuahua
 * Description:     PROTOTIPOS DE FUNCIONES DEL DRIVER
 * Authors:         JORGE GABRIEL LOZANO RODRIGUEZ
 *                  PEDRO MANCINAS HERNANDEZ
 *  Created on: 15 de mayo del 2024
 **************************************************/
/************************************************************************************************
 * * Copyright (C) 2024 by JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ- TecNM /IT Chihuahua
 * Se permite la redistribucion, modificacion o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 *  JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTES  y el TecNM /IT Chihuahua no son responsables del mal uso de este material.*/
#include "addresses.h"
#include "gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bsp.h"
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
		IO_24_REG,		 // PIN no valido
		IO_25_REG,
		IO_26_REG,
		IO_27_REG,
		IO_28_REG,  	// PIN no valido
		IO_29_REG,		// PIN no valido
		IO_30_REG,		// PIN no valido
		IO_31_REG,		// PIN no valido
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
            IO_INT_x_REG  ADDRESSES MAP
************************************************/
volatile uint32_t GPIO_INT_REG[] = {
    GPIO_PIN0_REG,
    GPIO_PIN1_REG,
    GPIO_PIN2_REG,
    GPIO_PIN3_REG,
    GPIO_PIN4_REG,
    GPIO_PIN5_REG,
    GPIO_PIN6_REG,
    GPIO_PIN7_REG,
    GPIO_PIN8_REG,
    GPIO_PIN9_REG,
    GPIO_PIN10_REG,
    GPIO_PIN11_REG,
    GPIO_PIN12_REG,
    GPIO_PIN13_REG,
    GPIO_PIN14_REG,
    GPIO_PIN15_REG,
    GPIO_PIN16_REG,
    GPIO_PIN17_REG,
    GPIO_PIN18_REG,
    GPIO_PIN19_REG,
    GPIO_PIN20_REG,
    GPIO_PIN21_REG,
    GPIO_PIN22_REG,
    GPIO_PIN23_REG,
    0,  // GPIO_PIN24_REG (PIN no válido)
    GPIO_PIN25_REG,
    GPIO_PIN26_REG,
    GPIO_PIN27_REG,
    0,  // GPIO_PIN28_REG (PIN no válido)
    0,  // GPIO_PIN29_REG (PIN no válido)
    0,  // GPIO_PIN30_REG (PIN no válido)
    0,  // GPIO_PIN31_REG (PIN no válido)
    GPIO_PIN32_REG,
    GPIO_PIN33_REG,
	GPIO_PIN34_REG,
	GPIO_PIN35_REG,
	GPIO_PIN36_REG,
	GPIO_PIN37_REG,
    GPIO_PIN38_REG,
    GPIO_PIN39_REG,
};

/******************************************************************************
 * Function: GPIO_Out
 * Preconditions:
 * Overview: sets the pin as out
 * Input: Pin(x).
 * Output: GND
 *
 *****************************************************************************/
extern void GPIO_OUT(uint_fast16_t selectedPins)
{
    uint_fast16_t inputPinValue_withoffsett;

    if( selectedPins > MAX_VALID_PIN || GPIO_PINX_REG[selectedPins] == 0 || selectedPins > MAX_OUTPUT_PIN){
    printf("Error el pin %d no disponible.",selectedPins);
    exit(1);
    }

    inputPinValue_withoffsett = DIR_GPIO2_BASE +  GPIO_PINX_REG[selectedPins]; //Obtenemos el alias de el reg

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
extern void  GPIO_WRITTE(uint_fast16_t selectedPins, uint_fast8_t state){


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
extern void GPIO_INPUT(uint_fast16_t selectedPins, uint_fast16_t MODE_PULL)
{

	uint_fast16_t inputPinValue_withoffsett;


    if( selectedPins > MAX_VALID_PIN || GPIO_PINX_REG[selectedPins] == 0){   // Las IO arriba de 34 son solo para entadas
    printf("Error el pin %d no disponible.",selectedPins);
    exit(1);
    }

    inputPinValue_withoffsett = DIR_GPIO2_BASE + GPIO_PINX_REG[selectedPins]; //Obtenemos el alias de el reg

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
extern int GPIO_READ(uint_fast16_t selectedPins)
{
    // Check if the selected pin is in the range of 32 to 39
    if (selectedPins >= 32 && selectedPins <= 39)
    {
        // Read the state of the corresponding pin in the GPIO_IN1_REG register
        // Subtract 32 because GPIO_IN1_REG handles pins 32 to 39
        if (GPIO_IN1_REG & (1 << (selectedPins - 32)))
        {
            // If the corresponding bit is 1, return 1
            return 1;
        }
        else
        {
            // If the corresponding bit is 0, return 0
            return 0;
        }
    }
    else
    {
        // For pins outside the range 32 to 39, read the state of the pin in the GPIO_IN_REG register
        if (GPIO_IN_REG & (1 << selectedPins))
        {
            // If the corresponding bit is 1, return 1
            return 1;
        }
        else
        {
            // If the corresponding bit is 0, return 0
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
extern void ini_board_GPIO()
{
	 GPIO_INPUT(BTN1,PULL_UP); //BTN1 AND BTN2 HAVE ONLY PULL-UP
	 GPIO_INPUT(BTN2,PULL_UP);
	 GPIO_INPUT(25,PULL_UP);

	 GPIO_OUT(RGB_RED);
	 GPIO_OUT(RGB_BLUE);
	 GPIO_OUT(RGB_GREEN);
	 GPIO_OUT(LED_1);
	 GPIO_OUT(LED_3);
	 GPIO_OUT(LED_B);

}
/******************************************************************************
 * Function: start_CAR
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void start_CAR()
{

	 GPIO_OUT(GPIO_UP);
	 GPIO_OUT(GPIO_DOWN);
	 GPIO_OUT(GPIO_DOWN2);
	 GPIO_OUT(GPIO_UP2);
	 GPIO_OUT(LED_CAR);

}

/******************************************************************************
 * Function:  MOTOR_UP
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void MOTOR_UP()
{

	GPIO_WRITTE(GPIO_UP2,HIGH);
   	GPIO_WRITTE(GPIO_DOWN2,LOW);
 	GPIO_WRITTE(GPIO_UP,HIGH);
	GPIO_WRITTE(GPIO_DOWN,LOW);

}

/******************************************************************************
 * Function: MOTOR_DOWN
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_DOWN()
{

	GPIO_WRITTE(GPIO_UP2,LOW);
   	GPIO_WRITTE(GPIO_DOWN2,HIGH);
    GPIO_WRITTE(GPIO_UP,LOW);
    GPIO_WRITTE(GPIO_DOWN,HIGH);

}

/******************************************************************************
 * Function:  MOTOR_LEFT
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_LEFT()
{

	GPIO_WRITTE(GPIO_UP2,LOW);
   	GPIO_WRITTE(GPIO_DOWN2,LOW);
    GPIO_WRITTE(GPIO_UP,HIGH);
    GPIO_WRITTE(GPIO_DOWN,LOW);

}

/******************************************************************************
 * Function:  MOTOR_RIGHT
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_RIGHT()
{

	GPIO_WRITTE(GPIO_UP2,HIGH);
 	GPIO_WRITTE(GPIO_DOWN2,LOW);
    GPIO_WRITTE(GPIO_UP,LOW);
    GPIO_WRITTE(GPIO_DOWN,LOW);

}

/******************************************************************************
 * Function:  MOTOR_STOP
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_STOP()
{

	GPIO_WRITTE(GPIO_UP2,LOW);
 	GPIO_WRITTE(GPIO_DOWN2,LOW);
    GPIO_WRITTE(GPIO_UP,LOW);
    GPIO_WRITTE(GPIO_DOWN,LOW);

}
/******************************************************************************
 * Function:  MOTOR_LED_ON
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_LED_ON()
{

	GPIO_WRITTE(LED_CAR,HIGH);

}


/******************************************************************************
 * Function:  MOTOR_LED_OFF
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_LED_OFF()
{

	GPIO_WRITTE(LED_CAR,LOW);

}


/******************************************************************************
 Funcion para instalar ISR y establecer interrupcion
 Necesita boton de entrada, funcion que ejecutara
 *****************************************************************************/
extern void set_interrupcion(uint_fast16_t selectedPins, int funcion) {
    switch (selectedPins) {
		   case 0:   if (intr_pendiente(selectedPins) == 0){return; } xTaskCreate((void *)funcion, "intr 0", 1000, 0, 1, 0); break;
			case 1:  if (intr_pendiente(selectedPins) == 0){return; } xTaskCreate((void *)funcion, "intr 2", 1000, 0, 1, 0); break;
			case 2:  if (intr_pendiente(selectedPins) == 0){return; } xTaskCreate((void *)funcion, "intr 2", 1000, 0, 1, 0); break;
			case 3:  if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 3", 1000, 0, 1, 0); break;
			case 4:  if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 4", 1000, 0, 1, 0); break;
			case 5:  if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 5", 1000, 0, 1, 0); break;
			case 6:  if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 6", 1000, 0, 1, 0); break;
			case 7:  if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 7", 1000, 0, 1, 0); break;
			case 8:  if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 8", 1000, 0, 1, 0); break;
			case 9:  if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 9", 1000, 0, 1, 0); break;
			case 10: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 10", 1000, 0, 1, 0); break;
			case 11: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 11", 1000, 0, 1, 0); break;
			case 12: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 12", 1000, 0, 1, 0); break;
			case 13: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 13", 1000, 0, 1, 0); break;
			case 14: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 14", 1000, 0, 1, 0); break;
			case 15: if (intr_pendiente(selectedPins) == 0){return; } xTaskCreate((void *)funcion, "intr 15", 1000, 0, 1, 0); break;
			case 16: if (intr_pendiente(selectedPins) == 0){return; } xTaskCreate((void *)funcion, "intr 16", 1000, 0, 1, 0); break;
			case 17: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 17", 1000, 0, 1, 0); break;
			case 18: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 18", 1000, 0, 1, 0); break;
			case 19: if (intr_pendiente(selectedPins) == 0){return; } xTaskCreate((void *)funcion, "intr 19", 1000, 0, 1, 0); break;
			case 20: if (intr_pendiente(selectedPins) == 0){return; } xTaskCreate((void *)funcion, "intr 20", 1000, 0, 1, 0); break;
			case 21: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 21", 1000, 0, 1, 0); break;
			case 22: if (intr_pendiente(selectedPins) == 0){return; } xTaskCreate((void *)funcion, "intr 22", 1000, 0, 1, 0); break;
			case 23: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 23", 1000, 0, 1, 0); break;
			case 24: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 24", 1000, 0, 1, 0); break;
			case 25: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 25", 1000, 0, 1, 0); break;
			case 26: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 26", 1000, 0, 1, 0); break;
			case 27: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 27", 1000, 0, 1, 0); break;
			case 28: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 28", 1000, 0, 1, 0); break;
			case 29: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 29", 1000, 0, 1, 0); break;
			case 30: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 30", 1000, 0, 1, 0); break;
			case 31: if (intr_pendiente(selectedPins) == 0){return; }xTaskCreate((void *)funcion, "intr 31", 1000, 0, 1, 0); break;
    }
}

/******************************************************************************
 Funcion para saber si hay interrupciones pendientes y en base a eso validar
 *****************************************************************************/

int intr_pendiente(int selectedPins) {

    if (GPIO_STATUS_REG == (1 << selectedPins)) {
    	switch (selectedPins) {
    					        case 32:case 33:case 34:case 35:case 36:case 37:case 38:case 39:
    					        	GPIO_STATUS1_W1TC_REG |= (1 << (selectedPins- 32));
    					            break;
    					        default:
    					        	GPIO_STATUS_W1TC_REG |= 1<<selectedPins;
    					            break;
    					    }
        return 1;
    } else {
    	switch (selectedPins) {
    					        case 32:case 33:case 34:case 35:case 36:case 37:case 38:case 39:
    					        	GPIO_STATUS1_W1TC_REG |= (1 << (selectedPins- 32));
    					            break;
    					        default:
    					        	GPIO_STATUS_W1TC_REG |= 1<<selectedPins;
    					            break;
    					    }
        return 0;
    }
}


/******************************************************************************
 funcion para habilitar interrupcion
 Necesita boton de entrada que hara la interrupcion
 *****************************************************************************/
void INT_ENABLE(uint_fast16_t selectedPins)
{


	 GPIO_INT_REG[selectedPins] |= (1<<13);
	 GPIO_INT_REG[selectedPins] |= (1<<14);


	switch (selectedPins) {
			        case 32:case 33:case 34:case 35:case 36:case 37:case 38:case 39:
			        	GPIO_STATUS1_W1TS_REG |= (1 << (selectedPins- 32));
			            break;
			        default:
			        	GPIO_STATUS_W1TS_REG |= 1<<selectedPins;
			            break;
			    }
}

/******************************************************************************
 Funcion para instalar ISR y establecer interrupcion
 Necesita boton de entrada, funcion que ejecutara
 *****************************************************************************/

extern void INT(uint_fast16_t selectedPins, uint_fast16_t TYPE)
{

	switch (TYPE){
				    case 0: // GPIO INTERRUPT DISABLE
				    	GPIO_INT_REG[selectedPins]  &= ~(1<<7); //2'7
				    	GPIO_INT_REG[selectedPins]  &= ~(1<<8); //2'8
				    	GPIO_INT_REG[selectedPins]  &= ~(1<<9); //2'9
				    	break;
				    case 1: // RISING EDGE TRIGGER
				    	GPIO_INT_REG[selectedPins]  |=  (1<<7); //2'7
				    	GPIO_INT_REG[selectedPins]  &= ~(1<<8); //2'8
				    	GPIO_INT_REG[selectedPins]  &= ~(1<<9); //2'9
				    	break;
				    case 2: // FALLING EDGE TRIGGER
				        GPIO_INT_REG[selectedPins]  &= ~(1<<7); //2'7
				        GPIO_INT_REG[selectedPins]  |=  (1<<8); //2'8
				        GPIO_INT_REG[selectedPins]  &= ~(1<<9); //2'9
				        break;
				    case 3: // GPIO ANY EDGE TRIGGER
				   		GPIO_INT_REG[selectedPins]  |=  (1<<7); //2'7
				   		GPIO_INT_REG[selectedPins]  |=  (1<<8); //2'8
				   		GPIO_INT_REG[selectedPins]  &= ~(1<<9); //2'9
				   		break;
				    case 4:// GPIO LOW LEVEL TRIGGER
				   		GPIO_INT_REG[selectedPins]  &= ~(1<<7); //2'7
				   		GPIO_INT_REG[selectedPins]  &= ~(1<<8); //2'8
				        GPIO_INT_REG[selectedPins]  |=  (1<<9); //2'9
				   		break;
				    case 5:// GPIO HIGH LEVEL TRIGGER
				   		GPIO_INT_REG[selectedPins]  |= (1<<7); //2'7
				   		GPIO_INT_REG[selectedPins]  &= ~(1<<8); //2'8
				   		GPIO_INT_REG[selectedPins]  |= (1<<9); //2'9
				   		break;
	 }
}

/******************************************************************************
 Funcion desabilitar interrupcion
 *****************************************************************************/

extern void CLN_ENABLE(uint_fast16_t selectedPins)
{

	switch (selectedPins) {
				        case 32:case 33:case 34:case 35:case 36:case 37:case 38:case 39:
				        	GPIO_STATUS1_W1TC_REG |= (1 << (selectedPins- 32));
				            break;
				        default:
				        	GPIO_STATUS_W1TC_REG |= 1<<selectedPins;
				            break;
				    }

}
/******************************************************************************
 Funcion desabilitar interrupcion
 *****************************************************************************/
int funcion(int pin, int type) {
    switch (type) {
        case 3:
        case 1: // Rising edge
            if (GPIO_READ(pin) != 1) {
                return 1;
            } else {
                return 0;
            }

        case 2: // Falling edge
            // Esperar hasta que el pin cambie de estado de 1 a 0
            while (GPIO_READ(pin) != 1);

            // Verificar que el pin está realmente en estado bajo
            if (GPIO_READ(pin) == 0) {
                return 1;
            } else {
                return 0;
            }

        default:
            return -1; // Valor de retorno para casos no manejados
    }
}


