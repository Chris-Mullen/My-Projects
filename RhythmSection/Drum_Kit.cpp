#include "RhythmSection.h"

using namespace std;

int Drum_Kit::getRhythmPatternCount(){ return compositeRhythms.size(); }
int Drum_Kit::getChannelCount(){ return Channels.size(); }

void Drum_Kit::addRhythm( vector< string > compositeRhythm ){ compositeRhythms.push_back( compositeRhythm ); }
void Drum_Kit::addRhythm( string rhythmPattern ){

	int rhythmLength = rhythmPattern.length();
	int subDivisions = Beat::getSubDivisions();

	if( rhythmLength < subDivisions ){

		if( subDivisions % rhythmLength == 0 ){

			string rhythmPatternIn = rhythmPattern;

			while( rhythmPattern.length() <= subDivisions ){

				rhythmPattern += rhythmPatternIn;

			}

		}

	}

	vector< string > tmpCompositeRhythm;

	tmpCompositeRhythm.push_back( rhythmPattern );

	compositeRhythms.push_back( tmpCompositeRhythm );

}

void Drum_Kit::printInfo(){

  cout << "\r\t\t" << DIVIDER3 << endl;
  cout << "\t\t" << "\"" << instrumentName << "\"" << endl;
	cout << "\r\t\t" << DIVIDER3 << endl;

	if( compositeRhythms.size() > 0 ){

		cout << "\t\tRhythms:\t";

		for( vector< string > tmpRhythms : compositeRhythms ){

			for( string tmpRhythm : tmpRhythms ){

				cout << "\r\t\t\t\t" << tmpRhythm << endl << "\t\t";

			}

			cout << "\r\t\t\t\t" << DIVIDER2 << endl;

		}

	}

	else{

		cout << "\t\tRhythms:\t[ NONE ]" << endl << "\t\t";

		beatInstance -> addWarningMessage( instrumentName + ": No Rhythms Added." );

	}

	int channelCount = getChannelCount();

	if( channelCount > 0 ){

		cout << "\r\t\tPieces:";

		for( int i = 0; i < channelCount; i++ ){

			cout << "\t\t\"" << ChannelNames[ i ] << "\":\t" << Channels[ i ] << "\t[ " << ChannelNumbers[ i ] << " ]" << endl << "\t\t";

		}

	}

	else{

		cout << "\r\t\tChannels:\t[ NONE ]" << endl << "\t\t";

		beatInstance -> addWarningMessage( instrumentName + ": No Channels Added." );

	}

}

void Drum_Kit::addChannel( const char * const c, string n ){

	ChannelNumbers.push_back( Beat::getNextChannel() );

	ChannelNames.push_back( n );

	Channels.push_back( Mix_LoadWAV( c ) );

}

void Drum_Kit::addChannel( const char * const c, string n, int v ){

	int thisChannel = Beat::getNextChannel();

	ChannelNumbers.push_back( thisChannel );

	ChannelNames.push_back( n );

	Mix_Volume( thisChannel, MIX_MAX_VOLUME / ( 100 / v ) );

	Channels.push_back( Mix_LoadWAV( c ) );

}

void Drum_Kit::playChannel( int channelNo ){

	if( ( channelNo + 1 ) > Channels.size() ){

		return;

	}

	playWAV( Channels.at( channelNo ), ChannelNumbers.at( channelNo ) );

}

void Drum_Kit::play(){

	int rhythmIndex = beatInstance -> getRhythmIndex();

	if( ! compositeRhythms.size() ){

		addRhythm( Beat::generateRhythm( getMeter() , '0' ) );

	}

	vector< string > tmpCompositeRhythm = compositeRhythms[ currentRhythm ];

	for( string tmpRhythm : tmpCompositeRhythm ){

		if( isdigit( tmpRhythm[ rhythmIndex ] ) ){

			playChannel( tmpRhythm[ rhythmIndex ] - '0' );

		}

	}

}
