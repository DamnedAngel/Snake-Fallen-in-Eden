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
#include "vdp_sprites.h"
#include "screens.h"
#include "tiles.h"
#include "sprites.h"
#include "sounds.h"

extern void buildEden(int VRAMAddr, char* RAMAddr, unsigned int blockLength);

#define NAMETABLE					0x1800
#define PATTERNTABLE				0x0000
#define COLORTABLE					0x2000
#define SPRITEPATTERNTABLE			0x3800
#define SPRITEATTRIBUTETABLE		0x1B00

bool EoG;
bool collision;
bool edenUp;
bool appleEaten;

unsigned char collisionTile;
unsigned char edenUpFrame;
unsigned char edenUpSound;
unsigned char appleEatenFrame;
unsigned char appleEatenBonusX;
unsigned char appleEatenBonusY;

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
	ret	z
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

/*
void blockToVRAM(int VRAMAddr, char* RAMAddr, unsigned int blockLength) {
	VpokeFirst(VRAMAddr);
	for (; blockLength > 0; blockLength--)
		VpokeNext(*(RAMAddr++));
} 
*/

void blockToVRAM(int VRAMAddr, char* RAMAddr, int blockLength) {
// Fabio suggested to leave a comment here that the
// function is not working for colors
// so HE can fix it someday.
	__asm

	ld		hl, #2
	add		hl, sp

	ld		a, (hl)
	out		(#0x99), a
	inc		hl
	ld		a, (hl)
	and		#0x3f
	or		#0x40
	out		(#0x99), a

	inc		hl
	ld		e, (hl)
	inc		hl
	ld		d, (hl)

	inc		hl
	ld		b, (hl)
	ld		a, b
	inc		hl
	or		a               ; cp 0 ==> tests if lsb is zero
	ld		a, (hl)
	ld		l, e
	ld		h, d
	ld		c, #0x98
	jr      z, b2vr_loop    ; if lsb is not zero
	inc		a               ;   adjusts (increment) msb
	
b2vr_loop:                  ; b (lsb) controls inner loop; a (msb) controls outer loop
	outi
	jr		nz, b2vr_loop
	dec		a
	jr		nz, b2vr_loop
	ret

	__endasm;
}

void buildFont() {
	unsigned char temp;
	for (int i = 0; i <= 127; i++) {
		for (int j = 0; j < 4; j++) {
			temp = Vpeek((int)(PATTERNTABLE + i * 8 + j));
			Vpoke((int)(PATTERNTABLE + i * 8 + j), temp >> 1);
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
	blockToVRAM(PATTERNTABLE + (TILE_GRASS + 8) * 8, tiles_grass, sizeof(tiles_grass));
}

void buildSprites() {
	VDPwriteNi(6, SPRITEPATTERNTABLE >> 11);
	SpriteOn();
	SpriteReset();
	Sprite8();
	SpriteSmall();

	/*
	// Alternative 1: Fusion-C Style (Too fast for MSX1's VDP)
	for (unsigned char i = 0; i < sizeof(sprite_patterns)/8; i++) {
		SetSpritePattern(i, sprite_patterns + (i * 8), 8);
	}
	*/

	/*
	// Alternative 2 (Even faster)
	SetSpritePattern(0, sprite_patterns, sizeof(sprite_patterns));
	*/

	// Alternative 3 (Very slow - solves the problem)
	blockToVRAM(SPRITEPATTERNTABLE, sprite_patterns, sizeof(sprite_patterns));
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
	//Set title colors
	blockToVRAM(COLORTABLE, tileColors_title, sizeof(tileColors_title));

	// Build Screen
	buildEden(NAMETABLE, titleScreen, sizeof(titleScreen));

	while (allJoysticks() || allTriggers()) {}		// waits for key release
	while (!(allJoysticks() || allTriggers())) {}	// waits for key press
}

void dropApple() {
	do {
		applePos = NAMETABLE + 32 + rand() % (21 * 32);
	} while (Vpeek(applePos) != TILE_GRASS_EMPTY);
	Vpoke(applePos, TILE_APPLE);
}

void game() {
	blockToVRAM(COLORTABLE, tileColors_game, sizeof(tileColors_game));

	srand(Peekw(BIOS_JIFFY));

	// Build screen
	buildEden(NAMETABLE, gameScreen, sizeof(gameScreen));

	Locate(18, 23);
	PrintNumber(highscore);

	// Initialize game variables
	edenUp = false;
	appleEaten = false;
	EoG = false;
	collision = false;
	collisionTile = TILE_HEADXPLOD;
	score = 0;
	growth = 0;
	snakeHeadPos = NAMETABLE + 10 * 32 + 11;
	direction = RIGHT;
	lastDirection = 0;	// initially, none
	Pokew(BIOS_JIFFY, 0);
	appleEatenBonusX = 0;
	appleEatenBonusY = 255;

	// Initialize snake
	snakeTail = snake;
	snakeHead = snake + 1;
	snake[0] = snakeHeadPos - 1;
	snake[1] = snakeHeadPos;
	Vpoke(snakeHeadPos - 1, TILE_SNAKETAIL);
	Vpoke(snakeHeadPos, (unsigned char) (TILE_SNAKEHEAD + 1));

	// Initialize difficulty
	waitFrames = 15;
	waitMoves = 100;
	eden = 1;

	// initialize sound
	for (unsigned char i = 0; i < sizeof(gameSound); i++) {
		PSGwrite(i, gameSound[i]);
	}

	dropApple();

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
				edenUpSound = 60;
				PSGwrite(10, 15);

				Locate(29, 23);
				PrintNumber(++eden);
				waitFrames--;
				waitMoves = 100;
			}

			// move snake
			switch (direction) {
			case UP:
				snakeHeadPos-=32;// snakeHeadPos = snakeHeadPos - 32;
				break;
			case RIGHT:
				snakeHeadPos++;  // snakeHeadPos = snakeHeadPos + 1;
				break;
			case DOWN:
				snakeHeadPos+=32;// snakeHeadPos = snakeHeadPos + 32;
				break;
			case LEFT:
				snakeHeadPos--;  // snakeHeadPos = snakeHeadPos - 1;
				break;
			}

			content = Vpeek(snakeHeadPos);

			collision = (content < TILE_GRASS) && (content != TILE_APPLE);
			if (collision) {
				// Collision start
				if (content < TILE_VINE) {
					Vpoke(COLORTABLE + TILE_HEADXPLOD / 8,
						((tileColors_game[TILE_HEADXPLOD / 8] & 0xf0) | (tileColors_game[TILE_GRASS / 8] & 0x0f)));


					/*
							0b10000000 = 0x80        0b00100011 = 0x23
						  &	0b11110000 = 0xf0      & 0b00001111 = 0x0f
						  ------------             ------------
							0b10000000               0b00000011

							0b10000000
						  | 0b00000011
						  ------------
							0b10000011 = 0x83
					*/
				}
				Vpoke(snakeHeadPos, TILE_HEADXPLOD);

				for (unsigned char i = 0; i < sizeof(xplodSound); i++) {
					PSGwrite(i, xplodSound[i]);
				}
				
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
					appleEaten = true;
					appleEatenFrame = 0;
					appleEatenBonusX = 8 * (snakeHeadPos % 32);
					appleEatenBonusY = 8 * (snakeHeadPos / 32) - 4;
				}

				// Draws head in new position
				Vpoke(snakeHeadPos, TILE_SNAKEHEAD + (direction - 1) / 2);
				PSGwrite(13, 4);
			}

			// Erases last tail segment
			if (growth == 0) {
				Vpoke(*snakeTail, TILE_GRASS + (rand() & 0x0f));
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

			lastDirection = direction;  // saves last direction after moving
			Pokew(BIOS_JIFFY, 0);
		}

		// here we will add the animation and sound effects routine
		{
			// Collision animation
			if (collision && (Peekw(BIOS_JIFFY) >= 6)) {
				Vpoke(snakeHeadPos, ++collisionTile);
				Pokew(BIOS_JIFFY, 0);
				EoG = collisionTile >= TILE_HEADXPLOD + 7;
			}

			// Apple eaten effect
			if (appleEaten) {
				if (appleEatenFrame < 16)
					PSGwrite(9, 15 - appleEatenFrame);
				if (!(appleEatenFrame & 3)) {
					PutSprite(0, bonus, appleEatenBonusX, --appleEatenBonusY, BONUS_COLOR);
					PutSprite(1, 9, appleEatenBonusX, appleEatenBonusY, BONUSBEVEL_COLOR);
				}
				if (!(appleEaten = (++appleEatenFrame < 90) && (!EoG))) {
					PutSprite(0, 0, 0, 255, 0);
					PutSprite(1, 0, 0, 255, 0);
					appleEatenBonusX = 0;		// Extra safety by Fábio Santos
					appleEatenBonusY = 255;		// Extra safety by Fábio Santos
				}
			}

			// Eden up effect
			if (edenUp) {
				if (++edenUpFrame & 1) {
					// random color & sound
					PSGwrite(4, rand());
					Vpoke(COLORTABLE + TILE_SNAKETAIL / 8,
						(rand() & 0x00f0) + 3);
				} else {
					// next color & freq up sound effect 
					PSGwrite(4, edenUpSound--);
					Vpoke(COLORTABLE + TILE_SNAKETAIL / 8,
						tailColors[(eden - 1) % sizeof(tailColors)]);
				}
				if (!(edenUp = edenUpFrame < 60)) {
					PSGwrite(10, 0);
				}
			}
		}

		lastJiffy = Peekw(BIOS_JIFFY);
		VDPwriteNi(6, SPRITEPATTERNTABLE >> 11);
	}

	Pokew(BIOS_JIFFY, 0);
	while (Peekw(BIOS_JIFFY) < 90) {}
}

void gameOver() {
	Locate(0, 10);
	_print(gameOverMsg);

	while (allJoysticks() || allTriggers()) {}		// waits for key release
	while (!(allJoysticks() || allTriggers())) {}	// waits for key press
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
	buildSprites();

#ifdef DEBUG
	blockToVRAM(COLORTABLE, tileColors_title, sizeof(tileColors_title));
	charMap();
	while (!(allJoysticks() || allTriggers())) {}	// waits for key press
#endif

	// program's infinite loop
	while (true) {
		title();
		game();
		gameOver();
	}
}
