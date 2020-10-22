
import time
import shlex
import serial
import select
import argparse
import readline
import threading
import traceback

filename = '/dev/ttyACM2'
baud = 115200
historyfile = '.synth_history'

NOTE_C  =   '0x4b'
NOTE_CS =   '0x6b'
NOTE_D  =   '0x81'
NOTE_DS  =  '0x98'
NOTE_E  =   '0xB0'
NOTE_F  =   '0xCA'
NOTE_FS  =  '0xE5'

NOTE_G  =   '0x81'
NOTE_GS  =   '0x81'
NOTE_A  =   '0x81'
NOTE_AS  =   '0x81'
NOTE_B  =   '0x81'

class Synth (object):
    def __init__(self):
        self.serial = serial.Serial(filename, baud)

        self.thread = threading.Thread(None, self.run, 'SerialThread')
        self.thread.stopflag = threading.Event()
        self.thread.start()

    def close(self):
        self.thread.stopflag.set()
        self.thread.join() 

    def send(self, data):
        print(data)
        self.serial.write(bytes(data + '\n', 'utf-8'))

    def on_receive(self, line):
        print("RECV <- " + line)
        """
        (ref, _, args) = line.partition(" ")
        if not ref:
            return
        with self.lock:
            for (i, query) in enumerate(self.waiting):
                if query.ref == ref:
                    self.waiting.pop(i)
                    query.result = args
                    query.ready.set()
                    return

        notify_ref = self.get_setting('query').rstrip('/') + '/' + ref + '/*'
        print(notify_ref)
        """

    def readline(self):
        (rl, wl, el) = select.select([ self.serial ], [ ], [ ], 1)
        if rl and self.serial in rl:
            return self.serial.readline()
        else:
            return None

    def run(self):
        while not self.thread.stopflag.is_set():
            while not self.thread.stopflag.is_set():
                try:
                    line = self.readline()
                    if line:
                        line = line.decode('utf-8').strip()
                        self.on_receive(line)

                except serial.serialutil.SerialException as exc:
                    print("serial error: " + repr(exc), logtype='error')
                    break

                except:
                    print(traceback.format_exc(), logtype='error')

    def note(self, *args):
        print(args)
        if len(args) > 0:
            self.send("write 0xa0 " + args[0])
        self.send("write 0xb0 0x31")
        time.sleep(0.8)
        self.send("write 0xb0 0x11")

    def play(self):
        self.note(NOTE_C)
        self.note(NOTE_D)
        self.note(NOTE_E)
        self.note(NOTE_F)

def main():
    #parser = argparse.ArgumentParser(prog='load', description='Load a program over serial into Computie68k')
    #parser.add_argument('filename')
    #parser.add_argument('-l', '--limit', action='store_true', help='Limit the speed of transmission')
    #args = parser.parse_args()


    synth = Synth()

    synth.send("write 0xb0 0x31\n")

    readline.read_history_file(historyfile)
    #controller = self.make_controller(nerve.Request(self, None, 'QUERY', "/", { }))
    #readline.set_completer(controller.tab_complete)
    #readline.parse_and_bind("tab: complete")

    while True:
        try:
            line = input(">> ")
            if line == 'quit':
                break
            elif line:
                """
                request = nerve.Request(self, None, 'QUERY', "/", { 'requests[]' : [ line ] }, headers=dict(accept='text/plain, text/html, application/json'))
                controller.handle_request(request)
                mimetype = controller.get_mimetype()
                output = controller.get_output()

                if mimetype == 'application/json':
                    data = json.loads(output.decode('utf-8'))
                    if data and data[0]:
                        print('\n'.join([ str(val) for val in data ]))
                else:
                    print(output.decode('utf-8'))
                """
                args = shlex.split(line)
                if (args[0] == 'delay'):
                    time.sleep(float(args[1]))
                else:
                    if hasattr(synth, args[0]):
                        func = getattr(synth, args[0])
                        func(*args[1:])
                    else:
                        synth.send(line)

        except KeyboardInterrupt:
            print("\nExiting...")
            break

        except:
            print(traceback.format_exc())


    readline.write_history_file(historyfile)
    synth.close()

if __name__ == '__main__':
    main()


