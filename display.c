#include <stdint.h>		/* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "header.h"		/* Prototypes and definitions */

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases.
   provided from course */
void quicksleep(int cyc) {

	int i;
	for(i = cyc; i > 0; i--);
}

/* display_send
 * sends data to display
 * provided from course but changed name
 */
uint8_t display_send(uint8_t data) {

	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

/* display_pixel_on
 * sets a specific pixel to 1 (turn on)
 */
void display_pixel_on(char x, char y){

	display_matrix[x][y] = 1;
}

/* display_pixel_off
 * sets a specific pixel to 0 (turn off)
 */
void display_pixel_off(char x, char y){

	display_matrix[x][y] = 0;
}

/* display_set_pixel
 * sets a specific pixel to a specified value
 */
void display_set_pixel(char x, char y, char set){

	display_matrix[x][y] = set;
}

/* display_get_pixel
 * gets the value/state of a specified pixel
 */
char display_get_pixel(char x, char y){

	return display_matrix[x][y];
}

/* display_reset
 * clear the display by writing 0
 * to the whole array
 */
void display_reset(){

	int x;
	int y;

	for(x = 0; x < 128; x++){
		for(y = 0; y < 32; y++){
			display_matrix[x][y] = 0;
		}
	}
}

/* display_update
 * update the display
 * row by row
 */
void display_update() {

	short x;
	short y;
	short value;
	short k;

	for (y = 0; y < 32 / 4; y++) {

		PORTFCLR = 0x10;		// Display command mode, same as DISPLAY_CHANGE_TO_COMMAND_MODE
		display_send(0x22);		// Set page start and end address
		display_send(y);		// Column to use.

		display_send(0x00);		// Set lower nibble of column start address
		display_send(0x10);		// Set higher part of column start address

		PORTFSET = 0x10;		// Set display to data mode, same as DISPLAY_CHANGE_TO_DATA_MODE

		// Load and send data for each segment
		for (x = 0; x < 128; x++) {

			value = (display_matrix[x][y * 8]);

			for(k = 1; k < 8; k++){

				value |= (display_matrix[x][y * 8 + k]) << k;
			}

			display_send(value);	// Send value to the display
		}

	}
}

// initiate the display
void display_init(void) {

	DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	display_send(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	display_send(0x8D);
	display_send(0x14);
	
	display_send(0xD9);
	display_send(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	display_send(0xA1);
	display_send(0xC8);
	
	display_send(0xDA);
	display_send(0x20);
	
	display_send(0xAF);
}
