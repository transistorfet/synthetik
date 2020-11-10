
#include <Arduino.h>
#include "YM3812.h"
#include "YM3812_instruments.h"

#define YM_LDATA_PORT	PORTA
#define YM_LDATA_PIN	PINA
#define YM_LDATA_DDR	DDRA

#define YM_CS		38
#define YM_RD		39
#define YM_WR		40
#define YM_A0		41
#define YM_RESET	50

#define YM_HIHAT	0
#define YM_CYMBAL	1
#define YM_TOMTOM	2
#define YM_SNAREDRUM	3
#define YM_BASSDRUM	4


byte ym_memmap[256];

// Based on a 3.57954 MHz crystal
word note_fnums[] = {
	// C2 C#2 D2 D#2 E2 F2 F#2 G2 G#2 A2 A#2 B2
	86, 91, 97, 103, 109, 115, 122, 129, 137, 145, 154, 163,
	// C3 C#3 D3 D#3 E3 F3 F#3 G3 G#3 A3 A#3 B3
	172, 183, 194, 205, 217, 230, 244, 258, 274, 290, 307, 326,
	// C4 C#4 D4 D#4 E4 F4 F#4 G4 G#4 A4 A#4 B4
	345, 365, 387, 410, 435, 460, 488, 517, 547, 580, 614, 651,
};

struct ym_channel channels[9] = {
	{ 0x00, 0x03 },
	{ 0x01, 0x04 },
	{ 0x02, 0x05 },
	{ 0x08, 0x0B },
	{ 0x09, 0x0C },
	{ 0x0A, 0x0D },
	{ 0x10, 0x13 },
	{ 0x11, 0x14 },
	{ 0x12, 0x15 },
};

struct instrument presets[] = {
	// Piano
	{ 0x01, 0x10, 0xF2, 0x77, 0x00, 0x00, 0x01, 0x00, 0xF2, 0x77, 0x00 },
	// Something
	{ 0x01, 0x10, 0xB0, 0xA7, 0x00, 0x00, 0x06, 0x00, 0xB0, 0xA7, 0x00 },
	// Muted Guitar
	{ 0x21, 0x09, 0x9C, 0x7B, 0x07, 0x00, 0x02, 0x03, 0x95, 0xFB, 0x00 },
	// Overdriven Guitar
	{ 0x21, 0x84, 0x81, 0x98, 0x07, 0x01, 0x21, 0x04, 0xA1, 0x59, 0x00 },
	// Distorted Guitar
	{ 0xB1, 0x0C, 0x78, 0x43, 0x01, 0x00, 0x22, 0x03, 0x91, 0xFC, 0x03 },

	//// Percussion ////
	// Bass Drum
	//{ 0x00, 0x00, 0xAA, 0x49, 0x05, 0x00,   0x01, 0x00, 0xAA, 0x39, 0x00,   0x00, 0x11 },
	{ 0x00, 0x0b, 0xA8, 0x4C, 0x00, 0x00,   0x00, 0x00, 0xD6, 0x4F, 0x00,   0x80, 0x10 },
	//{ 0x00, 0x0b, 0xa8, 0x4c, 0x00, 0x00,   0x0f, 0x00, 0xd6, 0x4f, 0x00,   0x00, 0x11 },
	// Hi Hat				// Snare Drum
	{ 0x06, 0x00, 0xAA, 0x49, 0x00, 0x00,   0x01, 0x00, 0xF7, 0xF7, 0x00,   0x20, 0x00 },
	//					// bad cymbal
	{ 0x06, 0x00, 0xAA, 0x49, 0x0F, 0x00,   0x01, 0x00, 0x9F, 0x39, 0x00,   0x60, 0x11 },
	//{ 0x01, 0x0b, 0xc9, 0x4f, 0x00, 0x00,   0x00, 0x00, 0xa4, 0x4f, 0x00 },
};

void setup_audio()
{
	pinMode(YM_CS, OUTPUT);
	pinMode(YM_RD, OUTPUT);
	pinMode(YM_WR, OUTPUT);
	pinMode(YM_A0, OUTPUT);
	pinMode(YM_RESET, OUTPUT);
	digitalWrite(YM_CS, 1);
	digitalWrite(YM_RD, 1);
	digitalWrite(YM_WR, 1);
	digitalWrite(YM_A0, 0);
	digitalWrite(YM_RESET, 1);

	// Data Bus
	YM_LDATA_PORT = 0x00;	// D0 - D7
	YM_LDATA_DDR = 0x00;
}

void ym_set_instrument(byte channel, struct instrument *config)
{
	struct ym_channel ch = channels[channel];

	ym_write_data(0x20 + ch.op1, config->a20);
	ym_write_data(0x40 + ch.op1, config->a40);
	ym_write_data(0x60 + ch.op1, config->a60);
	ym_write_data(0x80 + ch.op1, config->a80);
	ym_write_data(0xC0 + ch.op1, config->aC0);
	ym_write_data(0xE0 + ch.op1, config->aE0);
	ym_write_data(0x20 + ch.op2, config->b20);
	ym_write_data(0x40 + ch.op2, config->b40);
	ym_write_data(0x60 + ch.op2, config->b60);
	ym_write_data(0x80 + ch.op2, config->b80);
	ym_write_data(0xE0 + ch.op2, config->bE0);

	ym_write_data(0xA0 + channel, config->gA0);
	ym_write_data(0xB0 + channel, config->gB0);

}

void initialize_audio()
{
	digitalWrite(YM_RESET, 0);
	delay(10);
	digitalWrite(YM_RESET, 1);

	ym_write_data(0x01, 0x10);

	ym_write_data(0xBD, 0x20);

	ym_set_instrument(0, &presets[0]);
	ym_set_instrument(1, &presets[0]);
	ym_set_instrument(2, &presets[0]);
	ym_set_instrument(3, &presets[0]);
	ym_set_instrument(4, &presets[0]);
	ym_set_instrument(5, &presets[0]);
	ym_set_instrument(6, &presets[5]);	// Bass Drum
	ym_set_instrument(7, &presets[6]);	// HiHat and Snare Drum
	ym_set_instrument(8, &presets[7]);	// Cymbal?


	ym_write_data(0xB0, 0x31);		// Turn the voice on; set the octave and freq MSB
	delay(1000);
	ym_write_data(0xB0, 0x11);		// Turn the voice off; set the octave and freq MSB
}


struct instrument *instrument_select(byte number)
{
	if (number == 18)
		return &list[0];
	else if (number == 34 || number == 37)
		return &list[1];
	else if (number == 117 || number == 118)
		return &list[2];
	else if (number == 29)
		return &list[3];

	//if (number >= 1 && number <= 8)
	else
		return &presets[1];
	return NULL;
}

void ym_change_instrument(byte channel, byte number)
{
	if (number > 120)
		return;

	channel = channel % 6;
	//struct instrument *config = instrument_select(number);
	struct instrument *config = &list[number];
	if (config)
		ym_set_instrument(channel, config);
}


void ym_note_on(byte channel, byte note)
{
	channel = channel % 6;
	byte block = (note / 12);
	byte offset = note % 12;

	ym_write_data(0xA0 + channel, note_fnums[offset + 12]);
	ym_write_data(0xB0 + channel, 0x20 | (block << 2) | (note_fnums[offset + 12] >> 8));
}

void ym_note_off(byte channel, byte note)
{
	channel = channel % 6;
	ym_write_data(0xB0 + channel, 0x00);
}


byte percussion_select(byte note)
{
	switch (note) {
		case 35:
		case 36:
			return YM_BASSDRUM;

		case 38:
		case 40:
			return YM_SNAREDRUM;

		case 39:
		case 42:
		case 44:
		case 46:
		case 53:
			return YM_HIHAT;

		case 49:
		case 51:
		case 52:
		case 55:
		case 57:
		case 59:
			return YM_CYMBAL;

		case 41:
		case 43:
		case 45:
		case 47:
		case 48:
		case 50:
			return YM_TOMTOM;

		default:
			return 0;
	}
}



void ym_drum_on(byte drum)
{
	drum = percussion_select(drum);
	ym_write_data(0xBD, (ym_memmap[0xBD] & 0xE0) | (0x01 << drum));
}

void ym_drum_off(byte drum)
{
	drum = percussion_select(drum);
	ym_write_data(0xBD, ym_memmap[0xBD] & (0xE0 | ~(0x01 << drum)));
}


void ym_write_data(byte addr, byte data)
{
	// Record the data for future writes
	ym_memmap[addr] = data;

	// Output to data bus
	YM_LDATA_DDR = 0xFF;
	digitalWrite(YM_CS, 0);

	// A0=0 to select register
	digitalWrite(YM_A0, 0);
	YM_LDATA_PORT = addr;

	// Write register value
	digitalWrite(YM_WR, 0);
	delayMicroseconds(1);
	digitalWrite(YM_WR, 1);
	delayMicroseconds(5);

	// A0=1 to write data
	digitalWrite(YM_A0, 1);
	YM_LDATA_PORT = data;

	// Write data value
	digitalWrite(YM_WR, 0);
	delayMicroseconds(1);
	digitalWrite(YM_WR, 1);
	delayMicroseconds(23);

	digitalWrite(YM_CS, 1);
	digitalWrite(YM_A0, 0);
}


