#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "header.h"		/* Prototypes and definitions */

void input_init( void ){
	/*
	volatile int* trise = (volatile int*) 0xbf886100;
	*trise &= ~0xff; // Sätter bitar 0-7 till 0 (använder & för att inte ändra de andra bitarna)
	*/
	TRISE &= ~0xff;
	TRISD |= 0xfe0; // Sätter knappar och switchar 
}

/* getsw
 * when called returns the state of the switches at PORTD
 */
int getsw ( void ){

	return ((PORTD & 0x0f00) >> 8);
}

/* getbtns
 * when called returns the state of the buttons at PORTD
 */
int getbtns ( void ){

	return ((PORTD & 0x0e0) >> 5);
}
