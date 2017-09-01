#include <stdio.h>
#include "altera_up_avalon_parallel_port.h"
#include "io.h"
#include "system.h"

/* Global variables */
alt_up_parallel_port_dev *green_LEDs_dev;
alt_up_parallel_port_dev *red_LEDs_dev;
alt_up_parallel_port_dev *hex3_hex0_dev;
alt_up_parallel_port_dev *slider_switch_dev;
alt_up_parallel_port_dev *push_button_dev;

//interrupt handler
void button_handler();

int main(void)
{
	int slider_switch_status;

	printf("---pallalel_port_test start---\n");

	//open device
	green_LEDs_dev = alt_up_parallel_port_open_dev(GREEN_LEDS_NAME);
	if (green_LEDs_dev == NULL) {
		printf("Couldn't open green_LEDs_dev\n");
		return -1;
	}

	red_LEDs_dev = alt_up_parallel_port_open_dev(RED_LEDS_NAME);
	if (red_LEDs_dev == NULL) {
		printf("Couldn't open green_LEDs_dev\n");
		return -1;
	}

	hex3_hex0_dev = alt_up_parallel_port_open_dev(HEX3_HEX0_NAME);
	if (hex3_hex0_dev == NULL) {
		printf("Couldn't open hex3_hex0_dev\n");
		return -1;
	}

	slider_switch_dev = alt_up_parallel_port_open_dev(SLIDER_SWITCHES_NAME);
	if (slider_switch_dev == NULL) {
		printf("Couldn't open slider_switch_dev\n");
		return -1;
	}

	push_button_dev = alt_up_parallel_port_open_dev(PUSHBUTTONS_NAME);
	if (slider_switch_dev == NULL) {
		printf("Couldn't open push_button_dev\n");
		return -1;
	}


	//light green_LEDs
	//0x5A = 0b01011010
	alt_up_parallel_port_write_data(green_LEDs_dev, 0x5A);

	//show 2222 on 7seg
	alt_up_parallel_port_write_data(hex3_hex0_dev, 0x5B5B5B5B);

	//read slider_switch_status
	slider_switch_status = alt_up_parallel_port_read_data(slider_switch_dev);

	//light red_LEDs
	alt_up_parallel_port_write_data(red_LEDs_dev, slider_switch_status);

	//
	//init interrupt
	//
	alt_up_parallel_port_set_interrupt_mask(push_button_dev, 0xF);

	//clear edge_captrute resister
	alt_up_parallel_port_clear_edge_capture(push_button_dev);

	//resist interrupt handler
	alt_irq_register(
			PUSHBUTTONS_IRQ,
			NULL,
			(void *)button_handler);

	while(1);

	return 0;
}

void button_handler()
{
	int button_position;

	button_position = alt_up_parallel_port_read_edge_capture(push_button_dev);

	printf("interrupted, %x\n", button_position);

	//clear EDGE resister
	alt_up_parallel_port_clear_edge_capture(push_button_dev);
}
