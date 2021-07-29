#pragma once

static const char gameSound[] = {
	0,		0,				// Channel A Freq		none; movement
	255,	0,				// Channel B Freq		eat apple
	40,		0,				// Channel C Freq		level up
	31,						// Noise Freq			(Movement noise)
	49,						// Mixing				A: noise, B: tone, C: Tone
	16,		0,		0,		// Channels volume
	100,	4,				// Envelope freq
};