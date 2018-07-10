#include "Drum_Looper.h"

Beat * Beat::beatInstance;

void Beat::incrementRhythmReps(){ getCurrentSection() -> incrementRhythmReps(); }
void Beat::incrementSectionReps(){ getCurrentSection() -> incrementSectionReps(); }

int Beat::getBPM(){ return BPM; }
int Beat::getSyllables(){ return syllables; }
int Beat::getThisSectionRep(){ return getCurrentSection() -> getThisSectionRep(); }
int Beat::getThisRhythmRep(){ return getCurrentSection() -> getThisRhythmRep(); }
int Beat::getSectionReps(){ return getCurrentSection() -> getSectionReps(); }
int Beat::getRhythmReps(){ return getCurrentSection() -> getRhythmReps(); }

int Beat::getSyllableLength(){

  float BPS = float( BPM ) / 60;
  int64_t beatLength = int64_t( 1.0f / BPS * 1000.0f );
  int64_t barLength = beatLength * meter;
  int64_t syllableLength = barLength / syllables;

  return syllableLength;

 }

Section * Beat::getCurrentSection(){

  if( thisSection < sections.size() ){

    return sections[ thisSection ];

  }

  else{

    if( thisBeatRep < beatRepetitions || beatRepetitions == 0 ){

      thisBeatRep++;
      thisSection = 0;

      return sections[ thisSection ];

    }

    return NULL;

  }

}

string Beat::getTempoName(){

  if( BPM < 24 ){ return "Larghissimo"; }
  else if( BPM < 30 ){ return "Adagissimo"; }
  else if( BPM < 35 ){ return "Sostenuto"; }
  else if( BPM < 41 ){ return "Grave"; }
  else if( BPM < 46 ){ return "Lento"; }
  else if( BPM < 61 ){ return "Largo"; }
  else if( BPM < 67 ){ return "Larghetto"; }
  else if( BPM < 72 ){ return "Adagio"; }
  else if( BPM < 77 ){ return "Adagietto"; }
  else if( BPM < 80 ){ return "Andante"; }
  else if( BPM < 86 ){ return "Marcia moderato"; }
  else if( BPM < 109 ){ return "Andantino"; }
  else if( BPM < 113 ){ return "Andante Moderato"; }
  else if( BPM < 116 ){ return "Moderato"; }
  else if( BPM < 121 ){ return "Allegro Moderato"; }
  else if( BPM < 157 ){ return "Allegro"; }
  else if( BPM < 173 ){ return "Vivace"; }
  else if( BPM < 177 ){ return "Vivacissimo"; }
  else if( BPM < 201 ){ return "Presto"; }
  else{ return "Prestissimo"; }

}

void Beat::printInfo(){

  cout << DIVIDER4 << endl;
  cout << "\"" << beatName << "\"" << endl;
  cout << "BPM:\t\t" << BPM << endl;
  cout << "Time Signature:\t" << meter << "/" << noteValue << endl;
  cout << "Syllables:\t" << syllables << endl;
  cout << "Tempo:\t\t" << getTempoName() << endl;
  //cout << "Instruments( " << instruments.size() << " ):" << endl;
  cout << "Sections( " << sections.size() << " ):" << endl;

  //printInstrumentsInfo();
  printSectionsInfo();

  cout << endl << "PID: " << getpid() << endl << endl;

  cout << DIVIDER4 << endl;

}

void Beat::printSectionsInfo(){

  for( auto & section : sections ){

    section -> printInfo();

  }

}

//Convert timespec struct To Nanoseconds
int64_t Beat::timespec_nanoseconds( timespec tv ){

  return tv.tv_sec * 1000000000 + tv.tv_nsec;

}

//Convert Nanoseconds To timespec struct
timespec Beat::nanoseconds_timespec( int64_t n ){

  timespec result;
  result.tv_sec = n / 1000000000;
  result.tv_nsec = n % 1000000000;

  return result;

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

  cout << "Return Key To Close..." << endl;

  while( keepPlaying && ! getline( cin, anyKey ) ){

    sleep( 10 );

    getline( cin, anyKey );

    if( anyKey.length() > 0 ){

      keepPlaying = false;

    }

  }


}

void Beat::timer_handler( int signum ){

  int64_t timeNow = 0;
  struct timespec ts;

  clock_gettime( CLOCK_REALTIME, & ts );

  timeNow = timespec_nanoseconds( ts ); //Get Current Time In Nanoseconds

  incrementCounters();

  if( getCurrentSection() != 0 ){

    getCurrentSection() -> playInstruments();

  }

  else{

    keepPlaying = 0;

    struct itimerval timer;

    timer.it_value.tv_sec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer( ITIMER_REAL, & timer, NULL );

    keepPlaying = false;

  }

}

void Beat::static_timer_handler( int signum ){

  beatInstance -> timer_handler( signum );

}

void Beat::startBeat(){

  if( countIn ){

    //TODO - This Should Play Only Once, In The Beginning. Not Repeated Like Other Sections
    //Instrument metronome( "Metronome", "O---O---O---X---", FINGER_CLICK, HAND_CLAP );

  }

  struct sigaction sa;
  struct itimerval timer;

  int delay_us = getSyllableLength() * 1000;

  memset( & sa, 0, sizeof( sa ) ) ;

  sa.sa_handler = static_timer_handler;

  sigaction ( SIGALRM, & sa, NULL );

  timer.it_value.tv_sec = 0;
  timer.it_interval.tv_sec = 0;
  timer.it_value.tv_usec = delay_us;
  timer.it_interval.tv_usec = delay_us;

  setitimer( ITIMER_REAL, & timer, NULL );

  //Program Exits When The User Inputs A String.
  thread t1( & Beat::waitForKeyboardInput, this );
  t1.join();

}

void Beat::addSection( Section * s ){

  sections.push_back( s );

}

void Beat::incrementCounters(){

  if( rhythmIndex < syllables ){

    rhythmIndex++;

  }

  else{

    rhythmIndex = 1;
    incrementRhythmReps();

  }

}

void Beat::nextSection(){

  if( beatInstance -> thisSection < beatInstance -> sections.size() ){

    beatInstance -> thisSection++;

  }

}
