#ifndef INTERVALS_H
#define INTERVALS_H

#include <iostream>
#include <string>
#include <vector>

//Scales
const int SCALE_CHROMATIC = 0;

const int SCALE_MAJOR_PENTATONIC = 1;
const int SCALE_MINOR_PENTATONIC = 2;

const int MODE_IONIAN = 3;
const int MODE_DORIAN = 4;
const int MODE_PHRYGIAN = 5;
const int MODE_LYDIAN = 6;
const int MODE_MIXOLYDIAN = 7;
const int MODE_AEOLIAN = 8;
const int MODE_LOCRIAN = 9;

const int SCALE_MAJOR = MODE_IONIAN;	//Synonym
const int SCALE_MINOR = MODE_AEOLIAN;	//Synonym

//Chords
const int CHORD_MAJOR_TRIAD = 0;
const int CHORD_MINOR_TRIAD = 1;
const int CHORD_FIFTH = 2;
const int CHORD_SEVENTH = 3;
const int CHORD_MAJOR_SEVENTH = 4;
const int CHORD_MINOR_SEVENTH = 5;
const int CHORD_DOMINANT_SEVENTH = 6;
const int CHORD_SUSPENDED_FOURTH = 7;
const int CHORD_MAJOR_ADD_NINE = 8;
const int CHORD_SUSPENDED_SECOND = 9;
const int CHORD_SEVEN_SUSPENDED_FOURTH = 10;
const int CHORD_SEVEN_SHARP_NINTH = 11;
const int CHORD_NINTH = 12;

//Intervals
const int INTERVAL_PERFECT_UNISON = 0;
const int INTERVAL_MINOR_SECOND = 1;
const int INTERVAL_MAJOR_SECOND = 2;
const int INTERVAL_MINOR_THIRD = 3;
const int INTERVAL_MAJOR_THIRD = 4;
const int INTERVAL_PERFECT_FOURTH = 5;
const int INTERVAL_DIMINISHED_FIFTH = 6;
const int INTERVAL_PERFECT_FIFTH = 7;
const int INTERVAL_MINOR_SIXTH = 8;
const int INTERVAL_MAJOR_SIXTH = 9;
const int INTERVAL_MINOR_SEVENTH = 10;
const int INTERVAL_MAJOR_SEVENTH = 11;
const int INTERVAL_PERFECT_OCTAVE = 12;

const int INTERVALS_DIAD = 2;
const int INTERVALS_TRIAD = 3;
const int INTERVALS_TETRATONIC = 4;
const int INTERVALS_PENTATONIC = 5;
const int INTERVALS_HEXATONIC = 6;
const int INTERVALS_DIATONIC = 7;
const int INTERVALS_OCTATONIC = 8;
const int INTERVALS_NONATONIC = 9;

class Scale;

class Intervals{

public:

	Intervals(){

		std::cout << "Intervals()" << std::endl;

		calculateNoteNames();

	}

	~Intervals(){ std::cout << "~Intervals()" << std::endl; }

	static Intervals * intervalsInstance;

	//Scales
	static const int chromaticScale[];
	static const int pentatonicMajorScale[];
	static const int pentatonicMinorScale[];

	static const int ionianMode[];
	static const int dorianMode[];
	static const int phrygianMode[];
	static const int lydianMode[];
	static const int mixolydianMode[];
	static const int aeolianMode[];
	static const int locrianMode[];

	//Chords
	static const int MajorTriadChord[];
	static const int MinorTriadChord[];

	static const int FifthChord[];
	static const int SeventhChord[];
	static const int MajorSeventhChord[];
	static const int MinorSeventhChord[];
	static const int DominantSeventhChord[];
	static const int SuspendedFourthChord[];
	static const int MajorAddNineChord[];
	static const int SuspendedSecondChord[];
	static const int SevenSuspendedFourthChord[];
	static const int SevenSharpNinthChord[];
	static const int NinthChord[];

	const static std::string Notes[];
	const static std::string ScaleNames[];
	const static std::string ChordNames[];
	std::string getScaleName( int scaleType );

	static int getIntervalIndex( std::string noteName );
	static std::string getIntervalName( int noteIndex );
	static std::string getIntervalLabel( int semitones );

	void calculateNoteNames();
	void printInfo();

private:

	const int totalOctaves = 8;
	std::vector< std::string > noteNames;

};

class Scale : public Intervals{

public:

	Scale(){

			std::cout << "Scale()" << std::endl;

			setScalePattern( SCALE_CHROMATIC );

	}

	Scale( int scaleType ){

		std::cout << "Scale()" << std::endl;

		setScalePattern( scaleType );

	}

	~Scale(){ std::cout << "~Scale()" << std::endl; }

	void printInfo();
	void printInfo( int rootIndex );
	void setScalePattern( const int t );
	int getScaleSize();
	int * getScaleType();
	int const * getScalePattern();

private:

	int scaleType;
	int scaleSize;

	const int * scalePattern;

};

class Chord: public Scale{

public:

	Chord(){

			std::cout << "Chord()" << std::endl;

			setChordPattern( CHORD_MAJOR_TRIAD );

		}

	Chord( int chordType ){

		std::cout << "Chord()" << std::endl;

		setChordPattern( chordType );

	}

	~Chord(){ std::cout << "~Chord()" << std::endl; }

	void printInfo( int rootIndex );
	void setChordPattern( const int t );
	int getChordSize();
	int const * getChordPattern();

private:

	int chordType;
	int chordSize;

	const int * chordPattern;

};

#endif
