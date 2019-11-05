#include "grenade.hpp"
#include "hwlib.hpp"
hwuart::hwuart(){

		    // enable the clock to port A
	    PMC->PMC_PCER0 = 1 << ID_PIOA;
		
	    // disable PIO Control on PA10 and PA11 and set up for Peripheral A
		PIOA->PIO_PDR   = PIO_PA10; 
		PIOA->PIO_ABSR &= ~PIO_PA10; 
		PIOA->PIO_PDR   = PIO_PA11; 
		PIOA->PIO_ABSR &= ~PIO_PA11; 
        PIOA -> PIO_PUDR |= PIO_PA10;

		// enable the clock to the USART
	    PMC->PMC_PCER0 = ( 0x01 << ID_USART0 );

	    // Reset and disable receiver and transmitter.
	    USART0->US_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS;

	    // Set the baudrate to 9600.

	    USART0->US_BRGR = 2188; 

	    // No parity, normal channel mode.
	    USART0->US_MR = US_MR_PAR_NO| US_MR_NBSTOP_1_BIT | US_MR_CHRL_8_BIT;

	    // Disable all interrupts.	  
	    USART0->US_IDR = 0xFFFFFFFF;   

	    // Enable the receiver and the trasmitter.
	    USART0->US_CR = US_CR_RXEN | US_CR_TXEN;      
	}



	bool hwuart::char_available(){
	   	
	   return ( USART0->US_CSR & 1 ) != 0;
	}

	char hwuart::getc(){
	   // uart_init() is not needed because uart_char_available does that
	   while( ! char_available() ){}
	   return USART0->US_RHR; 
	}
	void hwuart::putc( char c ){
	      
	   //usart_init();	
	   while( ( USART0->US_CSR & 2 ) == 0 ){}
	   USART0->US_THR = c;

	}

//======================< Button >===============================
button::button( buttonListen* listener ):
	listener( listener )
	{}

void button::update(){
	if( !sw.read() ){
		hwlib::cout<<"In update\n";
		listener->buttonPressed();
		hwlib::cout<<"na buttonPressed()\n";
	}
}

void buttonListen::buttonPressed(){
	hwlib::cout<<"Flag Set in listen\n";
	
}

void mhz433Write::buttonPressed(){
	hwlib::cout<<"Flag Set in write\n";
	buttonFlag.set();
	
}

//======================< Write >===============================



mhz433Write::mhz433Write( uint8_t player, uint8_t damage  ):
	task( "433mhzWrite" ),
	buttonFlag(this),
	player(player),
	damage(damage)
	{ 
		
	}

void mhz433Write::write( uint8_t playerNumber, uint8_t damage ){

	 // The grenade dammage cap will be 50, if too low or high just change it.
	 if( damage > 51){ damage=50; }
	
	 // Making the checksum
	 uint8_t checksum = ( damage / 256 ) ^ ( damage & 0xFF);
	 
	 // Sending to the master, the number 2 is the protocol for newScore
	 uint8_t protocol = 2; 
	
	 // Start bit, player id 1, player id 2, damage, sound 1-8, checksum, end bit.
	 uint8_t explosionData[amount+2] = { 0xFF,0xFE, protocol, playerNumber, damage, checksum }; 
        
	 
	 hwlib::wait_ms(1500); 						// Wait 1.5 seconds until it explodes, if too short or long, just change it.
	 for(int i=0; i<amount+2; i++){
		putc( explosionData[i] );
		hwlib::wait_us(400);
	 }
	 hwlib::cout<<"sending"<<hwlib::endl;
}
/*
uint8_t mhz433Write::dmgTimer( uint8_t damage ){
	while( !sw.read() ){
		damage+=2;
		// The grenade dammage cap will be 50, if too low or high just change it.
	 	if( damage > 51){ damage=50; break; }
		hwlib::wait_ms(200);			// Add 5 damage every second, up to 50.
		
	}
	return damage;
}
*/

void mhz433Write::main(){
	state = states::IDLE;
    for(;;){
		switch( state ){
			case states::IDLE:
				for(;;){
					//wait(updateClock);
					bl.update();
					buttonFlag.set();
					auto event = wait( buttonFlag );
					if( event == buttonFlag){
						state = states::WRITE;
						hwlib::cout<<"State = write \n";
						break;
					}
				}
			case states::WRITE:
				hwlib::cout<<"In Write\n";
				write( player, damage );
				state = states::IDLE;
				break;
		}
	}
}


//======================< Read >===============================

mhz433Read::mhz433Read( long long int duration):
	task( "433mhzRead" ),
	sampleClock( this, duration, "wait for message clock")	
	{}


void mhz433Read::read(){
	if( char_available() ){
	   if( getc() == 254 ){												// If it's the start bit

		   uint8_t tmpArray[amount] = { 0, 0, 0, 0 };				// Make array where the data is stored

		   for(int i=0; i<amount; i++){									
			   tmpArray[i] = getc();								// Put the data in the array
			   hwlib::wait_us(800);
		   }

		   for(int i=0; i<amount; i++){									// Debug( reading the data )
			  hwlib::cout<<tmpArray[i]<<"\n";
			   hwlib::wait_us(800);
		   }

		   uint8_t damage = tmpArray[2];								// tmpArray[2] is the damage value

		   if( tmpArray[4] != ( ( damage / 256 ) ^ ( damage & 0xFF) ) ){		// If the checksum is not the same, it will stop.
				return;
		   }
		   //uint16_t playerID = (uint16_t)( tmpArray[0]<<8 | tmpArray[1] );					// Assemble the player number.

		   uint8_t len = 3;
		   uint8_t mhzData[len] = { tmpArray[0], tmpArray[1], tmpArray[2]};		// Protocol, playerId, damage.

		   for( int i = 0; i < amountMhzListeners; i++){
					listenMhz[i]->dataReceived( mhzData, len );
		   }
	   }
	}
}

void mhz433Read::addMhzListener( mhzListener * listener ){
	listenMhz[amountMhzListeners] = listener;
	amountMhzListeners++;
}

void mhz433Read::dataReceived( const uint8_t data[], const int len ){
	for( int i =0; i<len; i++){
		hwlib::cout<< data[i] <<"\n";
	}
}

void mhz433Read::main(){
	for(;;){
		wait( sampleClock );
		read();
		hwlib::cout<<"in read\n";
	}
}