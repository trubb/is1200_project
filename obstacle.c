#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "header.h"		/* Prototypes and definitions */

int space = 22;
int obstacle_width;
int obstacle_height_max;
int obstacle_height_min;

int environment[128] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2
};

void environment_update(){

	int i;
	int n;

	// generates a number between 1 and 8
	//srand(time(NULL));
	// better random generation
	n = rand() % 9 + 1;

	for(i = 0; i < 128 - 1; i++){
		environment[i] = environment[i + 1];
	}

	environment[127] = n;
}


void environment_set(){
	int x, y;

	for(x = 0; x < 128; x++){
		// Top environment
		for(y = 0; y < environment[x]; y++){
			display_pixel_on(x, y);
		}

		for (y = environment[x] + space; y < 32; y++){
			display_pixel_on(x, y);
		}

	}
}
