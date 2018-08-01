#include "RhythmSection.h"

using namespace std;

/*
reset; rm RhythmSection.out; g++ -std=c++11 -pthread main.cpp Intervals.cpp Beat.cpp Section.cpp Instrument.cpp Drum_Kit.cpp Double_Bass.cpp -o RhythmSection.out -lSDL2_mixer $(pkg-config --cflags --libs sdl2); ./RhythmSection.out 90 4.4
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
	Double_Bass DB_1( "Double Bass_1" );
	Double_Bass DB_2( "Double Bass_2" );

	DB_1.addScale( SCALE_MINOR_PENTATONIC );
	DB_2.addScale( SCALE_MINOR_PENTATONIC );

	string kick1 = 						"0---------------0---------------";
	string kick2 = 						"0-----0---------0-----0---------";
	string kick3 = 						"0-----0-------0-0-----0-------0-";
	string kick4 = 						"0-------------0-----------------";
	string kick5 = 						"0-------------0-------0-------0-";

	string kickTurn =					"0-------0-------0-------0-------";
	string highhatTurn1 =			"------1-1-----1-------1-1-----1-";
	string highhatTurn2 =			"------1-------1-------1-------1-";

	string snare1 = 					"--------1---------------1-------";
	string snare2 = 					"--------1---------------1-----1-";
	string snare3 = 					"--------1-2-------------1-2-----";
	string snare4 = 					"--2-----1-2-------2-----1-2-----";
	string snare5 = 					"--2-------2-----1-2-------2-----";

	string highhat1 = 				"3-----3-3-----3-3-----3-3-----3-";

	string bassTurnaround1 = 	"0-------3-------5-------7-------";
	string bassTurnaround2 = 	"0---0---3---3---5---5---7---7---";
	string bassTurnaround3 = 	"0-----0-3-----3-5-----5-7-----7-";
	string bassTurnaround4 = 	"0-----0-3-0---3-5-0---5-7-0-5-7-";
	string bassTurnaround5 = 	"0-----0-3-0-X-3-5-0---5-7-0-5-7-";
	string bassTurnaround6 = 	"0-----0-3-0---3-5-0-X-5-X-0-5-7-";
	string bassTurnaround7 = 	"0---X-0-3-0-X-3-5-0---5-X-0-5-7-";

	vector< string > compositeRhythm0;
	compositeRhythm0.push_back( kick1 );
	compositeRhythm0.push_back( snare1 );

	vector< string > compositeRhythm1;
	compositeRhythm1.push_back( highhat1 );
	compositeRhythm1.push_back( kick1 );
	compositeRhythm1.push_back( snare1 );

	vector< string > compositeRhythm2;
	compositeRhythm2.push_back( highhat1 );
	compositeRhythm2.push_back( kick2 );
	compositeRhythm2.push_back( snare2 );

	vector< string > compositeRhythm3;
	compositeRhythm3.push_back( highhat1 );
	compositeRhythm3.push_back( kick1 );
	compositeRhythm3.push_back( snare3 );

	vector< string > compositeRhythm4;
	compositeRhythm4.push_back( highhat1 );
	compositeRhythm4.push_back( kick3 );
	compositeRhythm4.push_back( snare4 );

	vector< string > compositeRhythm5;
	compositeRhythm5.push_back( highhat1 );
	compositeRhythm5.push_back( kick4 );
	compositeRhythm5.push_back( snare5 );

	vector< string > compositeRhythm6;
	compositeRhythm6.push_back( highhat1 );
	compositeRhythm6.push_back( kick5 );
	compositeRhythm6.push_back( snare5 );

	vector< string > turnaroundRhythm1;
	turnaroundRhythm1.push_back( kickTurn );
	turnaroundRhythm1.push_back( highhatTurn1 );

	vector< string > turnaroundRhythm2;
	turnaroundRhythm2.push_back( kickTurn );
	turnaroundRhythm2.push_back( highhatTurn2 );

	D_1.addRhythm( beat1.generateRhythm( beat1.getMeter() , '0' ) );
	D_1.addRhythm( compositeRhythm0 );
	D_1.addRhythm( compositeRhythm1 );
	D_1.addRhythm( compositeRhythm2 );
	D_1.addRhythm( compositeRhythm3 );
	D_1.addRhythm( compositeRhythm4 );
	D_1.addRhythm( compositeRhythm5 );
	D_1.addRhythm( compositeRhythm6 );

	D_2.addRhythm( beat1.generateRhythm( beat1.getMeter(), '0' ) );
	D_2.addRhythm( beat1.generateRhythm( beat1.getMeter() * 2, '0' ) );
	D_2.addRhythm( beat1.generateRhythm( beat1.getMeter() * 4, '0' ) );
	D_2.addRhythm( kick1 );
	D_2.addRhythm( kick2 );
	D_2.addRhythm( kick3 );
	D_2.addRhythm( turnaroundRhythm1 );
	D_2.addRhythm( turnaroundRhythm2 );
	D_2.addRhythm( compositeRhythm0 );

	DB_1.addRhythm( beat1.generateRhythm( beat1.getMeter(), '0' ) );
	DB_1.addRhythm( beat1.generateRhythm( beat1.getMeter() * 2, '0' ) );
	DB_1.addRhythm( beat1.generateRhythm( beat1.getMeter(), 'I' ) );

	DB_2.addRhythm( bassTurnaround1 );
	DB_2.addRhythm( bassTurnaround2 );
	DB_2.addRhythm( bassTurnaround3 );
	DB_2.addRhythm( bassTurnaround4 );
	DB_2.addRhythm( bassTurnaround5 );
	DB_2.addRhythm( bassTurnaround6 );
	DB_2.addRhythm( bassTurnaround7 );

	D_1.addChannel( KICK_DRUM, "Kick Drum" );
	D_1.addChannel( SNARE_DRUM_1, "Snare Drum" );
	D_1.addChannel( SNARE_BRUSH_2, "Snare Ghost" );
	D_1.addChannel( HIGH_HAT_CLOSED, "High Hat", 30 );

	D_2.addChannel( KICK_DRUM, "Kick Drum" );
	D_2.addChannel( HIGH_HAT_CLOSED, "High Hat", 30 );

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
