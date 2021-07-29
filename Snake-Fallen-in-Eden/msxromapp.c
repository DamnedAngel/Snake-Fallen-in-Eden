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
#include "tiles.h"

#define NAMETABLE					0x1800
#define PATTERNTABLE				0x0000
#define COLORTABLE					0X2000

bool EoG;
bool collision;
bool edenUp;

unsigned char collisionFrame;
unsigned char edenUpFrame;

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

#ifdef DEBUG
void charMap() {
	for (unsigned char y = 0; y < 16; y++) {
		Vpoke(NAMETABLE + 2 + y, y < 10 ? '0' + y : 'A' - 10 + y);
		Vpoke(NAMETABLE + 32 * (y + 2), y < 10 ? '0' + y : 'A' - 10 + y);
		for (unsigned char x = 0; x < 16; x++)
			Vpoke(NAMETABLE + 66 + y * 32 + x, y * 16 + x);
	}
}
#endif

void blockToVRAM(int VRAMAddr, char* RAMAddr, unsigned int blockLength) {
	VpokeFirst(VRAMAddr);
	for (; blockLength > 0; blockLength--)
		VpokeNext(*(RAMAddr++));
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

void buildTiles() {
	blockToVRAM(PATTERNTABLE + TILE_APPLE * 8, tiles_apple, sizeof(tiles_apple));
	blockToVRAM(PATTERNTABLE + TILE_SNAKEHEAD * 8, tiles_snakeHead, sizeof(tiles_snakeHead));
	blockToVRAM(PATTERNTABLE + TILE_SNAKETAIL * 8, tiles_snakeTail, sizeof(tiles_snakeTail));
	blockToVRAM(PATTERNTABLE + TILE_HEADXPLOD * 8, tiles_headXplod, sizeof(tiles_headXplod));
	blockToVRAM(PATTERNTABLE + TILE_VINE * 8, tiles_vine, sizeof(tiles_vine));
	blockToVRAM(PATTERNTABLE + TILE_GRASS * 8, tiles_grass, sizeof(tiles_grass));
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
	// Set colors
	blockToVRAM(COLORTABLE, tileColors_title, sizeof(tileColors_title));

	Cls();
	_print(titleScreen);

	while (allJoysticks() || allTriggers()) {}		// waits until key release
	while (!(allJoysticks() || allTriggers())) {}	// waits until key press
}

void dropApple() {
	do {
		applePos = NAMETABLE + 32 + rand() % (21 * 32);
	} while (Vpeek(applePos) != TILE_GRASS_EMPTY);
	Vpoke(applePos, TILE_APPLE);
}

void game() {
	// Set colors
	blockToVRAM(COLORTABLE, tileColors_game, sizeof(tileColors_game));

	srand(Peekw(BIOS_JIFFY));

	Cls();
	_print(gameScreen);
	Locate(18, 23);
	PrintNumber(highscore);

	// Initialize game variables
	edenUp = false;
	EoG = false;
	collision = false;
	collisionFrame = TILE_HEADXPLOD;
	score = 0;
	growth = 0;
	snakeHeadPos = NAMETABLE + 10 * 32 + 11;
	direction = RIGHT;
	lastDirection = 0;	// initially, none
	Pokew(BIOS_JIFFY, 0);

	// initialize snake
	snakeTail = snake;
	snakeHead = snake + 1;
	snake[0] = snakeHeadPos - 1;
	snake[1] = snakeHeadPos;
	Vpoke(snakeHeadPos - 1, TILE_SNAKETAIL);
	Vpoke(snakeHeadPos, TILE_SNAKEHEAD + 1);

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
		if ((Peekw(BIOS_JIFFY) >= waitFrames) && (!collision)) {

			// Controls eden progression
			if (!(--waitMoves)) {
				// Next Eden
				edenUp = true;
				edenUpFrame = 0;

				Locate(29, 23);
				PrintNumber(++eden);
				waitFrames--;
				waitMoves = 100;
			}

			// move snake
			switch (direction) {
			case UP:
				snakeHeadPos -= 32;
				break;
			case RIGHT:
				snakeHeadPos++;
				break;
			case DOWN:
				snakeHeadPos += 32;
				break;
			case LEFT:
				snakeHeadPos--;
				break;
			}

			content = Vpeek(snakeHeadPos);

			collision = (content != TILE_GRASS_EMPTY) && (content != TILE_APPLE);
			if (collision) {
				// Collision start
				if (content < TILE_VINE) {
					Vpoke(COLORTABLE + 0x12,
						(tileColors_game[TILE_HEADXPLOD / 8] & 0xf0) |
						(tileColors_game[TILE_GRASS / 8] & 0x0f));
				}
				Vpoke(snakeHeadPos, TILE_HEADXPLOD);
				Beep();
			} else {
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

				// Draws head in new position
				Vpoke(snakeHeadPos, TILE_SNAKEHEAD + (direction - 1) / 2);
			}

			// Erases last tail segment
			if (growth == 0) {
				Vpoke(*snakeTail, TILE_GRASS_EMPTY);
				snakeTail++;
				if (snakeTail > &snake[511])
					snakeTail = snake;
			}
			else {
				growth--;
			}

			// Replaces head with tail segment
			Vpoke(*snakeHead, TILE_SNAKETAIL);

			// update buffer
			snakeHead++;
			if (snakeHead > &snake[511]) snakeHead = snake;
			*snakeHead = snakeHeadPos;

			lastDirection = direction;		// saves last direction after moving
			Pokew(BIOS_JIFFY, 0);
		}

		// here we will add animations and sound effects routine 
		{
			// Eden Up effect
			if (edenUp) {
				if (++edenUpFrame & 1) {
					// random color
					Vpoke(COLORTABLE + TILE_SNAKETAIL / 8, (rand() & 0xf0) + 3);
				} else {
					// next color
					Vpoke(COLORTABLE + TILE_SNAKETAIL / 8, tailColors[((eden - 1) % sizeof(tailColors))]);
				}
				edenUp = edenUpFrame < 60;
			}

			// Collision animation
			if (collision && (Peekw(BIOS_JIFFY) >= 6)) {
				Vpoke(snakeHeadPos, ++collisionFrame);
				EoG = (collisionFrame == TILE_HEADXPLOD + 7);
				Pokew(BIOS_JIFFY, 0);
			}
		}

		lastJiffy = Peekw(BIOS_JIFFY);
	}

	Poke(BIOS_JIFFY, 0);
	while (Peek(BIOS_JIFFY) < 90) {}
}

void gameOver() {
	Locate(0, 9);
	_print(gameOverMsg);

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
	SetColors(12, 3, 1);

	buildFont();
	buildTiles();

#ifdef DEBUG
	blockToVRAM(COLORTABLE, tileColors_title, sizeof(tileColors_title));
	charMap();
	while (!(allJoysticks() || allTriggers())) {}	// waits until key press
#endif

	// program's infinite loop
	while (1) {
		title();
		game();
		gameOver();
	}
}
