#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#include "Drivers_GPIO\gpio.c"


void app_main(void)
{
    while (1) {
        printf("Hello from app_main!\n");
        sleep(1);
    }
}
