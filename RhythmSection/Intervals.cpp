#include "Intervals.h"
#include "Definitions.h"

using namespace std;

Intervals * Intervals::intervalsInstance;

const string Intervals::Notes[] = { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };
const string Intervals::ScaleNames[] = { "Chromatic", "Major Pentatonic", "Minor Pentatonic", "Ionian", "Dorian", "Phrygian", "Lydian", "Mixolydian", "Aeolian", "Locrian" };
const string Intervals::ChordNames[] = { "Major Triad", "Minor Triad", "Fifth", "Seventh", "Major Seventh", "Minor Seventh", "Dominant Seventh", "Suspended Fourth", "Major Add Nine", "Suspended Second", "Seven Suspended Fourth", "Seven Sharp Ninth", "Ninth" };

const int Intervals::chromaticScale[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MINOR_SECOND,
	INTERVAL_MAJOR_SECOND,
	INTERVAL_MINOR_THIRD,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_PERFECT_FOURTH,
	INTERVAL_DIMINISHED_FIFTH,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MINOR_SIXTH,
	INTERVAL_MAJOR_SIXTH,
	INTERVAL_MINOR_SEVENTH,
	INTERVAL_MAJOR_SEVENTH };

const int Intervals::pentatonicMajorScale[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_SECOND,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MAJOR_SIXTH };

const int Intervals::pentatonicMinorScale[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MINOR_THIRD,
	INTERVAL_PERFECT_FOURTH,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MINOR_SEVENTH };

const int Intervals::ionianMode[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_SECOND,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_PERFECT_FOURTH,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MAJOR_SIXTH,
	INTERVAL_MAJOR_SEVENTH };

const int Intervals::dorianMode[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_SECOND,
	INTERVAL_MINOR_THIRD,
	INTERVAL_PERFECT_FOURTH,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MAJOR_SIXTH,
	INTERVAL_MINOR_SEVENTH };

const int Intervals::phrygianMode[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MINOR_SECOND,
	INTERVAL_MINOR_THIRD,
	INTERVAL_PERFECT_FOURTH,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MINOR_SIXTH,
	INTERVAL_MINOR_SEVENTH };

const int Intervals::lydianMode[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_SECOND,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_DIMINISHED_FIFTH,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MAJOR_SIXTH,
	INTERVAL_MAJOR_SEVENTH };

const int Intervals::mixolydianMode[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_SECOND,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_PERFECT_FOURTH,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MAJOR_SIXTH,
	INTERVAL_MINOR_SEVENTH };

const int Intervals::aeolianMode[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_SECOND,
	INTERVAL_MINOR_THIRD,
	INTERVAL_PERFECT_FOURTH,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MINOR_SIXTH,
	INTERVAL_MINOR_SEVENTH };

const int Intervals::locrianMode[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MINOR_SECOND,
	INTERVAL_MINOR_THIRD,
	INTERVAL_PERFECT_FOURTH,
	INTERVAL_DIMINISHED_FIFTH,
	INTERVAL_MINOR_SIXTH,
	INTERVAL_MINOR_SEVENTH };

//Chords
const int Intervals::MajorTriadChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_PERFECT_FIFTH };

const int Intervals::MinorTriadChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MINOR_THIRD,
	INTERVAL_PERFECT_FIFTH };

const int Intervals::FifthChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_PERFECT_FIFTH };

const int Intervals::SeventhChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_MINOR_SEVENTH };

const int Intervals::MajorSeventhChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MAJOR_SEVENTH };

const int Intervals::MinorSeventhChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MINOR_THIRD,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MINOR_SEVENTH };

const int Intervals::DominantSeventhChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MINOR_SEVENTH };

const int Intervals::SuspendedFourthChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MINOR_SECOND,
	INTERVAL_PERFECT_FOURTH };

const int Intervals::MajorAddNineChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_SECOND,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_PERFECT_FIFTH };

const int Intervals::SuspendedSecondChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MINOR_SECOND,
	INTERVAL_PERFECT_FIFTH };

const int Intervals::SevenSuspendedFourthChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_PERFECT_FOURTH,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MINOR_SEVENTH };

const int Intervals::SevenSharpNinthChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MINOR_THIRD,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_MINOR_SEVENTH };

const int Intervals::NinthChord[] = {
	INTERVAL_PERFECT_UNISON,
	INTERVAL_MAJOR_SECOND,
	INTERVAL_MAJOR_THIRD,
	INTERVAL_PERFECT_FIFTH,
	INTERVAL_MINOR_SEVENTH };

string Intervals::getScaleName( int scaleType ){ return Intervals::ScaleNames[ scaleType ]; }
int Scale::getScaleSize(){ return scaleSize; }
int * Scale::getScaleType(){ return & scaleType; }
int const * Scale::getScalePattern(){ return scalePattern; }

void Intervals::calculateNoteNames(){

	for( int i = 0; i <= totalOctaves; i++ ){

		for( int j = 0; j < INTERVAL_PERFECT_OCTAVE; j++ ){

			noteNames.push_back( Notes[ j ] + to_string( i ) );

		}

	}

}

int Intervals::getIntervalIndex( string noteName ){

	int sharp = 0;	//Used To Increment Or Decrement Index Depending On Whether noteName Contains A Sharp: '#', Or A Flat: 'b'

	int octave = ( int )( noteName.back() - '0' );

	noteName.pop_back();	//Remove Octave Number

	if( noteName[ 1 ] == '#' ){

		cout << noteName << endl;

		noteName.pop_back();	//Remove #

		sharp++;

	}

	else if( noteName[ 1 ] == 'b' ){

		cout << noteName << endl;

		noteName.pop_back();	//Remove b

		sharp--;

	}

	for( int i = 0; i < INTERVAL_PERFECT_OCTAVE; i++ ){

		if( Notes[ i ] == noteName ){

			return ( octave * INTERVAL_PERFECT_OCTAVE ) + i + sharp;

		}

	}

	return -1;

}

string Intervals::getIntervalName( int noteIndex ){

	return intervalsInstance -> noteNames.at( noteIndex );

}

string Intervals::getIntervalLabel( int semitones ){

	switch( semitones ){

		case INTERVAL_PERFECT_UNISON:

			return "Perfect Unison";

			break;

		case INTERVAL_MINOR_SECOND:

			return "Minor Second";

			break;

		case INTERVAL_MAJOR_SECOND:

			return "Major Second";

			break;

		case INTERVAL_MINOR_THIRD:

			return "Minor Third";

			break;

		case INTERVAL_MAJOR_THIRD:

			return "Major Third";

			break;

		case INTERVAL_PERFECT_FOURTH:

		return "Perfect Fourth";

			break;

		case INTERVAL_DIMINISHED_FIFTH:

		return "Diminished Fifth / Augmented Fourth";

			break;

		case INTERVAL_PERFECT_FIFTH:

		return "Perfect Fifth";

			break;

		case INTERVAL_MINOR_SIXTH:

		return "Minor Sixth";

			break;

		case INTERVAL_MAJOR_SIXTH:

		return "Major Sixth";

			break;

		case INTERVAL_MINOR_SEVENTH:

		return "Minor Seventh";

			break;

		case INTERVAL_MAJOR_SEVENTH:

		return "Major Seventh";

			break;

		case INTERVAL_PERFECT_OCTAVE:

			return "Perfect Octave";

			break;

		default:

			return "Unknown Interval";

			break;

	}

}

void Scale::setScalePattern( int t ){

	scaleType = t;

	switch( t ){

		case SCALE_MAJOR_PENTATONIC:

			scalePattern = pentatonicMajorScale;
			scaleSize = INTERVALS_PENTATONIC;

			break;

		case SCALE_MINOR_PENTATONIC:

			scalePattern = pentatonicMinorScale;
			scaleSize = INTERVALS_PENTATONIC;

			break;

		case MODE_IONIAN:

			scalePattern = ionianMode;
			scaleSize = INTERVALS_DIATONIC;

			break;

		case MODE_DORIAN:

			scalePattern = dorianMode;
			scaleSize = INTERVALS_DIATONIC;

			break;

		case MODE_PHRYGIAN:

			scalePattern = phrygianMode;
			scaleSize = INTERVALS_DIATONIC;

			break;

		case MODE_LYDIAN:

			scalePattern = lydianMode;
			scaleSize = INTERVALS_DIATONIC;

			break;

		case MODE_MIXOLYDIAN:

			scalePattern = mixolydianMode;
			scaleSize = INTERVALS_DIATONIC;

			break;

		case MODE_AEOLIAN:

			scalePattern = aeolianMode;
			scaleSize = INTERVALS_DIATONIC;

			break;

		case MODE_LOCRIAN:

			scalePattern = locrianMode;
			scaleSize = INTERVALS_DIATONIC;

			break;

		default:

			scalePattern = chromaticScale;
			scaleSize = INTERVAL_PERFECT_OCTAVE;
			scaleType = SCALE_CHROMATIC;

			break;

	}

}

void Scale::printInfo(){

	cout << Intervals::ScaleNames[ scaleType ] << " Scale\t\t[ " << scaleSize << " Notes ]" << endl << "\t\t\t\t";

	int tmpInterval;

	for( int i = 0; i < scaleSize; i++ ){

		tmpInterval = * ( scalePattern + i );

		cout << "\t" << getIntervalLabel( tmpInterval ) << "\t\t[ " << tmpInterval << " Semitones ]" << endl << "\t\t\t\t";

	}

	cout << DIVIDER2 << endl;

}

void Scale::printInfo( int rootIndex ){

	cout << Intervals::ScaleNames[ scaleType ] << " Scale\t\t[ " << scaleSize << " Notes ]" << endl << "\t\t\t\t";

	int tmpInterval;

	for( int i = 0; i < scaleSize; i++ ){

		tmpInterval = * ( scalePattern + i );

		cout << "\t" << getIntervalLabel( tmpInterval ) << "\t( " << getIntervalName( rootIndex + tmpInterval ) << " )\t[ " << tmpInterval << " Semitones ]" << endl << "\t\t\t\t";

	}

	cout << DIVIDER2 << endl << "\t\t\t\t";

}

int Chord::getChordSize(){ return chordSize; }
int const * Chord::getChordPattern(){ return chordPattern; }

void Chord::printInfo( int rootIndex ){

	cout << Intervals::ChordNames[ chordType ] << " Chord\t\t[ " << chordSize << " Notes ]" << endl << "\t\t\t\t";

	int tmpInterval;

	for( int i = 0; i < chordSize; i++ ){

		tmpInterval = * ( chordPattern + i );

		cout << "\t" << getIntervalLabel( tmpInterval ) << "\t( " << getIntervalName( rootIndex + tmpInterval ) << " )\t[ " << tmpInterval << " Semitones ]" << endl << "\t\t\t\t";

	}

	cout << DIVIDER2 << endl << "\t\t\t\t";

}

void Chord::setChordPattern( int t ){

	chordType = t;

	switch( t ){

		case CHORD_MAJOR_TRIAD:

			chordPattern = MajorTriadChord;
			chordSize = INTERVALS_TRIAD;

			break;

		case CHORD_MINOR_TRIAD:

			chordPattern = MinorTriadChord;
			chordSize = INTERVALS_TRIAD;

			break;

		case CHORD_FIFTH:

			chordPattern = FifthChord;
			chordSize = INTERVALS_DIAD;

			break;

		case CHORD_SEVENTH:

			chordPattern = SeventhChord;
			chordSize = INTERVALS_TRIAD;

			break;

		case CHORD_MAJOR_SEVENTH:

			chordPattern = MajorSeventhChord;
			chordSize = INTERVALS_TETRATONIC;

			break;

		case CHORD_MINOR_SEVENTH:

			chordPattern = MinorSeventhChord;
			chordSize = INTERVALS_TETRATONIC;

			break;

		case CHORD_DOMINANT_SEVENTH:

			chordPattern = DominantSeventhChord;
			chordSize = INTERVALS_TETRATONIC;

			break;

		case CHORD_SUSPENDED_FOURTH:

			chordPattern = SuspendedFourthChord;
			chordSize = INTERVALS_TRIAD;

			break;

		case CHORD_MAJOR_ADD_NINE:

			chordPattern = MajorAddNineChord;
			chordSize = INTERVALS_TETRATONIC;

			break;

		case CHORD_SUSPENDED_SECOND:

			chordPattern = SuspendedSecondChord;
			chordSize = INTERVALS_TRIAD;

			break;

		case CHORD_SEVEN_SUSPENDED_FOURTH:

			chordPattern = SevenSuspendedFourthChord;
			chordSize = INTERVALS_TETRATONIC;

			break;

		case CHORD_SEVEN_SHARP_NINTH:

			chordPattern = SevenSharpNinthChord;
			chordSize = INTERVALS_TETRATONIC;

			break;

		case CHORD_NINTH:

			chordPattern = NinthChord;
			chordSize = INTERVALS_PENTATONIC;

			break;

		default:

			chordPattern = MajorTriadChord;
			chordSize = INTERVALS_TRIAD;
			chordType = CHORD_MAJOR_TRIAD;

			break;

	}

}
