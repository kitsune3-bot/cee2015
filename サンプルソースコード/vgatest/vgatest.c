#include <stdio.h>
#include "system.h"
#include "io.h"
#include "sys/alt_irq.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_parallel_port.h"

#define VGAWIDTH 320
#define VGAHEIGHT 240

alt_up_char_buffer_dev *char_buff_dev;
alt_up_pixel_buffer_dma_dev *pixel_buffer_dev;
alt_up_parallel_port_dev *push_button_dev;


void button_handler()
{
	printf("interrupted\n");

	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer_dev, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 0, 0, VGAWIDTH, VGAHEIGHT, 0x0000FF, 0);
	//alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer_dev);
	alt_up_char_buffer_clear(char_buff_dev);
	alt_up_char_buffer_string(char_buff_dev, "BUTTON PRESSED.", 10, 10);
	//clear edge_captrute resister
	alt_up_parallel_port_clear_edge_capture(push_button_dev);
}

void button_init()
{
	//
	alt_up_parallel_port_set_interrupt_mask(push_button_dev, 0xF);

	//clear edge_captrute resister
	alt_up_parallel_port_clear_edge_capture(push_button_dev);

	alt_irq_register(
			PUSHBUTTONS_IRQ,
			NULL,
			(void *)button_handler);
}


int main(void)
{
	printf("---vgatest start---\n");
	button_init();

	//open char-buffer device
	//‚È‚º‚©‚±‚¢‚Â‚Ísystem.h‚ÉVGA_CHAR_BUFFER_NAME‚Ý‚½‚¢‚É’è‹`‚³‚ê‚Ä‚È‚¢
	char_buff_dev = alt_up_char_buffer_open_dev("/dev/VGA_Char_Buffer");
	if(char_buff_dev == NULL) {
		printf("could not open char_buffer_dev\n");
		return -1;
	}

	//open pixel-buffer device
	pixel_buffer_dev = alt_up_pixel_buffer_dma_open_dev(VGA_PIXEL_BUFFER_NAME);
	if(pixel_buffer_dev == NULL) {
		printf("could not open pixel_buffer_dev\n");
		return -1;
	}

	push_button_dev = alt_up_parallel_port_open_dev(PUSHBUTTONS_NAME);
	if (push_button_dev == NULL) {
		printf("Couldn't open push_button_dev\n");
		return -1;
	}


	//show Color Bars
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer_dev, 0);
	//alt_up_pixel_buffer_dma_clear_screen(pixel_buffer_dev, 1);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, VGAWIDTH/7*0, 0, VGAWIDTH/7*(0+1), VGAHEIGHT, 0xFFFFFF, 0);//White
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, VGAWIDTH/7*1, 0, VGAWIDTH/7*(1+1), VGAHEIGHT, 0xFFFF00, 0);//Yellow
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, VGAWIDTH/7*2, 0, VGAWIDTH/7*(2+1), VGAHEIGHT, 0x00FFFF, 0);//Cyan
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, VGAWIDTH/7*3, 0, VGAWIDTH/7*(3+1), VGAHEIGHT, 0x00FF00, 0);//Green
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, VGAWIDTH/7*4, 0, VGAWIDTH/7*(4+1), VGAHEIGHT, 0xFF00FF, 0);//Magenta
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, VGAWIDTH/7*5, 0, VGAWIDTH/7*(5+1), VGAHEIGHT, 0xFF0000, 0);//Red
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, VGAWIDTH/7*6, 0, VGAWIDTH/7*(6+1), VGAHEIGHT, 0x0000FF, 0);//Blue
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, 0, VGAHEIGHT-VGAWIDTH/7*2, VGAWIDTH, VGAHEIGHT-VGAWIDTH/7*1, 0x000000, 0);//Black
	//alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer_dev);
	//show message
	alt_up_char_buffer_clear(char_buff_dev);
	alt_up_char_buffer_string(char_buff_dev, "Hell, World!", 34, 40);



	while(1)
	{

	}

	return 0;
}
