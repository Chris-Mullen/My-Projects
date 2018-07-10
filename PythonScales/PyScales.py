import os
import sys
import time
import datetime
import math

#Default Values
repetitions = 1
octaves = 1
reverseScale = True
BPM = 120
rootNote = 'C3'

inputArgs = sys.argv

for i in range( 1, len( inputArgs ) ):

    if( sys.argv[ i ].isdigit() ):

        BPM = sys.argv[ i ]

    else:

        rootNote = sys.argv[ i ]

class textFormatting:

    VIOLET = '\033[95m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    ENDC = '\033[0m'

    DIVIDERQUARTER = VIOLET + "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" + ENDC
    DIVIDERHALF = VIOLET + "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" + ENDC
    DIVIDERFULL = VIOLET + "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" + ENDC

class intervals:

    frequencyList = [

        16.35,
        17.32,
        18.35,
        19.45,
        20.6,
        21.83,
        23.12,
        24.5,
        25.96,
        27.5,
        29.14,
        30.87,
        32.7,
        34.65,
        36.71,
        38.89,
        41.2,
        43.65,
        46.25,
        49,
        51.91,
        55,
        58.27,
        61.74,
        65.41,
        69.3,
        73.42,
        77.78,
        82.41,
        87.31,
        92.5,
        98,
        103.83,
        110,
        116.54,
        123.47,
        130.81,
        138.59,
        146.83,
        155.56,
        164.81,
        174.61,
        185,
        196,
        207.65,
        220,
        233.08,
        246.94,
        261.63,
        277.18,
        293.66,
        311.13,
        329.63,
        349.23,
        369.99,
        392,
        415.3,
        440,
        466.16,
        493.88,
        523.25,
        554.37,
        587.33,
        622.25,
        659.25,
        698.46,
        739.99,
        783.99,
        830.61,
        880,
        932.33,
        987.77,
        1046.5,
        1108.73,
        1174.66,
        1244.51,
        1318.51,
        1396.91,
        1479.98,
        1567.98,
        1661.22,
        1760,
        1864.66,
        1975.53,
        2093,
        2217.46,
        2349.32,
        2489.02,
        2637.02,
        2793.83,
        2959.96,
        3135.96,
        3322.44,
        3520,
        3729.31,
        3951.07,
        4186.01,
        4434.92,
        4698.63,
        4978.03,
        5274.04,
        5587.65,
        5919.91,
        6271.93,
        6644.88,
        7040,
        7458.62,
        7902.13

    ]

    noteList = [

        'C0',
        'Db0',
        'D0',
        'Eb0',
        'E0',
        'F0',
        'Gb0',
        'G0',
        'Ab0',
        'A0',
        'Bb0',
        'B0',
        'C1',
        'Db1',
        'D1',
        'Eb1',
        'E1',
        'F1',
        'Gb1',
        'G1',
        'Ab1',
        'A1',
        'Bb1',
        'B1',
        'C2',
        'Db2',
        'D2',
        'Eb2',
        'E2',
        'F2',
        'Gb2',
        'G2',
        'Ab2',
        'A2',
        'Bb2',
        'B2',
        'C3',
        'Db3',
        'D3',
        'Eb3',
        'E3',
        'F3',
        'Gb3',
        'G3',
        'Ab3',
        'A3',
        'Bb3',
        'B3',
        'C4',
        'Db4',
        'D4',
        'Eb4',
        'E4',
        'F4',
        'Gb4',
        'G4',
        'Ab4',
        'A4',
        'Bb4',
        'B4',
        'C5',
        'Db5',
        'D5',
        'Eb5',
        'E5',
        'F5',
        'Gb5',
        'G5',
        'Ab5',
        'A5',
        'Bb5',
        'B5',
        'C6',
        'Db6',
        'D6',
        'Eb6',
        'E6',
        'F6',
        'Gb6',
        'G6',
        'Ab6',
        'A6',
        'Bb6',
        'B6',
        'C7',
        'Db7',
        'D7',
        'Eb7',
        'E7',
        'F7',
        'Gb7',
        'G7',
        'Ab7',
        'A7',
        'Bb7',
        'B7',
        'C8',
        'Db8',
        'D8',
        'Eb8',
        'E8',
        'F8',
        'Gb8',
        'G8',
        'Ab8',
        'A8',
        'Bb8',
        'B8'

    ]

    scaleIntervals = {

        'Chromatic' : [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 ],
        'Major' : [ 2, 4, 5, 7, 9, 11, 12 ],
        'Ionian' : [ 2, 4, 5, 7, 9, 11, 12 ],
        'Dorian' : [ 2, 3, 5, 7, 9, 10, 12 ],
        'Phrygian' : [ 1, 3, 5, 7, 8, 10, 12 ],
        'Lydian' : [ 2, 4, 6, 7, 9, 11, 12 ],
        'Mixolydian' : [ 2, 4, 5, 7, 9, 10, 12 ],
        'Aeolian' : [ 2, 3, 5, 7, 8, 10, 12 ],
        'Locrian' : [ 1, 3, 5, 6, 8, 10, 12 ]

    }

    chordIntervals = {

        'dom7' : [ 4, 7, 10 ],
        'maj7' : [ 4, 7, 11 ],
        'min7' : [ 3, 7, 10 ],
        'min7b5' : [ 3, 6, 10 ]

    }

    #Matches A Scale Type With A Chord Type That Will Harmonize When Played Together.
    scaleMatches = {

        'Ionian' : 'maj7',
        'Dorian' : 'min7',
        'Phrygian' : 'min7',
        'Lydian' : 'maj7',
        'Mixolydian' : 'dom7',
        'Aeolian' : 'min7',
        'Locrian' : 'min7b5'

    }

class scale:

    def __init__( self, rootNote, scaleType, octaves ):

        if not rootNote in intervals.noteList:

            print "Error: Unrecognised Root Note [" + rootNote + "]\nDefault: C3, Quitting..."
            sys.exit()

        if not scaleType in intervals.scaleIntervals:

            print "Error: Unrecognised Scale Type [" + scaleType + "] e.g. Ionian, Quitting..."
            sys.exit()

        self.rootNote = rootNote
        self.scaleType = scaleType
        self.octaves = octaves

        self.rootIndex = intervals.noteList.index( self.rootNote )
        self.rootFrequency = intervals.frequencyList[ intervals.noteList.index( rootNote ) ]

        if self.rootIndex + ( octaves * 12 ) > len( intervals.noteList ):

            print textFormatting.YELLOW + "Warning: Some Notes Out Of Range" + textFormatting.ENDC

        if not octaves in range( 1, 6 ):

            print "Octaves Out Of Range: " + str( octaves )
            return None

        self.constructScale( octaves )
        self.constructChord()

    def printScaleInfo( self ):

        print textFormatting.DIVIDERFULL

        print textFormatting.VIOLET + "Root: " + self.rootNote + "( " + str( self.rootFrequency ) + "Hz )\n"
        print "Scale: " + self.scaleType

        scaleString = "[ " + str( self.octaves ) + " Octave(s) ] | "

        for i in self.scaleNotes:

            scaleString += i + " | "

        print "Notes: " + scaleString + "\n"

        print "Chord: " + self.chordType

        chordString = " | "

        for i in self.chordNotes:

            chordString += i + " | "

        print "Notes: " + chordString + textFormatting.ENDC

        print textFormatting.DIVIDERFULL

        print

    def printNote( self, note, ascending ):

        #Remove Octave Number
        note = note[:-1]

        if note == self.rootNote[:-1]:

            print textFormatting.BLUE + textFormatting.BOLD + textFormatting.UNDERLINE + "\t" + note + textFormatting.ENDC

        else:

            if ascending:

                print textFormatting.GREEN + "\t" + note + textFormatting.ENDC

            else:

                print textFormatting.RED + "\t" + note + textFormatting.ENDC

    def constructScale( self, octaves ):

        self.scaleFrequencies = [ intervals.frequencyList[ self.rootIndex ] ]
        self.scaleNotes = [ intervals.noteList[ self.rootIndex ] ]

        for i in range( 0, octaves ):

            for j in intervals.scaleIntervals.get( self.scaleType ):

                self.scaleFrequencies.append( intervals.frequencyList[ int( self.rootIndex + ( i * 12 ) + j ) ] )
                self.scaleNotes.append( intervals.noteList[ int( self.rootIndex + ( i * 12 ) + j ) ] )

    def constructChord( self ):

        self.chordFrequencies = [ intervals.frequencyList[ self.rootIndex ] ]
        self.chordNotes = [ intervals.noteList[ self.rootIndex ] ]

        self.chordType = intervals.scaleMatches.get( self.scaleType )

        for i in intervals.chordIntervals.get( self.chordType ):

            self.chordFrequencies.append( intervals.frequencyList[ int( self.rootIndex + i ) ] )
            self.chordNotes.append( intervals.noteList[ int( self.rootIndex + i ) ] )

    def playScale( self, tempo, repetitions, ascending, reverseScale, playChord ):

        self.printScaleInfo()

        scaleLength = len( self.scaleNotes )

        noteValue = tempo.noteLength

        print textFormatting.VIOLET + "Scale Repetitions: " + str( repetitions ) + "\n" + textFormatting.ENDC

        for i in range( 0, repetitions ):

            print textFormatting.VIOLET + "( " + str( i + 1 ) + " /" + str( repetitions ) + ")\n" + textFormatting.ENDC

            if playChord:

                #self.playChord( tempo, 1, ascending, False, True )
                self.playChord( tempo, 1, ascending, False, False )

            if ascending:

                print textFormatting.VIOLET + "[ Scale: " + self.rootNote + " " + self.scaleType + " ]" + "\n" + textFormatting.ENDC

                for j, v in enumerate( self.scaleFrequencies ):

                    self.printNote( self.scaleNotes[ j ], ascending )
                    os.system( 'play -qn synth ' + str( noteValue ) + ' pluck ' + str( v ) + ' & sleep ' + str( noteValue ) + '; done' )

                if reverseScale:

                    print textFormatting.DIVIDERQUARTER


                    if playChord:

                        #self.playChord( tempo, 1, not ascending, False, True )
                        self.playChord( tempo, 1, not ascending, False, False )

                    print textFormatting.VIOLET + "[ Scale: " + self.rootNote + " " + self.scaleType + " ]" + "\n" + textFormatting.ENDC

                    for j, v in enumerate( reversed( self.scaleFrequencies ) ):

                        self.printNote( self.scaleNotes[ scaleLength - j - 1 ], not ascending )
                        os.system( 'play -qn synth ' + str( noteValue ) + ' pluck ' + str( v ) + ' & sleep ' + str( noteValue ) + '; done' )

                    print

            else:

                print textFormatting.VIOLET + "[ Scale: " + self.rootNote + " " + self.scaleType + " ]" + "\n" + textFormatting.ENDC

                for j, v in enumerate( reversed( self.scaleFrequencies ) ):

                    self.printNote( self.scaleNotes[ scaleLength - j - 1 ], ascending )
                    os.system( 'play -qn synth ' + str( noteValue ) + ' pluck ' + str( v ) + ' & sleep ' + str( noteValue ) + '; done' )

                print

                if reverseScale:

                    print textFormatting.DIVIDERQUARTER

                    print textFormatting.VIOLET + "[ Scale: " + self.rootNote + " " + self.scaleType + " ]" + "\n" + textFormatting.ENDC

                    for j, v in enumerate( self.scaleFrequencies ):

                        self.printNote( self.scaleNotes[ j ], not ascending )
                        os.system( 'play -qn synth ' + str( noteValue ) + ' pluck ' + str( v ) + ' & sleep ' + str( noteValue ) + '; done' )

                    print

            print textFormatting.DIVIDERHALF

    def playChord( self, tempo, repetitions, ascending, reverseScale, playInBackground ):

        chordLength = len( self.chordNotes )

        noteValue = tempo.barValue

        strumSpeed = ( float( noteValue ) / tempo.meter / 100.0 )

        if playInBackground:

            strumDelay = 0

        else:

            strumDelay = float( noteValue ) / tempo.meter

            print textFormatting.VIOLET + "Chord Repetitions: " + str( repetitions ) + "\n" + textFormatting.ENDC

        print textFormatting.VIOLET + "[ Chord: " + self.rootNote + " " + self.chordType + " ]" + "\n" + textFormatting.ENDC

        for i in range( 0, repetitions ):

            if ascending:

                for j, v in enumerate( self.chordFrequencies ):

                    self.printNote( self.chordNotes[ j ], ascending )
                    os.system( 'play -qn synth ' + str( noteValue ) + ' pluck ' + str( v ) + ' & sleep ' + str( strumSpeed ) + '; done' )

                time.sleep( strumDelay )

                if reverseScale:

                    print textFormatting.DIVIDERQUARTER

                    for j, v in enumerate( reversed( self.chordFrequencies ) ):

                        self.printNote( self.chordNotes[ chordLength - j - 1 ], not ascending )
                        os.system( 'play -qn synth ' + str( noteValue ) + ' pluck ' + str( v ) + ' & sleep ' + str( strumSpeed ) + '; done' )

                    time.sleep( strumDelay )

                    print

            else:

                for j, v in enumerate( reversed( self.chordFrequencies ) ):

                    self.printNote( self.chordNotes[ chordLength - j - 1 ], ascending )
                    os.system( 'play -qn synth ' + str( noteValue ) + ' pluck ' + str( v ) + ' & sleep ' + str( strumSpeed ) + '; done' )

                time.sleep( strumDelay )

                print

                if reverseScale:

                    print textFormatting.DIVIDERQUARTER

                    for j, v in enumerate( self.chordFrequencies ):

                        self.printNote( self.chordNotes[ j ], not ascending )
                        os.system( 'play -qn synth ' + str( noteValue ) + ' pluck ' + str( v ) + ' & sleep ' + str( strumSpeed ) + '; done' )

                    time.sleep( strumDelay )

                    print

            print textFormatting.DIVIDERHALF

    def playOrgan( self, tempo, repetitions, ascending, reverseScale, playInBackground ):

        noteValue = tempo.barValue * repetitions * octaves

        fadeInOut = noteValue / 2

        organVolume = 0.7

        chordString = ""

        if playInBackground:

            jobControl = ' &'

        else:

            jobControl = ''

        if reverseScale:

            noteValue *= ( 2 * octaves )

        for i in self.chordFrequencies:

            chordString += "sin " + str( i ) + " "

        os.system( 'play -v ' + str( organVolume ) + ' -qn synth ' + chordString + ' fade q ' + str( fadeInOut ) + ' ' + str( noteValue ) + ' ' + str( fadeInOut ) + jobControl )

class tempo:

    def __init__( self, bpm, timeSignature ):

        self.BPS = float( bpm ) / 60
        self.meter = int( math.floor( timeSignature ) )  # Meter = Number Of Beats Per Measure
        self.noteValue = int( 10 * ( timeSignature - float( self.meter ) ) )  # Note Value = Note The Beat Is On i.e. 4 Means The Beat Will Be In Quarter Notes

        self.noteLength = 1 / self.BPS
        self.barValue = self.noteLength * self.meter

        self.quarterNote = self.barValue / 4
        self.eighthNote = self.barValue / 8
        self.sixteenthNote = self.barValue / 16

        drumStringPrefix = 'ffplay -loglevel quiet -nodisp -autoexit -t '

        self.highHat = drumStringPrefix + str( self.sixteenthNote ) + ' \"/home/mint/Downloads/musicradar-drum-samples/Assorted Hits/Hi Hats/Zildjian K Hats/KHats Open-08.wav\" & '
        self.snare = drumStringPrefix + str( self.noteLength ) + ' \"/home/mint/Downloads/musicradar-drum-samples/Assorted Hits/Snares/Ludwig A/CYCdh_LudSnrA-03.wav\" & '
        self.kick = drumStringPrefix + str( self.noteLength ) + ' \"/home/mint/Downloads/musicradar-drum-samples/Assorted Hits/Kicks/Acoustic/CYCdh_AcouKick-16.wav\" & '

        self.crash = drumStringPrefix + str( self.barValue ) + ' \"/home/mint/Downloads/musicradar-drum-samples/Assorted Hits/Cymbals/CYCdh_Crash-01.wav\" & '

#Clear Screen
os.system( 'reset' )

def playMode( rootNote, tempo, modeName, repetitions, octaves ):

    mode = scale( rootNote, modeName, octaves )

    mode.playOrgan( tempo, repetitions, True, True, True )
    mode.playScale( tempo, repetitions, True, True, False )

songTempo = tempo( 60, 4.4 )

def playModes( rootNote, tempo, repetitions, reverseScale, octaves ):

    modeNames = [ 'Ionian', 'Dorian', 'Phrygian', 'Lydian', 'Mixolydian', 'Aeolian', 'Locrian' ]

    majorScale = scale( rootNote, 'Ionian', octaves )

    for i, mode in enumerate( majorScale.scaleNotes ):

        modeScale = scale( mode, modeNames[ i % len( modeNames ) ], octaves )

        modeScale.playOrgan( tempo, repetitions, True, reverseScale, True )
        modeScale.playScale( tempo, repetitions, True, reverseScale, False )

songTempo = tempo( BPM, 4.4 )

playModes( rootNote, songTempo, repetitions, reverseScale, octaves )
