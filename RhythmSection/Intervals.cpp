#include "Intervals.h"
#include "Definitions.h"

using namespace std;

Intervals * Intervals::intervalsInstance;

const string Intervals::Notes[] = { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };
const string Intervals::ScaleNames[] = { "Chromatic", "Major Pentatonic", "Minor Pentatonic", "Ionian", "Dorian", "Phrygian", "Lydian", "Mixolydian", "Aeolian", "Locrian" };

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

string Intervals::getScaleName( int scaleType ){ return Intervals::ScaleNames[ scaleType ]; }
int Scale::getScaleSize(){ return scaleSize; }
const int * Scale::getScaleType(){ return & scaleType; }
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

Scale Intervals::getScale( int scaleType ){

	Scale result( scaleType );

	return result;

}

void Scale::setScalePattern( int t ){

	scaleType = t;

	switch( t ){

		case SCALE_MAJOR_PENTATONIC:

			scalePattern = pentatonicMajorScale;
			scaleSize = INTERVALS_PENTATONIC_SCALE;

			break;

		case SCALE_MINOR_PENTATONIC:

			scalePattern = pentatonicMinorScale;
			scaleSize = INTERVALS_PENTATONIC_SCALE;

			break;

		case MODE_IONIAN:

			scalePattern = ionianMode;
			scaleSize = INTERVALS_DIATONIC_SCALE;

			break;

		case MODE_DORIAN:

			scalePattern = dorianMode;
			scaleSize = INTERVALS_DIATONIC_SCALE;

			break;

		case MODE_PHRYGIAN:

			scalePattern = phrygianMode;
			scaleSize = INTERVALS_DIATONIC_SCALE;

			break;

		case MODE_LYDIAN:

			scalePattern = lydianMode;
			scaleSize = INTERVALS_DIATONIC_SCALE;

			break;

		case MODE_MIXOLYDIAN:

			scalePattern = mixolydianMode;
			scaleSize = INTERVALS_DIATONIC_SCALE;

			break;

		case MODE_AEOLIAN:

			scalePattern = aeolianMode;
			scaleSize = INTERVALS_DIATONIC_SCALE;

			break;

		case MODE_LOCRIAN:

			scalePattern = locrianMode;
			scaleSize = INTERVALS_DIATONIC_SCALE;

			break;

		default:

			cout << endl << "DEFAULT" << endl << endl;

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

	cout << DIVIDER2 << endl;

}
