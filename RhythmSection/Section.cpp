#include "RhythmSection.h"

using namespace std;

void Section::setKey( string k ){ keyIndex = Intervals::getIntervalIndex( k ); }

void Section::addScale( Scale * s ){ scales.push_back( s ); }
void Section::clearInstruments(){ instruments.clear(); }
int Section::getInstrumentCount(){ return instruments.size(); }
int Section::getThisSectionRep(){ return thisSectionRepetition; }
int Section::getThisRhythmRep(){ return thisRhythmRepetition; }
int Section::getSectionReps(){ return sectionRepetitions; }
int Section::getRhythmReps(){ return rhythmRepetitions; }
int Section::getKeyIndex(){ return keyIndex; }
std::string Section::getSectionName(){ return sectionName; }

void Section::printInfo(){

  cout << "\"" << sectionName << "\"" << endl;
	cout << "Key:\t\t" << getKeyName() << endl;
  cout << "Tempo:\t\t" << getBPM() << " ( " << getTempoName() << " ) " << endl;
	cout << "Section Reps:\t" << getSectionReps() << endl;
	cout << "Rhythm Reps:\t" << getRhythmReps() << endl;
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

	i -> setScales( this -> scales );

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

		for( auto & instrument : instruments ){

			instrument -> nextRhythmPattern();

		}

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

string Section::getKeyName(){

	if( keyIndex == -1 ){

		return "_";

	}

	else{

		string keyName = Intervals::getIntervalName( keyIndex );

		return keyName.substr( 0, keyName.size() - 1 );

	}

}

Scale * Section::getCurrentScale(){

  if( thisScale < scales.size() ){

    return scales[ thisScale ];

  }

}
