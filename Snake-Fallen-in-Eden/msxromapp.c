// ----------------------------------------------------------
//		msxromapp.c - by Danilo Angelo, 2020
//
//		ROM program(cartridge) for MSX example
//		C version
// ----------------------------------------------------------

#include <stdbool.h>
#include "targetconfig.h"
#include "MSX/BIOS/msxbios.h"
#include "msx_fusion.h"
#include "screens.h"

#define NAMETABLE					0x1800

bool EoG;
unsigned char x, y, direction;
unsigned char joy;
unsigned char content;
unsigned int lastJiffy;

#define Peek( address )				( *( (volatile unsigned char*)(address) ) )
#define Peekw( address )			( *( (volatile unsigned int*)(address) ) )

// ----------------------------------------------------------
//	This is an example of embedding asm code into C.
//	This is only for the demo app.
//	You can safely remove it for your application.
#pragma disable_warning 85	// because the var msg is not used in C context
void _print(char* msg) {
	__asm
		ld      hl, #2; retrieve address from stack
		add     hl, sp
		ld		b, (hl)
		inc		hl
		ld		h, (hl)
		ld		l, b

		_printMSG_loop :
		ld		a, (hl); print
		or		a
		ret z
		push	hl
		push	ix
		ld		iy, (#0xfcc0); BIOS_ROMSLT
		ld		ix, #0x00a2; BIOS_CHPUT
		call	#0x001c; BIOS_CALSLT
		ei
		pop		ix
		pop		hl
		inc		hl
		jr		_printMSG_loop
	__endasm;

	return;
}

// ----------------------------------------------------------
//	This is an example of using debug code in C.
//	This is only for the demo app.
//	You can safely remove it for your application.
void print(char* msg) {
#ifdef DEBUG
	_print("[DEBUG]");
#endif
	_print(msg);
	return;
}

void title() {
	Cls();
	print(titleScreen);

	while (Inkey() > 0) {}			// wait until key release
	InputChar();					// wait for keypress
}

void game() {
	Cls();
	print(gameScreen);

	// Initialize game variables
	x = 10;
	y = 10;
	direction = RIGHT;
	EoG = false;
	Pokew(BIOS_JIFFY, 0);

	// Game's main loop
	while (!EoG) {
		while (lastJiffy == Peekw(BIOS_JIFFY)) {
			joy = JoystickRead(0);
			if ((joy == UP) || (joy == RIGHT) || (joy == DOWN) || (joy == LEFT)) {
				direction = joy;
			}
		}
		// from this point on, 1 pass per frame

		if (Peekw(BIOS_JIFFY) == 15) {

			// move snake
			switch (direction) {
			case UP:
				y--;
				break;
			case RIGHT:
				x++;
				break;
			case DOWN:
				y++;
				break;
			case LEFT:
				x--;
				break;
			}

			content = Vpeek(NAMETABLE + y * 32 + x);
			EoG = (content != ' ');

			Locate(x, y);
			print("*");

			Pokew(BIOS_JIFFY, 0);
		}

		// here we will add the sound effects routine
		{
		}

		lastJiffy = Peekw(BIOS_JIFFY);
	}

	Beep();
	Poke(BIOS_JIFFY, 0);
	while (Peek(BIOS_JIFFY) < 90) {}
}

void gameOver() {
	Locate(0, 9);
	print(gameOverMsg);

	while (Inkey() > 0) {}			// wait until key release
	InputChar();					// wait for keypress
}

// ----------------------------------------------------------
//	This is the main function for your C MSX APP!
//
//	Your fun starts here!!!
//	Replace the code below with your art.
void main(void) {
	Screen(1);
	Width(32);

	// program's infinite loop
	while (1) {
		title();
		game();
		gameOver();
	}
}
