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


mhz433::mhz433( hwlib::pin_in & sw):
	sw(sw)
	{}

void mhz433::write( uint16_t playerNumber, uint8_t damage ){
	
	 // Split the uint16_t playerNumber into two uint8_t, to be able to transmit it
	 uint8_t playerId = (uint8_t)(playerNumber>>8);
	 uint8_t playerId1 = (uint8_t) playerNumber;
	
	 // The grenade dammage cap will be 50, if too low or high just change it.
	 if( damage > 51){ damage=50; }
	
	 // Making the checksum
	 uint8_t checksum = ( damage / 256 ) ^ ( damage & 0xFF);
	
	 // Start bit, player id 1, player id 2, damage, sound, checksum, end bit.
	 uint8_t explosionData[amount+1] = { 0xFF, playerId, playerId1, damage, 1, checksum }; 
        
	 for(;;){
		 hwlib::wait_ms(1500); 						// Wait 1.5 seconds until it explodes, if too short or long, just change it.
		 for(int i=0; i<amount+1; i++){
			putc( explosionData[i] );
			hwlib::wait_us(400);
		 }
	 hwlib::cout<<"sending"<<hwlib::endl;
	 }
}


void mhz433::read(){
   for(;;){
	   if( char_available() ){
		   if( getc() == 254 ){												// If it's the start bit

			   uint8_t tmpArray[amount] = { 0, 0, 0, 0, 0 };				// Make array where the data is stored

			   for(int i=0; i<amount; i++){									
				   tmpArray[i] = usart_getc();								// Put the data in the array
				   hwlib::wait_us(800);
			   }

			   for(int i=0; i<amount; i++){									// Debug( reading the data )
				  hwlib::cout<<tmpArray[i]<<"\n";
				   hwlib::wait_us(800);
			   }

			   uint8_t damage = tmpArray[2];								// tmpArray[2] is tje damage value

			   if( tmpArray[4] != ( ( damage / 256 ) ^ ( damage & 0xFF) ) ){		// If the checksum is not the same, it will stop.
					return;
			   }
			   //uint16_t playerID = (uint16_t)( tmpArray[0]<<8 | tmpArray[1] );					// Assemble the player number.

			   // Dit gedeelte nog niet helemaal goed.
			   uint8_t len =3
			   uint8_t nrfData[len] = { tmpArray[0], tmpArray[1], tmpArray[2], tmpArray[3] };		// playerId, playerId, damage, song.
			   
			   nrf.write( nrfData, len );
			}
	   }
   }
}
	
uint8_t mhz433::dmgTimer( uint8_t damage ){
	while( !sw.read() ){
		damage++;
		// The grenade dammage cap will be 50, if too low or high just change it.
	 	if( damage > 51){ damage=50; break; }
		hwlib::wait_ms(200);			// Add 5 damage every second, up to 50.
		
	}
	return damage;
}