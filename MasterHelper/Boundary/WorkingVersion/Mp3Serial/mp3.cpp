///@file
#include "mp3.hpp"

hwuart::hwuart(){

		    // enable the clock to port A
	    PMC->PMC_PCER0 = 1 << ID_PIOA;
		
	    // disable PIO Control on PA10 and PA11 and set up for Peripheral A
		PIOA->PIO_PDR   = PIO_PA10; 
		PIOA->PIO_ABSR &= ~PIO_PA10; 
		PIOA->PIO_PDR   = PIO_PA11; 
		PIOA->PIO_ABSR &= ~PIO_PA11; 

		// enable the clock to the USART
	    PMC->PMC_PCER0 = ( 0x01 << ID_USART0 );

	    // Reset and disable receiver and transmitter.
	    USART0->US_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS;

	    // Set the baudrate to 9600.

	    USART0->US_BRGR = 567; 

	    // No parity, normal channel mode.
	    USART0->US_MR = US_MR_PAR_NO | US_MR_NBSTOP_1_BIT | US_MR_CHRL_8_BIT;

	    // Disable all interrupts.	  
	    USART0->US_IDR = 0xFFFFFFFF;   

	    // Enable the receiver and the trasmitter.
	    USART0->US_CR = US_CR_RXEN | US_CR_TXEN;      
	}

	bool hwuart::usart_char_available(){
	   	
	   return ( USART0->US_CSR & 1 ) != 0;
	}

	char hwuart::usart_getc(){
	   // uart_init() is not needed because uart_char_available does that
	   //while( ! usart_char_available() ){}
	   return USART0->US_RHR; 
	}
	void hwuart::usart_putc( char c ){
	      
	   //usart_init();	
	   while( ( USART0->US_CSR & 2 ) == 0 ){}
	   USART0->US_THR = c;

	}

void send::executeCMD( uint8_t CMD, uint8_t par1, uint8_t par2 ){ 		// Command, folder(in numbers 1-99), song(0-255)
	// Standard has the start, version, length, cmd, ack, par1, par2, check, check, end bytes
	uint8_t standard[10] = { 0x7E, 0xFF, 0x06, CMD, 0x00, par1, par2, 0xFF, 0xFF, 0xEF };
	
	uint16_t checksum = -( standard[1] + standard[2] + standard[3] + standard[4] + standard[4] + standard[5]+ standard[6] );
		
	// The bytes we will send to the mp3 module
	uint8_t commandLine[10] = { standard[0], standard[1], standard[2], standard[3], standard[4], standard[5], standard[6], uint8_t(checksum >> 8), uint8_t (checksum & 0xFF), 0xEF };
	hwlib::wait_ms(100);
		
	// We send via the usart_putc() function
	for(int i=0; i<10; i++){
			usart_putc(commandLine[i]);
			hwlib::wait_us(100);
			
		}
	// Wait 4 seconds, because the module needs 3-5 seconds to process the information
	hwlib::wait_ms(4000);
}

void mp3::sendCMD(uint8_t CMD, uint8_t par1, uint8_t par2){ executeCMD( CMD, par1, par2 );}

void mp3::playSound( int sound ){ executeCMD( 3, 0, sound );  }			// playSounds = ( specify track , folder 0, number with corresponding mp3 track )

void mp3::pauseSound(){ executeCMD( 0x0E, 0, 0 );}					    // Pause

void mp3::setVolume( int volume ){ executeCMD( 6, 0, volume); };		// setVolume = (set volume, nothing, volume range 0-30)

void mp3::resetModule(){ executeCMD( 0x0C, 0, 0 );}						// Reset the module 
			