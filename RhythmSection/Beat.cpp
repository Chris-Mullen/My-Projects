#include "RhythmSection.h"

using namespace std;

Beat * Beat::beatInstance;

int Beat::channelCounter = 1;

void Beat::incrementRhythmIndex(){ rhythmIndex = ( ++rhythmIndex ) % ( subDivisions * meter ); }
void Beat::incrementSectionReps(){ getCurrentSection() -> incrementSectionReps(); }
int Beat::getThisSectionRep(){ return getCurrentSection() -> getThisSectionRep(); }
int Beat::getThisRhythmRep(){ return getCurrentSection() -> getThisRhythmRep(); }
int Beat::getSectionReps(){ return getCurrentSection() -> getSectionReps(); }
int Beat::getRhythmReps(){ return getCurrentSection() -> getRhythmReps(); }
int Beat::getCurrentSubDivision(){ return beatInstance -> rhythmIndex; }
int Beat::getSubDivisions(){ return beatInstance -> subDivisions; }
int Beat::getMeter(){ return beatInstance -> meter; }
int Beat::getBPM(){ return beatInstance -> BPM; }
int Beat::getRhythmIndex(){ return rhythmIndex; }
int Beat::countDown(){ return countIn--; }

void Beat::addWarningMessage( string m ){

	for( string str : warningMessages ){

		if( m == str ){

			return;

		}

	}

	warningMessages.push_back( m );

}


//Update Bar Counter Display
void Beat::updateBarAnimation(){

	int stringLength = subDivisions;
	int beatIndex = subDivisions / meter;
	int s = getRhythmIndex();

	printf( "\r  %d BPM [%d/%d]: ", BPM, meter, noteValue );

	for ( int i = 0; i <= stringLength; i++ ){

		if( i == s ){

			putchar( 'O' );

		}

		else{

			if( i % beatIndex == 0 ){

				putchar( '|' );

			}

			else{

				putchar( '-' );

			}

		}

	}

	printf( " Bar: %d, Key: %s, Bass: %s \t\t", barCount, currentKey.c_str(), lastBassNote.c_str() );

	fflush( stdout );

}

void Beat::printInfo(){

  cout << DIVIDER4 << endl;
  cout << "\"" << beatName << "\"" << endl;
  cout << "BPM:\t\t" << BPM << endl;
  cout << "Time Signature:\t" << meter << "/" << noteValue << endl;
  cout << "subDivisions:\t" << subDivisions << endl;
  cout << "Tempo:\t\t" << getTempoName() << endl;
  cout << "Sections( " << sections.size() << " ):" << endl;

  printSectionsInfo();

  cout << DIVIDER4 << endl;

}

void Beat::printSectionsInfo(){

	int count = 0;

  for( auto & section : sections ){

		cout << DIVIDER4 << endl;

		cout << "Section " << ++count << ": ";

    section -> printInfo();

  }

}

//Pause Execution For A Given Time ( In Nanoseconds )
void Beat::rest( int delay_ns ){

  int64_t startTime, time_difference;
  struct timespec gettime_now;

  clock_gettime( CLOCK_REALTIME, & gettime_now );
  startTime = timespec_nanoseconds( gettime_now ); //Get Current Time In Nanoseconds

  while( true ){

    clock_gettime( CLOCK_REALTIME, & gettime_now );

    time_difference = timespec_nanoseconds( gettime_now ) - startTime;

    if( time_difference > delay_ns ){

      break;

    }

  }

}

void Beat::waitForKeyboardInput(){

  string anyKey;

	cout << endl << "\"" << beatName << "\"" << endl;

  cout << endl << "Return Key To Close..." << endl << endl;

  while( keepPlaying && ! getline( cin, anyKey ) ){

    sleep( 10 );

    getline( cin, anyKey );

    if( anyKey.length() > 0 ){

      keepPlaying = false;

    }

  }

	putchar( '\n' );

}

void Beat::timer_handler( int signum ){

	updateBarAnimation();

  int64_t timeNow = 0;
  struct timespec ts;

  clock_gettime( CLOCK_REALTIME, & ts );

  timeNow = timespec_nanoseconds( ts ); //Get Current Time In Nanoseconds

	if( getCurrentSection() != 0 ){

    getCurrentSection() -> playInstruments();

  }

  else{

    struct itimerval timer;

    timer.it_value.tv_sec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer( ITIMER_REAL, & timer, NULL );

    keepPlaying = false;

  }

	incrementCounters();

}

void Beat::static_timer_handler( int signum ){

  beatInstance -> timer_handler( signum );

}

void Beat::addSection( Section * s, int sectionReps ){

	for( int i = 0; i < sectionReps; i++ ){

		sections.push_back( s );

	}

}

void Beat::addSection( Section * s ){

  sections.push_back( s );

}

void Beat::incrementCounters(){

	if( rhythmIndex < ( subDivisions - 1 ) ){

		beatInstance -> incrementRhythmIndex();

  }

  else{

    rhythmIndex = 0;
    beatInstance -> incrementRhythmReps();

  }

}

void Beat::incrementRhythmReps(){

	if( beatInstance -> countIn > 0 ){

		beatInstance -> countDown();

	}

	else{

		beatInstance -> barCount++;

		getCurrentSection() -> incrementRhythmReps();

	}

}

void Beat::nextSection(){

  if( beatInstance -> thisSection < beatInstance -> sections.size() ){

    beatInstance -> thisSection++;

  }

	beatInstance -> currentKey = beatInstance -> getCurrentSection() -> getKeyName();

}

void Beat::startBeat(){

  struct sigaction sa;
  struct itimerval timer;

	beatInstance -> currentKey = sections[ 0 ] -> getKeyName();

	int delay_us = getSyllableLength() * 1000;

  memset( & sa, 0, sizeof( sa ) ) ;

  sa.sa_handler = static_timer_handler;

  sigaction ( SIGALRM, & sa, NULL );

  timer.it_value.tv_sec = 0;
  timer.it_interval.tv_sec = 0;
  timer.it_value.tv_usec = delay_us;
  timer.it_interval.tv_usec = delay_us;

  setitimer( ITIMER_REAL, & timer, NULL );

	if( beatInstance -> warningMessages.size() != 0 ){

		int count = 0;

		cout << endl << "Warnings Detected:" << endl;

		for( string str : warningMessages ){

			cout << ++count << " ]  " << str << endl;

		}

	}

  //Program Exits When The User Inputs A String.
  thread t1( & Beat::waitForKeyboardInput, this );
  t1.join();

}

void Beat::startBeat( int countInReps ){

	Instrument countIn( "Stick Clicks", generateRhythm( meter ), STICK_CLICK );
	Section countInSection( "Count-In", 1, 1 );
	countInSection.addInstrument( & countIn );

	beatInstance -> countIn = countInReps;
	beatInstance -> countInSection = & countInSection;

	cout << endl << "[ Counting In For " << countInReps << " Bars ]" << endl;

	startBeat();

}

int Beat::getSyllableLength(){

  float BPS = float( BPM ) / 60;
	int64_t beatLength = int64_t( 1.0f / BPS * 1000.0f );
  int64_t barLength = beatLength * meter;
  int64_t syllableLength = barLength / subDivisions;

  return syllableLength;

}

int Beat::getBeatLength(){

	float BPS = float( BPM ) / 60;
	int64_t beatLength = int64_t( 1.0f / BPS * 1000.0f );

	return beatLength * 1000000.0f;

}

Section * Beat::getCurrentSection(){

	if( beatInstance -> countIn > 0 ){

		if( beatInstance -> countIn == 0 ){

			countInSection -> clearInstruments();

		}

		return countInSection;

	}

  if( thisSection < sections.size() ){

    return sections[ thisSection ];

  }

  else{

    if( thisBeatRep < beatRepetitions || beatRepetitions == 0 ){

      thisBeatRep++;
      thisSection = 0;
			barCount = 1;

      return sections[ thisSection ];

    }

    return NULL;

  }

}

string Beat::generateRhythm( int noteValue ){

	return generateRhythm( noteValue, '0', SCALE_TYPE_ROOT_ONLY, true );

}

string Beat::generateRhythm( int noteValue, char rhythmChar ){

	return generateRhythm( noteValue, rhythmChar, SCALE_TYPE_DRUMKIT, true );

}

string Beat::generateRhythm( int noteValue, char rhythmChar, const int scaleType, bool divideBar ){

	int subDivisions = beatInstance -> getSubDivisions();
	int meter = beatInstance -> meter;
	int barSubDivisions = subDivisions / noteValue;
	int beatSubDivisions = subDivisions / meter;

	if( noteValue > subDivisions ){

		return string( subDivisions, '-' );

	}

	char secondaryInterval = '\\';

	if( noteValue == 0 ){

		return string( subDivisions, '-' );

	}

	else{

		if( subDivisions % noteValue != 0 ){

			if( noteValue != 1 ){

				cout << "Warning: noteValue ( " << noteValue << " ) *Should* Be A Factor Of " << subDivisions << " ( For Consistency ) " << endl << endl;

			}

		}

	}

	string rhythm = "";

	if( scaleType == SCALE_TYPE_DRUMKIT ){

		secondaryInterval = rhythmChar;

	}

	else if( scaleType == SCALE_TYPE_ROOT_ONLY ){

		secondaryInterval = '0';

	}

	if( divideBar ){

		for( int i = 0; i < subDivisions; i++ ){

			if( i % subDivisions == 0 ){

				rhythm += rhythmChar;

			}

			else{

				if( i % barSubDivisions == 0 ){

					rhythm += secondaryInterval;

				}

				else{

					rhythm += '-';

				}

			}

		}

	}

	else{

		for( int k = 0; k < meter; k++ ){

			for( int i = 0; i < beatSubDivisions; i++ ){

				if( i % noteValue == 0 ){

					rhythm += rhythmChar;

				}

				else{

					rhythm += "-";

				}

			}

		}

	}

	return rhythm;

}

string Beat::getTempoName(){

  if( beatInstance -> BPM < 24 ){ return "Larghissimo"; }
  else if( beatInstance -> BPM < 30 ){ return "Adagissimo"; }
  else if( beatInstance -> BPM < 35 ){ return "Sostenuto"; }
  else if( beatInstance -> BPM < 41 ){ return "Grave"; }
  else if( beatInstance -> BPM < 46 ){ return "Lento"; }
  else if( beatInstance -> BPM < 61 ){ return "Largo"; }
  else if( beatInstance -> BPM < 67 ){ return "Larghetto"; }
  else if( beatInstance -> BPM < 72 ){ return "Adagio"; }
  else if( beatInstance -> BPM < 77 ){ return "Adagietto"; }
  else if( beatInstance -> BPM < 80 ){ return "Andante"; }
  else if( beatInstance -> BPM < 86 ){ return "Marcia moderato"; }
  else if( beatInstance -> BPM < 109 ){ return "Andantino"; }
  else if( beatInstance -> BPM < 113 ){ return "Andante Moderato"; }
  else if( beatInstance -> BPM < 116 ){ return "Moderato"; }
  else if( beatInstance -> BPM < 121 ){ return "Allegro Moderato"; }
  else if( beatInstance -> BPM < 157 ){ return "Allegro"; }
  else if( beatInstance -> BPM < 173 ){ return "Vivace"; }
  else if( beatInstance -> BPM < 177 ){ return "Vivacissimo"; }
  else if( beatInstance -> BPM < 201 ){ return "Presto"; }
	else if( beatInstance -> BPM < TEMPO_LIMIT ){ return "Prestissimo"; }
  else{

		cout << "BPM Too High ( Setting To Max ): " << TEMPO_LIMIT << endl;

 		beatInstance -> BPM = TEMPO_LIMIT;

		return "Prestissimo";

	}

}

//Convert timespec struct To Nanoseconds
inline int64_t Beat::timespec_nanoseconds( timespec timeValue ){

  return timeValue.tv_sec * 1000000000 + timeValue.tv_nsec;

}

//Convert Nanoseconds To timespec struct
inline timespec Beat::nanoseconds_timespec( int64_t nano ){

  timespec result;
  result.tv_sec = nano / 1000000000;
  result.tv_nsec = nano % 1000000000;

  return result;

}
