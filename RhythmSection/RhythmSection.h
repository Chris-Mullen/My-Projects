#ifndef RHYTHM_SECTION_H
#define RHYTHM_SECTION_H

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

#include "Definitions.h"
#include "Intervals.h"

//Forward Declaring Classes So They Can Reference Each Other Out Of Order Of Initialization.
class Scale;
class Instrument;
class Section;

//Global Static Booleans For Loading Sound Files Only Once
static bool DoubleBassLoaded = false;

class Beat{

public:

  Beat() :
    BPM( 60 ),
    meter( 4 ),
    noteValue( 4 ),
    beatRepetitions( 1 ),
		countIn( false ),
    thisBeatRep( 0 ),
    thisRhythm( 0 ),
    thisSection( 0 ),
    beatName( "_BEAT_" ),
    rhythmIndex( 0 ),
		barCount( 1 ),
		subDivisions( 1 ),
		currentKey( "_" ),
		lastBassNote( "_" ),
		keepPlaying( true ){

			std::cout << "Beat()" << std::endl;

			//Reset Seed State To Ensure Randomness Of Generated Rhythms.
			srand( time( NULL ) );

	 }

  Beat( int bpm, float timesignature, int r, std::string n, int s ) :
		BPM( bpm ),
    meter( floor( timesignature ) ),
    noteValue( 10 * ( timesignature - meter ) ),
    beatRepetitions( r ),
		countIn( false ),
    thisBeatRep( 0 ),
    thisRhythm( 0 ),
    thisSection( 0 ),
		barCount( 1 ),
    beatName( n ),
    rhythmIndex( 0 ),
		subDivisions( s * meter ),
		currentKey( "_" ),
		lastBassNote( "_" ),
		keepPlaying( true ){

			std::cout << "Beat()" << std::endl;

			//Reset Seed State To Ensure Randomness Of Generated Rhythms.
			srand( time( NULL ) );

	 	}

  ~Beat(){

    std::cout << "~Beat()" << std::endl;

    sections.clear();
		warningMessages.clear();

  }

  static Beat * beatInstance;
	static int channelCounter;

	bool keepPlaying;
	int thisSection;
	int rhythmIndex;
	int meter;
	std::string lastBassNote;
	std::string lastNoteName;
	std::vector< std::string > warningMessages;

	static std::string generateRhythm();
	static std::string generateRhythm( char rhythmChar );
	static std::string generateRhythm( const int style );
	static std::string generateRhythm( const int style, int maxScaleInterval );
	static std::string generateRhythm( char rhythmChar, int noteValue );
	static std::string generateShuffleRhythm( int maxScaleInterval );
	static std::string generateRiffs();
	static std::string generateRiffs( int maxScaleInterval );

  virtual void printInfo();

  static void static_timer_handler( int signum );
  static void channel_finished( int channel );
	static int getSubDivisions();
	static int getBeatSubDivisions();
	static int getCurrentSubDivision();
	static int getNextChannel(){ return channelCounter++; }

	void initSDL();
	void closeSDL();
	void clear();
  void waitForKeyboardInput();
	void updateBarAnimation();
  void printSectionsInfo();
	void incrementRhythmIndex();
	void incrementCounters();
	void incrementRhythmReps();
	void incrementSectionReps();
	void playInstruments();
	void nextSection();
	void startTimer();
	void startBeat();
	void startBeat( int countInReps );
  void playBeat( bool * keepPlaying );
  void timer_handler( int signum );
  void addSection( Section * s );
	void addSection( Section * s, int sectionReps );
	void rest( int delay_ns );
	void addWarningMessage( std::string m );

	int getBPM();
	int getMeter();
  int getSyllableLength();
	int getBeatLength();
	int getThisSectionRep();
  int getThisRhythmRep();
  int getSectionReps();
  int getRhythmReps();
	int getRhythmIndex();
	int countDown();
	int pickRandom( int min, int max );
	char nextScaleInterval( char currentScaleInterval, char maxChar );
	std::string getTempoName();
	std::string generateAnimationString();
  Section * getCurrentSection();

private:

	int BPM, thisBeatRep, thisRhythm, barCount, beatRepetitions, noteValue, subDivisions, countIn;
	std::string beatName;
	std::string currentKey;
	Section * countInSection;
	std::vector< Section * > sections;

	int64_t timespec_nanoseconds( timespec timeValue );
	timespec nanoseconds_timespec( int64_t nano );

};

class Instrument : public Beat{

public:

  Instrument() :
  	rhythmCount( 1 ),
		currentRhythm( 0 ),
    sustain( -1 ),
    volume( 100 ),
		lowestInterval( 0 ),
		randomizeRyhthms( true ),
		rhythmLength( Beat::getSubDivisions() ){ std::cout << "Instrument()" << std::endl; }

	Instrument( std::string n ) :
		rhythmCount( 1 ),
		currentRhythm( 0 ),
		sustain( -1 ),
		volume( 100 ),
		instrumentName( n ),
		lowestInterval( 0 ),
		randomizeRyhthms( true ),
		rhythmLength( Beat::getSubDivisions() ){ std::cout << "Instrument()" << std::endl; }

	//Metronome / Count-In
  Instrument( std::string n, std::string r, const char * const s1 ) :
		rhythmCount( 1 ),
		currentRhythm( 0 ),
    sustain( -1 ),
    instrumentName( n ),
    rhythmLength( r.length() ),
		randomizeRyhthms( true ),
		lowestInterval( 0 ){

			addRhythm( r );
			addChannel( s1 );

			std::cout << "Instrument()" << std::endl;

	}

  ~Instrument(){

    std::cout << "~Instrument()" << std::endl;

		ChannelNumbers.clear();
		Channels.clear();
		rhythms.clear();

  }

	virtual void playWAV( Mix_Chunk * wav, int channelNo );
	virtual void addRhythm( std::string rhythmPattern );
	virtual void playChannel( int channelNo );
  virtual void printInfo();
  virtual void play();

	virtual void nextRhythmPattern();
	virtual int getRhythmPatternCount();

  void clear();
  void setVolume( int v );
	void addChannel( const char * const c );
	int getChannel();
	int getChannelCount();
  int getSubDivisions();

	Mix_Chunk * getSyllable();

	bool randomizeRyhthms;
	int rhythmLength;
	int currentRhythm;
	std::string instrumentName;
	std::vector< int > ChannelNumbers;
	std::vector< std::string > rhythms;
	std::vector< Mix_Chunk * > Channels;

private:

  int instrumentChannelCount;
	int rhythmCount;
  int sustain;
	int volume;
	int lowestInterval;

};

class Double_Bass: public Instrument{

public:

		Double_Bass( std::string n ) :
			lowestInterval( 16 ),	//E1
			highestInterval( 54 ),	//Gb4
			lastStringPlayed( 0 ),
			strumSpeed( DEFAULT_STRUM_SPEED ),
			rhythmCount( 1 ),
			currentRhythm( 0 ),
			currentScale( 0 ),
			currentChord( 0 ),
			sustain( -1 ),
			instrumentName( n ),
			volume( 100 ),
			rhythmLength( Beat::getSubDivisions() ){

			 std::cout << "Double_Bass()" << std::endl;

			 loadChannels();
			 loadStrings();

		 }

  ~Double_Bass(){

    std::cout << "~Double_Bass()" << std::endl;

		scales.clear();
		chords.clear();

		unloadStrings();

  }

	virtual void play();
  virtual void printInfo();
	virtual void playWAV( Mix_Chunk * wav, int channelNo );
	virtual void nextRhythmPattern();

	virtual void printScalesInfo();
	virtual void printChordsInfo();
	void addScale( int scaleType );
	void addChord( int chordType );
	void playNote( int noteIndex );
	void playNote( std::string noteName );
	void playNote( int noteIndex, int channelNo );
	void playArpeggio( std::string keyName, Scale s );
	void playArpeggio( std::string keyName, Scale s, int octaves );
	void playChord( int keyIndex, Chord * c );
	void playChord( int keyIndex, Chord * c, int octaves );
	void improvise();
	void playRoot();
	void playGhostNote();
	void loadChannels();
	void loadStrings();
	void unloadStrings();
	int getScaleCount();
	int getChordCount();

private:

	const static std::string OpenStrings[];

	static const int channelCount = 4;	//1 Channel Per String
	static const int fretCount = 25;	//Number Of Notes Per String

	int ChannelNumbers[ channelCount ];
	int rhythmLength;
  int volume;
  int sustain;
	int currentRhythm;
	int currentScale;
	int currentChord;
	int rhythmCount;
	int lowestInterval;
	int highestInterval;
	int lastStringPlayed;
	int strumSpeed;
	std::vector< Scale > scales;
	std::vector< Chord > chords;

	std::string instrumentName;

  Mix_Chunk * Strings[ channelCount ][ fretCount ];
	Mix_Chunk * GhostNote;

};

class Drum_Kit: public Instrument{

public:

	Drum_Kit( std::string n ) :
		instrumentName( n ){ std::cout << "Drum_Kit()" << std::endl; }

	~Drum_Kit(){

		std::cout << "~Drum_Kit()" << std::endl;

		ChannelNumbers.clear();
		ChannelNames.clear();
		Channels.clear();
		compositeRhythms.clear();

	}

	virtual void printInfo();
	virtual void play();
	virtual void addRhythm( std::string rhythmPattern );
	virtual void addRhythm( std::vector< std::string > compositeRhythm );
	virtual int getRhythmPatternCount();
	virtual int getChannelCount();
	void addChannel( const char * const c, std::string n );
	void addChannel( const char * const c, std::string n, int v );
	void playChannel( int channelNo );

private:

	std::string instrumentName;
	std::vector< int > ChannelNumbers;
	std::vector< std::string > ChannelNames;
	std::vector< Mix_Chunk * > Channels;
	std::vector< std::vector < std::string > > compositeRhythms;

};

class Section: public Beat{

public:

	Section( std::string n, std::string k ) :
		sectionName( n ),
		rhythmRepetitions( 1 ),
		sectionRepetitions( 1 ),
		keyIndex( Intervals::getIntervalIndex( k ) ),
		thisSectionRepetition( 1 ),
		thisRhythmRepetition( 1 ){ std::cout << "Section()" << std::endl; }

	Section( std::string n, std::string k, int s ) :
		sectionName( n ),
		rhythmRepetitions( 1 ),
		sectionRepetitions( s ),
		keyIndex( Intervals::getIntervalIndex( k ) ),
		thisSectionRepetition( 1 ),
		thisRhythmRepetition( 1 ){ std::cout << "Section()" << std::endl; }

  Section( std::string n, int r, int s ) :
    sectionName( n ),
    rhythmRepetitions( r ),
    sectionRepetitions( s ),
		keyIndex( -1 ),
    thisSectionRepetition( 1 ),
    thisRhythmRepetition( 1 ){ std::cout << "Section()" << std::endl; }

  Section( Section * s ) :
    sectionName( "_" + s -> sectionName + "_" ),
    rhythmRepetitions( s -> rhythmRepetitions ),
    sectionRepetitions( s -> sectionRepetitions ),
		keyIndex( s -> keyIndex ),
    thisSectionRepetition( s -> thisSectionRepetition ),
    thisRhythmRepetition( s -> thisRhythmRepetition ),
    instruments( s -> instruments ){ std::cout << "Section()" << std::endl; }

  Section( Section * s, std::string newName ) :
    sectionName( newName ),
    rhythmRepetitions( s -> rhythmRepetitions ),
    sectionRepetitions( s -> sectionRepetitions ),
		keyIndex(  s -> keyIndex ),
    thisSectionRepetition( s -> thisSectionRepetition ),
    thisRhythmRepetition( s -> thisRhythmRepetition ),
    instruments( s -> instruments ){ std::cout << "Section()" << std::endl; }

  ~Section(){

    std::cout << "~Section()" << std::endl;

    instruments.clear();

  }

	int sectionRepetitions, thisSectionRepetition;
  int rhythmRepetitions, thisRhythmRepetition;
	int keyIndex;

  virtual void printInfo();
	virtual void setKey( std::string k );

	void printInstrumentsInfo();
  void playInstruments();
	void incrementRhythmReps();
  void incrementSectionReps();
	void clearInstruments();
	void addInstrument( Instrument * i );
	int getKeyIndex();
	int getInstrumentCount();
  int getThisRhythmRep();
  int getThisSectionRep();
	int getSectionReps();
  int getRhythmReps();
	std::string getSectionName();
	std::string getKeyName();

private:

  std::string sectionName;
	std::vector< Instrument * > instruments;

};

#endif
