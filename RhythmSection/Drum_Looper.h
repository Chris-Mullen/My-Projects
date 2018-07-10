#ifndef DRUM_LOOPER_H
#define DRUM_LOOPER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <thread>
#include <chrono>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#include "definitions.h"

using namespace std;

//Forward Declaring Classes So They Can Reference Each Other Out Of Order Of Initialization.
class Section;
class Instrument;

class Beat{

public:

  Beat() :
    BPM( 60 ),
    meter( 4 ),
    noteValue( 4 ),
    beatRepetitions( 1 ),
    thisBeatRep( 0 ),
    thisRhythm( 0 ),
    thisSection( 0 ),
    beatName( "BEAT" ),
    rhythmIndex( 0 ),
    syllables( 16 ),
    countIn( false ),
    keepPlaying( true ){ cout << "Beat()" << endl; }

  Beat( int bpm, float timesignature, int r, string n, int s, bool c ) :
    BPM( bpm ),
    meter( floor( timesignature ) ),
    noteValue( 10 * ( timesignature - meter ) ),
    beatRepetitions( r ),
    thisBeatRep( 0 ),
    thisRhythm( 0 ),
    thisSection( 0 ),
    beatName( n ),
    rhythmIndex( 0 ),
    syllables( s ),
    countIn( c ),
    keepPlaying( true ){ cout << "Beat()" << endl; }

  ~Beat(){

    cout << "~Beat()" << endl;

    sections.clear();

  }

  static Beat * beatInstance;

  bool keepPlaying;
  int thisSection;

  static void static_timer_handler( int signum );
  static void channel_finished( int channel );
  
  void waitForKeyboardInput();
  void startBeat();
  void startTimer();
  void incrementCounters();
  void incrementRhythmReps();
  void incrementSectionReps();
  void playInstruments();
  void nextSection();
  void printInfo();
  void closeSDL();
  void initSDL();
  void clear();
  void playBeat( bool * keepPlaying );
  void timer_handler( int signum );
  void addSection( Section * s );
  void printSectionsInfo();
  void rest( int delay_ns );
  int getBPM();
  int getSyllables();
  int getSyllableLength();
  int getThisSectionRep();
  int getThisRhythmRep();
  int getSectionReps();
  int getRhythmReps();
  string getTempoName();
  timespec nanoseconds_timespec( int64_t n );
  int64_t timespec_nanoseconds( timespec tv );
  Section * getCurrentSection();

private:

  bool countIn;
  int BPM, thisBeatRep, thisRhythm, beatRepetitions, meter, noteValue, syllables, rhythmIndex;
  string beatName;
  vector< Section * > sections;

};

class Instrument : public Beat{

public:

  Instrument() :
    channelNo( getNextChannel() ),
    sustain( -1 ),
    rhythmIndex( 0 ),
    instrumentName( "Metronome" ),
    rhythmPattern( "OOOX" ),
    rhythmLength( 4 ),
    SOUND1( Mix_LoadWAV( FINGER_CLICK ) ),
    SOUND2( Mix_LoadWAV( HAND_CLAP ) ){ cout << "Instrument()" << endl; }

  Instrument( string n, string r, const char * const s1 ) :
    channelNo( getNextChannel() ),
    sustain( -1 ),
    rhythmIndex( 0 ),
    instrumentName( n ),
    rhythmPattern( r ),
    rhythmLength( r.length() ),
    SOUND1( Mix_LoadWAV( s1 ) ),
    SOUND2( NULL ){ cout << "Instrument()" << endl; }

  Instrument( string n, string r, const char * const s1, int s ) :
    channelNo( getNextChannel() ),
    sustain( s ),
    rhythmIndex( 0 ),
    instrumentName( n ),
    rhythmPattern( r ),
    rhythmLength( r.length() ),
    SOUND1( Mix_LoadWAV( s1 ) ),
    SOUND2( NULL ){ cout << "Instrument()" << endl; }

  Instrument( string n, string r, const char * const s1, const char * const s2 ) :
    channelNo( getNextChannel() ),
    sustain( 0 ),
    rhythmIndex( 0 ),
    instrumentName( n ),
    rhythmPattern( r ),
    volume( 100 ),
    rhythmLength( r.length() ),
    SOUND1( Mix_LoadWAV( s1 ) ),
    SOUND2( Mix_LoadWAV( s2 ) ){ cout << "Instrument()" << endl; }

  Instrument( string n, string r, const char * const s1, const char * const s2, int s ) :
    channelNo( getNextChannel() ),
    sustain( s ),
    rhythmIndex( 0 ),
    instrumentName( n ),
    rhythmPattern( r ),
    volume( 100 ),
    rhythmLength( r.length() ),
    SOUND1( Mix_LoadWAV( s1 ) ),
    SOUND2( Mix_LoadWAV( s2 ) ){ cout << "Instrument()" << endl; }

  ~Instrument(){

    cout << "~Instrument()" << endl;

    Mix_FreeChunk( SOUND1 );
    Mix_FreeChunk( SOUND2 );

    SOUND1 = NULL;
    SOUND2 = NULL;

  }

  static int getNextChannel(){ return channelCount++; }

  void printInfo();
  void play();
  int getChannel();
  void playWAV( Mix_Chunk * wav );
  void clear();
  void setRhythmPattern( string r );
  void setVolume( int v );

  int getSyllables();

  Mix_Chunk * getSyllable();

private:

  static int channelCount;

  int channelNo;
  int rhythmLength;
  int rhythmIndex;
  int volume;
  int sustain;
  string instrumentName;
  string rhythmPattern;

  Mix_Chunk * SOUND1, * SOUND2;

};

class Section: public Beat{

public:

  Section() :
    sectionName( "SECTION" ),
    sectionRepetitions( 0 ),
    rhythmRepetitions( 1 ),
    thisSectionRepetition( 1 ),
    thisRhythmRepetition( 1 ){ cout << "Section()" << endl; }

  Section( string n, int r, int s ) :
    sectionName( n ),
    rhythmRepetitions( r ),
    sectionRepetitions( s ),
    thisSectionRepetition( 1 ),
    thisRhythmRepetition( 1 ){ cout << "Section()" << endl; }

  Section( Section * s ) :
    sectionName( s -> sectionName + "_" ),
    rhythmRepetitions( s -> rhythmRepetitions ),
    sectionRepetitions( s -> sectionRepetitions ),
    thisSectionRepetition( s -> thisSectionRepetition ),
    thisRhythmRepetition( s -> thisRhythmRepetition ),
    instruments( s -> instruments ){ cout << "Section()" << endl; }

  Section( Section * s, string newName ) :
    sectionName( newName ),
    rhythmRepetitions( s -> rhythmRepetitions ),
    sectionRepetitions( s -> sectionRepetitions ),
    thisSectionRepetition( s -> thisSectionRepetition ),
    thisRhythmRepetition( s -> thisRhythmRepetition ),
    instruments( s -> instruments ){ cout << "Section()" << endl; }


  ~Section(){

    cout << "~Section()" << endl;

    instruments.clear();

  }

  //static Section * sectionInstance;

  int sectionRepetitions, thisSectionRepetition;
  int rhythmRepetitions, thisRhythmRepetition;

  int getInstrumentCount();
  void printInfo();
  void printInstrumentsInfo();
  void addInstrument( Instrument * i );
  void playInstruments();

  int getThisRhythmRep();
  int getThisSectionRep();

  int getRhythmReps();
  int getSectionReps();

  void incrementRhythmReps();
  void incrementSectionReps();

private:

  string sectionName;
  vector< Instrument * > instruments;

};

#endif
