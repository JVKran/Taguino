#include <array>
#include "hwlib.hpp"

#define startByte 0x7E//126
#define versionByte 0xFF//255
#define commandLength 0x06//6
#define endByte 0xEF//239
#define acknowledge 0x00//0

template< int N >
class sounds{
private:
	std::array<int, N> sound;
public:
	int play( int i ){ return sound[ i-1 ]; }
	void set( int setSound ){ sound[setSound-1] = setSound; }

};

class send{
private:
	hwlib::pin_out & mp3Reset;
	hwlib::pin_out & mp3Write;
public:
	send( hwlib::pin_out & mp3Reset, hwlib::pin_out & mp3Write );
	void reset(){ mp3Reset.write(1); };
	void write();
};

class mp3 : public send {
public:
	mp3( hwlib::pin_out & mp3Reset, hwlib::pin_out & mp3Write );	
	void playSound( int sound );
};
//Deze klasse is voor wanneer de nrf goed werkt
//class mp3Control : public mp3{
//private:
//	transceiver& transmitter;
//public:
//	void dataReceived( uint32_t data, sounds select );
//};


