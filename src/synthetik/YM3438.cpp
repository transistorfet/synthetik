
#include <Arduino.h>

#include "YM3438.h"

#define YM_LDATA_PORT	PORTF
#define YM_LDATA_PIN	PINF
#define YM_LDATA_DDR	DDRF

#define YM_CS_OPN	7
#define YM_RDWR		12
#define YM_A0		10
#define YM_A1		11
#define YM_RESET	5


// Based on a 3.57954 MHz crystal
word opn_fnums[] = {
	617, 653, 692, 733, 777, 823, 872, 924, 979, 1037, 1099, 1164,
};


#define INSTRUMENTS_MAX		3
opn_instrument_t instruments[] = {
	{
		{ 0x71, 0x23, 0x5F, 0x05, 0x02, 0x11 },	// Op 1
		{ 0x0D, 0x2D, 0x99, 0x05, 0x02, 0x11 },	// Op 2
		{ 0x33, 0x26, 0x5F, 0x05, 0x02, 0x11 },	// Op 3
		{ 0x01, 0x00, 0x94, 0x07, 0x02, 0xA6 },	// Op 4
		0x32,					// Algorithm
		0xC0,					// L/R, LFO Controls
	},
	{
		{ 0x71, 0x23, 0x5F, 0x05, 0x02, 0x11 },	// Op 1
		{ 0x0D, 0x2D, 0x99, 0x05, 0x02, 0x11 },	// Op 2
		{ 0x33, 0x26, 0x5F, 0x05, 0x02, 0x11 },	// Op 3
		{ 0x01, 0x00, 0x94, 0x07, 0x02, 0xA6 },	// Op 4
		0x25,					// Algorithm
		0xC0,					// L/R, LFO Controls
	},
	{
		{ 0x11, 0x23, 0x5F, 0x05, 0x02, 0x11 },	// Op 1
		{ 0x0D, 0x2D, 0x50, 0x05, 0x02, 0xA1 },	// Op 2
		{ 0x33, 0x26, 0x5F, 0x05, 0x02, 0x11 },	// Op 3
		{ 0x41, 0x00, 0x94, 0x07, 0x02, 0xA6 },	// Op 4
		0x20,					// Algorithm
		0xC0,					// L/R, LFO Controls
	},
};

byte opn_memmap[512];

extern void debug_midi(byte channel, byte data);

void opn_write_data(byte bank, byte addr, byte data)
{
	// Record the data for future writes
	opn_memmap[((word) bank << 8) + addr] = data;

	// Output to data bus
	YM_LDATA_DDR = 0xFF;

	// A0=0 to select register
	digitalWrite(YM_A0, 0);
	YM_LDATA_PORT = addr;

	// A1=0 to select bank 0, A1=1 to select bank 1
	digitalWrite(YM_A1, bank);

	// Write register value
	digitalWrite(YM_CS_OPN, 0);
	delayMicroseconds(1);
	digitalWrite(YM_RDWR, 0);
	delayMicroseconds(5);
	digitalWrite(YM_RDWR, 1);
	delayMicroseconds(5);
	digitalWrite(YM_CS_OPN, 1);

	// A0=1 to write data
	digitalWrite(YM_A0, 1);
	YM_LDATA_PORT = data;

	// Write data value
	digitalWrite(YM_CS_OPN, 0);
	delayMicroseconds(1);
	digitalWrite(YM_RDWR, 0);
	delayMicroseconds(5);
	digitalWrite(YM_RDWR, 1);
	delayMicroseconds(5);
	digitalWrite(YM_CS_OPN, 1);

	digitalWrite(YM_A0, 0);
	digitalWrite(YM_A1, 0);
}

void opn_modify_data(byte bank, byte addr, byte mask, byte data)
{
	opn_write_data(bank, addr, (opn_memmap[((word) bank << 8) + addr] & ~mask) | (data & mask));
}

void opn_setup()
{
	// Controls
	pinMode(YM_CS_OPN, OUTPUT);
	pinMode(YM_RDWR, OUTPUT);
	pinMode(YM_A0, OUTPUT);
	pinMode(YM_A1, OUTPUT);
	pinMode(YM_RESET, OUTPUT);
	digitalWrite(YM_CS_OPN, 1);
	digitalWrite(YM_RDWR, 1);
	digitalWrite(YM_A0, 0);
	digitalWrite(YM_A1, 0);
	digitalWrite(YM_RESET, 1);

	// Data Bus
	YM_LDATA_PORT = 0x00;	// D0 - D7
	YM_LDATA_DDR = 0x00;
}

void opn_init_audio()
{
	opn_reset();

	// LFO off
	opn_write_data(0, 0x22, 0);
	// Channel 3 Normal Mode
	opn_write_data(0, 0x27, 0);

	// Turn off all channels
	opn_write_data(0, 0x28, 0);
	opn_write_data(0, 0x28, 1);
	opn_write_data(0, 0x28, 2);
	opn_write_data(0, 0x28, 3);
	opn_write_data(0, 0x28, 4);
	opn_write_data(0, 0x28, 5);
	opn_write_data(0, 0x28, 6);

	// DAC off
	opn_write_data(0, 0x2B, 0);

/*
	opn_write_data(0, 0x30, 0x71);
	opn_write_data(0, 0x34, 0x0D);
	opn_write_data(0, 0x38, 0x33);
	opn_write_data(0, 0x3C, 0x01);
	opn_write_data(0, 0x40, 0x23);
	opn_write_data(0, 0x44, 0x2D);
	opn_write_data(0, 0x48, 0x26);
	opn_write_data(0, 0x4C, 0x00);
	opn_write_data(0, 0x50, 0x5F);
	opn_write_data(0, 0x54, 0x99);
	opn_write_data(0, 0x58, 0x5F);
	opn_write_data(0, 0x5C, 0x94);
	opn_write_data(0, 0x60, 5);
	opn_write_data(0, 0x64, 5);
	opn_write_data(0, 0x68, 5);
	opn_write_data(0, 0x6C, 7);
	opn_write_data(0, 0x70, 2);
	opn_write_data(0, 0x74, 2);
	opn_write_data(0, 0x78, 2);
	opn_write_data(0, 0x7C, 2);
	opn_write_data(0, 0x80, 0x11);
	opn_write_data(0, 0x84, 0x11);
	opn_write_data(0, 0x88, 0x11);
	opn_write_data(0, 0x8C, 0xA6);
	opn_write_data(0, 0x90, 0);
	opn_write_data(0, 0x94, 0);
	opn_write_data(0, 0x98, 0);
	opn_write_data(0, 0x9C, 0);
	opn_write_data(0, 0xB0, 0x32);
	opn_write_data(0, 0xB4, 0xC0);
	opn_write_data(0, 0x28, 0x00);

	// Play Test Sound
	//opn_write_data(0, 0xA4, 0x22);
	//opn_write_data(0, 0xA0, 0x69);
	//opn_write_data(0, 0x28, 0xF0);
*/

	opn_set_instrument(0, &instruments[0]);

	for (byte i = 0; i < 1; i++) {
		opn_note_on(0, 72);
		delay(1000);
		opn_note_off(0, 72);
	}

}

void opn_reset()
{
	digitalWrite(YM_RESET, 0);
	delay(10);
	digitalWrite(YM_RESET, 1);
	delay(10);
}

void opn_note_on(byte channel, byte note)
{
	channel %= 6;
	byte bank = channel / 3;
	byte reg = channel % 3;

	byte block = (note / 12);
	byte offset = note % 12;

	opn_write_data(bank, 0xA4 + reg, (block << 3) | (opn_fnums[offset] >> 8));
	opn_write_data(bank, 0xA0 + reg, opn_fnums[offset]);
	opn_write_data(0, 0x28, 0xF0 | channel);
}

void opn_note_off(byte channel, byte note)
{
	channel %= 6;
	byte bank = channel / 3;
	byte reg = channel % 3;

	opn_write_data(0, 0x28, channel);
}

void opn_change_instrument(byte channel, byte number)
{
	if (number > 120)
		return;

	channel = channel % 6;
	opn_instrument_t *config = &instruments[number % INSTRUMENTS_MAX];
	if (config)
		opn_set_instrument(channel, config);
}

void opn_set_instrument(byte channel, opn_instrument_t *instr)
{
	channel %= 6;
	byte bank = channel / 3;
	byte reg = channel % 3;

	opn_write_data(bank, 0x30 + reg, instr->op1[0]);
	opn_write_data(bank, 0x34 + reg, instr->op2[0]);
	opn_write_data(bank, 0x38 + reg, instr->op3[0]);
	opn_write_data(bank, 0x3C + reg, instr->op4[0]);
	opn_write_data(bank, 0x40 + reg, instr->op1[1]);
	opn_write_data(bank, 0x44 + reg, instr->op2[1]);
	opn_write_data(bank, 0x48 + reg, instr->op3[1]);
	opn_write_data(bank, 0x4C + reg, instr->op4[1]);
	opn_write_data(bank, 0x50 + reg, instr->op1[2]);
	opn_write_data(bank, 0x54 + reg, instr->op2[2]);
	opn_write_data(bank, 0x58 + reg, instr->op3[2]);
	opn_write_data(bank, 0x5C + reg, instr->op4[2]);
	opn_write_data(bank, 0x60 + reg, instr->op1[3]);
	opn_write_data(bank, 0x64 + reg, instr->op2[3]);
	opn_write_data(bank, 0x68 + reg, instr->op3[3]);
	opn_write_data(bank, 0x6C + reg, instr->op4[3]);
	opn_write_data(bank, 0x70 + reg, instr->op1[4]);
	opn_write_data(bank, 0x74 + reg, instr->op2[4]);
	opn_write_data(bank, 0x78 + reg, instr->op3[4]);
	opn_write_data(bank, 0x7C + reg, instr->op4[4]);
	opn_write_data(bank, 0x80 + reg, instr->op1[5]);
	opn_write_data(bank, 0x84 + reg, instr->op2[5]);
	opn_write_data(bank, 0x88 + reg, instr->op3[5]);
	opn_write_data(bank, 0x8C + reg, instr->op4[5]);
	opn_write_data(bank, 0x90 + reg, 0);
	opn_write_data(bank, 0x94 + reg, 0);
	opn_write_data(bank, 0x98 + reg, 0);
	opn_write_data(bank, 0x9C + reg, 0);

	// Feedback Algorithm
	opn_write_data(bank, 0xB0 + reg, instr->algorithm);
	// Stereo Mode
	opn_write_data(bank, 0xB4 + reg, instr->lfo);
}


#define OPN_CN_DETUNE		0x10
#define OPN_CN_MULTIPLE		0x14
#define OPN_CN_TOTAL_LEVEL	0x18
#define OPN_CN_RATE_SCALE	0x1B
#define OPN_CN_ATTACK_RATE	0x20
#define OPN_CN_MODULATION	0x24
#define OPN_CN_FIRST_DECAY	0x28
#define OPN_CN_SECOND_DECAY	0x2B
#define OPN_CN_SECOND_LEVEL	0x30
#define OPN_CN_RELEASE		0x34

#define OPN_CN_FEEDBACK		0x60
#define OPN_CN_ALGORITHM	0x61
#define OPN_CN_AMP_MOD		0x62
#define OPN_CN_FREQ_MOD		0x63


void opn_change_parameter(byte channel, byte number, byte value)
{
	byte addr;

	channel %= 6;
	byte bank = channel / 3;
	byte reg = channel % 3;
	byte op = number & 0x03;

	debug_midi(0, number & 0xFC);

	switch (number & 0xFC) {
	    case OPN_CN_DETUNE:
		opn_modify_data(bank, 0x30 + (op << 2) + reg, 0x70, (value & 0x07) << 4);
		return;
	    case OPN_CN_MULTIPLE:
		opn_modify_data(bank, 0x30 + (op << 2) + reg, 0x0F, (value & 0x0F));
		return;
	    case OPN_CN_TOTAL_LEVEL:
		opn_write_data(bank, 0x40 + (op << 2) + reg, value);
		return;
	    case OPN_CN_RATE_SCALE:
		opn_modify_data(bank, 0x50 + (op << 2) + reg, 0xC0, value << 6);
		return;
	    case OPN_CN_ATTACK_RATE:
		opn_modify_data(bank, 0x50 + (op << 2) + reg, 0x1F, value);
		return;
	    case OPN_CN_MODULATION:
		opn_modify_data(bank, 0x60 + (op << 2) + reg, 0x80, value << 7);
		return;
	    case OPN_CN_FIRST_DECAY:
		opn_modify_data(bank, 0x60 + (op << 2) + reg, 0x1F, value);
		return;
	    case OPN_CN_SECOND_DECAY:
		opn_modify_data(bank, 0x70 + (op << 2) + reg, 0x1F, value);
		return;
	    case OPN_CN_SECOND_LEVEL:
		opn_modify_data(bank, 0x80 + (op << 2) + reg, 0xF0, value << 4);
		return;
	    case OPN_CN_RELEASE:
		opn_modify_data(bank, 0x80 + (op << 2) + reg, 0x0F, value);
		return;
	    default:
		break;
	}

	switch (number) {
	    case OPN_CN_FEEDBACK:
		opn_modify_data(bank, 0xB0 + reg, 0x38, value << 3);
		return;
	    case OPN_CN_ALGORITHM:
		opn_modify_data(bank, 0xB0 + reg, 0x07, value);
		return;
	    case OPN_CN_AMP_MOD:
		opn_modify_data(bank, 0xB4 + reg, 0x38, value << 3);
		return;
	    case OPN_CN_FREQ_MOD:
		opn_modify_data(bank, 0xB4 + reg, 0x03, value);
		return;
	    default:
		break;
	}
}

