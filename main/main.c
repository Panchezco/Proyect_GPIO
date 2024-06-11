#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include "gpio.h"

void task1(void *pvParameter)//Funcion interrupcion 1
{ while(1){
	if(GPIO_READ(BTN1) != 1){
		GPIO_WRITTE(LED_B, LOW);
	}
 }
}

void task2(void *pvParameter)//Funcion interrupcion 2
{
	while(1){
		if(GPIO_READ(BTN2) != 1){
			GPIO_WRITTE(LED_B, HIGH);
		}
	 }
}

void app_main()
{
	ini_board_GPIO();
	GPIO_INPUT(2,PULL_UP);

    INT_ENABLE(BTN1);//habilitar interrupcion para btn1
   	set_interrupcion(BTN1,(int)&task1);//establecer interrupcion e instala ISR


   	INT_ENABLE(BTN2);//habilitar interrupcion para btn2
	set_interrupcion(BTN2,(int)&task2);//establecer interrupcion e  instala ISR

	while(1){//bucle infinito
		GPIO_WRITTE(RGB_RED, RGB_LOW);
		GPIO_WRITTE(RGB_BLUE,RGB_LOW);
		GPIO_WRITTE(RGB_GREEN,RGB_HIGH);
	}
}
