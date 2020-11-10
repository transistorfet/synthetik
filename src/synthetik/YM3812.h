
#ifndef YM3812_H
#define YM3812_H

struct ym_channel {
	byte op1;
	byte op2;
};

struct instrument {
	byte a20;
	byte a40;
	byte a60;
	byte a80;
	byte aC0;
	byte aE0;
	byte b20;
	byte b40;
	byte b60;
	byte b80;
	byte bE0;
	byte gA0;
	byte gB0;
};


void setup_audio();
void initialize_audio();
void ym_change_instrument(byte channel, byte number);
void ym_note_on(byte channel, byte note);
void ym_note_off(byte channel, byte note);
void ym_drum_on(byte drum);
void ym_drum_off(byte drum);
void ym_write_data(byte addr, byte data);

extern byte ym_memmap[256];
extern struct ym_channel channels[9];

#endif

