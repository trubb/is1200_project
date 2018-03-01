#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "header.h"		/* Prototypes and definitions */

char gravity = 1;
char y = 12;

char limit_roof = 0;
char limit_floor = 24;


/*
	Note that everything is reverse to what we think is normal

	0 == first row (top)
	24 == "bottom" row, out of 32 possible
*/
void helicopter_placement(){

	if((getbtns() & 0x04) == 4){	// if the button IS pressed

		if(y != limit_roof){	// if the helicopter is not at the roof
			y = y - gravity;	// send it up a little bit
		}
		else{
			y = limit_roof;		// else set y to the top limit
		}
	}
	else{						// if the button is NOT pressed

		if(y != limit_floor){	// if the helicopter is not at the floor
			y = y + gravity;	// send it down towards it
		}
		else{
			y = limit_floor;	// else set y to the bottom limit
		}
	}

	helicopter_draw(24, y, helicopter_bitmap);
}

void helicopter_draw(char x, char y, char helicopter_bitmap[8][8]){

	int i;
	int j;

	for(i = 0; i < 8; i++){

		for(j = 0; j < 8; j++){

			if (helicopter_bitmap[i][j] == 1) {

				display_pixel_on(x + i, y + j);
			}
		}
	}
}
