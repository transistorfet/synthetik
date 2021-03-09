
#include "NerveSerial.h"
#include "YM3812.h"
#include "YM3438.h"
#include "AY3.h"

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

	opl_write_data(addr, value);
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
		//opn_drum_on(note);
	}
	else {
		if (velocity)
			opn_note_on(channel - 1, note);
		else
			opn_note_off(channel - 1, note);
	}
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
	if (channel == 10) {
		//opn_drum_off(note);
	}
	else {
		opn_note_off(channel - 1, note);
	}
}

void handleProgramChange(byte channel, byte number)
{
	opn_change_instrument(channel - 1, number);
}

void handleControlChange(byte channel, byte number, byte value)
{
	opn_change_parameter(channel - 1, number, value);
}

void debug_midi(byte channel, byte data)
{
	MIDI.sendProgramChange(data, channel + 1);
}

void midi_init()
{
	MIDI.begin(MIDI_CHANNEL_OMNI);
	MIDI.setHandleNoteOn(handleNoteOn);
    	MIDI.setHandleNoteOff(handleNoteOff);
    	MIDI.setHandleProgramChange(handleProgramChange);
    	MIDI.setHandleControlChange(handleControlChange);
	Serial.begin(SERIAL_SPEED);
}

void setup()
{
	pinMode(13, OUTPUT);
	digitalWrite(13, 0);

	//opl_setup_audio();
	//opl_init_audio();

	opn_setup();
	opn_init_audio();

	//ay3_init_audio();
	//ay3_run_test();

	//nerve_init();
	midi_init();
}

void loop()
{
	//nSerial.check_read();

	MIDI.read();
}


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

