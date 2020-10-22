
#include <Arduino.h>
#include "YM3812.h"

#define YM_LDATA_PORT	PORTA
#define YM_LDATA_PIN	PINA
#define YM_LDATA_DDR	DDRA

#define YM_CS		38
#define YM_RD		39
#define YM_WR		40
#define YM_A0		41
#define YM_RESET	50


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

void initialize_audio()
{
	digitalWrite(YM_RESET, 0);
	delay(10);
	digitalWrite(YM_RESET, 1);

	ym_write_data(0x01, 0x10);

	ym_write_data(0x20, 0x01);		// Set the modulator's multiple to 1
	ym_write_data(0x40, 0x10);		// Set the modulator's level to about 40 dB
	ym_write_data(0x60, 0xF2);		// Modulator attack:  quick;   decay:   long
	ym_write_data(0x80, 0x77);		// Modulator sustain: medium;  release: medium
	ym_write_data(0xA0, 0x98);		// Set voice frequency's LSB (it'll be a D#)
	ym_write_data(0x23, 0x01);		// Set the carrier's multiple to 1
	ym_write_data(0x43, 0x00);		// Set the carrier to maximum volume (about 47 dB)
	ym_write_data(0x63, 0xF2);		// Carrier attack:  quick;   decay:   long
	ym_write_data(0x83, 0x77);		// Carrier sustain: medium;  release: medium

	//ym_write_data(0xB0, 0x31);		// Turn the voice on; set the octave and freq MSB

	//delay(10000);
	//ym_write_data(0x20, 0x81);
	//ym_write_data(0xBD, 0xC0);
	//delay(2000);

	ym_write_data(0xB0, 0x31);		// Turn the voice on; set the octave and freq MSB
	delay(1000);
	ym_write_data(0xB0, 0x11);		// Turn the voice off; set the octave and freq MSB
}

void ym_write_data(byte addr, byte data)
{
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


