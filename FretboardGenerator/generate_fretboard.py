from common import *
from fpdf import FPDF   # sudo apt-get install python3-fpdf
import os
import sys
import time
import warnings

size8 = 8
h5 = 5
h6 = 6
fretHeight = 4
w0 = 0
w1 = 1
w200 = 200

w5 = 4
w6 = 5

os.system("clear")

def createPDF():
    pdf = FPDF(orientation="P", unit="mm", format="A4")
    pdf.set_font("Helvetica", size=size8)
    pdf.set_text_color(0, 0, 0)
    return pdf

def savePDF(pdf, filename):
    pdf.output(filename)

def appendCellPDF(pdf, w, h, text, ln, align, colour="BLACK"):
    with warnings.catch_warnings():
        warnings.simplefilter('ignore')
        textColour(pdf, colour)
        pdf.cell(w=w, h=h, text=text, border=0, ln=ln, align=align)
    return pdf

def appendTextPDF(pdf, text, align="C", colour = "BLACK"):
    pdf.set_font("Helvetica", size=size8)
    appendCellPDF(pdf, w0, fretHeight, text, 1, align, colour)
    return pdf

def addPDFHeading1(pdf, text):
    appendCellPDF(pdf, w200, h6, text, 1, "C", "BLACK")
    return appendTextPDF(pdf=pdf, text='')

def addPDFHeading2(pdf, text):
    appendCellPDF(pdf, w200, h5, text, 1, "L", "BLACK")
    return appendTextPDF(pdf=pdf, text='')

def addPDFPage(pdf, title):
    pdf.add_page()
    pdf = addPDFHeading1(pdf, title)
    return pdf

def appendScaleDescription(pdf, scaleName, key):
    scale = scaleIntervals[scaleName]
    addPDFHeading2(pdf, "Scale Intervals")
    for interval in scale:
        pdf = appendTextPDF(pdf=pdf, text=("[" + addInterval(key, interval) + "] " + intervalNames[interval]), align="L", colour=getColourFromInterval(interval))
    return pdf

def appendFretPDF(pdf, text, colour):
    pdf.set_font("Helvetica", size=size8)
    appendCellPDF(pdf, w5, h6, text, 0, "C", colour)
    appendCellPDF(pdf, w1, h6, "|", 0, "C", "BLACK")
    return pdf

def appendFretMarkersPDF(pdf, frets):
    pdf.set_font("Helvetica", size=size8)

    for i in range(frets + 1):
        if(i>0 and i%12==0):
            marker = "8  "
        elif(i%12==3 or i%12==5 or i%12==7 or i%12==9):
            marker = "o  "
        else:
            marker = "   "
        appendCellPDF(pdf, w6, h6, marker, 0, "C", "BLACK")
    return appendTextPDF(pdf, '', "C", "BLACK")

def formatNote(note, isPDF=False):
    if(isPDF):
        padding = ""
    else:
        padding = "-"

    if(len(note) == 1):
        return note + padding
    elif(len(note) == 2):
        return note
    elif(len(note) == 5):
        return note[3:]
    else:
        return note

def formatNotePDF(note):
    return formatNote(note, True)

def getColourFromInterval(interval):
    if(interval == intervalUnison):
        return 'BLACK'
    elif(interval == intervalMinorSecond):
        return 'PURPLE'
    elif(interval == intervalMajorSecond):
        return 'YELLOW_LIGHT'
    elif(interval == intervalMinorThird):
        return 'BLUE_LIGHT'
    elif(interval == intervalMajorThird):
        return 'ORANGE_LIGHT'
    elif(interval == intervalPerfectFourth):
        return 'YELLOW_DARK'
    elif(interval == intervalAugmentedFourthDiminishedFifth):
        return 'BLUE_DARK'
    elif(interval == intervalPerfectFifth):
        return 'ORANGE_DARK'
    elif(interval == intervalMinorSixth):
        return 'GREEN_LIGHT'
    elif(interval == intervalMajorSixth):
        return 'RED_LIGHT'
    elif(interval == intervalMinorSeventh):
        return 'GREEN_DARK'
    elif(interval == intervalMajorSeventh):
        return 'RED_DARK'
    elif(interval == intervalOctave):
        return 'BLACK'
    else:
        return 'WHITE'

def textColour(pdf, colour):
    if(colour == "BLACK"):
        pdf.set_text_color(0, 0, 0)
    elif(colour == "PURPLE"):
        pdf.set_text_color(102, 0, 204)
    elif(colour == "YELLOW_LIGHT"):
        pdf.set_text_color(255, 255, 153)
    elif(colour == "BLUE_LIGHT"):
        pdf.set_text_color(0, 204, 204)
    elif(colour == "ORANGE_LIGHT"):
        pdf.set_text_color(255, 178, 102)
    elif(colour == "YELLOW_DARK"):
        pdf.set_text_color(255, 255, 0)
    elif(colour == "BLUE_DARK"):
        pdf.set_text_color(0, 0, 255)
    elif(colour == "ORANGE_DARK"):
        pdf.set_text_color(255, 128, 0)
    elif(colour == "GREEN_LIGHT"):
        pdf.set_text_color(0, 204, 0)
    elif(colour == "RED_LIGHT"):
        pdf.set_text_color(255, 0, 0)
    elif(colour == "GREEN_DARK"):
        pdf.set_text_color(0, 153, 0)
    elif(colour == "RED_DARK"):
        pdf.set_text_color(204, 0, 0)
    elif(colour == "GREY_LIGHT"):
        pdf.set_text_color(224, 224, 224)
    elif(colour == "WHITE"):
        pdf.set_text_color(255, 255, 255)
    return pdf

def getInterval(note1, note2):
    interval = intervalUnison
    tmpNote = ""

    while(formatNote(tmpNote.replace(' ', '-')) != formatNote(note1.replace(' ', '-'))):
        tmpNote = next(notesList)

    while(formatNote(tmpNote.replace(' ', '-')) != formatNote(note2.replace(' ', '-'))):
        tmpNote = next(notesList)
        interval = interval + 1

    return interval % intervalOctave

def addInterval(note, interval):
    result = ""
    while(result != formatNotePDF(note)):
        result = formatNotePDF(next(notesList))
    for i in range(interval):
        result = formatNotePDF(next(notesList))
    return result

def splitScaleAcrossStrings(scale, stringCount, notesPerString, scaleIndex=0, includeAdjacentChromatics=False):
    scalePosition = [[0]*notesPerString for i in range(stringCount)]
    for string in range(stringCount):
        for currentNotePerString in range(notesPerString):

            # Normal Operation
            currentInterval = scale[scaleIndex]
            scalePosition[string][currentNotePerString]=currentInterval

            # Check Previous Interval
            previousNote = (12 + currentInterval - 1)%12
            if(includeAdjacentChromatics and previousNote in scale):
                scalePosition[string].append(previousNote)

            # Check Next Interval
            nextNote = (12 + currentInterval + 1)%12
            if(includeAdjacentChromatics and nextNote in scale):
                scalePosition[string].append(nextNote)
                currentNotePerString = currentNotePerString + 1
                scaleIndex = (scaleIndex + 1) % (len(scale) - 1)

            currentNotePerString = currentNotePerString + 1
            scaleIndex = (scaleIndex + 1) % (len(scale) - 1)

    return scalePosition

def printScalePosition(pdf, tuning, scalePosition, key, position, frets):
    if(position == 0):
        addPDFHeading2(pdf, "All Positions: ")
    else:
        addPDFHeading2(pdf, "Position: " + str(position))

    appendFretMarkersPDF(pdf, frets)

    for stringIterator, string in enumerate(tuning):
        stringNotes = scalePosition[stringIterator]

        note=formatNotePDF(string)

        for i in range(0, frets):
            interval = getInterval(key, note)

            if(interval in stringNotes):
                appendFretPDF(pdf, note, colour=getColourFromInterval(interval))
            else:
                appendFretPDF(pdf, note, colour='GREY_LIGHT')

            note = formatNotePDF(next(notesList))
        pdf = appendTextPDF(pdf=pdf, text='\n\n', align="C", colour="BLACK")

    appendFretMarkersPDF(pdf, frets)
    pdf = appendTextPDF(pdf=pdf, text='\n\n', align="L", colour="BLACK")

def printAllScalePositions(pdf, tuning, scaleName, key, frets):
    scale = scaleIntervals[scaleName]
    scaleLength = len(scale)
    if(scaleLength < 8):
        notesPerString = 2
    elif(scaleLength == 8):
        notesPerString = 3
    else:
        notesPerString = 4

    printScalePosition(pdf, tuning, splitScaleAcrossStrings(scale, 6, scaleLength, 0, False), key, 0, frets)

    for position in range(0, scaleLength - 1):
        if(scaleName == "Minor Blues" or scaleName == "Major Blues"):
            printScalePosition(pdf, tuning, splitScaleAcrossStrings(scale, 6, notesPerString, position, True), key, position + 1, frets)
        else:
            printScalePosition(pdf, tuning, splitScaleAcrossStrings(scale, 6, notesPerString, position, False), key, position + 1, frets)
        pdf = appendTextPDF(pdf=pdf, text='\n\n', align="L", colour="BLACK")
    return pdf

# TODO - Finish
def printChord(pdf, tuning, chordName, intervals, key, frets):
    addPDFHeading2(pdf, chordName)
    # printScalePosition(pdf, tuning, splitScaleAcrossStrings(intervals, 6, 1, 0, False), key, 0, frets)
    return pdf

def printAllChordsInScale(pdf, tuning, scaleName, key, frets):
    scale = scaleIntervals[scaleName]
    for chordName, intervals in chordIntervals.items():
        if(set(intervals).issubset(scale)):
            printChord(pdf, tuning, chordName, intervals, key, frets)
    return pdf

def createScaleDocument(tuningGuitarStandard, scaleName, key):
    pdf = createPDF()
    pdf = addPDFPage(pdf, key + " " + scaleName + " Scale")

    pdf = printAllScalePositions(pdf, tuningGuitarStandard, scaleName, key, 38)
    pdf = printAllChordsInScale(pdf, tuningGuitarStandard, scaleName, key, 38)

    pdf = appendScaleDescription(pdf, scaleName, key)

    filename = key + "_" + scaleName.replace(" ", "_").replace("/", "|") + "_" + time.strftime("%Y%m%d_%H%M%S") + ".pdf"

    print("Saving PDF: \"" + filename + "\"")
    savePDF(pdf, filename)

def createStandardScaleDocuments(tuning):
    for scaleName in scaleIntervals.keys():
        for key in notes:
            key = formatNotePDF(key)
            createScaleDocument(tuning, scaleName, key)

# createScaleDocument(tuningGuitarStandard, "Minor Blues", "A")
createStandardScaleDocuments(tuningGuitarStandard)

