
#include <Arduino.h>
#include "YM3812.h"
#include "YM3812_instruments.h"


/*
#define YM_LDATA_PORT	PORTA
#define YM_LDATA_PIN	PINA
#define YM_LDATA_DDR	DDRA

#define YM_CS_OPL	38
#define YM_RDWR		40
#define YM_A0		41
#define YM_RESET	50
#define YM_A1		51
*/

#define YM_LDATA_PORT	PORTF
#define YM_LDATA_PIN	PINF
#define YM_LDATA_DDR	DDRF

#define YM_RESET	5
#define YM_CS_OPL	8
#define YM_RDWR		12
#define YM_A0		10
#define YM_A1		11




#define YM_HIHAT	0
#define YM_CYMBAL	1
#define YM_TOMTOM	2
#define YM_SNAREDRUM	3
#define YM_BASSDRUM	4


byte opl_memmap[256];

// Based on a 3.57954 MHz crystal
word note_fnums[] = {
	// C2 C#2 D2 D#2 E2 F2 F#2 G2 G#2 A2 A#2 B2
	86, 91, 97, 103, 109, 115, 122, 129, 137, 145, 154, 163,
	// C3 C#3 D3 D#3 E3 F3 F#3 G3 G#3 A3 A#3 B3
	172, 183, 194, 205, 217, 230, 244, 258, 274, 290, 307, 326,
	// C4 C#4 D4 D#4 E4 F4 F#4 G4 G#4 A4 A#4 B4
	345, 365, 387, 410, 435, 460, 488, 517, 547, 580, 614, 651,
};

struct opl_channel channels[9] = {
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

void opl_setup_audio()
{
	pinMode(YM_CS_OPL, OUTPUT);
	pinMode(YM_RDWR, OUTPUT);
	pinMode(YM_A0, OUTPUT);
	pinMode(YM_A1, OUTPUT);
	pinMode(YM_RESET, OUTPUT);
	digitalWrite(YM_CS_OPL, 1);
	digitalWrite(YM_RDWR, 1);
	digitalWrite(YM_A0, 0);
	digitalWrite(YM_A1, 0);
	digitalWrite(YM_RESET, 1);

	// Data Bus
	YM_LDATA_PORT = 0x00;	// D0 - D7
	YM_LDATA_DDR = 0x00;
}

void opl_set_instrument(byte channel, struct instrument *config)
{
	struct opl_channel ch = channels[channel];

	opl_write_data(0x20 + ch.op1, config->a20);
	opl_write_data(0x40 + ch.op1, config->a40);
	opl_write_data(0x60 + ch.op1, config->a60);
	opl_write_data(0x80 + ch.op1, config->a80);
	opl_write_data(0xC0 + ch.op1, config->aC0);
	opl_write_data(0xE0 + ch.op1, config->aE0);
	opl_write_data(0x20 + ch.op2, config->b20);
	opl_write_data(0x40 + ch.op2, config->b40);
	opl_write_data(0x60 + ch.op2, config->b60);
	opl_write_data(0x80 + ch.op2, config->b80);
	opl_write_data(0xE0 + ch.op2, config->bE0);

	opl_write_data(0xA0 + channel, config->gA0);
	opl_write_data(0xB0 + channel, config->gB0);

}

void opl_init_audio()
{
	opl_reset();

	opl_write_data(0x01, 0x10);

	opl_write_data(0xBD, 0x20);

	opl_set_instrument(0, &presets[0]);
	opl_set_instrument(1, &presets[0]);
	opl_set_instrument(2, &presets[0]);
	opl_set_instrument(3, &presets[0]);
	opl_set_instrument(4, &presets[0]);
	opl_set_instrument(5, &presets[0]);
	opl_set_instrument(6, &presets[5]);	// Bass Drum
	opl_set_instrument(7, &presets[6]);	// HiHat and Snare Drum
	opl_set_instrument(8, &presets[7]);	// Cymbal?


	opl_write_data(0xB0, 0x31);		// Turn the voice on; set the octave and freq MSB
	delay(2000);
	opl_write_data(0xB0, 0x11);		// Turn the voice off; set the octave and freq MSB
}

void opl_reset()
{
	digitalWrite(YM_RESET, 0);
	delay(10);
	digitalWrite(YM_RESET, 1);
	delay(10);
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

void opl_change_instrument(byte channel, byte number)
{
	if (number > 120)
		return;

	channel = channel % 6;
	//struct instrument *config = instrument_select(number);
	struct instrument *config = &list[number];
	if (config)
		opl_set_instrument(channel, config);
}


void opl_note_on(byte channel, byte note)
{
	channel = channel % 6;
	byte block = (note / 12);
	byte offset = note % 12;

	opl_write_data(0xA0 + channel, note_fnums[offset + 12]);
	opl_write_data(0xB0 + channel, 0x20 | (block << 2) | (note_fnums[offset + 12] >> 8));
}

void opl_note_off(byte channel, byte note)
{
	channel = channel % 6;
	opl_write_data(0xB0 + channel, 0x00);
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



void opl_drum_on(byte drum)
{
	drum = percussion_select(drum);
	opl_write_data(0xBD, (opl_memmap[0xBD] & 0xE0) | (0x01 << drum));
}

void opl_drum_off(byte drum)
{
	drum = percussion_select(drum);
	opl_write_data(0xBD, opl_memmap[0xBD] & (0xE0 | ~(0x01 << drum)));
}


void opl_write_data(byte addr, byte data)
{
	// Record the data for future writes
	opl_memmap[addr] = data;

	// Output to data bus
	YM_LDATA_DDR = 0xFF;
	digitalWrite(YM_CS_OPL, 0);

	// A0=0 to select register
	digitalWrite(YM_A0, 0);
	YM_LDATA_PORT = addr;

	// Write register value
	digitalWrite(YM_RDWR, 0);
	delayMicroseconds(1);
	digitalWrite(YM_RDWR, 1);
	delayMicroseconds(5);

	// A0=1 to write data
	digitalWrite(YM_A0, 1);
	YM_LDATA_PORT = data;

	// Write data value
	digitalWrite(YM_RDWR, 0);
	delayMicroseconds(1);
	digitalWrite(YM_RDWR, 1);
	delayMicroseconds(23);

	digitalWrite(YM_CS_OPL, 1);
	digitalWrite(YM_A0, 0);
}

#define CN_COMPOSITE		10
#define CN_AM_DEPTH		11
#define CN_VIB_DEPTH		12
#define CN_FEEDBACK		13
#define CN_DECAY_ALG		14

#define CN_OP1_AM		20
#define CN_OP2_AM		21
#define CN_OP1_VIB		22
#define CN_OP2_VIB		23
#define CN_OP1_MAINTAIN		24
#define CN_OP2_MAINTAIN		25
#define CN_OP1_MODFREQ		26
#define CN_OP2_MODFREQ		27
#define CN_OP1_LEVEL		28
#define CN_OP2_LEVEL		29
#define CN_OP1_ATTACK		30
#define CN_OP2_ATTACK		31
#define CN_OP1_DECAY		32
#define CN_OP2_DECAY		33
#define CN_OP1_SUSTAIN		34
#define CN_OP2_SUSTAIN		35
#define CN_OP1_RELEASE		36
#define CN_OP2_RELEASE		37
#define CN_OP1_WAVEFORM		38
#define CN_OP2_WAVEFORM		39


void opl_change_parameter(byte channel, byte number, byte value)
{
	byte addr;

	switch (number) {
	    case 1:
		opl_write_data(0xA3, value);
		opl_write_data(0xB3, 0x31);
		break;

	    case CN_COMPOSITE: 
		addr = 0x08;
		opl_write_data(addr, (opl_memmap[addr] & 0x7F) | (value ? 0x80 : 0x00));
		break;

	    case CN_AM_DEPTH: 
		addr = 0xBD;
		opl_write_data(addr, (opl_memmap[addr] & 0x7F) | (value ? 0x80 : 0x00));
		break;

	    case CN_VIB_DEPTH:
		addr = 0xBD;
		opl_write_data(addr, (opl_memmap[addr] & 0xBF) | (value ? 0x40 : 0x00));
		break;

	    case CN_FEEDBACK:
		addr = 0xC0;
		opl_write_data(addr, (opl_memmap[addr] & 0xF1) | ((value & 0x7) << 1));
		break;

	    case CN_DECAY_ALG:
		addr = 0xC0;
		opl_write_data(addr, (opl_memmap[addr] & 0xFE) | (value ? 0x01 : 0x00));
		break;


	    case CN_OP1_AM:
	    case CN_OP2_AM:
		addr = (number == CN_OP1_AM) ? 0x20 + channels[0].op1 : 0x20 + channels[0].op2;
		opl_write_data(addr, (opl_memmap[addr] & 0x7F) | (value ? 0x80 : 0x00));
		break;

	    case CN_OP1_VIB:
	    case CN_OP2_VIB:
		addr = (number == CN_OP1_VIB) ? 0x20 + channels[0].op1 : 0x20 + channels[0].op2;
		opl_write_data(addr, (opl_memmap[addr] & 0xBF) | (value ? 0x40 : 0x00));
		break;

	    case CN_OP1_MAINTAIN:
	    case CN_OP2_MAINTAIN:
		addr = (number == CN_OP1_VIB) ? 0x20 + channels[0].op1 : 0x20 + channels[0].op2;
		opl_write_data(addr, (opl_memmap[addr] & 0xDF) | (value ? 0x20 : 0x00));
		break;

	    case CN_OP1_MODFREQ:
	    case CN_OP2_MODFREQ:
		addr = (number == CN_OP1_MODFREQ) ? 0x20 + channels[0].op1 : 0x20 + channels[0].op2;
		opl_write_data(addr, (opl_memmap[addr] & 0xF0) | (value & 0x0F));
		break;

	    case CN_OP1_LEVEL:
	    case CN_OP2_LEVEL:
		addr = (number == CN_OP1_LEVEL) ? 0x40 + channels[0].op1 : 0x40 + channels[0].op2;
		opl_write_data(addr, (opl_memmap[addr] & 0xC0) | (value & 0x3F));
		break;

	    case CN_OP1_ATTACK:
	    case CN_OP2_ATTACK:
		addr = (number == CN_OP1_ATTACK) ? 0x60 + channels[0].op1 : 0x60 + channels[0].op2;
		opl_write_data(addr, (opl_memmap[addr] & 0x0F) | ((value & 0x0F) << 4));
		break;

	    case CN_OP1_DECAY:
	    case CN_OP2_DECAY:
		addr = (number == CN_OP1_DECAY) ? 0x60 + channels[0].op1 : 0x60 + channels[0].op2;
		opl_write_data(addr, (opl_memmap[addr] & 0xF0) | (value & 0x0F));
		break;

	    case CN_OP1_SUSTAIN:
	    case CN_OP2_SUSTAIN:
		addr = (number == CN_OP1_SUSTAIN) ? 0x80 + channels[0].op1 : 0x80 + channels[0].op2;
		opl_write_data(addr, (opl_memmap[addr] & 0x0F) | ((value & 0x0F) << 4));
		break;

	    case CN_OP1_RELEASE:
	    case CN_OP2_RELEASE:
		addr = (number == CN_OP1_RELEASE) ? 0x80 + channels[0].op1 : 0x80 + channels[0].op2;
		opl_write_data(addr, (opl_memmap[addr] & 0xF0) | (value & 0x0F));
		break;

	    case CN_OP1_WAVEFORM:
	    case CN_OP2_WAVEFORM:
		addr = (number == CN_OP1_WAVEFORM) ? 0xE0 + channels[0].op1 : 0xE0 + channels[0].op2;
		opl_write_data(addr, (opl_memmap[addr] & 0xFC) | (value & 0x03));
		break;

	    default:
		break;
	}
}

