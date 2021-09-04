#!/usr/bin/python3
#
# Reads in a preset *.bnk file containing a bank of instrument settings for the YM3812 (OPL2)
# and outputs it as a set of register values which can be used in the Arduino program
#

import struct

class OplRegisters (object):
    def __init__(self, bank):
        (self.op1_flags,) = struct.unpack('B', bank.read(1))
        (self.op1_attack,) = struct.unpack('B', bank.read(1))
        (self.op1_sustain,) = struct.unpack('B', bank.read(1))
        (self.op1_wave_sel,) = struct.unpack('B', bank.read(1))
        (self.op1_scale,) = struct.unpack('B', bank.read(1))
        (self.op1_level,) = struct.unpack('B', bank.read(1))
        (self.feedback,) = struct.unpack('B', bank.read(1))
        (self.op2_flags,) = struct.unpack('B', bank.read(1))
        (self.op2_attack,) = struct.unpack('B', bank.read(1))
        (self.op2_sustain,) = struct.unpack('B', bank.read(1))
        (self.op2_wave_sel,) = struct.unpack('B', bank.read(1))
        (self.op2_scale,) = struct.unpack('B', bank.read(1))
        (self.op2_level,) = struct.unpack('B', bank.read(1))
        (reserved1,) = struct.unpack('B', bank.read(1))
        (self.note_offset,) = struct.unpack('h', bank.read(2))

        #print("{:x} {:x} {:x} {:x} {:x} {:x} {:x} {:x} {:x} {:x} {:x} {:x} {:x} {:x}".format(self.op1_flags, self.op1_attack, self.op1_sustain, self.op1_wave_sel, self.op1_scale, self.op1_level, self.feedback, self.op2_flags, self.op2_attack, self.op2_sustain, self.op2_wave_sel, self.op2_scale, self.op2_level, self.note_offset))

    def build_config(self):
        data = [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ]
        data[0] = self.op1_flags
        data[1] = self.op1_scale | self.op1_level
        data[2] = self.op1_attack
        data[3] = self.op1_sustain
        data[4] = self.feedback
        data[5] = self.op1_wave_sel
        data[6] = self.op2_flags
        data[7] = self.op2_scale | self.op1_level
        data[8] = self.op2_attack
        data[9] = self.op2_sustain
        data[10] = self.op2_wave_sel
        return data


class Instrument (object):
    def __init__(self, name, bank):
        self.name = name
        (self.flags,) = struct.unpack('h', bank.read(2))
        (self.voice_detune,) = struct.unpack('B', bank.read(1))
        (self.perc_num,) = struct.unpack('B', bank.read(1))
        self.voice1 = OplRegisters(bank)
        self.voice2 = OplRegisters(bank)

    def build_config(self):
        data = self.voice1.build_config()
        #op2 = self.voice2.build_config()

        #data = op1 + op2

        print('{', ', '.join([ "0x{:02x}".format(d) for d in data ]), '},    //', self.perc_num if self.perc_num else '', self.name)



class SoundBank (object):
    def __init__(self):
        self.offset = 0
        self.num_instruments = 175

    def read(self, num):
        self.offset += num
        return self.f.read(num)

    def read_header(self):
        signature = self.read(8)
        if signature != b"#OPL_II#":
            raise Exception("Unexpected file signature")

    def read_instrument_data(self):
        self.instruments = []
        for i in range(0, self.num_instruments):
            self.instruments.append(Instrument("", bank))

    def read_instrument_names(self):
        self.instrument_names = []
        for i in range(0, self.num_instruments):
            name = self.read(32).decode('ascii')
            self.instrument_names.append(name)
            self.instruments[i].name = name

    def read_file(self, filename):
        with open(filename, 'rb') as f:
            self.f = f
            self.read_header()
            self.read_instrument_data()
            self.read_instrument_names()


bank = SoundBank()
bank.read_file('GENMIDI.op2')

for ins in bank.instruments:
    ins.build_config()

