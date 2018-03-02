#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "header.h"		/* Prototypes and definitions */

char gravity = 1;		// how far down the helicopter travels per call
char y = 12;				// initial vertical position

char limit_roof = 0;		// how far up we can go
char limit_floor = 24;	// how far down we can go

/*
	Note that everything is reverse to what we think is normal
	
	y: 0 == first row (top)
	y: 24 == "bottom" row, out of 32 possible
	x: 0 == left side
	x: 128 == right side
*/

/* helicopter_placement
 * when called updates the position of the helicopter
 * on the screen. Player can push the helicopter upwards
 * by pressing the leftmost button on the I/O shield
 */
void helicopter_placement(int x){

	if((getbtns() & 0x04) == 4){	// if the button IS pressed

		if(y != limit_roof){	// if the helicopter is not at the roof
			y = y - gravity;	// send it up a little bit
		} else {
			y = limit_roof;		// else set y to the top limit
		}
	} else {						// if the button is NOT pressed

		if(y != limit_floor){	// if the helicopter is not at the floor
			y = y + gravity;	// send it down towards it
		} else {
			y = limit_floor;	// else set y to the bottom limit
		}
	}

	// calls helicopter_draw to draw the new position on the screen
	helicopter_draw(x, y, helicopter_bitmap);
}

/* helicopter_draws
 * when called draws the helicopter on the screen
 * at the given position.
 */
void helicopter_draw(char x, char y, char helicopter_bitmap[8][8]){

	int i;
	int j;

	for(i = 0; i < 8; i++){			// step through x

		for(j = 0; j < 8; j++){		// step through y

			if (helicopter_bitmap[i][j] == 1) {

				display_pixel_on(x + i, y + j);
			}
		}
	}
}
