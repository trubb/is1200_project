#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "header.h"		/* Prototypes and definitions */

int space = 22;			// "width" of the canal that is free from obstacles

// the obstacles
int environment[128] = {
	2, 2, 4, 4, 6, 6, 8, 8, 8, 8, 7, 7, 5, 5, 3, 3,
	2, 2, 4, 4, 6, 6, 8, 8, 8, 8, 7, 7, 5, 5, 3, 3,
	2, 2, 4, 4, 6, 6, 8, 8, 8, 8, 7, 7, 5, 5, 3, 3,
	2, 2, 4, 4, 6, 6, 8, 8, 8, 8, 7, 7, 5, 5, 3, 3,
	2, 2, 4, 4, 6, 6, 8, 8, 8, 8, 7, 7, 5, 5, 3, 3,
	2, 2, 4, 4, 6, 6, 8, 8, 8, 8, 7, 7, 5, 5, 3, 3,
	2, 2, 4, 4, 6, 6, 8, 8, 8, 8, 7, 7, 5, 5, 3, 3,
	2, 2, 4, 4, 6, 6, 8, 8, 8, 8, 7, 7, 5, 5, 3, 3
};

/* environment_update
 * when called shifts all obstacle bumps of the array
 * 1 pixel to the left, while also repeating the obstacles
 * in a way that behaves similarly to a moebius strip
 */
void environment_update(){

	int i;
	int n;

	for(i = 0; i < 128; i++){
		
		if (i < 127){	// if we're not at the far right end
			environment[i] = environment[i + 1];
		} else {		// if we are at the far right end, start over
			environment[i] = environment[0];
		}
	}
}

/* environment_set
 * when called it draws the obstacles on the screen
 */
void environment_set(){

	int x;
	int y;

	for(x = 0; x < 128; x++){
		// Top environment
		for(y = 0; y < environment[x]; y++){
			display_pixel_on(x, y);
		}

		// bottom environment, offset [space] from the top
		for (y = environment[x] + space; y < 32; y++){
			display_pixel_on(x, y);
		}

	}
}
