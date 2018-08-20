#include "RhythmSection.h"

using namespace std;

/*
reset; rm RhythmSection.out; g++ -std=c++11 -pthread main.cpp Intervals.cpp Beat.cpp Section.cpp Instrument.cpp Drum_Kit.cpp Double_Bass.cpp -o RhythmSection.out -lSDL2_mixer $(pkg-config --cflags --libs sdl2); ./RhythmSection.out 90 4.4 A1
*/

//Initialize SDL Library
void initSDL(){

  if( SDL_Init( SDL_INIT_AUDIO ) < 0 ) exit( 1 );

  if( Mix_OpenAudio( SDL_SAMPLE_FREQUENCY, MIX_DEFAULT_FORMAT, 2, SDL_BUFFER_SIZE ) == -1 ) exit( 1 );

  Mix_AllocateChannels( SDL_RESERVED_CHANNELS );

}

void closeSDL(){

  Mix_HaltChannel( -1 );
  Mix_AllocateChannels( 0 );
  Mix_CloseAudio();
  SDL_Quit();

}

void demo_12BB_Shuffle( int BPM, float timeSignature, string key, int subDivisions ){

	Intervals intervals;
	intervals.intervalsInstance = & intervals;

	Beat beat1( BPM, timeSignature, 0, "Twelve Bar Blues In " + key, subDivisions );

	beat1.beatInstance = & beat1;

	//Check For Uncommon Key Names ( Special Cases: B# = C, Cb = B, E# = F, Fb = E )
	string tmpKey = key;
	tmpKey.pop_back();

	if( tmpKey == "B#" || tmpKey == "E#" || tmpKey == "Cb" || tmpKey == "Fb" ){

		beat1.addWarningMessage( key + ": Uncommon Note Name: " + tmpKey );

	}

	Drum_Kit D_1( "Drums_1" );
	Drum_Kit D_2( "Drums_2" );
	Double_Bass DB_1( "Double_Bass_1" );
	Double_Bass DB_2( "Double_Bass_2" );

	D_1.addChannel( KICK_DRUM, "Kick_Drum", 80 );
	D_1.addChannel( SNARE_DRUM_1, "Snare_Drum", 40 );
	D_1.addChannel( SNARE_BRUSH_2, "Snare_Ghost" );
	D_1.addChannel( HIGH_HAT_CLOSED, "High_Hat_Closed", 20 );

	D_2.addChannel( KICK_DRUM, "Kick_Drum" );
	D_2.addChannel( HIGH_HAT_CLOSED, "High_Hat_Closed", 40 );
	D_2.addChannel( HIGH_HAT_OPEN, "High_Hat_Open", 40 );
	D_1.addChannel( SNARE_DRUM_2, "Snare_Drum", 50 );
	D_2.addChannel( CRASH_CYMBAL, "Crash_Cymbal", 50 );
	D_2.addChannel( RIDE_CYMBAL, "Ride_Cymbal", 40 );
	D_2.addChannel( COW_BELL, "More_Cowbell", 50 );

	DB_1.addScale( SCALE_MINOR_PENTATONIC );
	DB_2.addScale( SCALE_MINOR_PENTATONIC );

	DB_1.addChord( CHORD_MINOR_TRIAD );
	DB_2.addChord( CHORD_MINOR_TRIAD );

	D_1.addRhythm( beat1.generateRhythm() );
	D_2.addRhythm( beat1.generateRhythm() );

	DB_1.addRhythm( beat1.generateRhythm() );
	DB_1.addRhythm( beat1.generateRhythm( 'C' ) );
	DB_1.addRhythm( beat1.generateRhythm( 'I' ) );
	DB_1.addRhythm( beat1.generateRhythm( 'C', 2 ) );
	DB_1.addRhythm( beat1.generateRhythm( 'I', 2 ) );
	DB_1.addRhythm( beat1.generateRiffs( INTERVALS_PENTATONIC ) );

	for( int i = 0; i < 10; i++ ){

		vector< string > tmpCompositeRhythm;
		tmpCompositeRhythm.push_back( "3-----3-" );
		tmpCompositeRhythm.push_back( beat1.generateRhythm( STYLE_SHUFFLE ) );

		D_1.addRhythm( tmpCompositeRhythm );
		D_2.addRhythm( tmpCompositeRhythm );
		D_2.addRhythm( beat1.generateRiffs( D_2.getChannelCount() ) );

		DB_1.addRhythm( beat1.generateRhythm( STYLE_SHUFFLE, INTERVALS_PENTATONIC ) );
		DB_2.addRhythm( beat1.generateRiffs( INTERVALS_PENTATONIC ) );

	}

	string IV_Chord = Intervals::getIntervalName( Intervals::getIntervalIndex( key ) + 5 );
	string V_Chord = Intervals::getIntervalName( Intervals::getIntervalIndex( key ) + 7 );

	Section section1( "I Chord", key, 4 );
	Section section2( "IV Chord", IV_Chord, 2 );
	Section section3( "I Chord", key, 2 );
	Section section4( "V Chord", V_Chord, 1 );
	Section section5( "IV Chord", IV_Chord, 1 );
	Section section6( "I Chord", key, 1 );
	Section turnaround( "Turnaround (V/I)", key, 1 );

	section1.addInstrument( & D_1 );
	section1.addInstrument( & DB_1 );

	section2.addInstrument( & D_1 );
	section2.addInstrument( & DB_1 );

	section3.addInstrument( & D_1 );
	section3.addInstrument( & DB_1 );

	section4.addInstrument( & D_1 );
	section4.addInstrument( & DB_1 );

	section5.addInstrument( & D_1 );
	section5.addInstrument( & DB_1 );

	section6.addInstrument( & D_1 );
	section6.addInstrument( & DB_1 );

	turnaround.addInstrument( & D_2 );
	turnaround.addInstrument( & DB_2 );

	beat1.addSection( & section1 );
	beat1.addSection( & section2 );
	beat1.addSection( & section3 );
	beat1.addSection( & section4 );
	beat1.addSection( & section5 );
	beat1.addSection( & section6 );
	beat1.addSection( & turnaround );

	beat1.printInfo();

	beat1.startBeat( 4 );

}

bool isNumber( string str ){

	int strLen = str.length();

	for( int i = 0; i < strLen; i++ ){

		if( ! isdigit( str[ i ] ) ){

			return false;

		}

	}

	return true;

}

int main( int argc, char * argv[] ){

  initSDL();

	//Defualt Parameters
  int BPM = 90;
	int subDivisions = 8;
  float timeSignature = 4.4;
	string key = "E1";

	if( argc == 1 ){

		cout << "No Input Parameters Recieved, Using Defaults:" << endl << "BPM: " << BPM << ", Sub-Divisions: " << subDivisions << ", Time Signature: " << timeSignature << ", Key: " << key << endl << endl << "Example: \"./RhythmSection.out 90 4.4 A1\"" << endl << endl;

	}

	string tmpParam;

  //Parse Input Parameters
  for( int i = 1; i < argc; i++ ){

		tmpParam = string( argv[ i ] );

		//Set BPM
		if( isNumber( tmpParam ) ){

			//Convert char * to int Using stringstream
			stringstream inputStream;
			inputStream << tmpParam;
			inputStream >> BPM;

		}

		//Set Time Signature
		else if( ( tmpParam.find_first_of( '.' ) != string::npos ) ){

			//Convert char * to float Using stringstream
	    stringstream inputStream;
	    inputStream << tmpParam;
	    inputStream >> timeSignature;

		}

		//Set Key ( Excluding Octave )
		else if( tmpParam.length() == 1 && ! isdigit( tmpParam[ 0 ] ) ){

			//Convert char * to string Using stringstream
			stringstream inputStream;
			inputStream << tmpParam;
			inputStream >> key;

			//Most Instruments Have Notes In The Second Octave. Default To This.
			key += '2';

		}

		//Set Key ( Half-Step Down ( b ) ) ( Excluding Octave )
		else if( tmpParam.length() == 2 && tmpParam[ 1 ] == 'b' ){

			//Convert char * to string Using stringstream
			stringstream inputStream;
			inputStream << tmpParam;
			inputStream >> key;

			//Most Instruments Have Notes In The Second Octave. Default To This.
			key += '2';

		}

		//Set Key ( Half-Step Up ( # ) ) ( Excluding Octave )
		else if( tmpParam.length() == 2 && tmpParam[ 1 ] == '#' ){

			//Convert char * to string Using stringstream
			stringstream inputStream;
			inputStream << tmpParam;
			inputStream >> key;

			//Most Instruments Have Notes In The Second Octave. Default To This.
			key += '2';

		}

		//Set Key ( Including Octave )
		else if( ( tmpParam.length() == 2 || tmpParam.length() == 3 ) && tmpParam.find_first_of( "0123456789" ) != string::npos ){

			//Convert char * to string Using stringstream
			stringstream inputStream;
			inputStream << tmpParam;
			inputStream >> key;

		}

		else{

			cout << "Unknown Parameter: " << tmpParam << endl;

		}

  }

	demo_12BB_Shuffle( BPM, timeSignature, key, subDivisions );

  closeSDL();

	setbuf( stdout, NULL );	//Flush stdout Buffer

  cout << endl << endl << "\t\t\t- FIN -" << endl << endl << endl;

  return 0;

}
