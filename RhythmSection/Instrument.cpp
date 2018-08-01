#include "RhythmSection.h"

using namespace std;

int Instrument::getChannelCount(){ return Channels.size(); }
int Instrument::getRhythmPatternCount(){ return rhythms.size(); }
void Instrument::addRhythm( string rhythmPattern ){ rhythms.push_back( rhythmPattern ); }
void Instrument::setScales( vector< Scale * > s ){ scales = s; }
void Instrument::playWAV( Mix_Chunk * wav, int channelNo ){ Mix_PlayChannelTimed( channelNo, wav, 0, sustain ); }

//Sets Volume To A Percentage Of Maximum Volume
void Instrument::setVolume( int v ){

	for( int i : ChannelNumbers ){

		Mix_Volume( i, MIX_MAX_VOLUME / ( 100 / v ) );

	}

}

void Instrument::nextRhythmPattern(){

	if( randomizeRyhthms ){

		currentRhythm = ( rand() % getRhythmPatternCount() );

	}

	else{

		currentRhythm = ( ++currentRhythm ) % getRhythmPatternCount();

	}

}

void Instrument::addChannel( const char * const c ){

	int thisChannel = Beat::getNextChannel();

	ChannelNumbers.push_back( thisChannel );

	Channels.push_back( Mix_LoadWAV( c ) );

}

void Instrument::playChannel( int channelNo ){

	if( ( channelNo + 1 ) > Channels.size() ){

		cout << "Channel Not Defined: " << channelNo << endl;
		cout << "Channels: " << Channels.size() << endl;

		return;

	}

	playWAV( Channels.at( channelNo ), channelNo );

}

void Instrument::printInfo(){

  cout << "\r\t\t" << DIVIDER3 << endl;
  cout << "\t\t" << "\"" << instrumentName << "\"" << endl;
	cout << "\r\t\t" << DIVIDER3 << endl;

	if( rhythms.size() > 0 ){

		cout << "\t\tRhythms:\t";

		for( string tmpRhythm : rhythms ){

				cout << tmpRhythm << endl << "\t\t\t\t";

		}

	}

	else{

		cout << "\t\tRhythms:\t[ NONE ]" << endl << "\t\t";

		beatInstance -> addWarningMessage( instrumentName + ": No Rhythms Added." );

	}

	int channelCount = getChannelCount();

	if( channelCount > 0 ){

		cout << "\r\t\tChannels:";

		for( int i = 0; i < channelCount; i++ ){

			cout << "\t" << ChannelNumbers.at( i ) << ": " << Channels.at( i ) << "\t[ " << ChannelNumbers[ i ] << " ]" << endl << "\r\t\t\t";

		}

	}

	else{

		cout << "\r\t\tChannels:\t[ NONE ]" << endl;

		beatInstance -> addWarningMessage( instrumentName + ": No Channels Added." );

	}

	if( scales.size() > 0 ){

		cout << "\r\t\tScales( " << scales.size() << " ):" << endl;

		printScalesInfo();

	}

	else{

		cout << "\r\t\tScales:\t[ NONE ]" << endl;

		beatInstance -> addWarningMessage( instrumentName + ": No Scales Added." );

	}

}

void Instrument::printScalesInfo(){

  for( auto & scale : scales ){

    scale -> Scale::printInfo();

  }

}

void Instrument::play(){

	int rhythmIndex = beatInstance -> getRhythmIndex();

	if( ! rhythms.size() ){

		cout << "NO RHYTHMS" << endl;

		keepPlaying = false;

		return;

	}

	if( isdigit( rhythms[ currentRhythm ][ rhythmIndex ] ) ){

		playChannel( rhythms[ currentRhythm ][ rhythmIndex ] - '0' );

	}

}
