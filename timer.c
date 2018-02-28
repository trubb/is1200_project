#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "header.h"		/* Prototypes and definitions */

void timer_init( void ){

	T2CON = 0x030;				// Stop the timer and clear the control register,
								// prescaler at 1:8,internal clock source
	
	TMR2 = 0x0;					// Clear the timer register
	PR2 = 10000;				// Load the period register
	
	
	IPCSET(2) = 0x0000001C;		// Set priority level 
	IPCSET(2) = 0x00000003;		// Set subpriority level
								
	IFSCLR(0) = 0x00000100;		// Clear the timer interrupt status flag
	IECSET(0) = 0x00000100;		// Enable timer interrupts
	T2CONSET = 0x8000;			// Start the timer

/*
	T2CON = 0x070;				// Stop the timer and clear the control register,
								// prescaler at 1:256,internal clock source
	
	TMR2 = 0x0;					// Clear the timer register
	PR2 = 32150;				// Load the period register
	
	T2CONSET = 0x0038;			// Set scale Frequency: 80MHz Scale: 1:8
    PR2 = 1000000;				// Load period register. Counts to 8*10^6 every second.
	
	IPCSET(2) = 0x0000001C;		// Set priority level 
	IPCSET(2) = 0x00000003;		// Set subpriority level
	
	IFSCLR(0) = 0x00000100;		// Clear the timer interrupt status flag
	IECSET(0) = 0x00000100;		// Enable timer interrupts
	T2CONSET = 0x8000;			// Start the timer
*/
}

void timer_wait(int ms) {
	
	timer_init();
	int i = 0;

	while(i < ms) {

		while((IFS(0) & 0x0100) == 0);
		IFS(0) &= ~0x0100;
		i++;	
	}
}
