from itertools import cycle

terminalWidth=248

colours = {
	'BLACK': '\033[0;30m',
	'RED': '\033[0;31m',
	'GREEN': '\033[0;32m',
	'YELLOW': '\033[0;33m',
	'BLUE': '\033[0;34m',
	'PURPLE': '\033[0;35m',
	'CYAN': '\033[0;36m',
	'WHITE': '\033[0;37m'
}

intervalUnison = 0
intervalMinorSecond = 1
intervalMajorSecond = 2
intervalMinorThird = 3
intervalMajorThird = 4
intervalPerfectFourth = 5
intervalAugmentedFourthDiminishedFifth = 6
intervalPerfectFifth = 7
intervalMinorSixth = 8
intervalMajorSixth = 9
intervalMinorSeventh = 10
intervalMajorSeventh = 11
intervalOctave = 12

intervalNames = {
    intervalUnison : "Unison",
    intervalMinorSecond : "Minor Second",
    intervalMajorSecond : "Major Second",
    intervalMinorThird : "Minor Third / Relative Minor",
    intervalMajorThird : "Major Third",
    intervalPerfectFourth : "Perfect Fourth",
    intervalAugmentedFourthDiminishedFifth : "Augmented Fourth / Diminished Fifth",
    intervalPerfectFifth : "Perfect Fifth",
    intervalMinorSixth : "Minor Sixth",
    intervalMajorSixth : "Major Sixth",
    intervalMinorSeventh : "Minor Seventh",
    intervalMajorSeventh : "Major Seventh",
    intervalOctave : "Octave"
}

scaleIntervals = {
    "Chromatic" : [ intervalUnison, intervalMinorSecond, intervalMajorSecond, intervalMinorThird, intervalMajorThird, intervalPerfectFourth, intervalAugmentedFourthDiminishedFifth, intervalPerfectFifth, intervalMinorSixth, intervalMajorSixth, intervalMinorSeventh, intervalMajorSeventh, intervalOctave ],
    "Major Ionian" : [ intervalUnison, intervalMajorSecond, intervalMajorThird, intervalPerfectFourth, intervalPerfectFifth, intervalMajorSixth, intervalMajorSeventh, intervalOctave ],
    "Major Dorian" : [ intervalUnison, intervalMajorSecond, intervalMinorThird, intervalPerfectFourth, intervalPerfectFifth, intervalMajorSixth, intervalMinorSeventh, intervalOctave ],
    "Major Phrygian" : [ intervalUnison, intervalMinorSecond, intervalMinorThird, intervalPerfectFourth, intervalPerfectFifth, intervalMinorSixth, intervalMinorSeventh, intervalOctave ],
    "Major Lydian" : [ intervalUnison, intervalMajorSecond, intervalMajorThird, intervalAugmentedFourthDiminishedFifth, intervalPerfectFifth, intervalMajorSixth, intervalMajorSeventh, intervalOctave ],
    "Major Mixolydian" : [ intervalUnison, intervalMajorSecond, intervalMajorThird, intervalPerfectFourth, intervalPerfectFifth, intervalMajorSixth, intervalMinorSeventh, intervalOctave ],
    "Major Aeolian / Natural Minor" : [ intervalUnison, intervalMajorSecond, intervalMinorThird, intervalPerfectFourth, intervalPerfectFifth, intervalMinorSixth, intervalMinorSeventh, intervalOctave ],
    "Major Locrian" : [ intervalUnison, intervalMinorSecond, intervalMinorThird, intervalPerfectFourth, intervalAugmentedFourthDiminishedFifth, intervalMinorSixth, intervalMinorSeventh, intervalOctave ],
    "Major Pentatonic" : [ intervalUnison, intervalMajorSecond, intervalMajorThird, intervalPerfectFifth, intervalMajorSixth, intervalOctave ],
    "Minor Pentatonic" : [ intervalUnison, intervalMinorThird, intervalPerfectFourth, intervalPerfectFifth, intervalMinorSeventh, intervalOctave ],
    "Major Blues" : [ intervalUnison, intervalMajorSecond, intervalMinorThird, intervalMajorThird, intervalPerfectFifth, intervalMajorSixth, intervalOctave ],
    "Minor Blues" : [ intervalUnison, intervalMinorThird, intervalPerfectFourth, intervalAugmentedFourthDiminishedFifth, intervalPerfectFifth, intervalMinorSeventh, intervalOctave ],
    "Major Minor Blues" : [ intervalUnison, intervalMajorSecond, intervalMinorThird, intervalMajorThird, intervalPerfectFourth, intervalAugmentedFourthDiminishedFifth, intervalPerfectFifth, intervalMajorSixth, intervalMinorSeventh, intervalOctave ],
    "Harmonic Minor" : [ intervalUnison, intervalMajorSecond, intervalMinorThird, intervalPerfectFourth, intervalPerfectFifth, intervalMinorSixth, intervalMajorSeventh, intervalOctave ],
    "Empty" : []
}

chordIntervals = {
    "Major" : [intervalUnison, intervalMajorThird, intervalPerfectFifth],
    "Minor" : [intervalUnison, intervalMinorThird, intervalPerfectFifth],
    "Augmented" : [intervalUnison, intervalMajorThird, intervalMinorSixth],
    "Diminished" : [intervalUnison, intervalMinorThird, intervalAugmentedFourthDiminishedFifth],
    "Major Seventh" : [intervalUnison, intervalMajorThird, intervalPerfectFifth, intervalMajorSeventh],
    "Minor Seventh" : [intervalUnison, intervalMinorThird, intervalPerfectFifth, intervalMinorSeventh],
    "Dominant Seventh" : [intervalUnison, intervalMajorThird, intervalPerfectFifth, intervalMinorSeventh],
    "Half Diminished Seventh" : [intervalUnison, intervalMinorThird, intervalAugmentedFourthDiminishedFifth, intervalMinorSeventh],
    "Diminished Seventh" : [intervalUnison, intervalMinorThird, intervalAugmentedFourthDiminishedFifth, intervalMajorSixth],
    "Minor Major Seventh" : [intervalUnison, intervalMinorThird, intervalPerfectFifth, intervalMajorSeventh],
    "Augmented Seventh" : [intervalUnison, intervalMajorThird, intervalMinorSixth, intervalMajorSeventh]
}

notes = ["C", "C#/Db", "D", "D#/Eb", "E", "F", "F#/Gb", "G", "G#/Ab", "A", "A#/Bb", "B"]
notesList = cycle(notes)

tuningGuitarStandard = ["E", "A", "D", "G", "B", "E"]
tuningGuitarDownHalfStep = ["Eb", "Ab", "Db", "Gb", "Bb", "Eb"]
tuningGuitarDropD = ["D", "A", "D", "G", "B", "E"]
tuningGuitar_GuitarManJerryReed = ["Db", "Ab", "Db", "Gb", "C", "Eb"]

def scaleChromaticNotes(scale):
    lastInterval = intervalUnison
    chromaticNotes = []
    for interval in scale:
        if(interval - lastInterval == 1):
            chromaticNotes.append(interval)
            lastInterval = intervalUnison
        else:
            lastInterval = interval
    return chromaticNotes

def scaleMinusChromaticNotes(scale):
    lastInterval = intervalUnison
    notes = []
    for interval in scale:
        if(interval - lastInterval != 1):
            notes.append(interval)
            lastInterval = intervalUnison
        else:
            lastInterval = interval
    return notes