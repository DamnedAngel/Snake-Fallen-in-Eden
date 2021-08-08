#pragma once

#define TILE_APPLE					0x98
#define TILE_SNAKEHEAD				0x80
#define TILE_SNAKETAIL				0x88
#define TILE_HEADXPLOD				0x90
#define TILE_VINE					0xa0
#define TILE_GRASS					0xa8
#define TILE_GRASS_EMPTY			0xaf

static const char tileColors_title[] = {
	0xc3,			// 0x00 - Graphic Symbols **Unused**
	0xc3,			// 0x08 - Graphic Symbols **Unused**
	0xc3,			// 0x10 - Graphic Symbols **Unused**
	0xc3,			// 0x18 - Graphic Symbols **Unused**
	0xc3,			// 0x20 - Symbols
	0xc3,			// 0x28 - Symbols
	0xc3,			// 0x30 - Numbers
	0xc3,			// 0x38 - Numbers, Symbols
	0xc3,			// 0x40 - Uppercase
	0xc3,			// 0x48 - Uppercase
	0xc3,			// 0x50 - Uppercase
	0xc3,			// 0x58 - Uppercase, Symbols
	0xc3,			// 0x60 - Lowercase
	0xc3,			// 0x68 - Lowercase
	0xc3,			// 0x70 - Lowercase
	0xc3,			// 0x78 - Lowercase, Symbols
	0xc3,			// 0x80 - Snake Head
	0x23,			// 0x88 - Snake Body
	0x80,			// 0x90 - Exploded snake head
	0x83,			// 0x98 - Apple
	0xc1,			// 0xa0 - Vine
	0x23,			// 0xa8 - Grass
	0xb3,			// 0xb0 - Grass
	0x00,			// 0xb8 - Graphic Symbols **Unused**
	0x43,			// 0xc0 - Mini Snake
	0x43,			// 0xc8 - Mini Snake
	0x43,			// 0xd0 - Mini Snake
	0x43,			// 0xd8 - Mini Snake
	0x43,			// 0xe0 - Mini Snake
	0x43,			// 0xe8 - Mini Snake
	0x43,			// 0xf0 - Mini Snake
	0x43,			// 0xf8 - Mini Snake
};

static const char tileColors_game[] = {
	0xc3,			// 0x00 - Graphic Symbols **Unused**
	0xc3,			// 0x08 - Graphic Symbols **Unused**
	0xc3,			// 0x10 - Graphic Symbols **Unused**
	0xc3,			// 0x18 - Graphic Symbols **Unused**
	0xa1,			// 0x20 - Symbols
	0xa1,			// 0x28 - Symbols
	0xa1,			// 0x30 - Numbers
	0xa1,			// 0x38 - Numbers, Symbols
	0x31,			// 0x40 - Uppercase
	0x31,			// 0x48 - Uppercase
	0x31,			// 0x50 - Uppercase
	0x31,			// 0x58 - Uppercase, Symbols
	0x31,			// 0x60 - Lowercase
	0x31,			// 0x68 - Lowercase
	0x31,			// 0x70 - Lowercase
	0x31,			// 0x78 - Lowercase, Symbols
	0xc3,			// 0x80 - Snake Head
	0x23,			// 0x88 - Snake Body
	0x80,			// 0x90 - Exploded snake head
	0x83,			// 0x98 - Apple
	0xc1,			// 0xa0 - Vine
	0x23,			// 0xa8 - Grass
	0xb3,			// 0xb0 - Grass
	0x00,			// 0xb8 - Graphic Symbols **Unused**
	0x43,			// 0xc0 - Mini Snake
	0x43,			// 0xc8 - Mini Snake
	0x43,			// 0xd0 - Mini Snake
	0x43,			// 0xd8 - Mini Snake
	0x43,			// 0xe0 - Mini Snake
	0x43,			// 0xe8 - Mini Snake
	0x43,			// 0xf0 - Mini Snake
	0x43,			// 0xf8 - Mini Snake
};

static const char tailColors[] = {
	0x23,
	0x43,
	0x53,
	0x63,
	0x73,
	0x93,
	0xa3,
	0xc3,
	0xd3,
	0xe3,
};

static const char tiles_apple[] = {
	// 1 tile
	0b00101100,
	0b00011000,
	0b01110110,
	0b10011111,
	0b10111111,
	0b11111111,
	0b01111110,
	0b00111100,
};

static const char tiles_snakeHead[] = {
	// 4 tiles

	// snake head up
	0b00000000,
	0b00111100,
	0b01000010,
	0b01000010,
	0b10100101,
	0b11000011,
	0b10000001,
	0b01000010,

	// snake head right
	0b01111110,
	0b10100001,
	0b00110001,
	0b00001111,
	0b00010010,
	0b10011000,
	0b01100100,
	0b00011100,

	// snake head down
	0b01000010,
	0b11100111,
	0b10100101,
	0b01000010,
	0b01111110,
	0b00100100,
	0b01000010,
	0b00111100,

	// snake head left
	0b01111110,
	0b10000101,
	0b10001100,
	0b11110000,
	0b01001000,
	0b00011001,
	0b00100110,
	0b00111000,
};

static const char tiles_snakeTail[] = {
	// 1 tile
	0b00111100,
	0b01111110,
	0b10011111,
	0b10111111,
	0b11111111,
	0b11111111,
	0b01111110,
	0b00111100,
};

static const char tiles_headXplod[] = {
	// 8 tiles

	// Frame 1
	0b00000000,
	0b00000000,
	0b00000000,
	0b00011000,
	0b00111000,
	0b00000100,
	0b00000000,
	0b00000000,

	// Frame 2
	0b00000000,
	0b00000000,
	0b00010100,
	0b00111000,
	0b00111100,
	0b00100100,
	0b00000010,
	0b00000000,

	// Frame 3
	0b00000000,
	0b00010010,
	0b01001110,
	0b01111100,
	0b01101110,
	0b00111110,
	0b00100110,
	0b00000000,

	// Frame 4
	0b10010001,
	0b11010110,
	0b01111110,
	0b11000101,
	0b01101110,
	0b01111111,
	0b01110110,
	0b10100011,

	// Frame 5
	0b10010001,
	0b11010110,
	0b01000110,
	0b11000001,
	0b01000110,
	0b01100111,
	0b01110110,
	0b10100011,

	// Frame 6
	0b10010001,
	0b10010010,
	0b00000000,
	0b10000001,
	0b00000010,
	0b01011011,
	0b01010110,
	0b10100011,

	// Frame 7
	0b10010001,
	0b10000000,
	0b00000000,
	0b10000001,
	0b00000010,
	0b00000001,
	0b01001000,
	0b10100011,

	// Frame 8
	0b10000001,
	0b00000000,
	0b00000000,
	0b10000001,
	0b00000000,
	0b00000000,
	0b00010000,
	0b00100001,
};

static const char tiles_vine[] = {
	// 6 tiles

	// vine vertical
	0b01011100,
	0b01100110,
	0b00111010,
	0b00011100,
	0b01101110,
	0b11001100,
	0b01110100,
	0b00111000,

	// vine horizontal
	0b00000100,
	0b11001110,
	0b01101011,
	0b10110011,
	0b10111101,
	0b11011110,
	0b01101000,
	0b00000000,

	// vine top-left
	0b01111100,
	0b11000110,
	0b01010110,
	0b00110110,
	0b01101101,
	0b11001101,
	0b01110100,
	0b00111000,

	// vine bottom-left
	0b01011000,
	0b11011011,
	0b10001101,
	0b11000110,
	0b01101011,
	0b00111101,
	0b00100000,
	0b11000000,

	// vine top-right
	0b00000010,
	0b01111001,
	0b11101101,
	0b01000111,
	0b10001110,
	0b11001100,
	0b01110100,
	0b00111000,

	// vine bottom-right
	0b00011100,
	0b00101110,
	0b01110110,
	0b10100111,
	0b10001110,
	0b11111100,
	0b01110100,
	0b00100000,
};

static const char tiles_grass[] = {
	// 8 tiles

	// grass 0
	0b00000000,
	0b00000000,
	0b00000000,
	0b00100000,
	0b00010000,
	0b00000000,
	0b00000000,
	0b00000000,

	// grass 1
	0b00000000,
	0b00000000,
	0b00001001,
	0b01100110,
	0b00010100,
	0b00001000,
	0b00001000,
	0b00000000,

	// grass 2
	0b00000000,
	0b00000000,
	0b00001000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01000000,
	0b00101000,

	// grass 3
	0b00010000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000100,
	0b00001000,
	0b00000000,

	// grass 4 (empty)
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,

	// grass 5 (empty)
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,

	// grass 6 (empty)
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,

	// grass 7 (empty)
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
};

