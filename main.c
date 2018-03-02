#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "header.h"		/* Prototypes and definitions */

/* start_run
 * stage the helicopter before starting the game
 */
void start_run(void){

	int x;

	for(x = 0; x < 8; x++){

		display_reset();
		environment_set();
		helicopter_draw(x, 12, helicopter_bitmap);
		display_update();

		timer_wait(100);
	}
}

/* running
 * called to have the helicopter scoot across the screen
 * while also awarding points to the "player"
 */
void running(void){

	int x;

	for(x = 8; x < 127; x++){

		display_reset();
		environment_set();
		environment_update();
		helicopter_placement(x);
		display_update();

		score_inc();

		timer_wait(100);
	}
}

/* main
 * does all the things
 */
int main(void) {
	/* Set up peripheral bus clock */
	/* OSCCONbits.PBDIV = 1; */
	OSCCONCLR = 0x100000; /* clear PBDIV bit 1 */
	OSCCONSET = 0x080000; /* set PBDIV bit 0 */

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;	// set leds to be outputs ???
	
	PORTE = 0x0;		// set PORTE to 0

	/* Set up PORTE to blink our leds for score 
	 * we should not have to do any manual setup,
	 * but simply do PORTE++ in order to 
	 * increment the value on the LEDs.

	 * Meaning that we should be able to initialise PORTE
	 * with e.g. 0xAC above to show that it activated*/

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
	SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	/* Initilize display */
	display_init();
	display_reset();

	start_run();

	// wait before starting the run across the field so
	// that the player has some time to see what is going on
	timer_wait(1000);

	while(1){
		running();
	}

	return 0;
}
