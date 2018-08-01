#ifndef INTERVALS_H
#define INTERVALS_H

#include <iostream>
#include <string>
#include <vector>

const int SCALE_TYPE_DRUMKIT = -1;	//Special Scale Type Used To Sequence Drum Beats
const int SCALE_TYPE_ROOT_ONLY = -2;	//Special Scale Type Used To Sequence Drum Beats

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

const int INTERVALS_PENTATONIC_SCALE = 5;
const int INTERVALS_HEXATONIC_SCALE = 6;
const int INTERVALS_DIATONIC_SCALE = 7;

class Scale;

class Intervals{

public:

	Intervals(){

		std::cout << "Intervals()" << std::endl;

		calculateNoteNames();

	}

	~Intervals(){ std::cout << "~Intervals()" << std::endl; }

	static Intervals * intervalsInstance;

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

	const static std::string Notes[];
	const static std::string ScaleNames[];
	static Scale getScale( int scaleType );
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

	Scale() : scaleType( 0 ){

			std::cout << "Scale()" << std::endl;

			setScalePattern( SCALE_CHROMATIC );

		}

	Scale( int scaleType ){

		std::cout << "Scale()" << std::endl;

		setScalePattern( scaleType );

	}

	Scale( std::string n, const int scaleType ){

			std::cout << "Scale()" << std::endl;

			setScalePattern( scaleType );

	}

	Scale( int r, std::string n, const int scaleType ){

			std::cout << "Scale()" << std::endl;

			setScalePattern( scaleType );

	}

	~Scale(){ std::cout << "~Scale()" << std::endl; }

	void printInfo();
	void printInfo( int rootIndex );
	void setScalePattern( const int t );
	int getScaleSize();
	const int * getScaleType();
	int const * getScalePattern();

private:

	int scaleType;
	int scaleSize;

	const int * scalePattern;

};

#endif
