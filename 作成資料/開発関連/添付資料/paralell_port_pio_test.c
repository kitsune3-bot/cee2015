#include <stdio.h>
#include "io.h"
#include "system.h"

int main(void){
	volatile int *green_LED_addr = GREEN_LEDS_BASE;
	int sw_val;

	puts("---paralell_port_pio_test---");

	//read slider_switch-bits
	sw_val = IORD(SLIDER_SWITCHES_BASE, 0);

	//light red_LEDs
	IOWR(RED_LEDS_BASE, 0, sw_val);

	//light all green LEDs
	*green_LED_addr = 0x0FF;

	return 0;
}
