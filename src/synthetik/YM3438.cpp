
#include <Arduino.h>

#include "YM3438.h"


#define YM_LDATA_PORT	PORTA
#define YM_LDATA_PIN	PINA
#define YM_LDATA_DDR	DDRA

#define YM_CS		38
#define YM_WR		39
#define YM_RD		40
#define YM_A0		41
#define YM_A1		51
#define YM_RESET	50


void opn_write_data(byte addr, byte data)
{
	// Output to data bus
	YM_LDATA_DDR = 0xFF;

	// A0=0 to select register
	digitalWrite(YM_A0, 0);
	YM_LDATA_PORT = addr;

	// Write register value
	digitalWrite(YM_CS, 0);
	delayMicroseconds(1);
	digitalWrite(YM_WR, 0);
	delayMicroseconds(5);
	digitalWrite(YM_WR, 1);
	delayMicroseconds(5);
	digitalWrite(YM_CS, 1);

	// A0=1 to write data
	digitalWrite(YM_A0, 1);
	YM_LDATA_PORT = data;

	// Write data value
	digitalWrite(YM_CS, 0);
	delayMicroseconds(1);
	digitalWrite(YM_WR, 0);
	delayMicroseconds(5);
	digitalWrite(YM_WR, 1);
	delayMicroseconds(5);
	digitalWrite(YM_CS, 1);

	digitalWrite(YM_A0, 0);
}

void set_tone(byte channel, word tone)
{
	opn_write_data(0 + (channel * 2), tone & 0xff);
	opn_write_data(1 + (channel * 2), (tone >> 8) & 0xff);
}

#define CLOCK	3686400

#define NOTE_C3		(CLOCK / (16 * 130.81))
#define NOTE_D3		(CLOCK / (16 * 146.83))
#define NOTE_E3		(CLOCK / (16 * 164.81))
#define NOTE_F3		(CLOCK / (16 * 174.61))
#define NOTE_G3		(CLOCK / (16 * 196.00))
#define NOTE_A3		(CLOCK / (16 * 220.00))
#define NOTE_B3		(CLOCK / (16 * 246.94))
#define NOTE_C4		(CLOCK / (16 * 261.63))
#define NOTE_D4		(CLOCK / (16 * 293.66))
#define NOTE_E4		(CLOCK / (16 * 329.63))
#define NOTE_F4		(CLOCK / (16 * 349.23))
#define NOTE_G4		(CLOCK / (16 * 392.00))

void opn_setup()
{
	// Controls
	pinMode(YM_CS, OUTPUT);
	pinMode(YM_RD, OUTPUT);
	pinMode(YM_WR, OUTPUT);
	pinMode(YM_A0, OUTPUT);
	pinMode(YM_A1, OUTPUT);
	pinMode(YM_RESET, OUTPUT);
	digitalWrite(YM_CS, 1);
	digitalWrite(YM_RD, 1);
	digitalWrite(YM_WR, 1);
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

	opn_write_data(0x22, 0);
	opn_write_data(0x27, 0);
	opn_write_data(0x28, 0);
	opn_write_data(0x28, 1);
	opn_write_data(0x28, 2);
	opn_write_data(0x28, 3);
	opn_write_data(0x28, 4);
	opn_write_data(0x28, 5);
	opn_write_data(0x28, 6);
	opn_write_data(0x2B, 0);
	opn_write_data(0x30, 0x71);
	opn_write_data(0x34, 0x0D);
	opn_write_data(0x38, 0x33);
	opn_write_data(0x3C, 0x01);
	opn_write_data(0x40, 0x23);
	opn_write_data(0x44, 0x2D);
	opn_write_data(0x48, 0x26);
	opn_write_data(0x4C, 0x00);
	opn_write_data(0x50, 0x5F);
	opn_write_data(0x54, 0x99);
	opn_write_data(0x58, 0x5F);
	opn_write_data(0x5C, 0x94);
	opn_write_data(0x60, 5);
	opn_write_data(0x64, 5);
	opn_write_data(0x68, 5);
	opn_write_data(0x6C, 7);
	opn_write_data(0x70, 2);
	opn_write_data(0x74, 2);
	opn_write_data(0x78, 2);
	opn_write_data(0x7C, 2);
	opn_write_data(0x80, 0x11);
	opn_write_data(0x84, 0x11);
	opn_write_data(0x88, 0x11);
	opn_write_data(0x8C, 0xA6);
	opn_write_data(0x90, 0);
	opn_write_data(0x94, 0);
	opn_write_data(0x98, 0);
	opn_write_data(0x9C, 0);
	opn_write_data(0xB0, 0x32);
	opn_write_data(0xB4, 0xC0);
	opn_write_data(0x28, 0x00);

	opn_write_data(0xA4, 0x22);
	opn_write_data(0xA0, 0x69);
	opn_write_data(0x28, 0xF0);
/*
	digitalWrite(YM_RESET, 0);
	delayMicroseconds(15);
	digitalWrite(YM_RESET, 1);

	opn_write_data(7, 0x3E);
	opn_write_data(8, 0x0F);
	opn_write_data(9, 0x00);
	opn_write_data(10, 0x00);
	set_tone(0, 0);

	Serial.println(read_data(7), HEX);
	Serial.println(read_data(10), HEX);
	Serial.println(read_data(15), HEX);
*/
}

void opn_reset()
{
	digitalWrite(YM_RESET, 0);
	delay(10);
	digitalWrite(YM_RESET, 1);
	delay(10);
}


void opn_mute()
{
	opn_write_data(7, 0x3F);
}

void opn_unmute()
{
	opn_write_data(7, 0x3E);
}











