#include "Drum_Looper.h"

/*
reset; rm DrumLooper.out; g++ -std=c++11 -pthread Section.cpp Beat.cpp Instrument.cpp main.cpp -o DrumLooper.out -lSDL2_mixer $(pkg-config --cflags --libs sdl2); ./DrumLooper.out 100 4.4
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

void demo_Layers( int BPM, float timeSignature ){

  Beat beat1( BPM, timeSignature, 0, "Layers Demo", 32, true );

  beat1.beatInstance = & beat1;

  Instrument K_1( "Kick1",            "-O---O---------------O-----O----", KICK_DRUM );
  Instrument K_2( "Kick2",            "-O---O-O-----O-O---OOO-O---O----", KICK_DRUM );
  Instrument K_3( "Kick3",            "-O---O---X-----------O-----O----", KICK_DRUM, HIGH_HAT_OPEN );
  Instrument K_4( "Kick4",            "-O---O---------------O-----O----", KICK_DRUM );
  Instrument S_1( "Snare1",           "---------O-----X---X---X-O-----X", SNARE_DRUM_1, SNARE_BRUSH_1 );
  Instrument H_1( "HighHat1",         "-X---X---X---X---X---X---X---X--", HIGH_HAT_OPEN, HIGH_HAT_CLOSED );
  Instrument H_2( "HighHat2",         "-X-X-X-X-X-O-X-X-X-X-X-X-X-O-X-X", HIGH_HAT_OPEN, HIGH_HAT_CLOSED );
  Instrument H_3( "HighHat3",         "---------O-----------X-O---X---X", HIGH_HAT_OPEN, HIGH_HAT_CLOSED );
  Instrument H_4( "HighHat4",         "-----X-X-O-----------X---X---X--", HIGH_HAT_OPEN, HIGH_HAT_CLOSED );
  Instrument H_5( "HighHat5",         "---------O-X-XXX-X-X-X-O--------", HIGH_HAT_OPEN, HIGH_HAT_CLOSED );
  Instrument H_6( "HighHat6",         "-------------------------O------", HIGH_HAT_OPEN );
  Instrument C_1( "Crash1",           "-O------------------------------", CRASH_CYMBAL );
  Instrument C_2( "Crash2",           "---------X---------------O------", CRASH_CYMBAL, RIDE_CYMBAL );
  Instrument C_3( "Crash3",           "-------------------------------O", CRASH_CYMBAL );
  Instrument CB_1( "More Cowbell1",   "---------O-O---O---O---O-O---O--", COW_BELL );
  Instrument CB_2( "More Cowbell2",   "---------O-O---O---O---O-X---X--", COW_BELL, CRASH_CYMBAL );
  Instrument FT_1( "FloorTom1",       "-----X---O-----X-----O---X-X-O--", FLOOR_TOM_1, FLOOR_TOM_2 );
  Instrument FT_2( "FloorTom2",       "-----O---X-----X-----X-X-O-X----", FLOOR_TOM_1, FLOOR_TOM_2 );

  H_1.setVolume( 40 );
  H_2.setVolume( 30 );
  H_3.setVolume( 40 );
  H_4.setVolume( 40 );
  H_5.setVolume( 40 );
  H_6.setVolume( 40 );
  FT_1.setVolume( 40 );
  FT_2.setVolume( 40 );
  CB_1.setVolume( 40 );
  CB_2.setVolume( 40 );


  Section section1( "SECTION1", 1, 4 );

  section1.addInstrument( & K_1 );

  Section section2( & section1, "SECTION2" );

  section2.addInstrument( & S_1 );

  Section section3( & section2, "SECTION3" );

  section3.addInstrument( & H_1 );

  Section section4( & section1, "SECTION4" );

  section4.addInstrument( & C_1 );
  section4.addInstrument( & S_1 );
  section4.addInstrument( & H_2 );

  Section section5( & section4, "SECTION5" );

  section5.addInstrument( & C_2 );

  Section section6( & section2, "SECTION6" );

  section6.addInstrument( & CB_1 );

  Section section7( & section3, "SECTION7" );

  section7.addInstrument( & CB_2 );

  Section section8( "SECTION8", 1, 1 );

  section8.addInstrument( & K_3 );

  Section section9( "SECTION9", 1, 3 );

  section9.addInstrument( & K_4 );

  Section solo1( "SOLO1", 1, 1 );

  solo1.addInstrument( & K_1 );
  solo1.addInstrument( & H_1 );

  Section solo2( "SOLO2", 1, 1 );

  solo2.addInstrument( & K_1 );
  solo2.addInstrument( & H_3 );

  Section solo3( "SOLO3", 1, 1 );

  solo3.addInstrument( & K_1 );
  solo3.addInstrument( & H_4 );
  solo3.addInstrument( & FT_1 );

  Section solo4( "SOLO4", 1, 1 );

  solo4.addInstrument( & K_2 );
  solo4.addInstrument( & C_3 );
  solo4.addInstrument( & FT_2 );
  solo4.addInstrument( & H_6 );

  beat1.addSection( & section1 );
  beat1.addSection( & section2 );
  beat1.addSection( & section3 );
  beat1.addSection( & section4 );
  beat1.addSection( & section5 );
  beat1.addSection( & section8 );
  beat1.addSection( & section9 );
  beat1.addSection( & solo1 );
  beat1.addSection( & solo2 );
  beat1.addSection( & solo3 );
  beat1.addSection( & solo4 );
  beat1.addSection( & section5 );
  beat1.addSection( & section6 );
  beat1.addSection( & section7 );
  beat1.addSection( & section5 );
  beat1.addSection( & section4 );
  beat1.addSection( & section3 );
  beat1.addSection( & section2 );

  beat1.printInfo();

  beat1.startBeat();

}

int main( int argc, char * argv[] ){

  initSDL();

  int BPM = 60;
  float timeSignature = 4.4;

  //Parse Input Parameters
  for( int i = 1; i < argc; i++ ){

    if( ( string( argv[ i ] ).find_first_of( '.' ) != string::npos ) ){

      //Convert char * to float Using stringstream
      stringstream tsString;
      tsString << argv[ i ];
      tsString >> timeSignature;

    }

    else{

      //Convert char * to int Using stringstream
      stringstream bpmString;
      bpmString << argv[ i ];
      bpmString >> BPM;

    }

  }

  demo_Layers( BPM, timeSignature );

  closeSDL();

  cout << endl << endl << "\t\t\t- FIN -" << endl << endl << endl;

  return 0;

}
