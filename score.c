#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "header.h"		/* Prototypes and definitions */

static int score = 0;
static int highscore = 0;

void score_inc(){

	score++;
}

int score_get(){

	return score;	// might be smart to return *score or &score?
}
