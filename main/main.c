#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include "Drivers_GPIO\gpio.h"

void app_main(void){

	ini_board_GPIO();

	while(1)
	{

         if(GPIO_READ(BTN1)==1)
         {
        	 GPIO_WRITTE(RGB_RED,RGB_LOW);
        	 GPIO_WRITTE(RGB_BLUE,RGB_LOW);
        	 GPIO_WRITTE(RGB_GREEN,RGB_HIGH);

         }

         if(GPIO_READ(BTN2)==1)
         {

             GPIO_WRITTE(RGB_RED,RGB_LOW);
             GPIO_WRITTE(RGB_BLUE,RGB_HIGH);
             GPIO_WRITTE(RGB_GREEN,RGB_LOW);

         }

         GPIO_WRITTE(RGB_RED,RGB_LOW);
         GPIO_WRITTE(RGB_BLUE,RGB_LOW);
         GPIO_WRITTE(RGB_GREEN,RGB_LOW);

     }

}

