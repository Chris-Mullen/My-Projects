#include "Drum_Looper.h"

int Section::getInstrumentCount(){ return instruments.size(); }
int Section::getThisSectionRep(){ return thisSectionRepetition; }
int Section::getThisRhythmRep(){ return thisRhythmRepetition; }
int Section::getSectionReps(){ return sectionRepetitions; }
int Section::getRhythmReps(){ return rhythmRepetitions; }

void Section::printInfo(){

  cout << DIVIDER4 << endl;
  cout << "\"" << sectionName << "\"" << endl;
  cout << "Tempo:\t\t" << getBPM() << " ( " << getTempoName() << " ) " << endl;
  cout << "Instruments( " << instruments.size() << " ):" << endl;

  printInstrumentsInfo();

  cout << endl << DIVIDER4 << endl;

}

void Section::printInstrumentsInfo(){

  for( auto & instrument : instruments ){

    instrument -> printInfo();

  }

}

void Section::addInstrument( Instrument * i ){

  instruments.push_back( i );

}

void Section::playInstruments(){

  for( auto & instrument : instruments ){

    instrument -> play();

  }

}

void Section::incrementRhythmReps(){

  if( thisRhythmRepetition < rhythmRepetitions ){

    thisRhythmRepetition++;

  }

  else{

    thisRhythmRepetition = 1;
    incrementSectionReps();

  }

}

void Section::incrementSectionReps(){

  if( sectionRepetitions == 0 ){

    return;

  }

  if( thisSectionRepetition < sectionRepetitions ){

    thisSectionRepetition++;

  }

  else{

    thisSectionRepetition = 1;

    Beat::nextSection();

  }

}
