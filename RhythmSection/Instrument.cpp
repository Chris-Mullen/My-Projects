#include "Drum_Looper.h"

//Static
int Instrument::channelCount = 1;

void Instrument::printInfo(){

  cout << "\t\t" << DIVIDER3 << endl;
  cout << "\t\t" << "\"" << instrumentName << "\"" << endl;
  cout << "\t\tChannel:\t" << channelNo << endl;
  cout << "\t\tRhythm:\t\t" << rhythmPattern << endl;
  cout << "\t\tPrimary Addr:\t" << SOUND1 << endl;
  cout << "\t\tSecondary Addr:\t" << SOUND2 << endl;

}

void Instrument::play(){

  if( rhythmPattern[ rhythmIndex ] == 'O' ){

    thread t1( & Instrument::playWAV, this, SOUND1 );
    t1.detach();

  }

  else if( rhythmPattern[ rhythmIndex ] == 'X' ){

    thread t1( & Instrument::playWAV, this, SOUND2 );
    t1.detach();

  }

  rhythmIndex = ( ++rhythmIndex ) % rhythmLength;

}

Mix_Chunk * Instrument::getSyllable(){

  if( rhythmPattern[ rhythmIndex ] == 'O' ){

    return SOUND1;

  }

  else if( rhythmPattern[ rhythmIndex ] == 'X' ){

    return SOUND2;

  }

  else{

    return NULL;

  }

  rhythmIndex = ( ++rhythmIndex ) % rhythmLength;

}

int Instrument::getChannel(){

  return channelNo;

}

void Instrument::clear(){

  Mix_FreeChunk( SOUND1 );
  Mix_FreeChunk( SOUND1 );

  SOUND1 = NULL;
  SOUND2 = NULL;

}

void Instrument::playWAV( Mix_Chunk * wav ){

  if( sustain > 0 ){

    cout << "Hear The Sustain: " << sustain << endl;

  }

  Mix_PlayChannelTimed( channelNo, wav, 0, sustain );

}

void Instrument::setRhythmPattern( string r ){

  rhythmPattern = r;
  rhythmLength = rhythmPattern.length();

}

int Instrument::getSyllables(){ return beatInstance -> getSyllables(); }

//Sets Volume To A Percentage Of Maximum Volume
void Instrument::setVolume( int v ){

  Mix_Volume( channelNo, MIX_MAX_VOLUME / ( 100 / v ) );

}
