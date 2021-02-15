// ----------------------------------------------------------
//		msxromapp.c - by Danilo Angelo, 2020
//
//		ROM program(cartridge) for MSX example
//		C version
// ----------------------------------------------------------

#include <stdbool.h>
#include "targetconfig.h"
#include "MSX\BIOS\msxbios.h"
#include "msx_fusion.h"
#include "screens.h"

unsigned char x, y;
bool EoG;

#define Peek( address )			( *( (volatile unsigned char*)(address) ) )
#define Peekw( address )		( *( (volatile unsigned int*)(address) ) )

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
	InputChar();
}

void game() {
	Cls();
	print(gameScreen);

	// Initialize game variables
	x = 10;
	y = 10;
	EoG = false;

	// Game's main loop
	while (!EoG) {
		Locate(x, y);
		print("*");
	}

	InputChar();
}

void gameOver() {
	Locate(0, 9);
	print(gameOverMsg);
	InputChar();
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
