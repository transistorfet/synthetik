
#define SERIAL_SPEED	115200


#define AY_LDATA_PORT	PORTA
#define AY_LDATA_PIN	PINA
#define AY_LDATA_DDR	DDRA

#define AY_BC1		40
#define AY_BDIR		39
#define AY_RESET	38


#undef INLINE_NOP
#define INLINE_NOP		__asm__("nop\n\t");



/******************************
 * Serial Communications Code *
 ******************************/

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


/**********************
 * Audio Control Code *
 **********************/

byte read_data(byte addr)
{
	byte value;

	AY_LDATA_DDR = 0xFF;
	AY_LDATA_PORT = addr;

	digitalWrite(AY_BC1, 1);
	digitalWrite(AY_BDIR, 1);
	delayMicroseconds(15);
	digitalWrite(AY_BC1, 0);
	digitalWrite(AY_BDIR, 0);

	AY_LDATA_DDR = 0x00;
	AY_LDATA_PORT = 0x00;

	digitalWrite(AY_BC1, 1);
	digitalWrite(AY_BDIR, 0);
	delayMicroseconds(1);
	value = AY_LDATA_PIN;
	digitalWrite(AY_BC1, 0);
	digitalWrite(AY_BDIR, 0);

	AY_LDATA_DDR = 0xFF;

	return value;
}

void write_data(byte addr, byte data)
{
	AY_LDATA_DDR = 0xFF;
	AY_LDATA_PORT = addr;

	digitalWrite(AY_BC1, 1);
	digitalWrite(AY_BDIR, 1);
	delayMicroseconds(15);
	digitalWrite(AY_BC1, 0);
	digitalWrite(AY_BDIR, 0);

	AY_LDATA_PORT = data;

	digitalWrite(AY_BC1, 0);
	digitalWrite(AY_BDIR, 1);
	delayMicroseconds(15);
	digitalWrite(AY_BC1, 0);
	digitalWrite(AY_BDIR, 0);
}

void set_tone(byte channel, word tone)
{
	write_data(0 + (channel * 2), tone & 0xff);
	write_data(1 + (channel * 2), (tone >> 8) & 0xff);
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

void init_audio()
{
	digitalWrite(AY_RESET, 0);
	delayMicroseconds(15);
	digitalWrite(AY_RESET, 1);

	write_data(7, 0x3E);
	write_data(8, 0x0F);
	write_data(9, 0x00);
	write_data(10, 0x00);
	set_tone(0, 0);

	Serial.println(read_data(7), HEX);
	Serial.println(read_data(10), HEX);
	Serial.println(read_data(15), HEX);
}

void run_reset()
{
	init_audio();
}

void run_test()
{
	write_data(13, 0xFF);
	write_data(14, 0xFF);
	write_data(15, 0x00);

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

byte noise = 0;

void run_noise()
{
	//byte noise = read_data(6);
	//Serial.println(noise, HEX);
	if (noise) {
		noise = 0;
		write_data(6, 0x00);
		write_data(7, 0x3E);
	} else {
		noise = 1;
		write_data(6, 0x0F);
		write_data(7, 0x00);
	}
}

void run_mute()
{
	write_data(7, 0x3F);
}

void run_unmute()
{
	write_data(7, 0x3E);
}




void do_command(String line)
{
	if (line.equals("test")) {
		run_test();
	}
	else if (line.equals("mute")) {
		run_mute();
	}
	else if (line.equals("unmute")) {
		run_unmute();
	}
	else if (line.equals("reset")) {
		run_reset();
	}
	else if (line.equals("noise")) {
		run_noise();
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

	// Controls
	pinMode(AY_BC1, OUTPUT);
	pinMode(AY_BDIR, OUTPUT);
	pinMode(AY_RESET, OUTPUT);
	digitalWrite(AY_BC1, 0);
	digitalWrite(AY_BDIR, 0);
	digitalWrite(AY_RESET, 1);

	// Data Bus
	AY_LDATA_PORT = 0x00;	// D0 - D7
	AY_LDATA_DDR = 0x00;

	init_audio();

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





