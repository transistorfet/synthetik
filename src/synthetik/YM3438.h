
#ifndef YM3438_H
#define YM3438_H

typedef byte opn_op_t[6];

typedef struct {
	opn_op_t op1;
	opn_op_t op2;
	opn_op_t op3;
	opn_op_t op4;
	byte algorithm;
	byte lfo;
} opn_instrument_t;


void opn_setup();
void opn_init_audio();
void opn_reset();
void opn_note_on(byte channel, byte note);
void opn_note_off(byte channel, byte note);
void opn_set_instrument(byte channel, opn_instrument_t *instr);
void opn_change_instrument(byte channel, byte number);
void opn_change_parameter(byte channel, byte number, byte value);

#endif

