#!/usr/bin/python3
#
# Given the octave settings, which are the exact frequencies in Hz for each note in the octave
# calculate the F number for the corresponding note in the YM3812 (OPL2)

crystal = 3.57954 * 1000000
block = 4
clock_divider = 72      # OPL2 divides the clock by 72, OPL3 divides it by 288
factor = pow(2, 20 - block) / (crystal / 72)

 
def calc(freq):
    f = factor * freq
    e1 = int(f) / factor
    e2 = (int(f) + 1) / factor
    #print("DEBUG: ", f, e1, e2)
    if (freq - e1) < (e2 - freq):
        return int(f)
    else:
        return int(f) + 1


octave0 = [  16.35,  17.32,  18.35,  19.45,  20.60,  21.83,  23.12,  24.50,  25.96,  27.50,  29.14,  30.87 ]
octave1 = [  32.70,  34.65,  36.71,  38.89,  41.20,  43.65,  46.25,  49.00,  51.91,  55.00,  58.27,  61.74 ]
octave2 = [  65.41,  69.30,  73.42,  77.78,  82.41,  87.31,  92.50,  98.00, 103.83, 110.00, 116.54, 123.47 ]
octave3 = [ 130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94 ]
octave4 = [ 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88 ]

octaves = [
    octave0,
    octave1,
    octave2,
    octave3,
    octave4,
]

for octave in octaves:
    for note in octave:
        fnumber = calc(note)
        print(str(fnumber) + ', ', end='')
    print('')

