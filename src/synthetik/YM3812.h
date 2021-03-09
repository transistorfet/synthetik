
#ifndef YM3812_H
#define YM3812_H

struct opl_channel {
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


void opl_setup_audio();
void opl_init_audio();
void opl_reset();
void opl_change_instrument(byte channel, byte number);
void opl_note_on(byte channel, byte note);
void opl_note_off(byte channel, byte note);
void opl_drum_on(byte drum);
void opl_drum_off(byte drum);
void opl_write_data(byte addr, byte data);
void opl_change_parameter(byte channel, byte number, byte value);

extern byte opl_memmap[256];
extern struct opl_channel channels[9];

#endif

