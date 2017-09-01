#include <stdio.h>
#include "altera_up_sd_card_avalon_interface.h"

void sdcard_init();

alt_up_sd_card_dev *sdcard_dev;

int main(void)
{
	printf("---sdcard_test start---\n");
	sdcard_init();

	//TODO: fullname‚É‚Ç‚¤‚É‚©‚µ‚Ä‘Î‰ž‚³‚¹‚½‚¢.FatFSŽg‚¤‚Æ‚©B
	short handler = alt_up_sd_card_fopen("SD.TXT", false);
	printf("\n\n");
	if(handler >= 0)
	{
	    short read;
	    while ((read = alt_up_sd_card_read(handler)) != -1)
	    {
	         printf("%c", read);
	    }
	} else {
		printf("could not open\n");
	}
	alt_up_sd_card_fclose(handler);


	return 0;
}

void sdcard_init(){
	sdcard_dev = alt_up_sd_card_open_dev(SD_CARD_NAME);
	if (sdcard_dev == NULL) {
		printf("!--SD Card device could not open---\n");
		return;
	}
	if (!alt_up_sd_card_is_FAT16()) {
		printf("!--Warning! This SD Card's FS is not FAT16---\n");
	}
}
