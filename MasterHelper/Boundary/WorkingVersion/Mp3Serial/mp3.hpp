///@file
#ifndef _MP3_HPP
#define _MP3_HPP

#include <array>
#include "hwlib.hpp"
/// \brief
/// This sounds class has a template "<int, N>" and an array called sound where songs are put in.
/// \details
/// The Array holds N amount of ints, these ints are used to play a song.
/// This class has 3 functions:
///		- play(int i): 	The play function returns the given sound on its position.	
///		- size(): 		The size function returns the size of the sound array.
///		- set(): 		The set function returns.

template< int N >
class sounds{
private:
	std::array< int, N > sound;
public:
/// \brief
/// Function to return from array sound.
/// \details
///
	int play( int i ){ return sound[ i-1 ]; }
/// \brief
/// Function to return size of sound.
/// \details
///
	int size(){ return sound.size();}
/// \brief
///	Function to set a sound.
/// \details
///
	void set( int setSound ){ sound[setSound-1] = setSound; }

};

class hwuart{
	//Usart * hw_usart = USART0;
	public:
	hwuart();
	bool usart_char_available();
	char usart_getc();
	void usart_putc(char c);
};
/// \brief
///	The class send inherits from hwuart and is used to send commands to the mp3 module.
/// \details
///	The class has one function:
/// 	- executeCMD( uint8_t CMD, uint8_t par1, uint8_t par2): 
///     	This needs the mp3 command, folder and mp3 file. It will send commands to the mp3 module.
class send : public hwuart{
public:
/// \brief
///	Function to execute commands to the mp3 module
/// \details
/// This needs the mp3 command, folder and mp3 file. It will send commands to the mp3 module.
	void executeCMD( uint8_t CMD, uint8_t par1, uint8_t par2);
};

/// \brief
///	The mp3 class inherits from send and is used to specify which commands need to be sent
/// \details
///	The class has 5 function:
/// 	- sendCMD(uint8_t CMD, uint8_t par1, uint8_t par2): Send your own commands.
/// 	- resetModule(): 			Reset the mp3 module.
/// 	- playSound( int sound ): 	Play the given sound.
/// 	- pauseSound(): 			Pause the sound.
/// 	- setVolume( int volume ): 	Set the volume.
class mp3 : public send{
public:
	void sendCMD( uint8_t CMD, uint8_t par1, uint8_t par2 );
	void resetModule();
	void playSound( int sound );
	void pauseSound();
	void setVolume( int volume ); //Van 0-30
};

/// \brief
/// The mp3Control class inherits mp3 and sounds<N>, it has a template "<int N>" and is used to play songs for given data in NRF
/// \details
/// This initializes the sound array and has 1 function:
/// 	- startPlayingSound(int data): If data is in the sound array, play it.

template< int N >
class mp3Control : public mp3, public sounds<N>{
private:
	int JAZZ=1; int SHOT=2; int ACTION=3; int AAAH=4; int DISCORD=5; int MONSTER=6; int TROMBONE=7; int LASER=8;
	std::array< int, N > soundTmp = { JAZZ, SHOT, ACTION, AAAH, DISCORD, MONSTER, TROMBONE, LASER };
	sounds<N> sound;
public:
	mp3Control()
	{
		for( const auto &s : soundTmp){
			sound.set(s);
		}
	}
	
	void startPlayingSound( int data ){
		for( int i=1; i<sound.size()+1; i++){ 
			if(data == sound.play(i+1)){ 			// If data is a song, play it
				playSound( sound.play( i ) );
				break;
			}
		}
	}
};

#endif //MP3_HPP