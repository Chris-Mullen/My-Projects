#include "RhythmSection.h"

using namespace std;

const string Double_Bass::OpenStrings[] = { "E1", "A1", "D2", "G2" };

void Double_Bass::addScale( const int scaleType ){ scales.push_back( Scale( scaleType ) ); }
void Double_Bass::addChord( const int chordType ){ chords.push_back( Chord( chordType ) ); }
void Double_Bass::playRoot(){ playNote( beatInstance -> getCurrentSection() -> getKeyIndex() ); }
void Double_Bass::playWAV( Mix_Chunk * wav, int stringChannel ){ Mix_PlayChannelTimed( stringChannel, wav, 0, sustain ); }
int Double_Bass::getScaleCount(){ return scales.size(); }
int Double_Bass::getChordCount(){ return chords.size(); }

void Double_Bass::nextRhythmPattern(){

	if( randomizeRyhthms ){

		currentRhythm = ( beatInstance -> pickRandom( 0, getRhythmPatternCount() ) );
		currentScale = ( beatInstance -> pickRandom( 0, getScaleCount() ) );
		currentChord = ( beatInstance -> pickRandom( 0, getChordCount() ) );

	}

	else{

		int rhythmPatternCount = getRhythmPatternCount();
		int scaleCount = getScaleCount();
		int chordCount = getChordCount();

		if( rhythmPatternCount ){ currentRhythm = ( ++currentRhythm ) % rhythmPatternCount; }
		else{ currentRhythm = 0; }

		if( scaleCount ){ currentScale = ( ++currentScale ) % scaleCount; }
		else{ currentScale = 0; }

		if( chordCount ){ currentChord = ( ++currentChord ) % chordCount; }
		else{ currentChord = 0; }

	}

}

void Double_Bass::printInfo(){

  cout << "\r\t\t" << DIVIDER3 << endl;
  cout << "\t\t" << "\"" << instrumentName << "\"" << endl;
	cout << "\r\t\t" << DIVIDER3 << endl;

	int keyIndex = beatInstance -> getCurrentSection() -> getKeyIndex();

	if( keyIndex < lowestInterval ){

		beatInstance -> addWarningMessage( instrumentName + ": Key ( " + Intervals::getIntervalName( keyIndex ) + " ) Out Of Range, Some Notes Will Be Missing. Lowest Note: " + Intervals::getIntervalName( lowestInterval ) );

	}

	if( rhythms.size() > 0 ){

		cout << "\t\tRhythms:";

		for( string tmpRhythm : rhythms ){

				cout << "\t" << tmpRhythm << endl << "\t\t\t";

		}

	}

	else{

		cout << "\t\tRhythms:\t[ NONE ]" << endl << "\t\t";

		beatInstance -> addWarningMessage( instrumentName + ": No Rhythms Added." );

	}

	cout << "\t" << DIVIDER2 << endl;

	cout << "\r\t\tOpen Strings:";

	for( int i = 0; i < channelCount; i++ ){

		cout << "\t" << OpenStrings[ i ] << ":\t" << Strings[ i ][ 0 ] << "\t[ " << ChannelNumbers[ i ] << " ]" << endl << "\t\t\t";

	}

	cout << "\t" << DIVIDER2 << endl;

	if( scales.size() > 0 ){

		cout << "\r\t\tScales( " << scales.size() << " ):\t";

		printScalesInfo();

	}

	else{

		cout << "\t\tScales:\t[ NONE ]" << endl << "\t\t";

		beatInstance -> addWarningMessage( instrumentName + ": No Scales Added." );

	}

	if( chords.size() > 0 ){

		cout << "\r\t\tChords( " << chords.size() << " ):\t";

		printChordsInfo();

	}

	else{

		cout << "\t\tChords:\t[ NONE ]" << endl << "\t\t";

		beatInstance -> addWarningMessage( instrumentName + ": No Chords Added." );

	}

}

void Double_Bass::printScalesInfo(){

	int keyIndex = beatInstance -> getCurrentSection() -> getKeyIndex();

	int scaleCount = scales.size();

	for( int i = 0; i < scaleCount; i++ ){

		scales[ i ].printInfo( keyIndex );

		if( keyIndex + ( * ( scales[ i ].getScalePattern() + scales[ i ].getScaleSize() - 1 ) ) > highestInterval ){

			beatInstance -> addWarningMessage( instrumentName + ": Key ( " + Intervals::getIntervalName( keyIndex ) + " ) Out Of Range, Some Notes Will Be Missing. Highest Note: " + Intervals::getIntervalName( highestInterval ) );

		}

	}

}

void Double_Bass::printChordsInfo(){

	int keyIndex = beatInstance -> getCurrentSection() -> getKeyIndex();

	int chordCount = chords.size();

	for( int i = 0; i < chordCount; i++ ){

		chords[ i ].printInfo( keyIndex );

		if( keyIndex + ( * ( chords[ i ].getChordPattern() + chords[ i ].getChordSize() - 1 ) ) > highestInterval ){

			beatInstance -> addWarningMessage( instrumentName + ": Key ( " + Intervals::getIntervalName( keyIndex ) + " ) Out Of Range, Some Notes Will Be Missing. Highest Note: " + Intervals::getIntervalName( highestInterval ) );

		}

	}

}

void Double_Bass::loadChannels(){

	ChannelNumbers[ 0 ] = Beat::getNextChannel();
	ChannelNumbers[ 1 ] = Beat::getNextChannel();
	ChannelNumbers[ 2 ] = Beat::getNextChannel();
	ChannelNumbers[ 3 ] = Beat::getNextChannel();

}

void Double_Bass::loadStrings(){

	GhostNote = Mix_LoadWAV( DB_GHOST );

	Strings[ 0 ][ 0 ] = Mix_LoadWAV( DB_E_0 );
	Strings[ 0 ][ 1 ] = Mix_LoadWAV( DB_E_1 );
	Strings[ 0 ][ 2 ] = Mix_LoadWAV( DB_E_2 );
	Strings[ 0 ][ 3 ] = Mix_LoadWAV( DB_E_3 );
	Strings[ 0 ][ 4 ] = Mix_LoadWAV( DB_E_4 );
	Strings[ 0 ][ 5 ] = Mix_LoadWAV( DB_E_5 );
	Strings[ 0 ][ 6 ] = Mix_LoadWAV( DB_E_6 );
	Strings[ 0 ][ 7 ] = Mix_LoadWAV( DB_E_7 );
	Strings[ 0 ][ 8 ] = Mix_LoadWAV( DB_E_8 );
	Strings[ 0 ][ 9 ] = Mix_LoadWAV( DB_E_9 );
	Strings[ 0 ][ 10 ] = Mix_LoadWAV( DB_E_10 );
	Strings[ 0 ][ 11 ] = Mix_LoadWAV( DB_E_11 );
	Strings[ 0 ][ 12 ] = Mix_LoadWAV( DB_E_12 );
	Strings[ 0 ][ 13 ] = Mix_LoadWAV( DB_E_13 );
	Strings[ 0 ][ 14 ] = Mix_LoadWAV( DB_E_14 );
	Strings[ 0 ][ 15 ] = Mix_LoadWAV( DB_E_15 );
	Strings[ 0 ][ 16 ] = Mix_LoadWAV( DB_E_16 );
	Strings[ 0 ][ 17 ] = Mix_LoadWAV( DB_E_17 );
	Strings[ 0 ][ 18 ] = Mix_LoadWAV( DB_E_18 );
	Strings[ 0 ][ 19 ] = Mix_LoadWAV( DB_E_19 );
	Strings[ 0 ][ 20 ] = Mix_LoadWAV( DB_E_20 );
	Strings[ 0 ][ 21 ] = Mix_LoadWAV( DB_E_21 );
	Strings[ 0 ][ 22 ] = Mix_LoadWAV( DB_E_22 );
	Strings[ 0 ][ 23 ] = Mix_LoadWAV( DB_E_23 );
	Strings[ 0 ][ 24 ] = Mix_LoadWAV( DB_E_24 );

	Strings[ 1 ][ 0 ] = Mix_LoadWAV( DB_A_0 );
	Strings[ 1 ][ 1 ] = Mix_LoadWAV( DB_A_1 );
	Strings[ 1 ][ 2 ] = Mix_LoadWAV( DB_A_2 );
	Strings[ 1 ][ 3 ] = Mix_LoadWAV( DB_A_3 );
	Strings[ 1 ][ 4 ] = Mix_LoadWAV( DB_A_4 );
	Strings[ 1 ][ 5 ] = Mix_LoadWAV( DB_A_5 );
	Strings[ 1 ][ 6 ] = Mix_LoadWAV( DB_A_6 );
	Strings[ 1 ][ 7 ] = Mix_LoadWAV( DB_A_7 );
	Strings[ 1 ][ 8 ] = Mix_LoadWAV( DB_A_8 );
	Strings[ 1 ][ 9 ] = Mix_LoadWAV( DB_A_9 );
	Strings[ 1 ][ 10 ] = Mix_LoadWAV( DB_A_10 );
	Strings[ 1 ][ 11 ] = Mix_LoadWAV( DB_A_11 );
	Strings[ 1 ][ 12 ] = Mix_LoadWAV( DB_A_12 );
	Strings[ 1 ][ 13 ] = Mix_LoadWAV( DB_A_13 );
	Strings[ 1 ][ 14 ] = Mix_LoadWAV( DB_A_14 );
	Strings[ 1 ][ 15 ] = Mix_LoadWAV( DB_A_15 );
	Strings[ 1 ][ 16 ] = Mix_LoadWAV( DB_A_16 );
	Strings[ 1 ][ 17 ] = Mix_LoadWAV( DB_A_17 );
	Strings[ 1 ][ 18 ] = Mix_LoadWAV( DB_A_18 );
	Strings[ 1 ][ 19 ] = Mix_LoadWAV( DB_A_19 );
	Strings[ 1 ][ 20 ] = Mix_LoadWAV( DB_A_20 );
	Strings[ 1 ][ 21 ] = Mix_LoadWAV( DB_A_21 );
	Strings[ 1 ][ 22 ] = Mix_LoadWAV( DB_A_22 );
	Strings[ 1 ][ 23 ] = Mix_LoadWAV( DB_A_23 );
	Strings[ 1 ][ 24 ] = Mix_LoadWAV( DB_A_24 );

	Strings[ 2 ][ 0 ] = Mix_LoadWAV( DB_D_0 );
	Strings[ 2 ][ 1 ] = Mix_LoadWAV( DB_D_1 );
	Strings[ 2 ][ 2 ] = Mix_LoadWAV( DB_D_2 );
	Strings[ 2 ][ 3 ] = Mix_LoadWAV( DB_D_3 );
	Strings[ 2 ][ 4 ] = Mix_LoadWAV( DB_D_4 );
	Strings[ 2 ][ 5 ] = Mix_LoadWAV( DB_D_5 );
	Strings[ 2 ][ 6 ] = Mix_LoadWAV( DB_D_6 );
	Strings[ 2 ][ 7 ] = Mix_LoadWAV( DB_D_7 );
	Strings[ 2 ][ 8 ] = Mix_LoadWAV( DB_D_8 );
	Strings[ 2 ][ 9 ] = Mix_LoadWAV( DB_D_9 );
	Strings[ 2 ][ 10 ] = Mix_LoadWAV( DB_D_10 );
	Strings[ 2 ][ 11 ] = Mix_LoadWAV( DB_D_11 );
	Strings[ 2 ][ 12 ] = Mix_LoadWAV( DB_D_12 );
	Strings[ 2 ][ 13 ] = Mix_LoadWAV( DB_D_13 );
	Strings[ 2 ][ 14 ] = Mix_LoadWAV( DB_D_14 );
	Strings[ 2 ][ 15 ] = Mix_LoadWAV( DB_D_15 );
	Strings[ 2 ][ 16 ] = Mix_LoadWAV( DB_D_16 );
	Strings[ 2 ][ 17 ] = Mix_LoadWAV( DB_D_17 );
	Strings[ 2 ][ 18 ] = Mix_LoadWAV( DB_D_18 );
	Strings[ 2 ][ 19 ] = Mix_LoadWAV( DB_D_19 );
	Strings[ 2 ][ 20 ] = Mix_LoadWAV( DB_D_20 );
	Strings[ 2 ][ 21 ] = Mix_LoadWAV( DB_D_21 );
	Strings[ 2 ][ 22 ] = Mix_LoadWAV( DB_D_22 );
	Strings[ 2 ][ 23 ] = Mix_LoadWAV( DB_D_23 );
	Strings[ 2 ][ 24 ] = Mix_LoadWAV( DB_D_24 );

	Strings[ 3 ][ 0 ] = Mix_LoadWAV( DB_G_0 );
	Strings[ 3 ][ 1 ] = Mix_LoadWAV( DB_G_1 );
	Strings[ 3 ][ 2 ] = Mix_LoadWAV( DB_G_2 );
	Strings[ 3 ][ 3 ] = Mix_LoadWAV( DB_G_3 );
	Strings[ 3 ][ 4 ] = Mix_LoadWAV( DB_G_4 );
	Strings[ 3 ][ 5 ] = Mix_LoadWAV( DB_G_5 );
	Strings[ 3 ][ 6 ] = Mix_LoadWAV( DB_G_6 );
	Strings[ 3 ][ 7 ] = Mix_LoadWAV( DB_G_7 );
	Strings[ 3 ][ 8 ] = Mix_LoadWAV( DB_G_8 );
	Strings[ 3 ][ 9 ] = Mix_LoadWAV( DB_G_9 );
	Strings[ 3 ][ 10 ] = Mix_LoadWAV( DB_G_10 );
	Strings[ 3 ][ 11 ] = Mix_LoadWAV( DB_G_11 );
	Strings[ 3 ][ 12 ] = Mix_LoadWAV( DB_G_12 );
	Strings[ 3 ][ 13 ] = Mix_LoadWAV( DB_G_13 );
	Strings[ 3 ][ 14 ] = Mix_LoadWAV( DB_G_14 );
	Strings[ 3 ][ 15 ] = Mix_LoadWAV( DB_G_15 );
	Strings[ 3 ][ 16 ] = Mix_LoadWAV( DB_G_16 );
	Strings[ 3 ][ 17 ] = Mix_LoadWAV( DB_G_17 );
	Strings[ 3 ][ 18 ] = Mix_LoadWAV( DB_G_18 );
	Strings[ 3 ][ 19 ] = Mix_LoadWAV( DB_G_19 );
	Strings[ 3 ][ 20 ] = Mix_LoadWAV( DB_G_20 );
	Strings[ 3 ][ 21 ] = Mix_LoadWAV( DB_G_21 );
	Strings[ 3 ][ 22 ] = Mix_LoadWAV( DB_G_22 );
	Strings[ 3 ][ 23 ] = Mix_LoadWAV( DB_G_23 );
	Strings[ 3 ][ 24 ] = Mix_LoadWAV( DB_G_24 );

}

void Double_Bass::unloadStrings(){

	Mix_FreeChunk( GhostNote );

	for( int i = 0; i < channelCount; i++ ){

		for( int j = 0; j < fretCount; j++ ){

			Mix_FreeChunk( Strings[ i ][ j ] );

		}

	}

}

void Double_Bass::play(){

	int rhythmIndex = beatInstance -> getRhythmIndex();
	int keyIndex = beatInstance -> getCurrentSection() -> getKeyIndex();
	char currentChar = rhythms[ currentRhythm ][ rhythmIndex ];
	int currentInterval = ( int )( currentChar - '0' );

	currentInterval %= scales[ currentScale ].getScaleSize();

	if( isdigit( currentChar ) ){

		if( keyIndex == -1 ){

			playNote( lowestInterval );

		}

		else{

			playNote( * ( scales[ currentScale ].getScalePattern() + currentInterval ) + keyIndex );

		}

	}

	else if( rhythms[ currentRhythm ][ rhythmIndex ] == 'C' ){

		playChord( keyIndex, & chords.at( currentChord ) );

	}

	else if( rhythms[ currentRhythm ][ rhythmIndex ] == 'X' ){

		playGhostNote();

	}

	else if( rhythms[ currentRhythm ][ rhythmIndex ] == 'R' ){

		playRoot();

	}

	else if( rhythms[ currentRhythm ][ rhythmIndex ] == 'I' ){

		improvise();

	}

}

void Double_Bass::playNote( const int noteIndex ){ playNote( Intervals::getIntervalName( noteIndex ) ); }

void Double_Bass::playNote( string noteName ){

	for( int i = 0; i < fretCount; i++ ){

		for( int j = 0; j < channelCount; j++ ){

			if( Intervals::getIntervalName( Intervals::getIntervalIndex( OpenStrings[ j ] ) + i ) == noteName ){

				beatInstance -> lastBassNote = noteName.substr( 0, noteName.size() - 1 );

				lastStringPlayed = j;

				thread t1( & Double_Bass::playWAV, this, Strings[ j ][ i ], ChannelNumbers[ j ] );
				t1.join();

				return;

			}

		}

	}

}

void Double_Bass::playNote( int noteIndex, int channelNo ){

	string noteName = Intervals::getIntervalName( noteIndex );

	for( int i = 0; i < fretCount; i++ ){

		if( ( Intervals::getIntervalIndex( OpenStrings[ channelNo ] ) + i ) == noteIndex ){

			beatInstance -> lastBassNote = noteName.substr( 0, noteName.size() - 1 );

			lastStringPlayed = channelNo;

			thread t1( & Double_Bass::playWAV, this, Strings[ channelNo ][ i ], ChannelNumbers[ channelNo ] );
			t1.join();

			return;

		}

		else if( ( Intervals::getIntervalIndex( OpenStrings[ channelNo ] ) + i ) % INTERVAL_PERFECT_OCTAVE == noteIndex % INTERVAL_PERFECT_OCTAVE ){

			beatInstance -> lastBassNote = noteName.substr( 0, noteName.size() - 1 );

			lastStringPlayed = channelNo;

			thread t1( & Double_Bass::playWAV, this, Strings[ channelNo ][ i ], ChannelNumbers[ channelNo ] );
			t1.join();

			return;

		}

	}

}

void Double_Bass::playArpeggio( string keyName, Scale s ){

	playArpeggio( keyName, s, 1 );

}

void Double_Bass::playArpeggio( string keyName, Scale s, int octaves ){

	int scaleSize = s.getScaleSize();
	int keyIndex = Intervals::getIntervalIndex( keyName );
	int const * scalePattern = s.getScalePattern();
	int const * scale = scalePattern;

	for( int i = 0; i < octaves; i++ ){

		for( int j = 0; j < scaleSize; j++ ){

			this -> playNote( * scale + ( keyIndex + ( i * INTERVAL_PERFECT_OCTAVE ) ) );
			rest( 1000000000 );

			++scale;

		}

		scale = scalePattern;

	}

}

void Double_Bass::playChord( int keyIndex, Chord * c ){

	playChord( keyIndex, c, 1 );

}

void Double_Bass::playChord( int keyIndex, Chord * c, int octaves ){

	int chordSize = c -> getChordSize();
	int const * chordPattern = c -> getChordPattern();
	int const * chord = chordPattern;
	string keyName = Intervals::getIntervalName( keyIndex );

	beatInstance -> lastBassNote = keyName.substr( 0, keyName.size() - 1 );

	for( int i = 0; i < octaves; i++ ){

		for( int j = 0; j < chordSize && j < channelCount; j++ ){

			this -> playNote( * chord + ( keyIndex + ( i * INTERVAL_PERFECT_OCTAVE ) ), j );

			rest( strumSpeed );

			++chord;

		}

		chord = chordPattern;

	}

}

void Double_Bass::improvise(){

	int keyIndex = beatInstance -> getCurrentSection() -> getKeyIndex();

	const int * scalePattern;

	int randomScale = ( beatInstance -> pickRandom( 0, getScaleCount() ) );
	int randomScaleNote = ( beatInstance -> pickRandom( 0, scales[ randomScale ].getScaleSize() ) );

	scalePattern = scales[ randomScale ].getScalePattern();

	scalePattern += randomScaleNote;

	if( beatInstance -> pickRandom( 0, IMPROV_CHORD_RATIO ) != 0 ){

		playNote( ( * scalePattern + keyIndex ) );

	}

	else{

		int randomChord = ( beatInstance -> pickRandom( 0, getChordCount() ) );

		playChord( keyIndex + randomScaleNote, & chords[ randomChord ] );

	}

}

void Double_Bass::playGhostNote(){

	beatInstance -> lastBassNote = "X";

	thread t1( & Double_Bass::playWAV, this, GhostNote, ChannelNumbers[ lastStringPlayed ] );
	t1.detach();

}
