#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include "C:\Users\DELL\workspace\Proyec\components\Drivers_GPIO\include\gpio.h"

void app_main(void) {
    ini_board_GPIO();  // Inicializa los GPIOs configurados en ini_board_GPIO

    int state = 0;
    bool button_pressed = false;

    while (1) {
        // Lee el estado del botón
        if (GPIO_READ(BTN1) != 1) {
            if (!button_pressed) {
                button_pressed = true;
                state = (state + 1) % 3;  // Cambia el estado del semáforo
            }
        } else {
            button_pressed = false;
        }

        // Actualiza las luces del semáforo basadas en el estado
        if (state == 0) {
        	// Luz verde
			GPIO_WRITTE(RGB_RED, RGB_LOW);
			GPIO_WRITTE( RGB_BLUE , RGB_LOW);
			GPIO_WRITTE(RGB_GREEN, RGB_HIGH);

        } else if (state == 1) {
            // Luz amarilla
             GPIO_WRITTE(RGB_RED, RGB_HIGH);
             GPIO_WRITTE( RGB_BLUE, RGB_LOW);
             GPIO_WRITTE(RGB_GREEN, RGB_HIGH);

        } else if (state == 2) {

            // Luz roja
			GPIO_WRITTE(RGB_RED, RGB_HIGH);
			GPIO_WRITTE( RGB_BLUE , RGB_LOW);
			GPIO_WRITTE(RGB_GREEN, RGB_LOW);
        }
        // Pequeño retraso para evitar problemas de rebote (debouncing)
        usleep(100000);
    }
}
