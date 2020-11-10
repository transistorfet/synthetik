 

import struct

class OplRegisters (object):
    def __init__(self, bank):
        (self.key_scaling,) = struct.unpack('B', bank.read(1))
        (self.freq_multiple,) = struct.unpack('B', bank.read(1))
        (self.feedback,) = struct.unpack('B', bank.read(1))
        (self.attack,) = struct.unpack('B', bank.read(1))
        (self.sustain,) = struct.unpack('B', bank.read(1))
        (self.env_gain,) = struct.unpack('B', bank.read(1))
        (self.decay,) = struct.unpack('B', bank.read(1))
        (self.release,) = struct.unpack('B', bank.read(1))
        (self.level,) = struct.unpack('B', bank.read(1))
        (self.amp_modulation,) = struct.unpack('B', bank.read(1))
        (self.vibrato,) = struct.unpack('B', bank.read(1))
        (self.key_scaling_rate,) = struct.unpack('B', bank.read(1))
        (self.connector,) = struct.unpack('B', bank.read(1))

        #print("{:x} {:x} {:x} {:x} {:x} {:x} {:x} {:x} {:x} ".format(self.key_scaling, self.freq_multiple, self.feedback, self.attack, self.sustain, self.env_gain, self.decay, self.release, self.level))

    def build_config(self):
        data = [ 0, 0, 0, 0, 0 ]
        data[0] = (0x80 if self.amp_modulation else 0x00) \
                | (0x40 if self.vibrato else 0x00) \
                | (0x20 if self.env_gain else 0x00) \
                | (0x01 if self.key_scaling_rate else 0x00) \
                | (0x0F & self.feedback)
        data[1] = (0xC0 & (self.key_scaling << 6)) \
                | (0x3F & self.level)
        data[2] = (0xF0 & (self.attack << 4)) \
                | (0x0F & self.decay)
        data[3] = (0xF0 & (self.sustain << 4)) \
                | (0x0F & self.release)
        data[4] = (0xE0 & (self.feedback << 1)) \
                | (0x01 if not self.connector else 0x00)
        return data


class Instrument (object):
    def __init__(self, name, bank):
        self.name = name
        (self.percussive,) = struct.unpack('B', bank.read(1))
        (self.voice_num,) = struct.unpack('B', bank.read(1))
        self.opl1 = OplRegisters(bank)
        self.opl2 = OplRegisters(bank)
        (self.op1_wave_sel,) = struct.unpack('B', bank.read(1))
        (self.op2_wave_sel,) = struct.unpack('B', bank.read(1))

    def build_config(self):
        op1 = self.opl1.build_config()
        op1.append(self.op1_wave_sel)

        op2 = self.opl2.build_config()
        op2.pop()
        op2.append(self.op2_wave_sel)

        data = op1 + op2

        if self.percussive:
            print('{', ', '.join([ "0x{:02x}".format(d) for d in data ]), '},    //', self.name)



class SoundBank (object):
    def __init__(self):
        self.offset = 0

    def read(self, num):
        self.offset += num
        return self.f.read(num)

    def skip_to(self, offset):
        diff = offset - self.offset
        if diff > 0:
            self.read(diff)

    def read_header(self):
        signature = self.read(8)
        if signature != b"\x01\x00ADLIB-":
            raise Exception("Unexpected file signature")
        used = struct.unpack('<h', self.read(2))
        (self.num_instruments,) = struct.unpack('<h', self.read(2))
        (self.name_offset,) = struct.unpack('<i', self.read(4))
        (self.data_offset,) = struct.unpack('<i', self.read(4))

    def read_instrument_names(self):
        self.instrument_names = []
        self.skip_to(self.name_offset)
        for i in range(0, self.num_instruments):
            (index,) = struct.unpack('<h', self.read(2))
            (used,) = struct.unpack('B', self.read(1))
            name = self.read(9).decode('ascii')
            self.instrument_names.append(name)

    def read_instrument_data(self):
        self.instruments = []
        self.skip_to(self.data_offset)
        for i in range(0, self.num_instruments):
            self.instruments.append(Instrument(self.instrument_names[i], bank))

    def read_file(self, filename):
        with open(filename, 'rb') as f:
            self.f = f
            self.read_header()
            self.read_instrument_names()
            self.read_instrument_data()


bank = SoundBank()
bank.read_file('$mlfbank.bnk')
#bank.read_file('STANDARD.BNK')

for ins in bank.instruments:
    ins.build_config()

