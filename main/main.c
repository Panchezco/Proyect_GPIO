#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include "Drivers_GPIO\gpio.c"

#define GPIO_OUT  (HWREG32(0x3FF44004))
#define GPIO_ENABLE (HWREG32(0x3FF44020))
#define GPIO_OUT_WITS (HWREG32(0x3FF44014))

void app_main(void)
{
	GPIO_INPUT_PULL(17, PULL_UP);

	GPIO_Out_pin(RGB_ROJO );
	GPIO_Out_pin(RGB_AZUL );
	GPIO_Out_pin(RGB_VERDE );
			 GPIO_OUTSET(RGB_ROJO ,LOW);
			 GPIO_OUTSET(RGB_VERDE ,LOW);
			 GPIO_OUTSET(RGB_AZUL ,LOW);



}
