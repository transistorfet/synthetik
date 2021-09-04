
#include <Arduino.h>

/*
#define AY_LDATA_PORT	PORTA
#define AY_LDATA_PIN	PINA
#define AY_LDATA_DDR	DDRA

#define AY_BC1		40
#define AY_BDIR		39
#define AY_RESET	38
*/

#define YM_LDATA_PORT	PORTF
#define YM_LDATA_PIN	PINF
#define YM_LDATA_DDR	DDRF

#define YM_CS_AY3	7
#define YM_RDWR		12
#define YM_A0		10
#define YM_A1		11
#define YM_RESET	5


byte ay3_read_data(byte addr)
{
	byte value;

	YM_LDATA_DDR = 0xFF;
	YM_LDATA_PORT = addr;

	digitalWrite(YM_CS_AY3, 1);
	digitalWrite(YM_RDWR, 1);
	delayMicroseconds(15);
	digitalWrite(YM_CS_AY3, 0);
	digitalWrite(YM_RDWR, 0);

	YM_LDATA_DDR = 0x00;
	YM_LDATA_PORT = 0x00;

	digitalWrite(YM_CS_AY3, 1);
	digitalWrite(YM_RDWR, 0);
	delayMicroseconds(1);
	value = YM_LDATA_PIN;
	digitalWrite(YM_CS_AY3, 0);
	digitalWrite(YM_RDWR, 0);

	YM_LDATA_DDR = 0xFF;

	return value;
}

void ay3_write_data(byte addr, byte data)
{
	YM_LDATA_DDR = 0xFF;
	YM_LDATA_PORT = addr;

	digitalWrite(YM_CS_AY3, 1);
	digitalWrite(YM_RDWR, 1);
	delayMicroseconds(15);
	digitalWrite(YM_CS_AY3, 0);
	digitalWrite(YM_RDWR, 0);

	YM_LDATA_PORT = data;

	digitalWrite(YM_CS_AY3, 0);
	digitalWrite(YM_RDWR, 1);
	delayMicroseconds(15);
	digitalWrite(YM_CS_AY3, 0);
	digitalWrite(YM_RDWR, 0);
}

void ay3_set_tone(byte channel, word tone)
{
	ay3_write_data(0 + (channel * 2), tone & 0xff);
	ay3_write_data(1 + (channel * 2), (tone >> 8) & 0xff);
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

void ay3_init_audio()
{
	digitalWrite(YM_RESET, 0);
	delayMicroseconds(15);
	digitalWrite(YM_RESET, 1);

	ay3_write_data(7, 0x3E);
	ay3_write_data(8, 0x0F);
	ay3_write_data(9, 0x00);
	ay3_write_data(10, 0x00);
	ay3_set_tone(0, 0);

	//Serial.println(ay3_read_data(7), HEX);
	//Serial.println(ay3_read_data(10), HEX);
	//Serial.println(ay3_read_data(15), HEX);
}

void ay3_run_test()
{
	ay3_write_data(13, 0xFF);
	ay3_write_data(14, 0xFF);
	ay3_write_data(15, 0x00);

	ay3_set_tone(0, NOTE_E4);
	delay(200);
	ay3_set_tone(0, 0);
	delay(20);

	ay3_set_tone(0, NOTE_E4);
	delay(150);
	ay3_set_tone(0, 0);
	delay(20);

	ay3_set_tone(0, NOTE_E4);
	delay(150);
	ay3_set_tone(0, 0);
	delay(20);

	delay(100);

	ay3_set_tone(0, NOTE_C4);
	delay(100);
	ay3_set_tone(0, 0);
	delay(20);

	ay3_set_tone(0, NOTE_E4);
	delay(100);
	ay3_set_tone(0, 0);
	delay(20);

	delay(200);

	ay3_set_tone(0, NOTE_G4);
	delay(200);
	ay3_set_tone(0, 0);
	delay(20);

	delay(200);

	ay3_set_tone(0, NOTE_G3);
	delay(200);
	ay3_set_tone(0, 0);
	delay(20);
}

byte noise = 0;

void run_noise()
{
	//byte noise = read_data(6);
	//Serial.println(noise, HEX);
	if (noise) {
		noise = 0;
		ay3_write_data(6, 0x00);
		ay3_write_data(7, 0x3E);
	} else {
		noise = 1;
		ay3_write_data(6, 0x0F);
		ay3_write_data(7, 0x00);
	}
}

void run_mute()
{
	ay3_write_data(7, 0x3F);
}

void run_unmute()
{
	ay3_write_data(7, 0x3E);
}

