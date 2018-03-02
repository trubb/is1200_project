#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "header.h"		/* Prototypes and definitions */

static int score = 0;
static int highscore = 0;

/* score_inc
 * when called increases score by one and sends
 * the value to the LEDs at PORTE which displays
 * the score in binary.
 */
void score_inc(){

	score++;
	PORTE = score;	// is this possible? Shouldn't have to give it a hex value?
}

/* score_get
 * when called returns the current score
 */
int score_get(){

	return score;	// might be smart to return *score or &score?
}

/* highscore_update
 * when called checks if the current score is higher
 * than the current highscore
 * if it is, the highscore is updated
 * if not, the highscore is left untouched
 */
void highscore_update(){

	if (score > highscore){
		highscore = score;
	} else {
		highscore = highscore;
	}
}

/* highscore_get
 * when called returns the current highscore
 */
int highscore_get(){

	return highscore;
}
