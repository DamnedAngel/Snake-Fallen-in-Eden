// ----------------------------------------------------------
//		msxromapp.c - by Danilo Angelo, 2020
//
//		ROM program(cartridge) for MSX example
//		C version
// ----------------------------------------------------------

#include <stdbool.h>
#include <stdlib.h>
#include "targetconfig.h"
#include "MSX/BIOS/msxbios.h"
#include "msx_fusion.h"
#include "screens.h"

#define NAMETABLE					0x1800
#define PATTERNTABLE				0x0000

#define TILE_GRASS					' '
#define TILE_SNAKETAIL				'o'
#define TILE_SNAKEHEAD				'*'
#define TILE_APPLE					'#'

bool EoG;
unsigned int snakeHeadPos;
unsigned char direction, lastDirection;
unsigned char joy;
unsigned char content;
unsigned int lastJiffy;

unsigned int snake[512];
unsigned int *snakeHead, *snakeTail;

unsigned int applePos;
unsigned char growth;

unsigned char bonus;
unsigned int score;
unsigned int highscore = 0;

unsigned char waitFrames, waitMoves, eden;

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

void buildFont() {
	// Italic
	unsigned char temp;
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 4; j++) {
			temp = Vpeek(PATTERNTABLE + i * 8 + j);
			Vpoke(PATTERNTABLE + i * 8 + j, temp >> 1);
		}
	}
}

char allJoysticks() {
	char result;
	if (result = JoystickRead(0)) return result;
	if (result = JoystickRead(1)) return result;
	return JoystickRead(2);
}

char allTriggers() {
	return TriggerRead(0) ||
		TriggerRead(1) || TriggerRead(2) ||
		TriggerRead(3) || TriggerRead(4);
}

void title() {
	Cls();
	print(titleScreen);

	while (allJoysticks() || allTriggers()) {}		// waits until key release
	while (!(allJoysticks() || allTriggers())) {}	// waits until key press
}

void dropApple() {
	do {
		applePos = NAMETABLE + 32 + rand() % (21 * 32);
	} while (Vpeek(applePos) != TILE_GRASS);
	Vpoke(applePos, TILE_APPLE);
}

void game() {
	srand(Peekw(BIOS_JIFFY));

	Cls();
	print(gameScreen);
	Locate(18, 23);
	PrintNumber(highscore);

	// Initialize game variables
	score = 0; 
	growth = 0;
	snakeHeadPos = NAMETABLE + 10 * 32 + 11;
	direction = RIGHT;
	lastDirection = 0;	// initially, none
	EoG = false;
	Pokew(BIOS_JIFFY, 0);

	// initialize snake
	snakeTail = snake;
	snakeHead = snake + 1;
	snake[0] = snakeHeadPos - 1;
	snake[1] = snakeHeadPos;
	Vpoke(snakeHeadPos - 1, TILE_SNAKETAIL);
	Vpoke(snakeHeadPos, TILE_SNAKEHEAD);

	// initialize difficulty
	waitFrames = 15;
	waitMoves = 100;
	eden = 1;

	// Drop first apple
	dropApple();

	// Game's main loop
	while (!EoG) {
		while (lastJiffy == Peekw(BIOS_JIFFY)) {
			joy = allJoysticks();

			// Alternative 1: IFs inside SWITCH/CASE
			switch (lastDirection) {
			case UP:
				if ((joy == LEFT) || (joy == RIGHT)) direction = joy;
				break;
			case RIGHT:
				if ((joy == UP) || (joy == DOWN)) direction = joy;
				break;
			case DOWN:
				if ((joy == LEFT) || (joy == RIGHT)) direction = joy;
				break;
			case LEFT:
				if ((joy == UP) || (joy == DOWN)) direction = joy;
				break;
			}

/*
			// Alternative 2: Composition of Conditions in a single IF
			if ((((lastDirection == UP) || (lastDirection == DOWN)) && ((joy == RIGHT) || (joy == LEFT))) ||
				(((lastDirection == RIGHT) || (lastDirection == LEFT)) && ((joy == UP) || (joy == DOWN))))
				direction = joy;
*/
		}
		// from this point on, 1 pass per frame
		if (Peekw(BIOS_JIFFY) >= waitFrames) {

			// Controls eden progression
			if (! (--waitMoves)) {
				// Next Eden
				Locate(29, 23);
				PrintNumber(++eden);
				waitFrames--;
				waitMoves = 100;
			}

			// move snake
			switch (direction) {
			case UP:
				snakeHeadPos-=32;
				break;
			case RIGHT:
				snakeHeadPos++;
				break;
			case DOWN:
				snakeHeadPos+=32;
				break;
			case LEFT:
				snakeHeadPos--;
				break;
			}

			content = Vpeek(snakeHeadPos);

			if (content == TILE_APPLE) {
				dropApple();
				bonus = (rand() & 7) + 1;
				growth += bonus;
				score += bonus;
				Locate(7, 23);
				PrintNumber(score);
				if (score > highscore) {
					highscore = score;
					Locate(18, 23);
					PrintNumber(highscore);
				}
			}
			else {
				EoG = (content != ' ');
			}

			// Erases last tail segment
			if (growth == 0) {
				Vpoke(*snakeTail, TILE_GRASS);
				snakeTail++;
				if (snakeTail > &snake[511])
					snakeTail = snake;
			}
			else {
				growth--;
			}

			// Replaces head with tail segment
			Vpoke(*snakeHead, TILE_SNAKETAIL);

			// Draws head in new position
			Vpoke (snakeHeadPos, TILE_SNAKEHEAD);
			snakeHead++;
			if (snakeHead > &snake[511]) snakeHead = snake;
			*snakeHead = snakeHeadPos;

			lastDirection = direction;		// saves last direction after moving
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

	while (allJoysticks() || allTriggers()) {}		// waits until key release
	while (!(allJoysticks() || allTriggers())) {}	// waits until key press
}

// ----------------------------------------------------------
//	This is the main function for your C MSX APP!
//
//	Your fun starts here!!!
//	Replace the code below with your art.
void main(void) {
	KeySound(0);
	Screen(1);
	Width(32);
	buildFont();

		// program's infinite loop
	while (1) {
		title();
		game();
		gameOver();
	}
}
