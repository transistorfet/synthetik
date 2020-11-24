
#include "NerveSerial.h"
#include "YM3812.h"
#include "YM3438.h"

#include <MIDI.h>


#define SERIAL_SPEED	115200

/*
NerveSerial nSerial(&Serial);

void command_write()
{
	byte addr;
	byte value;

	addr = strtol(nSerial.get_arg(0), NULL, 0);
	value = strtol(nSerial.get_arg(1), NULL, 0);

	ym_write_data(addr, value);
}

void command_reset()
{
	Serial.print("error\n");
}

void command_default()
{
	Serial.print("error\n");
}

NerveCommand_t command_list[] = {
	{ "write", 2, command_write },
	{ "reset", 0, command_reset },
	{ 0, 0, command_default }
};

void nerve_init()
{
	Serial.begin(SERIAL_SPEED);
	nSerial.set_commands(command_list);
}
*/

MIDI_CREATE_DEFAULT_INSTANCE();
//MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);


void handleNoteOn(byte channel, byte note, byte velocity)
{
	if (channel == 10) {
		ym_drum_on(note);
	}
	else {
		if (velocity)
			ym_note_on(channel - 1, note);
		else
			ym_note_off(channel - 1, note);
	}
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
	if (channel == 10) {
		ym_drum_off(note);
	}
	else {
		ym_note_off(channel - 1, note);
	}
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


void handleControlChange(byte channel, byte number, byte value)
{
	byte addr;

	switch (number) {
	    case 1:
		ym_write_data(0xA3, value);
		ym_write_data(0xB3, 0x31);
		break;

	    case CN_COMPOSITE: 
		addr = 0x08;
		ym_write_data(addr, (ym_memmap[addr] & 0x7F) | (value ? 0x80 : 0x00));
		break;

	    case CN_AM_DEPTH: 
		addr = 0xBD;
		ym_write_data(addr, (ym_memmap[addr] & 0x7F) | (value ? 0x80 : 0x00));
		break;

	    case CN_VIB_DEPTH:
		addr = 0xBD;
		ym_write_data(addr, (ym_memmap[addr] & 0xBF) | (value ? 0x40 : 0x00));
		break;

	    case CN_FEEDBACK:
		addr = 0xC0;
		ym_write_data(addr, (ym_memmap[addr] & 0xF1) | ((value & 0x7) << 1));
		break;

	    case CN_DECAY_ALG:
		addr = 0xC0;
		ym_write_data(addr, (ym_memmap[addr] & 0xFE) | (value ? 0x01 : 0x00));
		break;


	    case CN_OP1_AM:
	    case CN_OP2_AM:
		addr = (number == CN_OP1_AM) ? 0x20 + channels[0].op1 : 0x20 + channels[0].op2;
		ym_write_data(addr, (ym_memmap[addr] & 0x7F) | (value ? 0x80 : 0x00));
		break;

	    case CN_OP1_VIB:
	    case CN_OP2_VIB:
		addr = (number == CN_OP1_VIB) ? 0x20 + channels[0].op1 : 0x20 + channels[0].op2;
		ym_write_data(addr, (ym_memmap[addr] & 0xBF) | (value ? 0x40 : 0x00));
		break;

	    case CN_OP1_MAINTAIN:
	    case CN_OP2_MAINTAIN:
		addr = (number == CN_OP1_VIB) ? 0x20 + channels[0].op1 : 0x20 + channels[0].op2;
		ym_write_data(addr, (ym_memmap[addr] & 0xDF) | (value ? 0x20 : 0x00));
		break;

	    case CN_OP1_MODFREQ:
	    case CN_OP2_MODFREQ:
		addr = (number == CN_OP1_MODFREQ) ? 0x20 + channels[0].op1 : 0x20 + channels[0].op2;
		ym_write_data(addr, (ym_memmap[addr] & 0xF0) | (value & 0x0F));
		break;

	    case CN_OP1_LEVEL:
	    case CN_OP2_LEVEL:
		addr = (number == CN_OP1_LEVEL) ? 0x40 + channels[0].op1 : 0x40 + channels[0].op2;
		ym_write_data(addr, (ym_memmap[addr] & 0xC0) | (value & 0x3F));
		break;

	    case CN_OP1_ATTACK:
	    case CN_OP2_ATTACK:
		addr = (number == CN_OP1_ATTACK) ? 0x60 + channels[0].op1 : 0x60 + channels[0].op2;
		ym_write_data(addr, (ym_memmap[addr] & 0x0F) | ((value & 0x0F) << 4));
		break;

	    case CN_OP1_DECAY:
	    case CN_OP2_DECAY:
		addr = (number == CN_OP1_DECAY) ? 0x60 + channels[0].op1 : 0x60 + channels[0].op2;
		ym_write_data(addr, (ym_memmap[addr] & 0xF0) | (value & 0x0F));
		break;

	    case CN_OP1_SUSTAIN:
	    case CN_OP2_SUSTAIN:
		addr = (number == CN_OP1_SUSTAIN) ? 0x80 + channels[0].op1 : 0x80 + channels[0].op2;
		ym_write_data(addr, (ym_memmap[addr] & 0x0F) | ((value & 0x0F) << 4));
		break;

	    case CN_OP1_RELEASE:
	    case CN_OP2_RELEASE:
		addr = (number == CN_OP1_RELEASE) ? 0x80 + channels[0].op1 : 0x80 + channels[0].op2;
		ym_write_data(addr, (ym_memmap[addr] & 0xF0) | (value & 0x0F));
		break;

	    case CN_OP1_WAVEFORM:
	    case CN_OP2_WAVEFORM:
		addr = (number == CN_OP1_WAVEFORM) ? 0xE0 + channels[0].op1 : 0xE0 + channels[0].op2;
		ym_write_data(addr, (ym_memmap[addr] & 0xFC) | (value & 0x03));
		break;

	    default:
		break;
	}
}

void handleProgramChange(byte channel, byte number)
{
	ym_change_instrument(channel - 1, number);
}

void midi_init()
{
	MIDI.begin(MIDI_CHANNEL_OMNI);
	MIDI.setHandleNoteOn(handleNoteOn);
    	MIDI.setHandleNoteOff(handleNoteOff);
    	MIDI.setHandleControlChange(handleControlChange);
    	MIDI.setHandleProgramChange(handleProgramChange);
	Serial.begin(SERIAL_SPEED);
}

void setup()
{
	pinMode(13, OUTPUT);
	digitalWrite(13, 0);

	setup_audio();
	initialize_audio();

	//nerve_init();
	midi_init();
}

void loop()
{
	//nSerial.check_read();

	MIDI.read();
}


/*
void run_test()
{
	ym_write_data(13, 0xFF);
	ym_write_data(14, 0xFF);
	ym_write_data(15, 0x00);

	set_tone(0, NOTE_E4);
	delay(200);
	set_tone(0, 0);
	delay(20);

	set_tone(0, NOTE_E4);
	delay(150);
	set_tone(0, 0);
	delay(20);

	set_tone(0, NOTE_E4);
	delay(150);
	set_tone(0, 0);
	delay(20);

	delay(100);

	set_tone(0, NOTE_C4);
	delay(100);
	set_tone(0, 0);
	delay(20);

	set_tone(0, NOTE_E4);
	delay(100);
	set_tone(0, 0);
	delay(20);

	delay(200);

	set_tone(0, NOTE_G4);
	delay(200);
	set_tone(0, 0);
	delay(20);

	delay(200);

	set_tone(0, NOTE_G3);
	delay(200);
	set_tone(0, 0);
	delay(20);
}
*/






/*
#define SERIAL_SIZE	64

char serial_read_tail = 0;
char serial_read_head = 0;
char serial_avail = 0;
char serial_rb[SERIAL_SIZE];
char serial_write_head = 0;
char serial_write_tail = 0;
char serial_wb[SERIAL_SIZE];

byte read_serial()
{
	register char b;

	b = Serial.read();
	if (b == -1)
		return 0;

	noInterrupts();
	serial_rb[serial_read_tail] = b;
	if (b == '\n' || b == '\r') {
		serial_rb[serial_read_tail] = '\0';
		serial_avail = 1;
	}
	if (serial_read_tail < SERIAL_SIZE)
		serial_read_tail++;
	interrupts();
	return serial_avail;
}

inline byte serial_get_byte()
{
	register byte value;

	noInterrupts();
	if (serial_read_head == serial_read_tail) {
		//clear_read_buffer();
		value = -1;
	} else {
		value = serial_rb[serial_read_head++];
		if (serial_read_head >= SERIAL_SIZE)
			serial_read_head = 0;
	}
	interrupts();
	return value;
}

inline byte serial_add_byte(byte data)
{
	noInterrupts();
	serial_wb[serial_write_tail++] = data;
	interrupts();
}

void clear_read_buffer()
{
	noInterrupts();
	serial_avail = 0;
	serial_read_head = 0;
	serial_read_tail = 0;
	interrupts();
}

void flush_write_buffer()
{
	if (serial_write_tail > 0) {
		noInterrupts();
		for (byte i = 0; i < serial_write_tail; i++) {
			Serial.write(serial_wb[i]);
		}
		serial_write_head = 0;
		serial_write_tail = 0;
		interrupts();
	}
}



void do_command(String line)
{
	if (line.equals("mute")) {
		opn_mute();
	}
	else if (line.equals("unmute")) {
		opn_unmute();
	}
	else if (line.equals("reset")) {
		opn_reset();
	}
	else {
		Serial.println("No such command");
	}
}

void setup()
{
	Serial.begin(SERIAL_SPEED);

	pinMode(13, OUTPUT);
	digitalWrite(13, 0);

	opn_setup();

	opn_init_audio();

	Serial.print("> ");
}

void loop()
{
	//String line = Serial.readString();
	//do_command(line);

	//flush_write_buffer();

	if (read_serial()) {
		String line = String(serial_rb);
		clear_read_buffer();
		Serial.print(line);
		Serial.print("\n");
		do_command(line);
		Serial.print("\n> ");
	}
}


*/

