#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "header.h"		/* Prototypes and definitions */

// the display, pixels defined as fields in an array of 128x32
char display_matrix[128][32];

// the helicopter, as a 8x8 array
char helicopter_bitmap[8][8] = {
	{0, 0, 0, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 1, 1, 1, 0, 0},
	{1, 0, 0, 1, 1, 1, 1, 1},
	{1, 0, 1, 1, 1, 1, 1, 0},
	{1, 1, 1, 1, 1, 1, 1, 0},
	{1, 0, 1, 1, 0, 1, 1, 1},
	{1, 0, 0, 0, 1, 1, 0, 0}
};
