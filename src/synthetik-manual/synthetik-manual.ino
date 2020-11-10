
#include "NerveSerial.h"
#include "YM3812.h"

#include <MIDI.h>


/******************************
 * Serial Communications Code *
 ******************************/

#define SERIAL_SPEED	115200

NerveSerial nSerial(&Serial);
//MIDI_CREATE_DEFAULT_INSTANCE();


/**********************
 * Audio Control Code *
 **********************/

void set_tone(byte channel, word tone)
{
	ym_write_data(0 + (channel * 2), tone & 0xff);
	ym_write_data(1 + (channel * 2), (tone >> 8) & 0xff);
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

void run_reset()
{
	initialize_audio();
}

void play_note(byte note, word length)
{
	ym_write_data(0xA0, note);
	ym_write_data(0xB0, 0x31);		// Turn the voice on; set the octave and freq MSB
	delay(length);
	ym_write_data(0xB0, 0x11);		// Turn the voice off; set the octave and freq MSB
	delay(100);
}

void run_test()
{

	play_note(0x98, 800);
	play_note(0xA0, 800);
	play_note(0xB0, 800);
	play_note(0x85, 800);
	play_note(0x98, 800);

/*
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
*/
}

void command_write()
{
	byte addr;
	byte value;

	addr = strtol(nSerial.get_arg(0), NULL, 0);
	value = strtol(nSerial.get_arg(1), NULL, 0);

	ym_write_data(addr, value);
}

void command_default()
{
	Serial.print("error\n");
}

NerveCommand_t command_list[] = {
	{ "write", 2, command_write },
	{ 0, 0, command_default }
};

/*
void do_command(String line)
{
	if (line.equals("test")) {
		run_test();
	}
	else if (line.startsWith("write ")) {
		run_write(line);
	}
	else if (line.equals("reset")) {
		run_reset();
	}
	else {
		Serial.println("No such command");
	}
}
*/

void handleNoteOn(byte inChannel, byte inNote, byte inVelocity)
{
	word upper = (inNote >> 5);
	ym_write_data(0xA0, inNote << 3);
	ym_write_data(0xB0, 0x30 | upper);
}

void handleNoteOff(byte inChannel, byte inNote, byte inVelocity)
{
	ym_write_data(0xB0, 0x10);
}

void setup()
{
	setup_audio();
	initialize_audio();

	/*
	MIDI.begin(MIDI_CHANNEL_OMNI);
	MIDI.setHandleNoteOn(handleNoteOn);
    	MIDI.setHandleNoteOff(handleNoteOff);
	Serial.begin(SERIAL_SPEED);
	*/

	Serial.begin(SERIAL_SPEED);
	nSerial.set_commands(command_list);

	pinMode(13, OUTPUT);
	digitalWrite(13, 0);


	//Serial.print("> ");
}

void loop()
{
	//String line = Serial.readString();
	//do_command(line);

	//flush_write_buffer();

	/*
	if (read_serial()) {
		String line = String(serial_rb);
		clear_read_buffer();
		Serial.print(line);
		Serial.print("\n");
		do_command(line);
		Serial.print("\n> ");
	}
	*/

	nSerial.check_read();

	//MIDI.read();
}





